#pragma once

#include "Structures.h"
#include "CitiesData.h"
#include "PhoneTypesData.h"

/////////////////////////////////////////////////////////////////////////////
// CAdditionInfo

class CAdditionPersonInfo
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CAdditionPersonInfo();

	~CAdditionPersonInfo();

// Methods
// ----------------

public:
	/// <summary>
	/// Запълване на член променливата масив с градове
	/// </summary>
	/// <param name="oCitiesArray">Масив съдържащ данните с градове</param>
	void SetCitiesData(const CCitiesArray& oCitiesArray);

	/// <summary>
	/// Запълване на член променливата масив с типове телефони
	/// </summary>
	/// <param name="oPhoneTypesArray">Масив съдържащ данните с типове телефони</param>
	void SetPhoneTypesData(const CPhoneTypesArray& oPhoneTypesArray);

	/// <summary>
	/// Метод за достъп до член променлива масив с градове
	/// </summary>
	const CCitiesArray& GetAllCities();

	/// <summary>
	/// Метод за достъп до член променлива масив с телефонни номера
	/// </summary>
	const CPhoneTypesArray& GetAllPhoneTypes();

	/// <summary>
	/// Метод за търсене на област в масива с градове по ИД
	/// </summary>
	/// <param name="lId">Параметър за ИД на запис, който ще се търси</param>
	/// <returns>Връща указател към открит обект или nullptr при неуспех</returns>
	CITIES* CAdditionPersonInfo::FindCityInArrayById(const int lId);

	/// <summary>
	/// Метод за търсене на телефонен номер в масива с номера по ИД
	/// </summary>
	/// <param name="lId">Параметър за ИД на зипс, който ще се търси</param>
	/// <returns>Връща указател към открит обект или nullptr при неуспех</returns>
	PHONE_TYPES* CAdditionPersonInfo::FindPhoneTypesInArrayById(const int lId);


// Overrides
// ----------------


// Members
// ----------------
private:
	/// <summary>
	/// Член променлива масив, която съдържа всички градове
	/// </summary>
	CCitiesArray m_oCitiesArray;

	/// <summary>
	/// Член променлива масив, която съдържа всчики типове телефони
	/// </summary>
	CPhoneTypesArray m_oPhoneTypesArray;
};

