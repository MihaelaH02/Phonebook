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
	
	
	CTableDataMap(const CTableDataMap& oTableDataMap)
	{
		InitializeMap();
		AddAllNewElementsToMap(oTableDataMap);
	}


	CTableDataMap(const CTableDataArray<Type>& oTableDataArray)
	{
		InitializeMap();
		AddAllElementsToKey(oTableDataArray);
	}


	//Динамично се освобождава заделената памет
	virtual ~CTableDataMap()
	{
		RemoveAllElementsInAllKeys();
	};


// Methods
// ----------------

public:
	void InitializeMap()
	{
		//Задаване на флагове и инициализация на масиви
		SetAt(OPERATIONS_WITH_DATA_FLAGS_READED, new CTableDataArray<Type>());
		SetAt(OPERATIONS_WITH_DATA_FLAGS_INSERT, new CTableDataArray<Type>());
		SetAt(OPERATIONS_WITH_DATA_FLAGS_UPDATE, new CTableDataArray<Type>());
		SetAt(OPERATIONS_WITH_DATA_FLAGS_DELETE, new CTableDataArray<Type>());
	}

	/// <summary>
	/// Метод за добавяне на нов елемент по подаден ключ
	/// </summary>
	/// <param name="oType">Параметър за елемент, който ще се добавя</param>
	/// <param name="oFlag"Параметър за флаг, към който ще се добавя></param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL AddOneElementToKey(const Type& oType, LPARAM lFlag = OPERATIONS_WITH_DATA_FLAGS_READED)
	{
		//Добавяне на елемент към подаден флаг
		CTableDataArray<Type>* pDataArray;
		if (!Lookup(lFlag, pDataArray))
		{
			return FALSE;
		}
		
		//Добавяне на елемент към масива с елементи
		if (pDataArray->AddElement(oType) == -1)
		{
			return FALSE;
		}

		return TRUE;
	};

	/// <summary>
	/// Метод за добавяне на нов масив по подаден ключ
	/// </summary>
	/// <param name="oTableDataArray">Параметър за масив, който ще се добавя</param>
	/// <param name="oFlag"Параметър за флаг, към който ще се добавя</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL AddAllElementsToKey(const CTableDataArray<Type>& oTableDataArray, LPARAM lFlag = OPERATIONS_WITH_DATA_FLAGS_READED)
	{
		//Обход на всички елементи от подаден масив
		for (INT_PTR nIndex = 0; nIndex < oTableDataArray.GetCount(); nIndex++)
		{
			Type* pType = oTableDataArray.GetAt(nIndex);
			if (pType == nullptr)
			{
				return FALSE;
			}

			//Добавяне на текущ елемен към ключ
			if (!AddOneElementToKey(*pType, lFlag))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	/// <summary>
	/// Метод за добавяне на всички елементи от попаден масив
	/// </summary>
	/// <param name="oCTableDataMap">Параметър за масив, който ще се добавя</param>
	/// <returns></returns>
	BOOL AddAllNewElementsToMap(const CTableDataMap& oCTableDataMap)
	{
		//Премахване на старите данни
		RemoveAllElementsInAllKeys();

		//Обход на мапа
		POSITION oPos = oCTableDataMap.GetStartPosition();
		LPARAM lKey;
		CTableDataArray<Type>* pValue;
		if (oPos == NULL)
		{
			return FALSE;
		}

		while (oPos != NULL)
		{
			//Достъпваме текущ елемент от мапа
			oCTableDataMap.GetNextAssoc(oPos, lKey, pValue);
			if (pValue == nullptr)
			{
				return FALSE;
			}

			//Добавяне на всички елементи към ключ текущ ключ
			if (!AddAllElementsToKey(*pValue, lKey))
			{
				return FALSE;
			}
		}
		return TRUE;
	};

	/// <summary>
	/// Метод за търсене ключ по подаден елемент
	/// </summary>
	/// <param name="oType">Параметър за елемент, който ще се търси</param>
	/// <returns>Метода връща открит ключ или -1 при неуспех</returns>
	LPARAM FindKeyByValue(const Type& oType)
	{
		//Обход на мапа
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

		//Връщаме -1 при неоткрит елемент
		return -1;
	}

	/// <summary>
	/// Метод за премахване на елемент от масива по подаден ключ 
	/// </summary>
	/// <param name="lId">Параметър за елемент, който ще се изтрива</param>
	/// <param name="oFlag"Параметър за флаг, от който ще се изтирва</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
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
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL RemoveAllElementsFromKey(LPARAM oFlag)
	{
		//Достъпваме масива по поданен флаг-ключ
		CTableDataArray<Type>* pDataArray;
		if (!Lookup(oFlag, pDataArray))
		{
			return FALSE;
		}

		//Премахване на всички елементи
		pDataArray->RemoveAllElements();
		return TRUE;
	};

	/// <summary>
	/// Метод, който премахва всички елемементи от всички ключове
	/// </summary>
	void RemoveAllElementsInAllKeys()
	{
		RemoveAllElementsFromKey(OPERATIONS_WITH_DATA_FLAGS_READED);
		RemoveAllElementsFromKey(OPERATIONS_WITH_DATA_FLAGS_INSERT);
		RemoveAllElementsFromKey(OPERATIONS_WITH_DATA_FLAGS_UPDATE);
		RemoveAllElementsFromKey(OPERATIONS_WITH_DATA_FLAGS_DELETE);
	}

	/// <summary>
	/// Метод за достъп до висчки елементи от всички ключове без ключ - изтрито
	/// </summary>
	/// <param name="oType">Параметър за масив за резултат</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL GetOnlyActiveValuesFromAllKeysInArray(CTableDataArray<Type>& oType)
	{
		//Обход на мапа
		POSITION oPos = GetStartPosition();
		LPARAM lKey;
		CTableDataArray<Type>* pValue;
		if (oPos == NULL)
		{
			return FALSE;
		}

		while (oPos != NULL)
		{
			//Достъпваме текущ елемент от мапа
			GetNextAssoc(oPos, lKey, pValue);

			//При достигане на кюча-флаг с изтрити елементи спираме прочита на данни
			if (lKey == OPERATIONS_WITH_DATA_FLAGS_DELETE)
			{
				break;
			}

			if (pValue == nullptr)
			{
				return FALSE;
			}

			if (pValue->IsEmpty())
			{
				continue;
			}

			//Добавяне на всички елементи от настоящия масив в нов
			if (!oType.AddAllElements(*pValue))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	/// <summary>
	/// Метод за преместване на всички елементи към първия елемент и изтрива по ключ-изтрито
	/// </summary>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL MoveActiveValuesIntoKey(LPARAM oFlag = OPERATIONS_WITH_DATA_FLAGS_READED)
	{
		//Обход на мапа
		POSITION oPos = GetStartPosition();
		LPARAM lKey;
		CTableDataArray<Type>* pValue;

		if (oPos == NULL)
		{
			return FALSE;
		}

		while (oPos != NULL)
		{
			//Достъпваме текущ елемент от мапа
			GetNextAssoc(oPos, lKey, pValue);

			//Ако ключа е проченено да не се обхождат елементите му
			if (lKey == oFlag )
			{
				continue;
			}

			if (pValue->IsEmpty())
			{
				continue;
			}

			//Променлива съдържаща елементите в текущ ключ 
			CTableDataArray<Type> oDataArrayByKey = *pValue;

			//Премахват се всички елементи от текущия ключ
			if (!RemoveAllElementsFromKey(lKey))
			{
				AfxMessageBox(_T("Failed do move data!\n Try to reload."));
			}

			if (lKey == OPERATIONS_WITH_DATA_FLAGS_DELETE)
			{
				break;
			}

			//Добавят се всички прочетени елементи от текущия ключ към първия-прочетено
			if (!AddAllElementsToKey(oDataArrayByKey, oFlag))
			{
				AfxMessageBox(_T("Failed to do operation with phone numbers!\n Try to reload."));
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