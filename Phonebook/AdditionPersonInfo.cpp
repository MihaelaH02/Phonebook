#include "pch.h"
#include "AdditionalDBModelsPersons.h"

/////////////////////////////////////////////////////////////////////////////
// CAdditionInfo


// Constructor / Destructor
// ----------------
CAdditionalDBModelsPersons::CAdditionalDBModelsPersons()
{
}

CAdditionalDBModelsPersons::~CAdditionalDBModelsPersons()
{

}


// Methods
// ----------------

void CAdditionalDBModelsPersons::SetCities(const CCitiesArray& oCitiesArray)
{
	m_oCitiesArray.AddAllElements(oCitiesArray);
}

void CAdditionalDBModelsPersons::SetPhoneTypes(const CPhoneTypesArray& oPhoneTypesArray)
{
	m_oPhoneTypesArray.AddAllElements(oPhoneTypesArray);
}

const CCitiesArray& CAdditionalDBModelsPersons::GetCities()
{
	return m_oCitiesArray;
}

const CPhoneTypesArray& CAdditionalDBModelsPersons::GetPhoneTypes()
{
	return m_oPhoneTypesArray;
}

CITIES* CAdditionalDBModelsPersons::GetCityById(const int lId)
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

PHONE_TYPES* CAdditionalDBModelsPersons::GetPhoneTypeById(const int lId)
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

// Overrides
// ----------------