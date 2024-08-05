#pragma once

#include "Structures.h"
#include "TableDataArray.h"
#include "EnumsWithFlags.h"
/////////////////////////////////////////////////////////////////////////////
// CTableDataMap

/// <summary>
///Темплейт клас отгоравящ за обработката на CTypedPtrArrays
/// </summary>
template<class Type>
class CTableDataMap : public CMap<LPARAM, LPARAM, Type*, Type*>
{

	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------

public:
	CTableDataMap()
	{
	};

	CTableDataMap(const CTableDataMap& oCTableDataMap)
	{
		AddAllElements(oCTableDataMap);
	}

	//Динамично се освобождава заделената памет
	virtual ~CTableDataMap()
	{
		RemoveAllElements();
	};


// Methods
// ----------------

public:
	/// <summary>
	/// Метод за добавяне на елемент динамично
	/// </summary>
	BOOL AddElement(Type& oType, LPARAM oFlag = OPERATIONS_WITH_DATA_FLAGS_READED)
	{
		//Динамично заделяне на памет за елелмент масив
		Type* pType = new Type(oType);
		if (pType == nullptr)
		{
			return FALSE;
		}
		//Добавяне на елемент с ключ - флаг, по който ще се определя операция и стойност - указател към масив с данни, чийито елементи ще се оперират
		SetAt(oFlag, pType);
		return TRUE;
	};

	/// <summary>
	/// Метод за търсене на стойност по подаден ключ
	/// </summary>
	/// <param name="oFlag">Флаг на опреция</param>
	/// <returns>Връща указател към намерена стойност</returns>
	Type* GetKeyByValue(LPARAM oFlag)
	{
		Type* pType;

		if (!Lookup(eFlag, pType))
		{
			return nullptr;
		}
			
		return *pType;

	}

	/// <summary>
	/// Метод за премахване на елемент от масива динамично 
	/// </summary>
	/// <param name="lId">ИД на елемент, който да се премахне</param>
	BOOL RemoveElemetByKey(LPARAM oFlag)
	{
		Type* pType = GetKeyByValue(oFlag);
		
		if (pType == nullptr)
		{
			return FALSE;
		}

		delete pType;

		if(!RemoveKey(oFlag))
		{
			return FALSE;
		}

		return TRUE;
	};

	/// <summary>
	/// Метод за премахване на всички елементи от масива динамично
	/// </summary>
	BOOL RemoveAllElements()
	{
/*		POSITION oPos = GetStartPosition();

		for (POSITION oPos = GetStartPosition(); oPos != NULL; oPos = GetNextPosotion())
		{
			RemoveElemetByKey
		}*/
		return TRUE;
	};


	BOOL GetAllValuesInArray(Type& oType)
	{
		POSITION oPos = GetStartPosition();
		LPARAM oKey;
		Type* pValue;
		if (oPos == NULL)
		{
			//oPos = 0/1;
		}

		while (oPos != NULL)
		{
			//Достъпваме текущ елемент от мапа
			GetNextAssoc(oPos, oKey, pValue);
			if (pValue == nullptr)
			{
				return FALSE;
			}
			oType.AddAllElements(*pValue);
		}
		return TRUE;
	}

	/// <summary>
	/// Добавяне на няколко елемента
	/// </summary>
	/// <param name="oCTableDataMap"></param>
	/// <returns></returns>
	BOOL AddAllElements(const CTableDataMap& oCTableDataMap)
	{
		POSITION oPos = oCTableDataMap.GetStartPosition();
		LPARAM oKey;
		Type* pValue;
		if (oPos == NULL)
		{
			//oPos = 0/1;
		}

		while (oPos != NULL)
		{
			//Достъпваме текущ елемент от мапа
			oCTableDataMap.GetNextAssoc(oPos, oKey, pValue);
			if (pValue == nullptr)
			{
				return FALSE;
			}
			AddElement(*pValue, oKey);
		}
		return TRUE;
	};

// Overrides
// ----------------


// Members
// ----------------
};