#pragma once

#include "Structures.h"

/////////////////////////////////////////////////////////////////////////////
// CTypePtrDataArray

/// <summary>
///Темплейт клас отгоравящ за обработката на CTypedPtrArrays
/// </summary>
template<class Type>
class CTypedPtrDataArray : public CTypedPtrArray<CPtrArray, Type*>
{

// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CTypedPtrDataArray() {};

	CTypedPtrDataArray(const CTypedPtrDataArray& oCTypePtrDataArray)
	{
		AddAllElements(oCTypePtrDataArray);
	};

	//Динамично се освобождава заделената памет
	virtual ~CTypedPtrDataArray()
	{
		RemoveAllElements();
	};


// Methods
// ----------------
public:
	/// <summary>
	/// Метод за добавяне на елемент динамично
	/// </summary>
	/// <param name="recStructData">Елемент, който ще се добавя към масива</param>
	/// <returns>Връща се индека на добавения елемент в масва или -1 при неотрит запис</returns>
	INT_PTR AddElement(const Type& oElement)
	{
		Type* pStruct = new Type(oElement);
		if (pStruct == nullptr)
		{
			return -1;
		}

		return Add(pStruct);
	}

	/// <summary>
	/// Метод за добавяне на всички подаденти емеленти към масива
	/// </summary>
	/// <param name="oCTypePtrDataArray">Параметър за масив, чиито елементи ще се добавят</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL AddAllElements(const CTypedPtrDataArray& oCTypePtrDataArray)
	{
		//apend
		for (INT_PTR nIndex = 0; nIndex < oCTypePtrDataArray.GetCount(); nIndex++)
		{

			Type* pElement = oCTypePtrDataArray.GetAt(nIndex);
			if (pElement == nullptr)
			{
				return FALSE;
			}

			if (AddElement(*pElement) == -1) 
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	/// <summary>
	/// Метод за премахване на елемент
	/// </summary>
	/// <param name="recStructData"></param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL RemoveElement(const Type& oElement, BOOL(*Compare)(const Type&, const Type&))
	{
		for (INT_PTR nIndex = 0; nIndex < GetCount(); nIndex++)
		{
			Type* pElement = GetAt(nIndex);
			if (pElement == nullptr)
			{
				return FALSE;
			}

			if (Compare(*pElement, oElement))
			{
				delete pElement;
				RemoveAt(nIndex);
				break;
			}
		}
		return TRUE;
	}

	/// <summary>
	/// Метод за премахване на всички елементи от масива динамично
	/// </summary>
	void RemoveAllElements()
	{
		for (INT_PTR nIndex = 0; nIndex < GetCount(); ++nIndex)
		{
			Type* pElement = GetAt(nIndex);
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
	/// <param name="recElement">Параметър за елемент, който ще се търси</param>
	/// <returns>Връща се индека на елемента в масва или -1 при неотрит запис</returns>
	INT_PTR FindIndexByElement(const Type& oElement, BOOL(*Compare)(const Type&, const Type&))
	{
		//Цисъл, който преминава през всеки елемент
		for (INT_PTR nIndex = 0; nIndex < GetCount(); ++nIndex)
		{
			//Ако се намери съотведствие се връща индекса на елемента
			Type* pCurrentElement = GetAt(nIndex);
			if (pCurrentElement == nullptr)
			{
				return -1;
			}

			if (Compare(*pCurrentElement, oElement))
			{
				return nIndex;
			}
		}

		//При неуспех
		return -1;
	}

	/// <summary>
	/// Редакция на елемент по индект
	/// </summary>
	/// <param name="lIndex">Пъраметър за идекс на елемент</param>
	/// <param name="recNewDataElement">Параметър с обновени данни да елемент</param>
	BOOL ReplaceElement(INT_PTR lIndex, const Type& oNewData)
	{
		//Премахване на указателя към старите данни
		Type* pOldData = GetAt(lIndex);

		if(pOldData == nullptr)
		{
			return FALSE;
		}

		delete pOldData;

		//Задаване на нов указател към нови данни за индекс
		Type* pNewDataForElement = new Type(oNewData);
		SetAt(lIndex, pNewDataForElement);

		return TRUE;
	}


// Overrides
// ----------------


// Members
// ----------------
};