#pragma once

#pragma once

#include "PhoneTypesTable.h"
#include "Structures.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesData

class CPhoneTypesData
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------

public:
	CPhoneTypesData();
	virtual ~CPhoneTypesData();


// Methods
// ----------------
public:
	/// <summary>
	///Метод за селект на всички данни от таблица PHONE_TYPES от базата данни
	/// </summary>
	/// <param name="oPhoneTypesArray">Масив, в който ще се съхраняват прочетените данни</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray);

	/// <summary>
	/// Метод за селект само на един елемент от базата данни
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <param name="recPhoneTypes">Променлива, в която ще се запише прочетената стойност</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectPhoneTypeWhereID(const long lID, PHONE_TYPES& recPhoneTypes);

	/// <summary>
	/// Метод за редакция на запис
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <param name="recPhoneTypes">Променлива, която съдържа структура, с която ще се замени записа</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL UpdatePhoneTypeWhereID(const long lID, const PHONE_TYPES& recPhoneTypes);

	/// <summary>
	/// Метод за добавяне на запис
	/// </summary>
	/// <param name="recStruct">Променлива от тип стуктура PHONE_TYPES, която ще се добавя</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL InsertPhoneType(PHONE_TYPES& recPhoneTypes);

	/// <summary>
	/// Метода за изтриване на запис
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL DeletePhoneTypeWhereID(const long lID);


// Overrides
// ----------------


// Members
// ----------------
};

