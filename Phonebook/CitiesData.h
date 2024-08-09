#pragma once

#include "CitiesTable.h"
#include "Structures.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData

class CCitiesData
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CCitiesData();
	virtual ~CCitiesData();


// Methods
// ----------------
public:
	/// <summary>
	///Метод за селект на всички данни от таблица CITIES от базата данни
	/// </summary>
	/// <param name="oCitiesArray">Масив, в който ще се съхраняват прочетените данни</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectAllCities(CCitiesArray& oCitiesArray);
	
	/// <summary>
	/// Метод за селект само на един елемент от базата данни
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <param name="recCity">Променлива, в която ще се запише прочетената стойност</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectCityWhereID(const long lID, CITIES& recCity);
	
	/// <summary>
	/// Метод за редакция на запис
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <param name="recCity">Променлива, която съдържа структура, с която ще се замени записа</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL UpdateCityWhereID(const long lID, const CITIES& recCity);

	/// <summary>
	/// Метод за добавяне на запис
	/// </summary>
	/// <param name="recCity">Променлива от тип стуктура CITIES, която ще се добавя</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL InsertCity(CITIES& recCity);

	/// <summary>
	/// Метода за изтриване на запис
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL DeleteCityWhereID(const long lID);
		
// Overrides
// ----------------


// Members
// ----------------
};
