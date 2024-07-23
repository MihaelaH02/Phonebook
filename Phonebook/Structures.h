#pragma once

#include <afxtempl.h>
#include "DynamicArray.h"

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
	/// Параметризиран конструтор по избрани полета
	/// </summary>
	CITIES(const TCHAR szCityNameValue[TCHAR_SIZE_FOR_STRUCT_MEMBERS], const TCHAR szRegionValue[TCHAR_SIZE_FOR_STRUCT_MEMBERS])
	{
		lId = INIT_VALUE_UPDATE_COUNTER;
		lUpdateCounter = INIT_VALUE_UPDATE_COUNTER;
		_tcscpy_s(szCityName, szCityNameValue);
		_tcscpy_s(szRegion, szRegionValue);
	}

	/// <summary>
	/// Параметризиран констурктор по всички полета
	/// </summary>
	CITIES(const CITIES& recCity)
	{
		lId = recCity.lId;
		lUpdateCounter = recCity.lUpdateCounter;
		_tcsncpy_s(szCityName, recCity.szCityName, _TRUNCATE);
		_tcsncpy_s(szRegion, recCity.szRegion, _TRUNCATE);
	}
}; typedef CDynamicArray<CITIES> CCitiesArray;


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
};

///<summary> Псевдоним на CTypedPtrArray с тип PHONE_TYPES</summary> 
typedef CDynamicArray<PHONE_TYPES> CPhoneTypesArray;

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
	long lIddCity;
	/// <summary> Адрес член променлива </summary>
	TCHAR szAddress[TCHAR_SIZE_FOR_STRUCT_MEMBERS];

	/// <summary> Конструктор </summary>
	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

///<summary> Псевдоним на PERSONS с тип CITIES</summary> 
typedef CDynamicArray<PERSONS> CPersonsArray;


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
};

///<summary> Псевдоним на CTypedPtrArray с тип PHONE_NUMBERS</summary> 
typedef CDynamicArray<PHONE_NUMBERS> CPhoneNumbersArray;