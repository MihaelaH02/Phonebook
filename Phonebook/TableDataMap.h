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
	};


// Methods
// ----------------

public:
	/// <summary>
	/// Метод за добавяне на елемент динамично
	/// </summary>
	/// <param name="recStructData">Елемент от тип структура, който се се добави към масива</param>
	void AddElement(CTableDataArray& oTableDataArray, OPERATIONS_WITH_DATA_FLAGS FLAG = OPERATIONS_WITH_DATA_FLAGS_READED)
	{
		CTableDataArray* pTableDataArray = new CTableDataArray(oTableDataArray);
		if (pTableDataArray != nullptr)
		{
			SetAt(FLAG, pTableDataArray);
		}
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
		while (oPos != NULL)
		{
			GetNextAssoc(oPos, oKey, pValue);
			if (pValue == nullptr)
			{
				return FALSE;
			}
			AddElement(*pValue, oKey);
		}
		return TRUE;
	};

	/// <summary>
	/// Метод за премахване на елемент от масива динамично 
	/// </summary>
	/// <param name="lId">ИД на елемент, който да се премахне</param>
	/*BOOL RemoveElemetByKey(const CTableDataArray& oClassArray)
	{
		CClass* pClass = nullptr;
		if (!Lookup(oClassArray, pClass))
		{
			return FALSE;
		}

		if (pClass == nullptr)
		{
			return FALSE;
		}
		delete pClass;
		RemoveKey(pClass)
		{
			return FALSE;
		}

		return TRUE;
	};*/

	/// <summary>
	/// Метод за премахване на всички елементи от масива динамично
	/// </summary>
	/*void RemoveAllElements()
	{
		POSITION oPosDelete = GetStartPosition();
		CClass* pKeyDelete = nullptr;
		LPARAM oValueDelete = NULL;
		while (oPosDelete != NULL)
		{
			GetNextAssoc(oPosDelete, pKeyDelete, oValueDelete);
			if (pKeyDelete != nullptr)
			{
				delete pKeyDelete;
			}
		}
		RemoveAll();
	};*/


// Overrides
// ----------------


// Members
// ----------------
};