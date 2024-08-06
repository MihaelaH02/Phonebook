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

const CPhoneTypesArray& CAdditionInfo::GetAllPhoneTypes()
{
	return m_oPhoneTypesArray;
}

CITIES* CAdditionInfo::FindCityInArrayById(const int lId)
{
	//Обхождаме всчки градове
	for (INT_PTR nIndex = 0; nIndex < m_oCitiesArray.GetCount(); nIndex++)
	{
		//Променлива за текущ елемент от масива с данни
		CITIES* pCity = m_oCitiesArray.GetAt(nIndex);

		//При открит град по подаденот ид връщаме обект от тип градове
		if (pCity->lId == lId)
		{
			return pCity;
		}
	}
	//Не е  открит град по подаденото ид
	return nullptr;
}

PHONE_TYPES* CAdditionInfo::FindPhoneTypesInArrayById(const int lId)
{
	//Обхождаме всчки телефонни типове
	for (INT_PTR nIndex = 0; nIndex < m_oPhoneTypesArray.GetCount(); nIndex++)
	{
		//Променлива за текущ елемент от масива с данни
		PHONE_TYPES* pPhoneTypes = m_oPhoneTypesArray.GetAt(nIndex);

		//При открит тип по подаденот ид връщаме обект от тип телефонен номер
		if (pPhoneTypes->lId == lId)
		{
			return pPhoneTypes;
		}
	}

	//Не е  открит тип тилифонен номер по подаденото ид
	return nullptr;
}