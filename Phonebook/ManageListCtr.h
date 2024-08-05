#pragma once
#include "afxdialogex.h"
#include "TableDataArray.h"

template<class CTypeElements>
class CListCtrlManager
{

public:
	CListCtrlManager()
	{
	}

	~CListCtrlManager()
	{
	}

	int GetSelectedItemListCtrByIndex(CListCtrl& lscListCtr)
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

	BOOL ManageAddingDataInElementListCtr(CListCtrl& lscListCtr, const CTypeElements& oTypeElement, const CTableDataArray<CString>& strArrayWithDataToDisplay,  int nOldIndexExistingElement = -1)
	{		
		//Ако е подаден индекс на стар елемент да се изтрие
		if (nOldIndexExistingElement != -1)
		{
			//Премахваме елемент от лист контролата
			if (!DeleteElementListCtr(lscListCtr, nOldIndexExistingElement))
			{
				return FALSE;
			}
		}

		//Връщаме новия индекс на елемента
		int nIndex = AddDataToElementListCtr(lscListCtr, oTypeElement);
		if (nIndex == -1)
		{
			return FALSE;
		}

		if (!AddElemenInListCtr(lscListCtr, nIndex, strArrayWithDataToDisplay))
		{
			return FALSE;
		}

		return TRUE;
	}

	CTypeElements& GetItemFromListCtr(CListCtrl& lscListCtr, const int nIndexItem)
	{
		//Нов обект от типа на елементите в лист контролата
		CTypeElements* pElement = (CTypeElements*)(lscListCtr.GetItemData(nIndexItem));

		if (pElement != nullptr)
		{
			//Връщаме пълен елемент
			return *pElement;
		}
	}

	BOOL LoadDataInListCtrFromResourse(CListCtrl& lscListCtr, const CTableDataArray<CTypeElements>& oResourseArray,const CTableDataArray<CTableDataArray<CString>>& oArrayWithdataToDisplay)
	{
		if (lscListCtr.GetItemCount() > 0)
		{
			//Изтриваве на всички останали данни
			if (!lscListCtr.DeleteAllItems())
			{
				return FALSE;
			}
		}
		if (oResourseArray.GetCount() != oArrayWithdataToDisplay.GetCount())
		{
			return FALSE;
		}

		//Добавяме данните от подаден масив в лист контролата
		for (INT_PTR nIndex = 0; nIndex < oResourseArray.GetCount(); ++nIndex)
		{
			CTypeElements* pElement = oResourseArray.GetAt(nIndex);
			CTableDataArray<CString>* pElementToDisplay = oArrayWithdataToDisplay.GetAt(nIndex);
			CString str = *pElementToDisplay->GetAt(0);		
			CString str1 = *pElementToDisplay->GetAt(1);

			if (pElement == nullptr)
			{
				return FALSE;
			}

			if (!ManageAddingDataInElementListCtr(lscListCtr, *pElement, *pElementToDisplay))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	BOOL IsAllDataLoadFromResourse(CListCtrl& lscListCtr, const int oResourseSize)
	{
		//Проверка дали броя на елементите, в лест контролата, е еднакъв с този в документа
		if (lscListCtr.GetItemCount() != oResourseSize)
		{
			return FALSE;
		}
		return TRUE;
	}
	
	BOOL DeleteElementListCtr(CListCtrl& lscListCtr, int nIndex)
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

	int FindIndexByElement(CListCtrl& lscListCtr, const CTypeElements& oTypeElement)
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
			/*if (*pElement == oTypeElement)
			{
				return nIndex;
			}*/
		}

		//Не е открит елемент
		return -1;
	}

private:
	int AddDataToElementListCtr(CListCtrl& lscListCtr, const CTypeElements& oTypeElement)
	{
		//Указател към елемента
		CTypeElements* pElement = new CTypeElements(oTypeElement);

		if (pElement == nullptr)
		{
			return -1;
		}

		//Правим структура, като задаваме индекс(последния), текст в първа колона и параметър(указател към структура)
		LVITEM lvItem = { 0 };
		lvItem.mask = LVIF_TEXT | LVIF_PARAM;
		lvItem.iItem = lscListCtr.GetItemCount();
		lvItem.lParam = (LPARAM)pElement;

		//Добавяме елемент
		return lscListCtr.InsertItem(&lvItem);
	}

	BOOL DeleteAllElementsListCtr(CListCtrl& lscListCtr)
	{
		//Преход през всеки елемент от контролата като започваме от последния
		for (int nIndex = lscListCtr.GetItemCount(); nIndex >= 0; --nIndex)
		{
			//Премахване на всеки елемент
			if (!DeleteElementListCtr(lscListCtr, nIndex))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	BOOL AddElemenInListCtr(CListCtrl& lscListCtr, const int nIndex, const CTableDataArray<CString>& strArrayWithDataToDisplay)
	{
		//Добавяме елементите от сткуктурата в таблиците
		for (INT_PTR nNumbersOfColsToAdd = 0; nNumbersOfColsToAdd < strArrayWithDataToDisplay.GetCount(); nNumbersOfColsToAdd++)
		{
			CString* strDataToDisplayInCol = strArrayWithDataToDisplay.GetAt(nNumbersOfColsToAdd);
			if (strDataToDisplayInCol == nullptr)
			{
				return FALSE;
			}

			if (!lscListCtr.SetItemText(nIndex, nNumbersOfColsToAdd, *strDataToDisplayInCol))
			{
				return FALSE;
			}
		}
		return TRUE;
	}
};
