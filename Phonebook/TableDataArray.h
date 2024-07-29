#pragma once

#include "Structures.h"

/////////////////////////////////////////////////////////////////////////////
// CTableDataArray

/// <summary>
///Темплейт клас отгоравящ за обработката на CTypedPtrArrays
/// </summary>
template<class CStruct>
class CTableDataArray : public CTypedPtrArray<CPtrArray, CStruct*>
{

// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CTableDataArray() {};

	//Динамично се освобождава заделената памет
	virtual ~CTableDataArray()
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
	INT_PTR AddElement(const CStruct& recStructData)
	{
		CStruct* pStruct = new CStruct(recStructData);
		return Add(pStruct);
	}

	/// <summary>
	/// Метод за премахване на елемент от масива динамично 
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
				pElement = NULL;
				RemoveAt(nIndex);
			}
		}
	}

	/// <summary>
	/// Метод за премахване на всички елементи от масива динамично
	/// </summary>
	void RemoveAllElements()
	{
		for (INT_PTR nIndex = 0; nIndex < GetCount(); ++nIndex)
		{
			CStruct* pElement = GetAt(nIndex);
			if (pElement != nullptr)
			{
				delete pElement;
				pElement = NULL;
			}
		}
		RemoveAll();
	}
// Overrides
// ----------------


// Members
// ----------------
};