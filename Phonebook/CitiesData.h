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
	BOOL SelectAll(CCitiesArray& oCitiesArray);
	
	/// <summary>
	/// Метод за селект само на един елемент от базата данни
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <param name="recCity">Променлива, в която ще се запише прочетената стойност</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectWhereID(const long lID, CITIES& recCity);
	
	/// <summary>
	/// Метод за редакция на запис
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <param name="recCity">Променлива, която съдържа структура, с която ще се замени записа</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL UpdateWhereID(const long lID, const CITIES& recCity);

	/// <summary>
	/// Метод за добавяне на запис
	/// </summary>
	/// <param name="recStruct">Променлива от тип стуктура CITIES, която ще се добавя</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL Insert(CITIES& recStruct);

	/// <summary>
	/// Метода за изтриване на запис
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL DeleteWhereID(const long lID);
		
// Overrides
// ----------------


// Members
// ----------------
private:
	/// <summary>
	/// Член променилва, съдържаща методи, за извършване на операции в базата данни
	/// </summary>
	CCitiesTable m_oCitiesTable;
};
