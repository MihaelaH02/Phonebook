#include "pch.h"
#include "AdditionInfo.h"
#include "CitiesDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CAdditionInfo


// Constructor / Destructor
// ----------------
CAdditionInfo::CAdditionInfo()
{
	/*CCitiesDoc* pCitiesDoc;
	if (pCitiesDoc == nullptr)
	{
		return;
	}

	m_oCitiesArray.AddAllElements(pCitiesDoc->GetCitiesArray());*/

	//типове телефони
}

CAdditionInfo::~CAdditionInfo()
{

}


// Methods
// ----------------
const CCitiesArray& CAdditionInfo::GetAllCities()
{
	return m_oCitiesArray;
}

/*const CPhoneTypesArray& CAdditionInfo::GetAllPhoneTypes()
{
	return 
}*/

CString CAdditionInfo::FindCityInArrayById(const int lId)
{
	for (INT_PTR nIndex = 0; nIndex < m_oCitiesArray.GetCount(); nIndex++)
	{
		CITIES* pCity = m_oCitiesArray.GetAt(nIndex);

		if (pCity == nullptr)
		{
			return NULL;
		}

		if (pCity->lId == lId)
		{
			return pCity->szRegion;
		}
	}
	return NULL;
}

CString CAdditionInfo::FindPhoneTypesInArrayById(const int lId)
{
	for (INT_PTR nIndex = 0; nIndex < m_oPhoneTypesArray.GetCount(); nIndex++)
	{
		PHONE_TYPES* pPhoneTypes = m_oPhoneTypesArray.GetAt(nIndex);

		if (pPhoneTypes == nullptr)
		{
			return NULL;
		}

		if (pPhoneTypes->lId == lId)
		{
			return pPhoneTypes->czPhoneType;
		}
	}
	return NULL;
}