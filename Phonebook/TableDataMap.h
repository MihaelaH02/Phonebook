#pragma once

#include "Structures.h"
#include "EnumsWithFlags.h"
/////////////////////////////////////////////////////////////////////////////
// CTableDataMap

/// <summary>
///Темплейт клас отгоравящ за обработката на CTypedPtrArrays
/// </summary>
template<class CTableDataArray>
class CTableDataMap : public CMap<OPERATIONS_WITH_DATA_FLAGS, OPERATIONS_WITH_DATA_FLAGS, CTableDataArray*, CTableDataArray*>
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
	/// <param name="recStructData">Елемент от тип структура, който се се добави към масива</param>
	BOOL AddElement(CTableDataArray& oTableDataArray, OPERATIONS_WITH_DATA_FLAGS eFlag = OPERATIONS_WITH_DATA_FLAGS_READED)
	{
		//Динамично заделяне на памет за елелмент масив
		CTableDataArray* pTableDataArray = new CTableDataArray(oTableDataArray);
		if (pTableDataArray == nullptr)
		{
			return FALSE;
		}
		//Добавяне на елемент с ключ - флаг, по който ще се определя операция и стойност - указател към масив с данни, чийито елементи ще се оперират
		SetAt(eFlag, pTableDataArray);
		return TRUE;
	};

	/// <summary>
	/// 
	/// </summary>
	/// <param name="oCTableDataMap"></param>
	/// <returns></returns>
	BOOL AddAllElements(const CTableDataMap& oCTableDataMap)
	{
		POSITION oPos = oCTableDataMap.GetStartPosition();
		OPERATIONS_WITH_DATA_FLAGS oKey;
		CTableDataArray* pValue;
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

	CTableDataArray& FindValueByKey(OPERATIONS_WITH_DATA_FLAGS eFlag)
	{
		CTableDataArray* pTableDataArray;

		if (Lookup(eFlag, pTableDataArray))
		{

			if (pTableDataArray != nullptr)
			{

				return *pTableDataArray;
			}
		}
	}

	/// <summary>
	/// Метод за премахване на елемент от масива динамично 
	/// </summary>
	/// <param name="lId">ИД на елемент, който да се премахне</param>
	BOOL RemoveElemetByKey(OPERATIONS_WITH_DATA_FLAGS eFlag)
	{
		CTableDataArray* pTableDataArray = FindValueByKey(eFlag);
		
		if (pTableDataArray == nullptr)
		{
			return FALSE;
		}

		delete pTableDataArray;

		if(!RemoveKey(eFlag))
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


	BOOL GetAllValuesInArray(CTableDataArray& oCTableDataArray)
	{
		POSITION oPos = GetStartPosition();
		OPERATIONS_WITH_DATA_FLAGS oKey;
		CTableDataArray* pValue;
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
			oCTableDataArray.AddAllElements(*pValue);
		}
		return TRUE;
	}

// Overrides
// ----------------


// Members
// ----------------
};