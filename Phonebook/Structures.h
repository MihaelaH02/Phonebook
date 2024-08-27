#pragma once

#include <afxtempl.h>
#include "TypePtrDataArray.h"
#include "TableDataOperationsMap.h"
#include "StructsInfo.h"

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
	TCHAR szCityName[STRUCT_MEMBER_SIZE_TYPE_TCHAR];
	/// <summary> Община член променлива </summary>
	TCHAR szRegion[STRUCT_MEMBER_SIZE_TYPE_TCHAR];


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

	BOOL CompareAll(const CITIES& recCity) const 
	{
		if (_tcscmp(szCityName, recCity.szCityName) != 0)
		{
			return 1;
		}

		if(_tcscmp(szRegion, recCity.szRegion))
		{
			return 1;
		}

		return 0;
	}
};
///<summary> Псевдоним на  CTypePtrDataArray<CITIES> с тип CITIES</summary> 
typedef CTypedPtrDataArray<CITIES> CCitiesArray;


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
	TCHAR czPhoneType[STRUCT_MEMBER_SIZE_TYPE_TCHAR];

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

	BOOL CompareAll(const PHONE_TYPES& recPhoneType) const
	{
		if (_tcscmp(czPhoneType, recPhoneType.czPhoneType) != 0)
		{
			return 1;
		}

		return 0;
	}
};

///<summary> Псевдоним на  CTypePtrDataArray<PHONE_TYPES> с тип PHONE_TYPES</summary> 
typedef CTypedPtrDataArray<PHONE_TYPES> CPhoneTypesArray;

<<<<<<< Updated upstream
=======

/// <summary> 
/// Дискова структура по таблица Код на държава
/// </summary>
struct PHONE_ISO_CODES
{
	/// <summary> Ид член променлива </summary>
	long lId;
	/// <summary> Брояч за модификация член променлива </summary>
	long lUpdateCounter;
	/// <summary> Код на държава номер член променлива </summary>
	TCHAR czPhoneISOCode[STRUCT_MEMBER_SIZE_TYPE_TCHAR_FOR_PHONE_ISO_CODES];

	/// <summary> Конструктор </summary>
	PHONE_ISO_CODES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

	/// <summary>
	/// Копи констурктор по всички полета
	/// </summary>
	PHONE_ISO_CODES(const PHONE_ISO_CODES& recPhoneISOCode)
	{
		lId = recPhoneISOCode.lId;
		lUpdateCounter = recPhoneISOCode.lUpdateCounter;
		_tcscpy_s(czPhoneISOCode, recPhoneISOCode.czPhoneISOCode);
	}

	BOOL CompareAll(const PHONE_ISO_CODES& recPhoneISOCode) const
	{
		if (_tcscmp(czPhoneISOCode, recPhoneISOCode.czPhoneISOCode) != 0)
		{
			return 1;
		}

		return 0;
	}
};

///<summary> Псевдоним на  CTypePtrDataArray<PHONE_ISO_CODES> с тип PHONE_ISO_CODES</summary> 
typedef CTypedPtrDataArray<PHONE_ISO_CODES> CPhoneISOCodesArray;


>>>>>>> Stashed changes
/// <summary> 
/// Дискова структура по таблица Типове клиенти
/// </summary>
struct PERSON_TYPES
{
	/// <summary> Ид член променлива </summary>
	long lId;
	/// <summary> Брояч за модификация член променлива </summary>
	long lUpdateCounter;
	/// <summary> Тип клиент член променлива </summary>
	TCHAR czPersonType[STRUCT_MEMBER_SIZE_TYPE_TCHAR];

	/// <summary> Конструктор </summary>
	PERSON_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

	/// <summary>
	/// Параметризиран констурктор по всички полета
	/// </summary>
	PERSON_TYPES(const PERSON_TYPES& recPersonTypes)
	{
		lId = recPersonTypes.lId;
		lUpdateCounter = recPersonTypes.lUpdateCounter;
		_tcscpy_s(czPersonType, recPersonTypes.czPersonType);
	}

	BOOL CompareAll(const PERSON_TYPES& recPersonTypes) const
	{
		if (_tcscmp(czPersonType, recPersonTypes.czPersonType) != 0)
		{
			return 1;
		}

		return 0;
	}
};

///<summary> Псевдоним на  CTypePtrDataArray<PERSON_TYPES> с тип PERSON_TYPES</summary> 
typedef CTypedPtrDataArray<PERSON_TYPES> CPersonTypesArray;
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
	TCHAR szFirstName[STRUCT_MEMBER_SIZE_TYPE_TCHAR];
	/// <summary> Второ име член променлива </summary>
	TCHAR szSecondName[STRUCT_MEMBER_SIZE_TYPE_TCHAR];
	/// <summary> Трето име член променлива </summary>
	TCHAR szLastName[STRUCT_MEMBER_SIZE_TYPE_TCHAR];
	/// <summary> ЕГН член променлива </summary>
	TCHAR szEGN[STRUCT_MEMBER_SIZE_TYPE_TCHAR_FOR_PERSON_EGN];
	/// <summary> Град член променлива </summary>
	long lIdCity;
	/// <summary> Тип клиент член променлива </summary>
	long lIdPersonType;
	/// <summary> Адрес член променлива </summary>
	TCHAR szAddress[STRUCT_MEMBER_SIZE_TYPE_TCHAR];

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
		lIdPersonType = recPersons.lIdPersonType;
		_tcscpy_s(szAddress, recPersons.szAddress);
	}

	BOOL CompareAll(const PERSONS& recPerson) const
	{
		if (_tcscmp(szFirstName, recPerson.szFirstName) != 0)
		{
			return 1;
		}

		if (_tcscmp(szSecondName, recPerson.szSecondName) != 0)
		{
			return 1;
		}

		if (_tcscmp(szLastName, recPerson.szLastName) != 0)
		{
			return 1;
		}

		if (_tcscmp(szAddress, recPerson.szAddress) != 0)
		{
			return 1;
		}

		if (_tcscmp(szEGN, recPerson.szEGN) != 0)
		{
			return 1;
		}

		if (lIdCity != recPerson.lIdCity)
		{
			return 1;
		}

		if (lIdPersonType != recPerson.lIdPersonType)
		{
			return 1;
		}

		return 0;
	}

};

///<summary> Псевдоним на CTypePtrDataArray<PERSONS> с тип PERSONS</summary> 
typedef CTypedPtrDataArray<PERSONS> CPersonsArray;


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
	TCHAR szPhone[STRUCT_MEMBER_SIZE_TYPE_TCHAR_FOR_PHONE_NUMBER];

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

	int CompareAll(const PHONE_NUMBERS& recPhoneNumber) const
	{
		if (_tcscmp(recPhoneNumber.szPhone, szPhone) != 0)
		{
			return 1;
		}

		if(recPhoneNumber.lIdPhoneType != lIdPhoneType)
		{
			return 1;
		}

		return 0;
	}
};

///<summary> Псевдоним на CTypePtrDataArray<PHONE_NUMBERS> с тип PHONE_NUMBERS</summary> 
typedef CTypedPtrDataArray<PHONE_NUMBERS> CPhoneNumbersArray;

/// <summary>Псевдоним на клас CTableDataMap с тип PHONE_NUMBERS</summary>
typedef CTableDataOperationsMap<PHONE_NUMBERS> CPhoneNumbersMap;


template<typename Struct>
int CompareId(const Struct& recStruct1, const Struct& recStruct2)
{
	if (recStruct1.lId != recStruct2.lId)
	{
		return 1;
	}

	return 0;
};

template<typename Struct>
int CompareAll(const Struct& recStruct1, const Struct& recStruct2)
{
	return recStruct1.CompareAll(recStruct2);
};