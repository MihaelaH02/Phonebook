#pragma once

#include "PersonTypesTable.h"
#include "Structures.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonTypesData

class CPersonTypesData
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------

public:
	CPersonTypesData();
	virtual ~CPersonTypesData();


// Methods
// ----------------
public:
	/// <summary>
	///Метод за селект на всички данни от таблица PERSON_TYPES от базата данни
	/// </summary>
	/// <param name="oPersonTypesArray">Масив, в който ще се съхраняват прочетените данни</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectAllPersonTypes(CPersonTypesArray& oPersonTypesArray);

	/// <summary>
	/// Метод за селект само на един елемент от базата данни
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <param name="recPersonTypes">Променлива, в която ще се запише прочетената стойност</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectPersonTypeWhereID(const long lID, PERSON_TYPES& recPersonTypes);

	/// <summary>
	/// Метод за редакция на запис
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <param name="recPersonTypes">Променлива, която съдържа структура, с която ще се замени записа</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL UpdatePersonTypeWhereID(const long lID, const PERSON_TYPES& recPersonTypes);

	/// <summary>
	/// Метод за добавяне на запис
	/// </summary>
	/// <param name="recStruct">Променлива от тип стуктура PERSON_TYPES, която ще се добавя</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL InsertPersonType(PERSON_TYPES& recPersonTypes);

	/// <summary>
	/// Метода за изтриване на запис
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL DeletePersonTypeWhereID(const long lID);


	// Overrides
	// ----------------


	// Members
	// ----------------
};

