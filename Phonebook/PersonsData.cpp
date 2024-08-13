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
BOOL CPersonsData::SelectAllPersons(CPersonsArray& oPersonsArray)
{
	//Инстанция на дватата класа с табличните данни, подавайки им една сесия
	CPersonsTable oPersonsTable;

	if (!oPersonsTable.SelectAll(oPersonsArray))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::SelectPersonDataByPersonId(const long& lID, CPersonDBModel& oPersonDBModel)
{
	//Инстанция на дватата класа с табличните данни
	CPersonsTable oPersonsTable;
	CPhoneNumbersTable oPhoneNumbersTable;


	//Временна променлива на клиента, който ще се селектира
	PERSONS recPersonToFind;

	//Прочитаме клиента, който се търси в базата данни и се записва във временната променлива
	if (!oPersonsTable.SelectWhere(lID, recPersonToFind))
	{
		return FALSE;
	}

	//Временна променлива на масива с телефонни номера за клиента
	CPhoneNumbersArray oPhoneNumbersForPerson;

	//Достъпваме всички телефонни номера за съответния клиент
	if (!oPhoneNumbersTable.SelectWhere(recPersonToFind.lId, oPhoneNumbersForPerson, oPhoneNumbersTable.ColIdPerson()))
	{
		return FALSE;
	}

	//Добавяме данните за клиент и масив с телефонните му номера към променвилата с всички данни за клиент
	oPersonDBModel.AddPerson(recPersonToFind);

	if (!oPersonDBModel.AddAllPhoneNumbers(CPhoneNumbersMap(oPhoneNumbersForPerson)))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::DoOperationWithPerson(CPersonDBModel& oPersonDBModel, LPARAM lOperationFlag)
{
	//Инстанция на клас, който управлява сесиите и транзакциите
	CDatabaseTransactionManager oDatabaseTransactionManager;
	if(!oDatabaseTransactionManager.OpenSafeTransaction())
	{
		return FALSE;
	}

	//Извършване на опреации с клиентските данни
	if (!ProcessPersonOperations(oDatabaseTransactionManager.GetSession(), oPersonDBModel, lOperationFlag))
	{
		oDatabaseTransactionManager.CloseSafeTransactoin(FALSE);
		return FALSE;
	}

	//Затваряме сесията и записваме данните в базата с данни
	if (!oDatabaseTransactionManager.CloseSafeTransactoin())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::ProcessPersonOperations(CInitializeSession* pInitializeSession, CPersonDBModel& oPersonDBModel, LPARAM& lFlagOperation)
{
	if (pInitializeSession == nullptr)
	{
		return FALSE;
	}

	//Инстанция на дватата класа с табличните данни
	CPersonsTable oPersonsTable(pInitializeSession);
	CPhoneNumbersTable oPhoneNumbersTable(pInitializeSession);

	//Инстнация на клиент, върху който ще се извършват операции
	PERSONS recPerson = oPersonDBModel.GetPerson();

	switch (lFlagOperation)
	{

	case OPERATIONS_WITH_DATA_FLAGS_READED:
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
		oPersonDBModel.SetIdPerson(recPerson.lId);

		//Добавяне на ид на клиент за всички телефонни номера
		if (!oPersonDBModel.SetPhoneNumbersPersonId())
		{
			return FALSE;
		}

		//Извършване на операции само за телефонни номер
		if (!ProcessPhoneNumbers(oPhoneNumbersTable, oPersonDBModel.GetPhoneNumbers()))
		{
			return FALSE;
		}
	}
	break;

	//Извършване на операция редакция на клиентски данни
	case OPERATIONS_WITH_DATA_FLAGS_DELETE:
	{
		//Изтриване на всички телефонни номера за клиента
		if (!ProcessPhoneNumbers(oPhoneNumbersTable, oPersonDBModel.GetPhoneNumbers()))
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
		if (!ProcessPhoneNumbers(oPhoneNumbersTable, oPersonDBModel.GetPhoneNumbers()))
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
	CPhoneNumbersMap oPhoneNumbersOperationsMap = oPersonDBModel.GetPhoneNumbers();
	oPhoneNumbersOperationsMap.ChangeValuesToOperation();

	return TRUE;
}
	
BOOL CPersonsData::ProcessPhoneNumbers(CPhoneNumbersTable& oPhoneNumbersTable,const CPhoneNumbersMap& oPhoneNumbersOperationsMap)
{
	//Променливи за обход на мап
	POSITION oPos = oPhoneNumbersOperationsMap.GetStartPosition();
	LPARAM lFlagOperation;
	CPhoneNumbersArray* pPhoneNumberArray;

	if (oPos == NULL)
	{
		return FALSE;
	}

	while (oPos != NULL)
	{
		//Достъпваме настоящ елемент
		oPhoneNumbersOperationsMap.GetNextAssoc(oPos, lFlagOperation, pPhoneNumberArray);

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

BOOL CPersonsData::ChoosePhoneNumbersOperation(CPhoneNumbersTable& oPhoneNumbersTable, LPARAM& lFlagOperation, const CPhoneNumbersArray& oPhoneNumberArray)
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

BOOL CPersonsData::LoadAdditionalModels(CAdditionalDBModelsPersons& oAdditionalModels)
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
	oAdditionalModels.SetCities(oCitiesArray);
	oAdditionalModels.SetPhoneTypes(oPhoneTypesArray);
	return TRUE;
}


// Overrides
// ----------------