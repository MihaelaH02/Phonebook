#pragma once
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
	/// Запълване на член променливата масив с градове с данни
	/// </summary>
	/// <param name="oCitiesArray">Масив съдържащ данните с градове</param>
	void SetCitiesData(const CCitiesArray& oCitiesArray);

	/// <summary>
	/// Запълване на член променливата масив с типове телефони с данни
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
	/// Метод за търсене на област по ид
	/// </summary>
	/// <param name="lId">Параметър за ИД на зипс, който ще се търси</param>
	/// <returns>Връща указалет към открит обект или nullptr при неуспех</returns>
	CITIES* CAdditionPersonInfo::FindCityInArrayById(const int lId);

	/// <summary>
	/// Метод за търсене на телефонен номер по ид
	/// </summary>
	/// <param name="lId">Параметър за ИД на зипс, който ще се търси</param>
	/// <returns>Връща указалет към открит обект или nullptr при неуспех</returns>
	PHONE_TYPES* CAdditionPersonInfo::FindPhoneTypesInArrayById(const int lId);


// Overrides
// ----------------


// Members
// ----------------
private:
	/// <summary>
	/// Променлива масив, който съдържа всички градове
	/// </summary>
	CCitiesArray m_oCitiesArray;

	/// <summary>
	/// Променлива масив, който съдържа всчики типове телефони
	/// </summary>
	CPhoneTypesArray m_oPhoneTypesArray;
};

