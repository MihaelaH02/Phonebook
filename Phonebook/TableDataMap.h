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
class CTableDataMap : public CMap<LPARAM, LPARAM, CTableDataArray<Type>*, CTableDataArray<Type>*>
{

// Constants
// ----------------


// Constructor / Destructor
// ----------------

public:
	CTableDataMap()
	{
		SetAt(OPERATIONS_WITH_DATA_FLAGS_READED, new CTableDataArray<Type>());
		SetAt(OPERATIONS_WITH_DATA_FLAGS_INSERT, new CTableDataArray<Type>());
		SetAt(OPERATIONS_WITH_DATA_FLAGS_UPDATE, new CTableDataArray<Type>());
		SetAt(OPERATIONS_WITH_DATA_FLAGS_DELETE, new CTableDataArray<Type>());
	};

	CTableDataMap(const CTableDataMap& oCTableDataMap)
	{
		SetAt(OPERATIONS_WITH_DATA_FLAGS_READED, new CTableDataArray<Type>());
		SetAt(OPERATIONS_WITH_DATA_FLAGS_INSERT, new CTableDataArray<Type>());
		SetAt(OPERATIONS_WITH_DATA_FLAGS_UPDATE, new CTableDataArray<Type>());
		SetAt(OPERATIONS_WITH_DATA_FLAGS_DELETE, new CTableDataArray<Type>());
		AddAllElementsToMap(oCTableDataMap);
	}

	//Динамично се освобождава заделената памет
	virtual ~CTableDataMap()
	{
		RemoveAllElementsFromKey(OPERATIONS_WITH_DATA_FLAGS_READED);
		RemoveAllElementsFromKey(OPERATIONS_WITH_DATA_FLAGS_INSERT);
		RemoveAllElementsFromKey(OPERATIONS_WITH_DATA_FLAGS_UPDATE);
		RemoveAllElementsFromKey(OPERATIONS_WITH_DATA_FLAGS_DELETE);
	};


// Methods
// ----------------

public:
	/// <summary>
	/// Метод за добавяне на елемент динамично
	/// </summary>
	BOOL AddOneElementToKey(const Type& oType, LPARAM oFlag = OPERATIONS_WITH_DATA_FLAGS_READED)
	{
		//Динамично заделяне на памет за елемент масив
		Type* pType = new Type(oType);

		if (pType == nullptr)
		{
			return FALSE;
		}

		//Добавяне на елемент към подаден флаг
		CTableDataArray<Type>* pDataArray;
		if (!Lookup(oFlag, pDataArray))
		{
			return FALSE;
		}
		
		if (pDataArray->AddElement(oType) == -1)
		{
			return FALSE;
		}
		return TRUE;
	};

	/// <summary>
	/// 
	/// </summary>
	/// <param name="oTableDataArray"></param>
	/// <param name="oFlag"></param>
	/// <returns></returns>
	BOOL AddAllElementsToKey(const CTableDataArray<Type>& oTableDataArray,LPARAM oFlag = OPERATIONS_WITH_DATA_FLAGS_READED)
	{
		for (INT_PTR nIndex = 0; nIndex < oTableDataArray.GetCount(); nIndex++)
		{
			Type* pType = oTableDataArray.GetAt(nIndex);
			if (pType == nullptr)
			{
				return FALSE;
			}

			if (!AddOneElementToKey(*pType))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	/// <summary>
	/// Добавяне на няколко елемента
	/// </summary>
	/// <param name="oCTableDataMap"></param>
	/// <returns></returns>
	BOOL AddAllElementsToMap(const CTableDataMap& oCTableDataMap)
	{
		POSITION oPos = oCTableDataMap.GetStartPosition();
		LPARAM oKey;
		CTableDataArray<Type>* pValue;
		if (oPos == NULL)
		{
			return FALSE;
		}

		while (oPos != NULL)
		{
			//Достъпваме текущ елемент от мапа
			oCTableDataMap.GetNextAssoc(oPos, oKey, pValue);
			if (pValue == nullptr)
			{
				return FALSE;
			}
			if (!AddAllElementsToKey(*pValue, oKey))
			{
				return FALSE;
			}
		}
		return TRUE;
	};

	/// <summary>
	/// Метод за търсене на ключ по подаден елемент
	/// </summary>
	/// <param name="oType"></param>
	/// <returns></returns>
	LPARAM FindKeyByValue(const Type& oType)
	{
		POSITION oPos = GetStartPosition();
		LPARAM oKey;
		CTableDataArray<Type>* pValue;
		if (oPos == NULL)
		{
			return -1;
		}

		while (oPos != NULL)
		{
			//Достъпваме текущ елемент от мапа
			GetNextAssoc(oPos, oKey, pValue);
			if (pValue == nullptr)
			{
				return -1;
			}

			//Търсим дали е записан в текущия масив
			INT_PTR nIndex = pValue->FindIndexByElement(oType);

			//Ако е открит връщаме ключа - флаг, под който е записан
			if (nIndex != -1)
			{
				return oKey;
			}
		}

		//Връщаме при -1 не открит елемент
		return -1;
	}

	/// <summary>
	/// Метод за премахване на елемент от масива динамично 
	/// </summary>
	/// <param name="lId">ИД на елемент, който да се премахне</param>
	BOOL RemoveElemetFromKey(const Type& oType, LPARAM oFlag)
	{
		//Достъпваме масива по поданен флаг-ключ
		CTableDataArray<Type>* pDataArray;
		if (!Lookup(oFlag, pDataArray))
		{
			return FALSE;
		}

		//Премахване на подадения елемен от масива
		if (!pDataArray->RemoveElement(oType))
		{
			return FALSE;
		}
		
		return TRUE;
	};

	/// <summary>
	/// Метод за премахване на всички елементи от масива динамично
	/// </summary>
	BOOL RemoveAllElementsFromKey(LPARAM oFlag)
	{
		//Достъпваме масива по поданен флаг-ключ
		CTableDataArray<Type>* pDataArray;
		if (!Lookup(oFlag, pDataArray))
		{
			return FALSE;
		}

		pDataArray->RemoveAllElements();
		return TRUE;
	};

	/// <summary>
	/// 
	/// </summary>
	/// <param name="oType"></param>
	/// <returns></returns>
	BOOL GetOnlyNonDeletedElementsInArray(CTableDataArray<Type>& oType)
	{
		POSITION oPos = GetStartPosition();
		LPARAM oKey;
		CTableDataArray<Type>* pValue;
		if (oPos == NULL)
		{
			return FALSE;
		}

		while (oPos != NULL)
		{
			//Достъпваме текущ елемент от мапа
			GetNextAssoc(oPos, oKey, pValue);

			//При достигане на кюба-флаг с изтрити елементи спираме прочита на данни
			if (oKey == OPERATIONS_WITH_DATA_FLAGS_DELETE)
			{
				break;
			}

			if (pValue == nullptr)
			{
				return FALSE;
			}

			if (!oType.AddAllElements(*pValue))
			{
				return FALSE;
			}
		}
		return TRUE;
	}


// Overrides
// ----------------


// Members
// ----------------
};