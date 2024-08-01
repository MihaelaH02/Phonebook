#include "pch.h"
#include "PersonsData.h"

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
	//Инстанция на дватата класа с табличните данни
	CPersonsTable oPersonsTable;
	CPhoneNumbersTable oPhoneNumbersTable;

	//Помощни масива, в които ще се съхранява прочетеното от базата данни
	CPersonsArray oPersonsArray;
	CPhoneNumbersArray oPhoneNumbersArray;

	//Извършване на опирация от базата данни
	//транзакция + сесия
	if (!oPersonsTable.SelectAll(oPersonsArray))
	{
		return FALSE;
	}

	if (!oPhoneNumbersTable.SelectAll(oPhoneNumbersArray))
	{
		return FALSE;
	}
	//край транзация

	//Преминава се през всеки прочетен клиент от базата данни 
	for (INT_PTR nIndexPersons = 0; nIndexPersons < oPersonsArray.GetCount(); nIndexPersons++)
	{
		//Достъпваме настоящия елемент от масива с клиенти
		PERSONS pPerson = *oPersonsArray.GetAt(nIndexPersons);
		
		//Откриваме всички телефонни номера за настоящия клиент
		FindAllPhoneNumbersForPerson(nIndexPersons, oPhoneNumbersArray);

		CPhoneNumbersMap oPhoneNumberMap;
		oPhoneNumberMap.AddElement(oPhoneNumbersArray);

		//Добавяме данните за клиент и масив с телефонните му номера
		CPersonInfo oPersonInfo(pPerson, oPhoneNumberMap);

		//Добавяме времения обект с данни към масива с данни за клиенти
		oPersonsInfo.AddElement(oPersonInfo);
	}

	return TRUE;
}

BOOL CPersonsData::SelectPersonInfoWithId(const long lID, CPersonInfo& oPersonInfo)
{
	//Инстанция на дватата класа с табличните данни
	CPersonsTable oPersonsTable;
	CPhoneNumbersTable oPhoneNumbersTable;

	//Временна променлива на клиента, който ще се селектира
	PERSONS recPersonToFind;

	//Временна променлива на масива с телефонни номера за клиента
	CPhoneNumbersArray oPhoneNumbersArray;

	//Прочитаме клиента, който се търси в базата данни и се записва във временната променлива
	if (!oPersonsTable.SelectWhereID(lID, recPersonToFind))
	{
		return FALSE;
	}

	//Достъпваме всички телефонни номера
	if (!oPhoneNumbersTable.SelectAll(oPhoneNumbersArray))
	{
		return FALSE;
	}

	FindAllPhoneNumbersForPerson(recPersonToFind.lId, oPhoneNumbersArray);

	//Откриваме всички телефонни номера за настоящия клиент
	CPhoneNumbersMap oPhoneNumbersMapForOnePerson;
	oPhoneNumbersMapForOnePerson.AddElement(oPhoneNumbersArray);

	//Добавяме данните за клиент и масив с телефонните му номера към променвилата с всички данни за клиент
	oPersonInfo.AddPerson(recPersonToFind);
	oPersonInfo.AddAllPhoneNumbers(oPhoneNumbersMapForOnePerson);
}

BOOL CPersonsData::ManagePersonInfo(CPersonInfo& oPersonInfo, LPARAM oOperationFlag)
{
	//КЛАС ЗА ТРАНЗАКЦИИ И СЕСИИ
	//Инстнация на клиент, върху който ще се извършват операции
	PERSONS recPerson = oPersonInfo.GetPerson();

	if (!ManagePersonOperations(recPerson, oOperationFlag))
	{
		return FALSE;
	}

	//Инстнация на масив с телефонин номера за клиент, върху който ще се извършват операции
	CPhoneNumbersMap oPhoneNumbersMap = oPersonInfo.GetPhoneNumbers();

	if (!ManagePhoneNumbersOperations(oPhoneNumbersMap))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::ManagePersonOperations(PERSONS& recPerson, LPARAM oFlagOperation)
{
	//Инстанция на дватата класа с табличните данни
	CPersonsTable oPersonsTable;

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

/*BOOL CPersonsData::PersonInsert(PERSONS& recPerson)
{
	//Инстанция на дватата класа с табличните данни
	CPersonsTable oPersonsTable;

	if (!oPersonsTable.Insert(recPerson))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::PersonUpdate(const long lid, PERSONS& recPerson)
{
	//Инстанция на дватата класа с табличните данни
	CPersonsTable oPersonsTable;

	if (!oPersonsTable.UpdateWhereID(recPerson.lId, recPerson))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::PersonDelete(const long lId)
{
	//Инстанция на дватата класа с табличните данни
	CPersonsTable oPersonsTable;

	if (!oPersonsTable.DeleteWhereID(lId))
	{
		return FALSE;
	}

	return TRUE;
}*/

BOOL CPersonsData::ManagePhoneNumbersOperations(CPhoneNumbersMap& oPhoneNumbersMap)
{
	//Не се очаква да се извършват операции с таблица телефонни номера
	if (oPhoneNumbersMap.IsEmpty())
	{
		return TRUE;
	}

	//Променливи за обход на мап
	POSITION oPos = oPhoneNumbersMap.GetStartPosition();
	OPERATIONS_WITH_DATA_FLAGS oFlagOperation;
	CPhoneNumbersArray* pPhoneNumberArray;

	while (oPos != NULL)
	{
		//Достъпваме настоящ елемент
		oPhoneNumbersMap.GetNextAssoc(oPos, oFlagOperation, pPhoneNumberArray);

		if (pPhoneNumberArray == nullptr)
		{
			return FALSE;
		}
		//Извършваме операция връху обекта според флага
		if (ChoosePhoneNumbersOperation(oFlagOperation, *pPhoneNumberArray))
		{
			return FALSE;
		}
	}
	return FALSE;
}

BOOL CPersonsData::ChoosePhoneNumbersOperation(LPARAM oFlagOperation, CPhoneNumbersArray& oPhoneNumberArray)
{
	CPhoneNumbersTable oPhoneNumbersTable;

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

BOOL CPersonsData::FindAllPhoneNumbersForPerson(const long lId, CPhoneNumbersArray& oPhoneNumbersArray)
{
	for (INT_PTR nIndex = oPhoneNumbersArray.GetCount(); nIndex >= 0; --nIndex)
	{
		//Достъпваме настоящ елемент
		PHONE_NUMBERS* pPhoneNumber = oPhoneNumbersArray.GetAt(nIndex);
		if (pPhoneNumber == nullptr)
		{
			return FALSE;
		}
		//Ако ид на клиент на настоящия телефонен номер е идентично с настоящия клеинт
		if (pPhoneNumber->lIdPerson != lId)
		{
			oPhoneNumbersArray.RemoveElement(*pPhoneNumber);
		}
	}
	return TRUE;
}


// Overrides
// ----------------