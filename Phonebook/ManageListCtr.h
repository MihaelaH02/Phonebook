#pragma once
#include "afxdialogex.h"
#include "TableDataArray.h"

template<class CTypeElements>
class CManageListCtr: public CListCtrl
{

public:
	CManageListCtr()
	{	

	}

	~CManageListCtr()
	{
		//Динамично освобождаваме паметта
		DeleteAllElementsListCtr();
	}

	int GetSelectedItemListCtrByIndex()
	{
		//Вземаме позицията на селектирания елемент
		POSITION oPositionCursor = GetFirstSelectedItemPosition();
		if (oPositionCursor == NULL)
		{
			return -1;
		}

		//Връщаме индекса на елемента или -1 ако няма такъв
		return GetNextSelectedItem(oPositionCursor);
	}

	BOOL ManageAddingDataInElementListCtr(const CTypeElements& oTypeElement, int nOldIndexExistingElement = -1)
	{		
		//Ако е подаден индекс на стар елемент да се изтрие
		if (nOldIndexExistingElement != -1)
		{
			//Премахваме елемент от лист контролата
			if (!DeleteAllElementsListCtr())
			{
				return FALSE;
			}
		}

		//Връщаме новия индекс на елемента
		int nIndex = AddDataToElementListCtr(oTypeElement);
		if (nIndex == -1)
		{
			return FALSE;
		}

		CArray<CString, CString> strTypeElementArray;
		if (!oTypeElement.ConvertStructToCArray(strTypeElementArray))
		{
			return FALSE;
		}

		if (!AddElemenInListCtr(nIndex, strTypeElementArray))
		{
			return FALSE;
		}

		return TRUE;
	}

	CTypeElements& GetItemFromListCtr(const int nIndexItem)
	{
		//Нов обект от типа на елементите в лист контролата
		CTypeElements* pElement = (CTypeElements*)(GetItemData(nIndexItem));

		if (pElement != nullptr)
		{
			//Връщаме пълен елемент
			return *pElement;
		}
	}

	BOOL LoadDataInListCtrFromResourse(const CTableDataArray<CTypeElements>& oResourseArray)
	{
		
		//Изтриваве на всички останали данни
		if (!DeleteAllItems())
		{
			return FALSE;
		}

		//Добавяме данните от подаден масив в лист контролата
		for (INT_PTR i = 0; i < oResourseArray.GetCount(); ++i)
		{
			CTypeElements* pElement = oResourseArray.GetAt(i);
			if (pElement == nullptr)
			{
				return FALSE;
			}

			if (!ManageAddingDataInElementListCtr(*pElement))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	BOOL IsAllDataLoadFromResourse(const INT_PTR oResourseSize)
	{
		//Проверка дали броя на елементите, в лест контролата, е еднакъв с този в документа
		if (GetItemCount() != oResourseSize)
		{
			return FALSE;
		}
		return TRUE;
	}
	
	CListCtrl& GetListCtrl()
	{
		return GetListCtr();
	}

	BOOL DeleteElementListCtr(int nIndex)
	{
		//Досъпваме укаателя към елемента в лист контролата по подаден индекс
		CTypeElements* pElement = (CTypeElements*)(GetItemData(nIndex));

		//Проверка за нулев указател
		if (pElement == nullptr)
		{
			return FALSE;
		}

		//Освобождаваме заделеното място
		delete pElement;

		//Изтриваме елемента от констролата
		if (!DeleteItem(nIndex))
		{
			return FALSE;
		}
		return TRUE;
	}

	int FindIndexByElement(const CTypeElements& oTypeElement)
	{
		for (int nIndex = 0; nIndex < GetItemCount(); ++nIndex)
		{
			//Досъпваме укаателя към елемента в лист контролата по подаден индекс
			CTypeElements* pElement = (CTypeElements*)(GetItemData(nIndex));

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
	int AddDataToElementListCtr(const CTypeElements& oTypeElement)
	{
		//Указател към елемента
		CTypeElements* pElement = new CTypeElements;
		*pElement = oTypeElement;

		if (pElement == nullptr)
		{
			return -1;
		}

		//Правим структура, като задаваме индекс(последния), текст в първа колона и параметър(указател към структура)
		LVITEM lvItem = { 0 };
		lvItem.mask = LVIF_TEXT | LVIF_PARAM;
		lvItem.iItem = GetItemCount();
		//lvItem.pszText = pCity->szRegion;
		lvItem.lParam = (LPARAM)pElement;

		//Добавяме елемент
		return InsertItem(&lvItem);
	}

	BOOL DeleteAllElementsListCtr()
	{
		//Преход през всеки елемент от контролата като започваме от последния
		for (int nIndex = GetItemCount(); nIndex >= 0; --nIndex)
		{
			//Премахване на всеки елемент
			if (!DeleteElementListCtr(nIndex))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	BOOL AddElemenInListCtr(const int nIndex, const CArray<CString, CString>& strTypeElementArray)
	{

		//Добавяме елементите от сткуктурата в таблиците
		for (INT_PTR nNumbersOfColsToAdd = 0; nNumbersOfColsToAdd < strTypeElementArray.GetCount(); nNumbersOfColsToAdd++)
		{

			if (!SetItemText(nIndex, nNumbersOfColsToAdd, strTypeElementArray.GetAt(nIndex)))
			{
				return FALSE;
			}
		}
		return TRUE;
	}
};
