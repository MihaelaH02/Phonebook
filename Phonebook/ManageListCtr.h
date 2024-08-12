#pragma once
#include "afxdialogex.h"
#include "TypePtrDataArray.h"
#include "RowDataListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CListCtrlManager

/// <summary>
/// Клас, който менажира всички опирации с лист контрола
/// </summary>
/// <typeparam name="CTypeElements">Обекти, които ще се съдържат в лист контролата</typeparam>
template<class CTypeElements>
class CListCtrlManager
{

// Constructor / Destructor
// ----------------
public:
	CListCtrlManager()
	{
	}

	~CListCtrlManager()
	{
	}

// Methods
// ----------------

	int GetIndexSelectedItem(CListCtrl& lscListCtr)
	{
		//Вземаме позицията на селектирания елемент
		POSITION oPositionCursor = lscListCtr.GetFirstSelectedItemPosition();
		if (oPositionCursor == NULL)
		{
			return -1;
		}

		//Връщаме индекса на елемента или -1 ако няма такъв
		return lscListCtr.GetNextSelectedItem(oPositionCursor);
	}

	BOOL AddOrEditElement(CListCtrl& lscListCtr, const CRowDataListCtrl<CTypeElements>& oRowData, int nIndexExistingElement = -1)
	{		
		//Връщаме новия индекс на елемента
		int nIndex = AddDataToElement(lscListCtr, oRowData.GetData(), nIndexExistingElement);
		if (nIndex == -1)
		{
			return FALSE;
		}

		if (!AddElement(lscListCtr, nIndex, oRowData.GetDisplayData()))
		{
			return FALSE;
		}

		return TRUE;
	}

	CTypeElements* GetElementByIndex(CListCtrl& lscListCtr, const int nIndexItem)
	{
		//Нов обект от типа на елементите в лист контролата
		CTypeElements* pElement = (CTypeElements*)(lscListCtr.GetItemData(nIndexItem));

		//Връщаме елемент
		return pElement;
	}

	BOOL LoadDataFromResourse(CListCtrl& lscListCtr, const CTypedPtrDataArray<CRowDataListCtrl<CTypeElements>>& oRowsDataArray)
	{
		//Премахване на всички зиписани елементи
		if (lscListCtr.GetItemCount() > 0)
		{
			//Изтриваве на всички останали данни
			if (!lscListCtr.DeleteAllItems())
			{
				return FALSE;
			}
		}

		//Добавяме данните от подаден масив в лист контролата
		for (INT_PTR nIndex = 0; nIndex < oRowsDataArray.GetCount(); ++nIndex)
		{
			//Достъп до текущ елемент от масива с данни
			CRowDataListCtrl<CTypeElements>* pElement = oRowsDataArray.GetAt(nIndex);

			if (pElement == nullptr)
			{
				return FALSE;
			}
			//Добавяне на нов елемент
			if (!AddOrEditElement(lscListCtr, *pElement))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	BOOL IsAllDataLoadFromResourse(CListCtrl& lscListCtr, const INT_PTR oResourseSize)
	{
		//Проверка дали броя на елементите, в лест контролата, е еднакъв с този в документа
		if (lscListCtr.GetItemCount() != oResourseSize)
		{
			return FALSE;
		}
		return TRUE;
	}
	
	BOOL RemoveElement(CListCtrl& lscListCtr, int nIndex)
	{
		//Досъпваме укаателя към елемента в лист контролата по подаден индекс
		CTypeElements* pElement = (CTypeElements*)(lscListCtr.GetItemData(nIndex));

		//Проверка за нулев указател
		if (pElement == nullptr)
		{
			return FALSE;
		}

		//Освобождаваме заделеното място
		delete pElement;

		//Изтриваме елемента от констролата
		if (!lscListCtr.DeleteItem(nIndex))
		{
			return FALSE;
		}
		return TRUE;
	}

	int GetIndexByElement(CListCtrl& lscListCtr, const CTypeElements& oTypeElement)
	{
		for (int nIndex = 0; nIndex < lscListCtr.GetItemCount(); ++nIndex)
		{
			//Досъпваме указтеля към елемента в лист контролата по подаден индекс
			CTypeElements* pElement = (CTypeElements*)(lscListCtr.GetItemData(nIndex));

			//Проверка за нулев указател
			if (pElement == nullptr)
			{
				return FALSE;
			}

			//Проверка за открит елемент
			if (*pElement == oTypeElement)
			{
				return nIndex;
			}
		}

		//Не е открит елемент
		return -1;
	}

	CTypeElements* GetSelectedItem(CListCtrl& lscListCtr)
	{
		//Достъп до индекса на селектирания запис
		int nIndexItem = GetIndexSelectedItem(lscListCtr);

		if (nIndexItem == -1)
		{
			return nullptr;
		}

		//Достъпваме селектирания клиент от лист контролата
		return GetElementByIndex(lscListCtr, nIndexItem);
	}


private:
	int AddDataToElement(CListCtrl& lscListCtr, const CTypeElements& oTypeElement, int nIndex = -1)
	{
		//Ако нямаме подаден индекс на елемент да се вземе последния от лист контролата
		if (nIndex != -1)
		{
			return EditDataToElement(lscListCtr, oTypeElement, nIndex);
		}

		//Указател към елемента
		CTypeElements* pElement = new CTypeElements(oTypeElement);

		//Проверка за празен указател
		if (pElement == nullptr)
		{
			return -1;
		}
		nIndex = lscListCtr.GetItemCount();
		//Правим структура, като задаваме индекс, текст в първа колона и параметър(указател към структура)
		LVITEM lvItem = { 0 };
		lvItem.mask = LVIF_TEXT | LVIF_PARAM;
		lvItem.iItem = nIndex;
		lvItem.lParam = (LPARAM)pElement;

		//Добавяме елемент
		lscListCtr.InsertItem(&lvItem);
		return nIndex;
	}

	int EditDataToElement(CListCtrl& lscListCtr, const CTypeElements& oTypeElement, int nIndex)
	{
		//Указател към елемента
		const CTypeElements* pElement = &oTypeElement;

		//Проверка за празен указател
		if (pElement == nullptr)
		{
			return -1;
		}

		//Правим структура, като задаваме индекс, текст в първа колона и параметър(указател към структура)
		LVITEM lvItem = { 0 };
		lvItem.iItem = nIndex;
		lvItem.lParam = (LPARAM)pElement;

		//Промяна на датата на елемента
		if (!lscListCtr.SetItem(&lvItem))
		{
			return -1;
		}

		return nIndex;
	}

	BOOL AddElement(CListCtrl& lscListCtr, const int nIndex, const CTypedPtrDataArray<CString>& strArrayWithDataToDisplay)
	{
		//Добавяме елементите от сткуктурата в таблиците
		for (INT_PTR nNumbersOfColsToAdd = 0; nNumbersOfColsToAdd < strArrayWithDataToDisplay.GetCount(); nNumbersOfColsToAdd++)
		{
			CString* pDataToDisplayInCol = strArrayWithDataToDisplay.GetAt(nNumbersOfColsToAdd);
			if (pDataToDisplayInCol == nullptr)
			{
				return FALSE;
			}

			if (!lscListCtr.SetItemText(nIndex, (int)nNumbersOfColsToAdd, *pDataToDisplayInCol))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	BOOL RemoveAllElements(CListCtrl& lscListCtr)
	{
		//Преход през всеки елемент от контролата като започваме от последния
		for (int nIndex = lscListCtr.GetItemCount(); nIndex >= 0; --nIndex)
		{
			//Премахване на всеки елемент
			if (!RemoveElement(lscListCtr, nIndex))
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
