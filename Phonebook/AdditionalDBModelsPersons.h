#pragma once

#include "Structures.h"
#include "CitiesData.h"
#include "PhoneTypesData.h"
<<<<<<< Updated upstream
=======
#include "PhoneISOcodesData.h"
#include "PersonTypesData.h"
>>>>>>> Stashed changes

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

	// <summary>
	/// Запълване на член променливата масив с типове клиенти
	/// </summary>
	/// <param name="oCitiesArray">Масив съдържащ данните с типове клиенти</param>
	void SetPersonTypes(const CPersonTypesArray& oPersonTypesArray);

	/// <summary>
	/// Метод за достъп до член променлива масив с градове
	/// </summary>
	const CCitiesArray& GetCities();

	/// <summary>
	/// Метод за достъп до член променлива масив с типове телефонни номера
	/// </summary>
	const CPhoneTypesArray& GetPhoneTypes();

	/// <summary>
<<<<<<< Updated upstream
=======
	/// Метод за достъп до член променливата масив с държави за телефонни номера
	/// </summary>
	/// <returns></returns>
	const CPhoneISOCodesArray& GetPhoneISOCodes();

	/// <summary>
	/// Метод за достъп до член променлива масив с типове клиенти
	/// </summary>
	const CPersonTypesArray& GetPersonTypes();

	/// <summary>
>>>>>>> Stashed changes
	/// Метод за търсене на град в масива с градове по ИД
	/// </summary>
	/// <param name="lId">Параметър за ИД на запис, по който ще се търси</param>
	/// <returns>Връща указател към открит обект или nullptr при неуспех</returns>
	CITIES* CAdditionalDBModelsPersons::GetCityById(const int lId);

	/// <summary>
	/// Метод за търсене на тип телефонен номер в масива с типове клиенти по ИД
	/// </summary>
	/// <param name="lId">Параметър за ИД на зипс, по който ще се търси</param>
	/// <returns>Връща указател към открит обект или nullptr при неуспех</returns>
	PERSON_TYPES* GetPersonTypeById(const int lId);

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
<<<<<<< Updated upstream
=======

	/// <summary>
	/// Член променлива масив, която съдържа всчики типове клиенти
	/// </summary>
	CPersonTypesArray m_oPersonTypesArray;

	/// <summary>
	/// Член променлива, която съдържа всички държави за телефонен номер
	/// </summary>
	CPhoneISOCodesArray m_oPhoneISOCodeArray;
>>>>>>> Stashed changes
};

