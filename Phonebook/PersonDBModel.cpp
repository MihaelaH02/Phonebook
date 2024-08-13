#include "pch.h"
#include "PersonDBMOdel.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonDBModel

// Constructor / Destructor
// ----------------

CPersonDBModel::CPersonDBModel()
{
};

CPersonDBModel::CPersonDBModel(const PERSONS& recPerson,const CPhoneNumbersMap& oPhoneNumbersOperationsMap)
	:m_oPhoneNumbers(oPhoneNumbersOperationsMap), m_recPerson(recPerson)
{
}

CPersonDBModel::CPersonDBModel(const CPersonDBModel& oPersonDBModel)
	:m_oPhoneNumbers(oPersonDBModel.GetPhoneNumbers()),
	 m_recPerson(oPersonDBModel.GetPerson()) 
{
}


CPersonDBModel::~CPersonDBModel()
{
}


// Methods
// ----------------
const PERSONS& CPersonDBModel::GetPerson() const
{
	return m_recPerson;
}

CPhoneNumbersMap& CPersonDBModel::GetPhoneNumbers() 
{
	return m_oPhoneNumbers;
}

const CPhoneNumbersMap& CPersonDBModel::GetPhoneNumbers() const 
{
	return m_oPhoneNumbers;
}

BOOL CPersonDBModel::AddPersonData(const PERSONS& recPerson, const CPhoneNumbersMap& oPhoneNumbersOperationsMap)
{
	AddPerson(recPerson);
	if (!AddAllPhoneNumbers(oPhoneNumbersOperationsMap))
	{
		return FALSE;
	}

	return TRUE;
}

void CPersonDBModel::AddPerson(const PERSONS& recNewPerson)
{
	m_recPerson = recNewPerson;
}

void CPersonDBModel::SetIdPerson(long lId)
{
	m_recPerson.lId = lId;
}

BOOL CPersonDBModel::AddPhoneNumber(const PHONE_NUMBERS& recPhoneNumber)
{
	return m_oPhoneNumbers.AddOneElementToDataOperation(recPhoneNumber);
}

BOOL CPersonDBModel::AddAllPhoneNumbers(const CPhoneNumbersMap& oPhoneNumbersOperationsMap)
{
	return m_oPhoneNumbers.AddAllNewElementsToMap(oPhoneNumbersOperationsMap);
}

void CPersonDBModel::RemoveAllPhoneNumbers()
{
	m_oPhoneNumbers.SetEmptyDataOperationsValues();
}

BOOL CPersonDBModel::SetPhoneNumbersPersonId()
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

			if (pPhoneNumber == nullptr)
			{
				return FALSE;
			}

			if (pPhoneNumber->lIdPerson == m_recPerson.lId)
			{
				continue;
			}

			pPhoneNumber->lIdPerson = m_recPerson.lId;
		}
	}

	return TRUE;
}

// Overrides
// ----------------