#pragma once
#pragma once

#include "Structures.h"
#include "CitiesDoc.h"
#include "PhoneTypesDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CAdditionInfo

class CAdditionInfo
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CAdditionInfo();

	~CAdditionInfo();


// Methods
// ----------------

public:
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
	CITIES* CAdditionInfo::FindCityInArrayById(const int lId);

	/// <summary>
	/// Метод за търсене на телефонен номер по ид
	/// </summary>
	/// <param name="lId">Параметър за ИД на зипс, който ще се търси</param>
	/// <returns>Връща указалет към открит обект или nullptr при неуспех</returns>
	PHONE_TYPES* CAdditionInfo::FindPhoneTypesInArrayById(const int lId);


// Overrides
// ----------------


// Members
// ----------------

	/// <summary>
	/// Променлива масив, който съдържа всички градове
	/// </summary>
	CCitiesArray m_oCitiesArray;

	/// <summary>
	/// Променлива масив, който съдържа всчики типове телефони
	/// </summary>
	CPhoneTypesArray m_oPhoneTypesArray;
};

