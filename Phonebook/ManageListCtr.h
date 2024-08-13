#pragma once
#include "afxdialogex.h"
#include "TypePtrDataArray.h"
#include "RowDataListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CListCtrlManager

/// <summary>
/// Клас, който управлява всички опирации с лист контрола
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

public:
	/// <summary>
	/// Метод за достъп до селектиран елемент
	/// </summary>
	/// <param name="lscListCtr">Параметър за лист контрола</param>
	/// <returns>Връща се индекса на селектирания елемент</returns>
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

	/// <summary>
	/// Метод за добавяне или редактиране на елемент
	/// </summary>
	/// <param name="lscListCtr">Параметър за лист контрола</param>
	/// <param name="oRowData">Параметър за клас, който съдържа необходимите данни за елемент</param>
	/// <param name="nIndexExistingElement">Параметър за подаден индект на съществуващ елемент</param>
	/// <returns>Връща TRUE при успех и FALSE при открита грешка</returns>
	BOOL AddOrEditElement(CListCtrl& lscListCtr, const CRowDataListCtrl<CTypeElements>& oRowData, int nIndexExistingElement = -1)
	{		
		// Добавяме DATA към нов или вече съдържащ се елемент
		int nIndex = AddDataToElement(lscListCtr, oRowData.GetData(), nIndexExistingElement);
		if (nIndex == -1)
		{
			return FALSE;
		}

		//Добавяме данните за визуализация към индекса на елемента
		if (!AddElement(lscListCtr, nIndex, oRowData.GetDisplayData()))
		{
			return FALSE;
		}

		return TRUE;
	}

	/// <summary>
	/// Метод за достъп до елемент
	/// </summary>
	/// <param name="lscListCtr">Параметър за лист контрола</param>
	/// <param name="nIndexItem">Параметър за индекс на елемент</param>
	/// <returns>Връща указател към открит елемент или nullptr при липса</returns>
	CTypeElements* GetElementByIndex(CListCtrl& lscListCtr, const int nIndexItem)
	{
		//Проверка за валиден указател
		if (nIndexItem == -1)
		{
			return nullptr;
		}

		//Достъпваме обекта по подадения индекс в лист контролата
		CTypeElements* pElement = (CTypeElements*)(lscListCtr.GetItemData(nIndexItem));

		//Връщаме елемент
		return pElement;
	}

	/// <summary>
	/// Метод, който запълва лист контролата с елементи от ресурс
	/// </summary>
	/// <param name="lscListCtr">Параметър за лист контрола</param>
	/// <param name="oRowsDataArray">Параметър за ресурс - масив</param>
	/// <returns>Връща TRUE при успех и FALSE при открита грешка</returns>
	BOOL LoadDataFromResource(CListCtrl& lscListCtr, const CTypedPtrDataArray<CRowDataListCtrl<CTypeElements>>& oRowsDataArray)
	{
		//Проверка за налични елементи
		if (lscListCtr.GetItemCount() > 0)
		{
			//Изтриваве на всички останали данни
			if (!lscListCtr.DeleteAllItems())
			{
				return FALSE;
			}
		}

		//Добавяме данните от подаден масив в лист контролата
		for (INT_PTR lIndex = 0; lIndex < oRowsDataArray.GetCount(); ++lIndex)
		{
			//Достъп до текущ елемент от масива с данни
			CRowDataListCtrl<CTypeElements>* pElement = oRowsDataArray.GetAt(lIndex);

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

	/// <summary>
	/// Метод за сравнение дали всички данни от ресурса за добавени
	/// </summary>
	/// <param name="lscListCtr">Параметър за лист контрола</param>
	/// <param name="oResourseSize">Параметър за размер на ресурса - масив</param>
	/// <returns>Връща TRUE при съвпадение и FALSE при разминаване</returns>
	BOOL IsAllDataLoadFromResourse(CListCtrl& lscListCtr, const INT_PTR lResourseSize)
	{
		//Проверка дали броя на елементите, в лест контролата, е еднакъв с този в документа
		if (lscListCtr.GetItemCount() != lResourseSize)
		{
			return FALSE;
		}
		return TRUE;
	}
	
	/// <summary>
	/// Метод за премахване на елемент от лист контролата
	/// </summary>
	/// <param name="lscListCtr">Параметър за лист контрола</param>
	/// <param name="nIndex">Параметър за подаден индект на съществуващ елемент</param>
	/// <returns>Връща TRUE при успех и FALSE при открита грешка</returns>
	BOOL RemoveElement(CListCtrl& lscListCtr, int nIndex)
	{
		if (nIndex == -1)
		{
			return FALSE;
		}

		//Досъпваме укаателя към елемента в лист контролата по подаден индекс
		CTypeElements* pElement = (CTypeElements*)(lscListCtr.GetItemData(nIndex));

		//Проверка за нулев указател
		if (pElement == nullptr)
		{
			return FALSE;
		}

		//Освобождаваме заделеното място
		delete pElement;

		//Изтриваме елемента от контролата
		if (!lscListCtr.DeleteItem(nIndex))
		{
			return FALSE;
		}
		return TRUE;
	}

	/// <summary>
	/// Метод за достъп до селектиран елемент
	/// </summary>
	/// <param name="lscListCtr">Параметър за лист контрола</param>
	/// <returns>Връща указател към селектиран елемент или nullptr при липса</returns>
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
	/// <summary>
	/// Метод за добавяне на DATA към елемент
	/// </summary>
	/// <param name="lscListCtr">Параметър за лист контрола</param>
	/// <param name="oTypeElement">Елемент, който ще се добавя</param>
	/// <param name="nIndex"><Параметър за индект, ако е подаден/param>
	/// <returns>Връща се индекса на добавен елемент, при редакция - параметъра за индекс или -1 при неуспех</returns>
	int AddDataToElement(CListCtrl& lscListCtr, const CTypeElements& oTypeElement, int nIndex = -1)
	{
		//Прверка за подаден индект - редакция
		if (nIndex != -1)
		{
			//Редакция на дата при съществуващ елемент
			return EditDataToElement(lscListCtr, oTypeElement, nIndex);
		}

		//Указател към елемента
		CTypeElements* pElement = new CTypeElements(oTypeElement);

		//Проверка за празен указател
		if (pElement == nullptr)
		{
			return -1;
		}

		//Ако нямаме подаден индекс на елемент да се вземе последния от лист контролата
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

	/// <summary>
	/// Метод за редакиця на DATA към елемент
	/// </summary>
	/// <param name="lscListCtr">Параметър за лист контрола</param>
	/// <param name="oTypeElement">Елемент, с който ще се редактира</param>
	/// <param name="nIndex"><Параметър за индект, по който ще се редактира/param>
	/// <returns>Връща се параметъра за индекс или -1 при неуспех</returns>
	int EditDataToElement(CListCtrl& lscListCtr, const CTypeElements& oTypeElement, int nIndex)
	{
		if (nIndex == -1)
		{
			return -1;
		}

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

	/// <summary>
	/// Метод за добавяне на визуални данни съм елемент в лист контролата
	/// </summary>
	/// <param name="lscListCtr">Параметър за лист контрола</param>
	/// <param name="nIndex"><Параметър за индекс на елемент в лист контролата/param>
	/// <param name="strArrayWithDataToDisplay">Парметър за масив с визуални данни</param>
	/// <returns>Връща TRUE при успех и FALSE при открита грешка</returns>
	BOOL AddElement(CListCtrl& lscListCtr, const int nIndex, const CTypedPtrDataArray<CString>& strArrayWithDataToDisplay)
	{
		if (nIndex == -1)
		{
			return FALSE;
		}

		//Добавяме елементите от масива с визуални данни в колоните на лист контролата
		for (INT_PTR nNumbersOfColsToAdd = 0; nNumbersOfColsToAdd < strArrayWithDataToDisplay.GetCount(); nNumbersOfColsToAdd++)
		{
			//Достъп до текущ стрингов елемент в масива
			CString* pDataToDisplayInCol = strArrayWithDataToDisplay.GetAt(nNumbersOfColsToAdd);
			if (pDataToDisplayInCol == nullptr)
			{
				return FALSE;
			}

			//Добавяне на текст в текуща колона от лист контролата
			if (!lscListCtr.SetItemText(nIndex, (int)nNumbersOfColsToAdd, *pDataToDisplayInCol))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	/// <summary>
	/// Метод за прмахване на всички елементи от лист контролата
	/// </summary>
	/// <param name="lscListCtr">Параметър за лист контрола</param>
	/// <param name="lscListCtr">Параметър за лист контрола</param>
	BOOL RemoveAllElements(CListCtrl& lscListCtr)
	{
		//Обход на всеки елемент от контролата, като започваме от последния
		for (int nIndex = lscListCtr.GetItemCount(); nIndex >= 0; --nIndex)
		{
			//Премахване на елемент
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
