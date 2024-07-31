#pragma once

#include <afxtempl.h>
#include "TableDataArray.h"

#define TCHAR_SIZE_FOR_STRUCT_MEMBERS 128
#define TCHAR_SIZE_FOR_PERSON_EGN 16
#define TCHAR_SIZE_FOR_PHONE_NUMBER_MEMBER 16
#define INIT_VALUE_UPDATE_COUNTER 0


/// <summary>
/// Дискова структура по таблица Градове 
/// </summary>
struct CITIES
{
	/// <summary> Ид члeн променлива </summary>
	long lId;
	/// <summary> Брояч за модификация члeн променлива </summary>
	long lUpdateCounter;
	/// <summary> Име на град член променлива </summary>
	TCHAR szCityName[TCHAR_SIZE_FOR_STRUCT_MEMBERS];
	/// <summary> Община член променлива </summary>
	TCHAR szRegion[TCHAR_SIZE_FOR_STRUCT_MEMBERS];


	/// <summary> Конструктор </summary>
	CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

	/// <summary>
	/// Параметризиран констурктор по всички полета
	/// </summary>
	CITIES(const CITIES& recCity)
	{
		lId = recCity.lId;
		lUpdateCounter = recCity.lUpdateCounter;
		_tcscpy_s(szCityName, recCity.szCityName);
		_tcscpy_s(szRegion, recCity.szRegion);
	}

};
///<summary> Псевдоним на  CTableDataArray<CITIES> с тип CITIES</summary> 
typedef CTableDataArray<CITIES> CCitiesArray;


/// <summary> 
/// Дискова структура по таблица Типове телефони
/// </summary>
struct PHONE_TYPES
{
	/// <summary> Ид член променлива </summary>
	long lId;
	/// <summary> Брояч за модификация член променлива </summary>
	long lUpdateCounter;
	/// <summary> Тип телефонен номер член променлива </summary>
	TCHAR czPhoneType[TCHAR_SIZE_FOR_STRUCT_MEMBERS];

	/// <summary> Конструктор </summary>
	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

	/// <summary>
	/// Параметризиран констурктор по всички полета
	/// </summary>
	PHONE_TYPES(const PHONE_TYPES& recPhoneType)
	{
		lId = recPhoneType.lId;
		lUpdateCounter = recPhoneType.lUpdateCounter;
		_tcscpy_s(czPhoneType, recPhoneType.czPhoneType);
	}
};

///<summary> Псевдоним на  CTableDataArray<PHONE_TYPES> с тип PHONE_TYPES</summary> 
typedef CTableDataArray<PHONE_TYPES> CPhoneTypesArray;

/// <summary> 
/// Дискова структура по таблица Клиенти 
/// </summary>
struct PERSONS
{
	/// <summary> Ид член променлива </summary>
	long lId;
	/// <summary> Блояч за модификация член променлива </summary>
	long lUpdateCounter;
	/// <summary> Първо име член променлива </summary>
	TCHAR szFirstName[TCHAR_SIZE_FOR_STRUCT_MEMBERS];
	/// <summary> Второ име член променлива </summary>
	TCHAR szSecondName[TCHAR_SIZE_FOR_STRUCT_MEMBERS];
	/// <summary> Трето име член променлива </summary>
	TCHAR szLastName[TCHAR_SIZE_FOR_STRUCT_MEMBERS];
	/// <summary> ЕГН член променлива </summary>
	TCHAR szEGN[TCHAR_SIZE_FOR_PERSON_EGN];
	/// <summary> Град член променлива </summary>
	long lIdCity;
	/// <summary> Адрес член променлива </summary>
	TCHAR szAddress[TCHAR_SIZE_FOR_STRUCT_MEMBERS];

	/// <summary> Конструктор </summary>
	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

	/// <summary>
	/// Параметризиран констурктор по всички полета
	/// </summary>
	PERSONS(const PERSONS& recPersons)
	{
		lId = recPersons.lId;
		lUpdateCounter = recPersons.lUpdateCounter;
		_tcscpy_s(szFirstName, recPersons.szFirstName);
		_tcscpy_s(szSecondName, recPersons.szSecondName);
		_tcscpy_s(szLastName, recPersons.szLastName);
		_tcscpy_s(szEGN, recPersons.szEGN);
		lIdCity = recPersons.lIdCity;
		_tcscpy_s(szAddress, recPersons.szAddress);
	}
};

///<summary> Псевдоним на CTableDataArray<PERSONS> с тип PERSONS</summary> 
typedef CTableDataArray<PERSONS> CPersonsArray;


/// <summary> 
//Дискова структура по таблица Телефонни номера 
/// </summary>
struct PHONE_NUMBERS
{
	/// <summary> Ид член променлива </summary>
	long lId;
	/// <summary> Брояч за модификация член променлива </summary>
	long lUpdateCounter;
	/// <summary> Клиент член променлива </summary>
	long lIdPerson;
	/// <summary> Тип телефон член променлива </summary>
	long lIdPhoneType;
	/// <summary> Телефонен номер член променлива </summary>
	TCHAR szPhone[TCHAR_SIZE_FOR_PHONE_NUMBER_MEMBER];

	/// <summary> Конструктор </summary>
	PHONE_NUMBERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

	/// <summary>
	/// Параметризиран констурктор по всички полета
	/// </summary>
	PHONE_NUMBERS(const PHONE_NUMBERS& recPhoneNumbers)
	{
		lId = recPhoneNumbers.lId;
		lUpdateCounter = recPhoneNumbers.lUpdateCounter;
		lIdPerson = recPhoneNumbers.lIdPerson;
		lIdPhoneType = recPhoneNumbers.lIdPhoneType;
		_tcscpy_s(szPhone, recPhoneNumbers.szPhone);
	}
};

///<summary> Псевдоним на CTableDataArray<PHONE_NUMBERS> с тип PHONE_NUMBERS</summary> 
typedef CTableDataArray<PHONE_NUMBERS> CPhoneNumbersArray;