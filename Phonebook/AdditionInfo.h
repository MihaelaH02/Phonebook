#pragma once
#pragma once

#include "Structures.h"
#include "CitiesDoc.h"
//#include "PhoneTypesDoc.h"

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
	/// <returns>Връща област на открит град</returns>
	CString CAdditionInfo::FindCityInArrayById(const int lId);

	/// <summary>
	/// Метод за търсене на телефонен номер по ид
	/// </summary>
	/// <param name="lId"></param>
	/// <returns>Връща тип на открит телефонен номер</returns>
	CString CAdditionInfo::FindPhoneTypesInArrayById(const int lId);

// Overrides
// ----------------


// Members
// ----------------

	/// <summary>
	/// Променлива, която съдържа всички градове
	/// </summary>
	CCitiesArray m_oCitiesArray;

	/// <summary>
	/// Променлива, която съдържа всчики типове телефони
	/// </summary>
	CPhoneTypesArray m_oPhoneTypesArray;
};

