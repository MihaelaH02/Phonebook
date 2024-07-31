#include "AdditionInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CAdditionInfo


// Constructor / Destructor
// ----------------
CAdditionInfo::CAdditionInfo()
{
}

CAdditionInfo::~CAdditionInfo()
{

}


// Methods
// ----------------

CCitiesDoc* CAdditionInfo::GetCitiesDocument() const 
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDoc)));
	return (CCitiesDoc*)m_pDocument;
}

/*CPhoneTypesDoc* CAdditionInfo::GetPhoneTypesDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhoneTypesDoc)));
	return (CPhoneTypesDoc*)m_pDocument;
}*/


const CCitiesArray CAdditionInfo::GetAllCities() const
{
	return GetCitiesDocument()->GetCitiesArray();
}

/*const CPhoneTypesArray CAdditionInfo::GetAllPhoneTypes() const
{
	return GetPhoneTypesDocument()->GetPhoneTypesArray();

}*/