#pragma once

#include "Structures.h"
#include "TypePtrDataArray.h"
#include "Flags.h"

/////////////////////////////////////////////////////////////////////////////
// CTableDataMap

/// <summary>
///Темплейт клас, киото ще бъде елемент на CTypedPtrDataArray масив
/// </summary>
template<class Type>
class CTableDataOperationsMap : public CMap<LPARAM, LPARAM, CTypedPtrDataArray<Type>*, CTypedPtrDataArray<Type>*>
{

// Constants
// ----------------


// Constructor / Destructor
// ----------------

public:
	CTableDataOperationsMap()
	{
		InitializeMap();
	};
	
	/// <param name="oTableDataMap">Параметър за мап чиито елементи ще се добавят към настоящия мап</param>
	CTableDataOperationsMap(const CTableDataOperationsMap& oTableDataMap)
	{
		InitializeMap();
		AddAllNewElementsToMap(oTableDataMap);
	}

	/// <param name="oTableDataArray">Параметър за масив, чиито променливи ще се добавят към ключ - прочетено на мапа</param>
	CTableDataOperationsMap(const CTypedPtrDataArray<Type>& oTableDataArray)
	{
		InitializeMap();
		AddAllElementsToDataOperations(oTableDataArray);
	}

	//Динамично се освобождава заделената памет
	virtual ~CTableDataOperationsMap()
	{
		SetEmptyDataOperationsValues();
	};


// Methods
// ----------------

public:
	/// <summary>
	/// Метод за добавяне на нов елемент по подаден ключ
	/// </summary>
	/// <param name="oType">Параметър за елемент, който ще се добавя</param>
	/// <param name="oFlag"Параметър за флаг, към който ще се добавя></param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL AddOneElementToDataOperation(const Type& oType, LPARAM lFlag = OPERATIONS_WITH_DATA_FLAGS_READED)
	{
		if (!CheckItIsKey(lFlag))
		{
			return FALSE;
		}

		//Добавяне на елемент към подаден флаг
		CTypedPtrDataArray<Type>* pDataArray = nullptr;
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
	BOOL AddAllElementsToDataOperations(const CTypedPtrDataArray<Type>& oTableDataArray, LPARAM lFlag = OPERATIONS_WITH_DATA_FLAGS_READED)
	{
		if (!CheckItIsKey(lFlag))
		{
			return FALSE;
		}

		//Обход на всички елементи от подаден масив
		for (INT_PTR nIndex = 0; nIndex < oTableDataArray.GetCount(); nIndex++)
		{
			Type* pType = oTableDataArray.GetAt(nIndex);
			if (pType == nullptr)
			{
				return FALSE;
			}

			//Добавяне на текущ елемен към ключ
			if (!AddOneElementToDataOperation(*pType, lFlag))
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
	BOOL AddAllNewElementsToMap(const CTableDataOperationsMap& oCTableDataMap)
	{
		//Премахване на старите данни
		SetEmptyDataOperationsValues();

		//Обход на мапа
		POSITION oPos = oCTableDataMap.GetStartPosition();
		LPARAM lKey = 0;
		CTypedPtrDataArray<Type>* pValue = nullptr;
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
			if (!AddAllElementsToDataOperations(*pValue, lKey))
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
	LPARAM FindDataOperationFlagByElement(const Type& oType)
	{
		//Обход на мапа
		POSITION oPos = GetStartPosition();
		LPARAM oKey = 0;
		CTypedPtrDataArray<Type>* pValue = nullptr;
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
			INT_PTR nIndex = pValue->FindIndexByElement(oType, &CompareAll);

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
	BOOL RemoveElemetFromDataOperation(const Type& oType, LPARAM lFlag)
	{
		if (!CheckItIsKey(lFlag))
		{
			return FALSE;
		}

		//Достъпваме масива по поданен флаг-ключ
		CTypedPtrDataArray<Type>* pDataArray = nullptr;
		if (!Lookup(lFlag, pDataArray))
		{
			return FALSE;
		}

		//Премахване на подадения елемен от масива
		if (!pDataArray->RemoveElement(oType, &CompareAll))
		{
			return FALSE;
		}
		
		return TRUE;
	};

	/// <summary>
	/// Метод за премахване на всички елементи от масива динамично
	/// </summary>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL RemoveAllElementsFromDataOperation(LPARAM oFlag)
	{
		if (!CheckItIsKey(oFlag))
		{
			return FALSE;
		}

		//Достъпваме масива по поданен флаг-ключ
		CTypedPtrDataArray<Type>* pDataArray = nullptr;
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
	void SetEmptyDataOperationsValues()
	{
		RemoveAllElementsFromDataOperation(OPERATIONS_WITH_DATA_FLAGS_READED);
		RemoveAllElementsFromDataOperation(OPERATIONS_WITH_DATA_FLAGS_INSERT);
		RemoveAllElementsFromDataOperation(OPERATIONS_WITH_DATA_FLAGS_UPDATE);
		RemoveAllElementsFromDataOperation(OPERATIONS_WITH_DATA_FLAGS_DELETE);
	}

	/// <summary>
	/// Метод за достъп до висчки елементи от всички ключове без ключ - изтрито
	/// </summary>
	/// <param name="oType">Параметър за масив за резултат</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL GetOnlyActiveValuesFromAllKeysInArray(CTypedPtrDataArray<Type>& oType)
	{
		//Обход на мапа
		POSITION oPos = GetStartPosition();
		LPARAM lKey = 0;
		CTypedPtrDataArray<Type>* pValue = nullptr;
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
				continue;
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
	BOOL ChangeValuesToOperation(LPARAM oFlag = OPERATIONS_WITH_DATA_FLAGS_READED)
	{
		if (!CheckItIsKey(oFlag))
		{
			return FALSE;
		}

		//Обход на мапа
		POSITION oPos = GetStartPosition();
		LPARAM lKey = 0;
		CTypedPtrDataArray<Type>* pValue = nullptr;

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
			CTypedPtrDataArray<Type> oDataArrayByKey = *pValue;

			//Премахват се всички елементи от текущия ключ
			if (!RemoveAllElementsFromDataOperation(lKey))
			{
				AfxMessageBox(_T("Failed do move data!\n Try to reload."));
			}

			if (lKey == OPERATIONS_WITH_DATA_FLAGS_DELETE)
			{
				break;
			}

			//Добавят се всички прочетени елементи от текущия ключ към първия-прочетено
			if (!AddAllElementsToDataOperations(oDataArrayByKey, oFlag))
			{
				AfxMessageBox(_T("Failed to do operation with phone numbers!\n Try to reload."));
				return FALSE;
			}
		}
		return TRUE;
	}

private:

	/// <summary>
	/// Метод за начална инициализация на ключовете и стойностите в мапа
	/// </summary>
	void InitializeMap()
	{
		//Задаване на флагове и инициализация на масиви
		SetAt(OPERATIONS_WITH_DATA_FLAGS_READED, new CTypedPtrDataArray<Type>());
		SetAt(OPERATIONS_WITH_DATA_FLAGS_INSERT, new CTypedPtrDataArray<Type>());
		SetAt(OPERATIONS_WITH_DATA_FLAGS_UPDATE, new CTypedPtrDataArray<Type>());
		SetAt(OPERATIONS_WITH_DATA_FLAGS_DELETE, new CTypedPtrDataArray<Type>());
	}

	/// <summary>
	// Метод за проверка дали подаден флаг се съдържа като ключ от мапа
	/// </summary>
	/// <param name="oFlag">Параметър за флаг, който ще се търси</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL CheckItIsKey(const LPARAM lFlag)
	{
		switch (lFlag)
		{
		case OPERATIONS_WITH_DATA_FLAGS_READED:
		case OPERATIONS_WITH_DATA_FLAGS_INSERT:
		case OPERATIONS_WITH_DATA_FLAGS_UPDATE:
		case OPERATIONS_WITH_DATA_FLAGS_DELETE:
		{
			return TRUE;
		}
		break;
		default:
		{
			return FALSE;
		}
		break;
		}
	}


// Overrides
// ----------------


// Members
// ----------------
};