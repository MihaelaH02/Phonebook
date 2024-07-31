#pragma once

#include "PersonsTable.h"
#include "PhoneNumbersTable.h"
#include "PersonInfo.h"
#include "EnumsWithFlags.h"
//#include "Structures.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsData

class CPersonsData
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPersonsData();
	virtual ~CPersonsData();


// Methods
// ----------------
public:
	/// <summary>
	///Метод за селект на всички данни от таблица PHONE_TYPES от базата данни
	/// </summary>
	/// <param name="oPersonsInfo">Масив, в който ще се съхраняват прочетените данни</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectAll(CTableDataArray<CPersonInfo>& oPersonsInfo);

	/// <summary>
	/// Метод за селект само на един елемент от базата данни
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <param name="recPhoneTypes">Променлива, в която ще се запише прочетената стойност</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectWhereID(const long lID, CPersonInfo& oPersonInfo);

	/// <summary>
	/// Метод за редакция на запис
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <param name="oPersonInfo">Променлива, която съдържа новите данни</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL UpdateWhereID(const long lID, CPersonInfo& oPersonInfo, LPARAM oUpdateFlag);

	/// <summary>
	/// Метод за добавяне на запис
	/// </summary>
	/// <param name="oPersonInfo">Променлива с данни, които ще се добавя</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL Insert(CPersonInfo& oPersonInfo, LPARAM oUpdateFlag);

	/// <summary>
	/// Метода за изтриване на запис
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL DeleteWhereID(const long lID, LPARAM oUpdateFlag);

private:
	CPhoneNumbersArray FindAllPhoneNumbersForPerson(const long lId, CPhoneNumbersArray oPhoneNumbersArray);

// Overrides
// ----------------


// Members
// ----------------
};

