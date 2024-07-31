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
BOOL CPersonsData::SelectAll(CTableDataArray<CPersonInfo>& oPersonsInfo)
{
	//Инстанция на дватата класа с табличните данни
	CPersonsTable oPersonsTable;
	CPhoneNumbersTable oPhoneNumbersTable;

	//Помощни масива, в които ще се съхранява прочетеното от базата данни
	CPersonsArray oPersonsArray;
	CPhoneNumbersArray oPhoneNumbersArray;

	//Извършване на опирация от дабата данни
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
		PERSONS* pPerson = oPersonsArray.GetAt(nIndexPersons);
		
		if (pPerson == nullptr)
		{
			return FALSE;
		}

		//Откриваме всички телефонни номера за настоящия клиент
		CPhoneNumbersArray oPhoneNumberArrayForOnePerson =  FindAllPhoneNumbersForPerson(nIndexPersons, oPhoneNumbersArray);

		//Добавяме данните за клиент и масив с телефонните му номера
		CPersonInfo oPersonInfo(*pPerson,oPhoneNumberArrayForOnePerson);

		//Добавяме времения обект с данни към масива с данни за клиенти
		oPersonsInfo.AddElement(oPersonInfo);
	}

	return TRUE;
}

BOOL CPersonsData::SelectWhereID(const long lID, CPersonInfo& oPersonInfo)
{
	//Инстанция на дватата класа с табличните данни
	CPersonsTable oPersonsTable;
	CPhoneNumbersTable oPhoneNumbersTable;

	//Временна променлива 
	PERSONS recPersonToFind;

	//
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

	//Откриваме всички телефонни номера за настоящия клиент
	CPhoneNumbersArray oPhoneNumberArrayForOnePerson = FindAllPhoneNumbersForPerson(recPersonToFind.lId, oPhoneNumbersArray);

	//Добавяме данните за клиент и масив с телефонните му номера
	CPersonInfo oPersonInfo(recPersonToFind, oPhoneNumberArrayForOnePerson);

}

BOOL CPersonsData::UpdateWhereID(const long lID, CPersonInfo& oPersonInfo, LPARAM oUpdateFlag)
{
	//Инстанция на дватата класа с табличните данни
	CPersonsTable oPersonsTable;
	CPhoneNumbersTable oPhoneNumbersTable;

	switch(oUpdateFlag)
	{
	case DO_OPERATION_FOR_PERSON_AND_PHONE_NUMBERS_TABLE:
	{
		if (!oCitiesTable.UpdateWhereID(lID, recCity))
			//транзакция + сесия
			if (!oPersonsTable.UpdateWhereID(oPersonInfo.GetPerson().lId, oPersonInfo.GetPerson()))
			{
				return FALSE;
			}

		if (!oPhoneNumbersTable.UpdateWhereID(oPersonInfo))
		{
			return FALSE;
		}
		//край транзация
	}break;
	}
}

BOOL CPersonsData::Insert(CPersonInfo& oPersonInfo, LPARAM oUpdateFlag)
{
	//Инстанция на класа с табличните данни
	CPersonsTable oPersonsTable;

	if (!oCitiesTable.Insert(recCity))
	{
		return FALSE;
	}
	return TRUE;
}


BOOL CPersonsData::DeleteWhereID(const long lID, LPARAM oUpdateFlag)
{
	//Инстанция на класа с табличните данни
	CPersonsTable oPersonsTable;

	if (!oCitiesTable.DeleteWhereID(lID))
	{
		return FALSE;
	}
	return TRUE;
}

CPhoneNumbersArray CPersonsData::FindAllPhoneNumbersForPerson(const long lId, CPhoneNumbersArray oPhoneNumbersArray )
{
	//Масив с резултати
	CPhoneNumbersArray oPhoneNumbersArrayWithResults;

	for (INT_PTR nIndexPhoneNumbers = oPhoneNumbersArray.GetCount(); nIndexPhoneNumbers >= 0; --nIndexPhoneNumbers)
	{
		//Достъпваме настоящия елемент от масива с телефонни номера
		PHONE_NUMBERS* pPhoneNumber = oPhoneNumbersArray.GetAt(nIndexPhoneNumbers);

		if (pPhoneNumber == nullptr)
		{
			return;
		}

		//Ако ид на клиент на настоящия телефонен номер е идентично с настоящия клеинт
		if (pPhoneNumber->lIdPerson == lId)
		{
			//Добавяме настоящия телефонен номер към обекта с данните за един клиент
			oPhoneNumbersArrayWithResults.AddElement(*pPhoneNumber);
		}
	}
	return oPhoneNumbersArrayWithResults;
}
// Overrides
// ----------------