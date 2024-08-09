#include "pch.h"
#include "PersonsData.h"
#include "DatabaseTransactionManager.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsData

// Constructor / Destructor
// ----------------

CPersonsData::CPersonsData()
{
}

CPersonsData::~CPersonsData()
{
}


// Methods
// ----------------
BOOL CPersonsData::SelectAllPersonsInfo(CTableDataArray<CPersonInfo>& oPersonsInfoArray)
{
	//Инстанция на клас, който управлява сесиите и транзакциите
	CDatabaseTransactionManager oDatabaseTransactionManager;

	//Начало на транзакция
	if (!oDatabaseTransactionManager.OpenSafeTransaction())
	{
		return FALSE;
	}

	//Инстанция на дватата класа с табличните данни, подавайки им една сесия
	CPersonsTable oPersonsTable(oDatabaseTransactionManager.GetSession());
	CPhoneNumbersTable oPhoneNumbersTable(oDatabaseTransactionManager.GetSession());

	//Декларация на масив с прочетени клиенти от базата данни
	CPersonsArray oPersonsArray;

	if (!oPersonsTable.SelectAll(oPersonsArray))
	{
		oDatabaseTransactionManager.CloseSafeTransactoin(FALSE);
		return FALSE;
	}

	//Преминава се през всеки прочетен клиент от базата данни 
	for (INT_PTR nIndexPersons = 0; nIndexPersons < oPersonsArray.GetCount(); nIndexPersons++)
	{
		//Достъпваме настоящия елемент от масива с клиенти
		PERSONS* pPerson = oPersonsArray.GetAt(nIndexPersons);
		if (pPerson == nullptr)
		{
			return FALSE;
		}

		//Декларация на масив с прочетени телефонни номера за един клиент
		CPhoneNumbersArray oPhoneNumbersArrayForPerson;

		//Достъпваме всички телефонни номера за съответния клиент
		if (!oPhoneNumbersTable.SelectWhereID(pPerson->lId, oPhoneNumbersArrayForPerson, oPhoneNumbersTable.ColIdPerson()))
		{
			oDatabaseTransactionManager.CloseSafeTransactoin(FALSE);
			return FALSE;
		}

		//Добавяме данните за клиент и масива, с телефонните му номера, към мап
		oPersonsInfoArray.AddElement(CPersonInfo(*pPerson, CPhoneNumbersMap(oPhoneNumbersArrayForPerson)));
	}

	//Затваряне на транзакцията
	if (!oDatabaseTransactionManager.CloseSafeTransactoin())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::SelectPersonInfoWithPersonId(const long lID, CPersonInfo& oPersonInfo)
{
	//Инстанция на клас, който управлява сесиите и транзакциите
	CDatabaseTransactionManager oDatabaseTransactionManager;
	if(!oDatabaseTransactionManager.OpenSafeTransaction())
	{
		return FALSE;
	}
	CInitializeSession* pSession = oDatabaseTransactionManager.GetSession();
	if (pSession == nullptr)
	{
		oDatabaseTransactionManager.CloseSafeTransactoin(FALSE);
		return FALSE;
	}

	//Инстанция на дватата класа с табличните данни
	CPersonsTable oPersonsTable(pSession);
	CPhoneNumbersTable oPhoneNumbersTable(pSession);


	//Временна променлива на клиента, който ще се селектира
	PERSONS recPersonToFind;

	//Прочитаме клиента, който се търси в базата данни и се записва във временната променлива
	if (!oPersonsTable.SelectWhereID(lID, recPersonToFind))
	{
		oDatabaseTransactionManager.CloseSafeTransactoin(FALSE);
		return FALSE;
	}

	//Временна променлива на масива с телефонни номера за клиента
	CPhoneNumbersArray oPhoneNumbersForPerson;

	//Достъпваме всички телефонни номера за съответния клиент
	if (!oPhoneNumbersTable.SelectWhereID(recPersonToFind.lId, oPhoneNumbersForPerson, oPhoneNumbersTable.ColIdPerson()))
	{
		oDatabaseTransactionManager.CloseSafeTransactoin(FALSE);
		return FALSE;
	}

	if(!oDatabaseTransactionManager.CloseSafeTransactoin())
	{
		return FALSE;
	}

	//Добавяме данните за клиент и масив с телефонните му номера към променвилата с всички данни за клиент
	oPersonInfo.AddPerson(recPersonToFind);
	if (!oPersonInfo.AddAllPhoneNumbers(CPhoneNumbersMap(oPhoneNumbersForPerson)))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::DoOperationWithPersonInfo(CPersonInfo& oPersonInfo, LPARAM lOperationFlag)
{
	//Инстанция на клас, който управлява сесиите и транзакциите
	CDatabaseTransactionManager oDatabaseTransactionManager;
	if(!oDatabaseTransactionManager.OpenSafeTransaction())
	{
		return FALSE;
	}

	//Извършване на опреации с клиентските данни
	if (!ManagePersonInfoOperations(oDatabaseTransactionManager.GetSession(), oPersonInfo, lOperationFlag))
	{
		oDatabaseTransactionManager.CloseSafeTransactoin(FALSE);
		return FALSE;
	}

	//Затваряме сесията и записваме данните в базата с данни
	if (!oDatabaseTransactionManager.CloseSafeTransactoin())
	{
		return FALSE;
	}

	//Изчистване на заделенат памет
	AfxMessageBox(_T("Successful operation!"));

	return TRUE;
}

BOOL CPersonsData::ManagePersonInfoOperations(CInitializeSession* pInitializeSession, CPersonInfo& oPersonInfo, LPARAM lFlagOperation)
{
	if (pInitializeSession == nullptr)
	{
		return FALSE;
	}

	//Инстанция на дватата класа с табличните данни
	CPersonsTable oPersonsTable(pInitializeSession);
	CPhoneNumbersTable oPhoneNumbersTable(pInitializeSession);

	//Инстнация на клиент, върху който ще се извършват операции
	PERSONS recPerson = oPersonInfo.GetPerson();

	switch (lFlagOperation)
	{

	case OPERATIONS_WITH_DATA_FLAGS_READED:
	{
		//Извършване на операции само за телефонни номер
		if (!ManagePhoneNumbersOperations(oPhoneNumbersTable, oPersonInfo.GetPhoneNumbers()))
		{
			return FALSE;
		}
	}
	break;

	//Извършване на операция добавяне на клиентски данни
	case OPERATIONS_WITH_DATA_FLAGS_INSERT:
	{
		//Добавяне на клиент
		if (!oPersonsTable.Insert(recPerson))
		{
			return FALSE;
		}
		//Добавяне на новогенерирани ИД на клиент
		oPersonInfo.SetIdPerson(recPerson.lId);

		//Добавяне на ид на клиент за всички телефонни номера
		if (!oPersonInfo.CheckAndConnectAllPhoneNumbersWithPersonId())
		{
			return FALSE;
		}

		//Извършване на операции само за телефонни номер
		if (!ManagePhoneNumbersOperations(oPhoneNumbersTable, oPersonInfo.GetPhoneNumbers()))
		{
			return FALSE;
		}
	}
	break;

	//Извършване на операция редакция на клиентски данни
	case OPERATIONS_WITH_DATA_FLAGS_DELETE:
	{
		//Изтриване на всички телефонни номера за клиента
		if (!ManagePhoneNumbersOperations(oPhoneNumbersTable, oPersonInfo.GetPhoneNumbers()))
		{
			return FALSE;
		}

		//Изтриване на клиент
		if (!oPersonsTable.DeleteWhereID(recPerson.lId))
		{
			return FALSE;
		}
	}
	break;

	//Извършване на операция редакция на клиентски данни
	case OPERATIONS_WITH_DATA_FLAGS_UPDATE:
	{
		if (!oPersonsTable.UpdateWhereID(recPerson.lId, recPerson))
		{
			return FALSE;
		}

		//Извършване на операции само за телефонни номер
		if (!ManagePhoneNumbersOperations(oPhoneNumbersTable, oPersonInfo.GetPhoneNumbers()))
		{
			return FALSE;
		}
	}
	break;

	default:
	{
		return FALSE;
	}
	break;

	}

	//Обновление на мапа с телефинни номера
	CPhoneNumbersMap oPhoneNumbersMap = oPersonInfo.GetPhoneNumbers();
	oPhoneNumbersMap.MoveActiveValuesIntoKey();

	return TRUE;
}
	
BOOL CPersonsData::ManagePhoneNumbersOperations(CPhoneNumbersTable& oPhoneNumbersTable,const CPhoneNumbersMap& oPhoneNumbersMap)
{
	//Променливи за обход на мап
	POSITION oPos = oPhoneNumbersMap.GetStartPosition();
	LPARAM lFlagOperation;
	CPhoneNumbersArray* pPhoneNumberArray;

	if (oPos == NULL)
	{
		return FALSE;
	}

	while (oPos != NULL)
	{
		//Достъпваме настоящ елемент
		oPhoneNumbersMap.GetNextAssoc(oPos, lFlagOperation, pPhoneNumberArray);

		if (pPhoneNumberArray == nullptr)
		{
			return FALSE;
		}

		if (pPhoneNumberArray->IsEmpty())
		{
			continue;
		}

		//Извършваме операция връху обекта според флага
		if (!ChoosePhoneNumbersOperation(oPhoneNumbersTable, lFlagOperation, *pPhoneNumberArray))
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CPersonsData::ChoosePhoneNumbersOperation(CPhoneNumbersTable& oPhoneNumbersTable, LPARAM lFlagOperation, const CPhoneNumbersArray& oPhoneNumberArray)
{
	switch (lFlagOperation)
	{
	case OPERATIONS_WITH_DATA_FLAGS_READED:
	break;

	case OPERATIONS_WITH_DATA_FLAGS_INSERT:
	{
		if (!oPhoneNumbersTable.InsertAll(oPhoneNumberArray))
		{
			return FALSE;
		}
	}
	break;

	case OPERATIONS_WITH_DATA_FLAGS_DELETE:
	{
		if (!oPhoneNumbersTable.DeleteAll(oPhoneNumberArray))
		{
			return FALSE;
		}
	}
	break;

	case OPERATIONS_WITH_DATA_FLAGS_UPDATE:
	{
		if (!oPhoneNumbersTable.UpdateAll(oPhoneNumberArray))
		{
			return FALSE;
		}
	}
	break;

	default:
	{
		return FALSE;
	}
	break;
	}

	return TRUE;
}

BOOL CPersonsData::LoadAllAdditionalPersonInfo(CAdditionPersonInfo& oAdditionalPersonInfo)
{
	CCitiesData oCitiesData;
	CCitiesArray oCitiesArray;

	if (!oCitiesData.SelectAllCities(oCitiesArray))
	{
		AfxMessageBox(_T("Failed to select all cities from doc!\n Try to reload."));
		return FALSE;
	}

	CPhoneTypesData oPhoneTypesData;
	CPhoneTypesArray oPhoneTypesArray;
	if (!(oPhoneTypesData.SelectAllPhoneTypes(oPhoneTypesArray)))
	{
		AfxMessageBox(_T("Failed to select all cities from doc!\n Try to reload."));
		return FALSE;
	}
	oAdditionalPersonInfo.SetCitiesData(oCitiesArray);
	oAdditionalPersonInfo.SetPhoneTypesData(oPhoneTypesArray);
	return TRUE;
}


// Overrides
// ----------------