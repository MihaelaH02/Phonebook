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
	:m_oPhoneNumbers(oPhoneNumbersMap), m_recPerson(recPerson)
{
}

CPersonInfo::CPersonInfo(const CPersonInfo& oPersonInfo)
	:m_oPhoneNumbers(oPersonInfo.GetPhoneNumbers()), m_recPerson(oPersonInfo.GetPerson())
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

const CPhoneNumbersMap& CPersonInfo::GetPhoneNumbers() const
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

int CPersonInfo::AddPhoneNumber(CPhoneNumbersArray& oPhoneNumbersArray)
{
	return m_oPhoneNumbers.AddElement(oPhoneNumbersArray);
}

BOOL CPersonInfo::AddAllPhoneNumbers(const CPhoneNumbersMap& oPhoneNumbersMap)
{
	return m_oPhoneNumbers.AddAllElements(oPhoneNumbersMap);
}

// Overrides
// ----------------