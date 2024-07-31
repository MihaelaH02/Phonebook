#pragma once

#include "Structures.h"

/////////////////////////////////////////////////////////////////////////////
// CTableDataArray

/// <summary>
///Темплейт клас отгоравящ за обработката на CTypedPtrArrays
/// </summary>
template<class CClass>
class CTableDataArray : public CTypedPtrArray<CPtrArray, CClass*>
{

// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CTableDataArray() {};

	CTableDataArray(const CTableDataArray& oCTableDataArray)
	{
		AddAll(oCTableDataArray);
	};

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
	INT_PTR AddElement(const CClass& recStructData)
	{
		CClass* pStruct = new CClass(recStructData);
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
			CClass* pElement = GetAt(nIndex);
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
			CClass* pElement = GetAt(nIndex);
			if (pElement != nullptr)
			{
				delete pElement;
				pElement = NULL;
			}
		}
		RemoveAll();
	}

	/// <summary>
	/// Метод, който търси елемент в масива
	/// </summary>
	/// <param name="recElement"></param>
	/// <returns></returns>
	int FindElement(const CClass& recElement)
	{
		//Цисъл, който преминава през всеки елемент
		for (INT_PTR nIndex = 0; nIndex < GetCount(); ++nIndex)
		{
			//Ако се намери съотведствие се връща индекса на елемента
			CClass& recCurrentElement = *GetAt(nIndex);
			if (recElement == recCurrentElement)
			{
				return nIndex;
			}
		}
		//При неуспех
		return -1;
	}
// Overrides
// ----------------


// Members
// ----------------
};