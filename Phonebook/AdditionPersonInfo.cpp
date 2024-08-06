#include "pch.h"
#include "AdditionPersonInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CAdditionInfo


// Constructor / Destructor
// ----------------
CAdditionPersonInfo::CAdditionPersonInfo()
{
}

CAdditionPersonInfo::~CAdditionPersonInfo()
{

}


// Methods
// ----------------

void CAdditionPersonInfo::SetCitiesData(const CCitiesArray& oCitiesArray)
{
	m_oCitiesArray.AddAllElements(oCitiesArray);
}

void CAdditionPersonInfo::SetPhoneTypesData(const CPhoneTypesArray& oPhoneTypesArray)
{
	m_oPhoneTypesArray.AddAllElements(oPhoneTypesArray);
}

const CCitiesArray& CAdditionPersonInfo::GetAllCities()
{
	return m_oCitiesArray;
}

const CPhoneTypesArray& CAdditionPersonInfo::GetAllPhoneTypes()
{
	return m_oPhoneTypesArray;
}

CITIES* CAdditionPersonInfo::FindCityInArrayById(const int lId)
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

PHONE_TYPES* CAdditionPersonInfo::FindPhoneTypesInArrayById(const int lId)
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