#pragma once

#include "Structures.h"
#include "CitiesData.h"
#include "PhoneTypesData.h"

/////////////////////////////////////////////////////////////////////////////
// CAdditionalDBModelsPersons

/// <summary>
/// Клас съдържащ допълнителни модели, необходими за модел клиенти
/// </summary>
class CAdditionalDBModelsPersons
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CAdditionalDBModelsPersons();

	~CAdditionalDBModelsPersons();

// Methods
// ----------------

public:
	/// <summary>
	/// Запълване на член променливата масив с градове
	/// </summary>
	/// <param name="oCitiesArray">Масив съдържащ данните с градове</param>
	void SetCities(const CCitiesArray& oCitiesArray);

	/// <summary>
	/// Запълване на член променливата масив с типове телефони
	/// </summary>
	/// <param name="oPhoneTypesArray">Масив съдържащ данните с типове телефони</param>
	void SetPhoneTypes(const CPhoneTypesArray& oPhoneTypesArray);

	/// <summary>
	/// Метод за достъп до член променлива масив с градове
	/// </summary>
	const CCitiesArray& GetCities();

	/// <summary>
	/// Метод за достъп до член променлива масив с типове телефонни номера
	/// </summary>
	const CPhoneTypesArray& GetPhoneTypes();

	/// <summary>
	/// Метод за търсене на град в масива с градове по ИД
	/// </summary>
	/// <param name="lId">Параметър за ИД на запис, по който ще се търси</param>
	/// <returns>Връща указател към открит обект или nullptr при неуспех</returns>
	CITIES* CAdditionalDBModelsPersons::GetCityById(const int lId);

	/// <summary>
	/// Метод за търсене на тип телефонен номер в масива с типове номера по ИД
	/// </summary>
	/// <param name="lId">Параметър за ИД на зипс, по който ще се търси</param>
	/// <returns>Връща указател към открит обект или nullptr при неуспех</returns>
	PHONE_TYPES* CAdditionalDBModelsPersons::GetPhoneTypeById(const int lId);


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

