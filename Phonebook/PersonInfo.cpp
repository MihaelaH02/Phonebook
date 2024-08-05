#include "pch.h"
#include "PersonInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonInfo

// Constructor / Destructor
// ----------------

CPersonInfo::CPersonInfo()
{
};

CPersonInfo::CPersonInfo(const PERSONS& recPerson, const CPhoneNumbersMap& oPhoneNumbersMap)
{
	m_recPerson = recPerson;
	m_oPhoneNumbers.AddAllElements(oPhoneNumbersMap);
}

CPersonInfo::CPersonInfo(const CPersonInfo& oPersonInfo)
{
	m_recPerson = oPersonInfo.GetPerson();
	m_oPhoneNumbers.AddAllElements(oPersonInfo.GetPhoneNumbers());
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

const CPhoneNumbersMap CPersonInfo::GetPhoneNumbers() const
{
	return m_oPhoneNumbers;
}

void CPersonInfo::AddPerson(PERSONS& recNewPerson)
{
	m_recPerson = recNewPerson;
}
void CPersonInfo::SetIdPerson(long lId)
{
	m_recPerson.lId = lId;
}

void CPersonInfo::AddPhoneNumber(CPhoneNumbersArray& oPhoneNumbersArray)
{
	m_oPhoneNumbers.AddElement(oPhoneNumbersArray);
}

void CPersonInfo::AddAllPhoneNumbers(const CPhoneNumbersMap oPhoneNumbersMap)
{
	m_oPhoneNumbers.AddAllElements(oPhoneNumbersMap);
}

// Overrides
// ----------------