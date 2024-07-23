#pragma once

#include "Structures.h"

/////////////////////////////////////////////////////////////////////////////
// CTableDataArray

/// <summary>
///Темплейт клас отгоравящ за обработката на CTypedPtrArrays
/// </summary>
template<class CStruct>
class CDynamicArray : public CTypedPtrArray<CPtrArray, CStruct*>
{

// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CDynamicArray() {};

	//Динамично се освобождава заделената памет
	virtual ~CDynamicArray()
	{
		for (INT_PTR nIndex = 0; nIndex < GetCount(); ++nIndex)
		{
			CStruct* pElement = GetAt(nIndex);
			if (pElement != nullptr)
			{
				delete pElement;
			}
		}
		RemoveAll();
	};


// Methods
// ----------------

	/// <summary>
	/// Добавяне на елемент динамично
	/// </summary>
	/// <param name="recStructData">Елемент от тип структура, който се се добави към масива</param>
	void AddElement(const CStruct& recStructData)
	{
		CStruct* pStruct = new CStruct(recStructData);
		Add(pStruct);
	}

	/// <summary>
	/// Премахване на елемент от масива динамично 
	/// </summary>
	/// <param name="lId">ИД на елемент, който да се премахне</param>
	void RemoveElemetById(const long lId)
	{
		for (INT_PTR nIndex = 0; nIndex < GetCount(); nIndex++)
		{
			CStruct* pElement = GetAt(nIndex);
			if ( pElement->lId == lId)
			{
				delete pElement;
				RemoveAt(nIndex);
			}
		}
	}

// Overrides
// ----------------


// Members
// ----------------
};