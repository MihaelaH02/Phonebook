#include "pch.h"
#include "PersonInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonInfo

// Constructor / Destructor
// ----------------

CPersonInfo::CPersonInfo()
{
};

CPersonInfo::CPersonInfo(const PERSONS& recPerson,const CPhoneNumbersMap& oPhoneNumbersMap)
	:m_oPhoneNumbers(oPhoneNumbersMap), m_recPerson(recPerson)
{
}

CPersonInfo::CPersonInfo(const CPersonInfo& oPersonInfo)
	:m_oPhoneNumbers(oPersonInfo.GetPhoneNumbers()),
	 m_recPerson(oPersonInfo.GetPerson()) 
{
}


CPersonInfo::~CPersonInfo()
{
}


// Methods
// ----------------
const PERSONS& CPersonInfo::GetPerson() const
{
	return m_recPerson;
}

CPhoneNumbersMap& CPersonInfo::GetPhoneNumbers() 
{
	return m_oPhoneNumbers;
}

const CPhoneNumbersMap& CPersonInfo::GetPhoneNumbers() const 
{
	return m_oPhoneNumbers;
}

BOOL CPersonInfo::AddPersonInfo(const PERSONS& recPerson, const CPhoneNumbersMap& oPhoneNumbersMap)
{
	AddPerson(recPerson);
	if (!AddAllPhoneNumbers(oPhoneNumbersMap))
	{
		return FALSE;
	}

	return TRUE;
}

void CPersonInfo::AddPerson(const PERSONS& recNewPerson)
{
	m_recPerson = recNewPerson;
}

void CPersonInfo::SetIdPerson(long lId)
{
	m_recPerson.lId = lId;
}

BOOL CPersonInfo::AddPhoneNumber(const PHONE_NUMBERS& recPhoneNumber)
{
	return m_oPhoneNumbers.AddOneElementToKey(recPhoneNumber);
}

BOOL CPersonInfo::AddAllPhoneNumbers(const CPhoneNumbersMap& oPhoneNumbersMap)
{
	return m_oPhoneNumbers.AddAllNewElementsToMap(oPhoneNumbersMap);
}

void CPersonInfo::RemoveAllPhoneNumbers()
{
	m_oPhoneNumbers.RemoveAllElementsInAllKeys();
}

BOOL CPersonInfo::CheckAndConnectAllPhoneNumbersWithPersonId()
{
	POSITION oPos = m_oPhoneNumbers.GetStartPosition();
	LPARAM lFlagOperation;
	CPhoneNumbersArray* pPhoneNumberArray;

	if (oPos == NULL)
	{
		return FALSE;
	}

	while (oPos != NULL)
	{
		//Достъпваме настоящ елемент
		m_oPhoneNumbers.GetNextAssoc(oPos, lFlagOperation, pPhoneNumberArray);
		if (pPhoneNumberArray == nullptr)
		{
			return FALSE;
		}

		if (pPhoneNumberArray->IsEmpty())
		{
			continue;
		}
		
		//Преминаваме през всеки елемент в масива с телефонни номера
		for (INT_PTR nIndexElementArray = 0; nIndexElementArray < pPhoneNumberArray->GetCount(); nIndexElementArray++)
		{
			//Добавяме ид на клиент за настоящия номер
			PHONE_NUMBERS* pPhoneNumber = pPhoneNumberArray->GetAt(nIndexElementArray);

			if (pPhoneNumber->lIdPerson == m_recPerson.lId)
			{
				continue;
			}
			pPhoneNumber->lIdPerson = m_recPerson.lId;
			pPhoneNumber;
		}
	}

	return TRUE;
}

// Overrides
// ----------------