#include "pch.h"
#include "PersonInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonInfo

// Constructor / Destructor
// ----------------

CPersonInfo::CPersonInfo()
{
}

CPersonInfo::CPersonInfo(const PERSONS& recPerson, const CPhoneNumbersArray& oPhoneNumbers)
	:m_recPerson(recPerson), m_oPhoneNumbers(oPhoneNumbers)
{
}

CPersonInfo::~CPersonInfo()
{
}


// Methods
// ----------------
const PERSONS CPersonInfo::GetPerson() const
{
	return m_recPerson;
}

const CPhoneNumbersArray CPersonInfo::GetPhoneNumbers() const
{
	return m_oPhoneNumbers;
}

int CPersonInfo::FindPhoneNumber(const PHONE_NUMBERS& recPhoneNumber) 
{
	return m_oPhoneNumbers.FindElement(recPhoneNumber);
}

void CPersonInfo::AddPerson(PERSONS& recNewPerson)
{
	m_recPerson = recNewPerson;
}

void CPersonInfo::AddPhoneNumber(PHONE_NUMBERS& recPhoneNumber)
{
	m_oPhoneNumbers.AddElement(recPhoneNumber);
}


// Overrides
// ----------------