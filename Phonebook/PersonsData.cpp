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
BOOL CPersonsData::SelectAllPersonsInfo(CTableDataArray<CPersonInfo>& oPersonsInfo)
{
	//Помощни масива, в които ще се съхранява прочетеното от базата данни
	CPersonsArray oPersonsArray;
	CPhoneNumbersArray oAllPhoneNumbersArray;

	//Инстанция на клас, който управлява сесиите и транзакциите
	CDatabaseTransactionManager	oDatabaseTransactionManager;
	if (!oDatabaseTransactionManager.StartTransacion())
	{
		return FALSE;
	}

	//Инстанция на дватата класа с табличните данни
	CPersonsTable oPersonsTable(oDatabaseTransactionManager);
	CPhoneNumbersTable oPhoneNumbersTable(oDatabaseTransactionManager);

	if (!oPersonsTable.SelectAll(oPersonsArray))
	{
		return FALSE;
	}

	if (!oPhoneNumbersTable.SelectAll(oAllPhoneNumbersArray))
	{
		return FALSE;
	}

	if(!oDatabaseTransactionManager.CommitTransaction())
	{
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

		//Откриваме всички телефонни номера за настоящия клиент
		CPhoneNumbersArray oPhoneNumbersArrayForPerson;
		if (!FindAllPhoneNumbersForPerson(pPerson->lId, oAllPhoneNumbersArray, oPhoneNumbersArrayForPerson))
		{
			return FALSE;
		}

		//Добавяне на всички елементи от масива с телефонни номера в мапа
		CPhoneNumbersMap oPhoneNumberMap;
		for (INT_PTR nIndex = 0; nIndex < oPhoneNumbersArrayForPerson.GetCount(); nIndex++)
		{
			PHONE_NUMBERS* pPhoneNumber = oPhoneNumbersArrayForPerson.GetAt(nIndex);
			if (pPhoneNumber == nullptr)
			{
				return FALSE;
			}

			if (!oPhoneNumberMap.AddOneElementToKey(*pPhoneNumber))
			{
				return FALSE;
			}
		}

		//Добавяме данните за клиент и масив с телефонните му номера
		CPersonInfo oPersonInfo(*pPerson, oPhoneNumberMap);

		//Добавяме времения обект с данни към масива с данни за клиенти
		oPersonsInfo.AddElement(oPersonInfo);
	}

	return TRUE;
}

BOOL CPersonsData::SelectPersonInfoWithId(const long lID, CPersonInfo& oPersonInfo)
{
	//Временна променлива на клиента, който ще се селектира
	PERSONS recPersonToFind;

	//Временна променлива на масива с телефонни номера за клиента
	CPhoneNumbersArray oAllPhoneNumbersArray;

	//Инстанция на клас, който управлява сесиите и транзакциите
	CDatabaseTransactionManager	oDatabaseTransactionManager;
	if(!oDatabaseTransactionManager.StartTransacion())
	{
		return FALSE;
	}

	//Инстанция на дватата класа с табличните данни
	CPersonsTable oPersonsTable(oDatabaseTransactionManager);
	CPhoneNumbersTable oPhoneNumbersTable(oDatabaseTransactionManager);

	//Прочитаме клиента, който се търси в базата данни и се записва във временната променлива
	if (!oPersonsTable.SelectWhereID(lID, recPersonToFind))
	{
		return FALSE;
	}

	//Достъпваме всички телефонни номера
	if (!oPhoneNumbersTable.SelectAll(oAllPhoneNumbersArray))
	{
		return FALSE;
	}

	if(!oDatabaseTransactionManager.CommitTransaction())
	{
		return FALSE;
	}

	//Откриваме всички телефонни номера за настоящия клиент
	CPhoneNumbersArray oPhoneNumbersArrayForPerson;
	if (!FindAllPhoneNumbersForPerson(recPersonToFind.lId, oAllPhoneNumbersArray, oPhoneNumbersArrayForPerson))
	{
		return FALSE;
	}

	//Откриваме всички телефонни номера за настоящия клиент
	CPhoneNumbersMap oPhoneNumbersMapForOnePerson;
	for (INT_PTR nIndex = 0; nIndex < oPhoneNumbersArrayForPerson.GetCount(); nIndex++)
	{
		PHONE_NUMBERS* pPhoneNumber = oPhoneNumbersArrayForPerson.GetAt(nIndex);
		if (pPhoneNumber == nullptr)
		{
			return FALSE;
		}

		if (!oPhoneNumbersMapForOnePerson.AddOneElementToKey(*pPhoneNumber))
		{
			return FALSE;
		}
	}

	//Добавяме данните за клиент и масив с телефонните му номера към променвилата с всички данни за клиент
	oPersonInfo.AddPerson(recPersonToFind);
	if (!oPersonInfo.AddAllPhoneNumbers(oPhoneNumbersMapForOnePerson))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPersonsData::ManagePersonInfo(CPersonInfo& oPersonInfo, LPARAM oOperationFlag)
{
	//Инстанция на клас, който управлява сесиите и транзакциите
	CDatabaseTransactionManager	oDatabaseTransactionManager;
	if(!oDatabaseTransactionManager.StartTransacion())
	{
		return FALSE;
	}

	//Инстанция на дватата класа с табличните данни
	CPersonsTable oPersonsTable(oDatabaseTransactionManager);
	CPhoneNumbersTable oPhoneNumbersTable(oDatabaseTransactionManager);

	//Инстнация на масив с телефонин номера за клиент, върху който ще се извършват операции
	CPhoneNumbersMap oPhoneNumbersMap = oPersonInfo.GetPhoneNumbers();

	if (!ManagePhoneNumbersOperations(oPhoneNumbersTable, oPhoneNumbersMap))
	{
		return FALSE;
	}

	//Инстнация на клиент, върху който ще се извършват операции
	PERSONS recPerson = oPersonInfo.GetPerson();

	if (!ManagePersonOperations(oPersonsTable, recPerson, oOperationFlag))
	{
		return FALSE;
	}

	if(!oDatabaseTransactionManager.CommitTransaction())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::ManagePersonOperations(CPersonsTable& oPersonsTable, PERSONS& recPerson, LPARAM oFlagOperation)
{
	switch (oFlagOperation)
	{
	case OPERATIONS_WITH_DATA_FLAGS_INSERT:
	{
		if (!oPersonsTable.Insert(recPerson))
		{
			return FALSE;
		}
	}
	break;
	case OPERATIONS_WITH_DATA_FLAGS_DELETE:
	{
		if (!oPersonsTable.DeleteWhereID(recPerson.lId))
		{
			return FALSE;
		}
	}
	break;
	case OPERATIONS_WITH_DATA_FLAGS_UPDATE:
	{
		if (!oPersonsTable.UpdateWhereID(recPerson.lId, recPerson))
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
	
BOOL CPersonsData::ManagePhoneNumbersOperations(CPhoneNumbersTable& oPhoneNumbersTable, CPhoneNumbersMap& oPhoneNumbersMap)
{
	//Променливи за обход на мап
	POSITION oPos = oPhoneNumbersMap.GetStartPosition();
	LPARAM oFlagOperation;
	CPhoneNumbersArray* pPhoneNumberArray;

	while (oPos != NULL)
	{
		//Достъпваме настоящ елемент
		oPhoneNumbersMap.GetNextAssoc(oPos, oFlagOperation, pPhoneNumberArray);

		if (oFlagOperation == OPERATIONS_WITH_DATA_FLAGS_READED)
		{
			continue;
		}

		if (pPhoneNumberArray == nullptr)
		{
			return FALSE;
		}

		if (pPhoneNumberArray->IsEmpty())
		{
			continue;
		}

		//Извършваме операция връху обекта според флага
		if (!ChoosePhoneNumbersOperation(oPhoneNumbersTable, oFlagOperation, *pPhoneNumberArray))
		{
			return FALSE;
		}
		
		if (!oPhoneNumbersMap.RemoveAllElementsFromKey(oFlagOperation))
		{
			AfxMessageBox(_T("Failed do operation with phone numbers!\n Try to reload."));
		}
		if (oFlagOperation == OPERATIONS_WITH_DATA_FLAGS_DELETE)
		{
			continue;
		}

		//Добавяме елемента към масива с флаг за редакция на данни в мапа с гтелефонни номера
		if (!oPhoneNumbersMap.AddAllElementsToKey(*pPhoneNumberArray, OPERATIONS_WITH_DATA_FLAGS_READED))
		{
			AfxMessageBox(_T("Failed to do operation with phone numbers!\n Try to reload."));
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CPersonsData::ChoosePhoneNumbersOperation(CPhoneNumbersTable& oPhoneNumbersTable, LPARAM oFlagOperation, CPhoneNumbersArray& oPhoneNumberArray)
{
	switch (oFlagOperation)
	{
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

BOOL CPersonsData::FindAllPhoneNumbersForPerson(const long lId, const CPhoneNumbersArray& oAllPhoneNumbersArray, CPhoneNumbersArray& oPhoneNumbersArrayForPerson)
{
	for (INT_PTR nIndex = oAllPhoneNumbersArray.GetCount()-1; nIndex >= 0; --nIndex)
	{
		//Достъпваме настоящ елемент
		PHONE_NUMBERS* pPhoneNumber = oAllPhoneNumbersArray.GetAt(nIndex);
		if (pPhoneNumber == nullptr)
		{
			return FALSE;
		}
		//Ако ид на клиент на настоящия телефонен номер е идентично с настоящия клеинт
		if (pPhoneNumber->lIdPerson == lId)
		{
			oPhoneNumbersArrayForPerson.AddElement(*pPhoneNumber);
		}
	}
	return TRUE;
}

BOOL CPersonsData::LoadAllAdditionalPersonInfo(CAdditionPersonInfo& oAdditionalPersonInfo)
{
	CCitiesData oCitiesData;
	CCitiesArray oCitiesArray;

	if (!(oCitiesData.SelectAll(oCitiesArray)))
	{
		AfxMessageBox(_T("Failed to select all cities from doc!\n Try to reload."));
		return FALSE;
	}

	CPhoneTypesData oPhoneTypesData;
	CPhoneTypesArray oPhoneTypesArray;
	if (!(oPhoneTypesData.SelectAll(oPhoneTypesArray)))
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