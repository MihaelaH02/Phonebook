#pragma once
#include <atldbcli.h>
#include <typeinfo>

#include "Session.h"
#include "TableDataArray.h"

/////////////////////////////////////////////////////////////////////////////
// CBaseTable


/// <summary>
/// Базов клас изпълняващ CRUD операции с базата данни
/// </summary>
/// <typeparam name="CStructAccessor">Клас Accessor за съотватната дискова структура </typeparam>
/// <typeparam name="CStruct">Дискова структура</typeparam>
template<class CStructAccessor, class CStruct>
class CBaseTable : protected CCommand<CAccessor<CStructAccessor>> 
{
public:
// Constants
// ----------------
	

// Constructor / Destructor
// ----------------
	CBaseTable() {};
	~CBaseTable() {};

// Methods
// ----------------

	/// <summary>
	/// Метод за извеждане на всички записи от таблица, като резултата се записва с масив
	/// </summary>
	/// <param name="oTableArray">Параметър масив за съответната дискова структура</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectAll(CTableDataArray<CStruct>& oTableArray)
	{
		//Отваряне на нова на сесията
		if (!m_oSession.OpenSession())
		{
			return FALSE;
		}

		//Извършване на заявка за селект на всички записи
		CString strQuery;
		strQuery.Format(_T("SELECT * FROM %s"), GetTableName());

		//Изпълниение на заявката
		HRESULT hResult = Open(m_oSession.GetSession(), strQuery);
		if (FAILED(hResult))
		{
			DoMesgStatusExit(_T("Error executing query.\n Error: %d. Query: %s"), hResult, strQuery);
			return FALSE;
		}

		//Обхождане на всички записи
		while ((hResult = MoveNext()) == S_OK)
		{
			//Добавяне на елемент към масива с дании от таблицата
			CStruct recStruct = GetRowData();
			oTableArray.AddElement(recStruct);
		}

		if (hResult != DB_S_ENDOFROWSET)
		{
			DoMesgStatusExit(_T("Failed to read data from database!\n Error: %d"), hResult);
			return FALSE;
		}

		//Затваряне на заявката и сесията
		DoMesgStatusExit();
		return TRUE;
	};

	/// <summary>
	/// Метод за извеждане на запис по подадено ИД
	/// </summary>
	/// <param name="lID">Параметър за ИД, по който ще се търси запис</param>
	/// <param name="recStruct">Параметър за съответната дискова структура</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectWhereID(const long lID, CStruct& recStruct)
	{
		//Отваряне на нова на сесията
		if (!m_oSession.OpenSession())
		{
			return FALSE;
		}

		//Изпълнение на заявка
		CString strQuery;
		strQuery.Format(_T("SELECT * FROM %s WHERE [ID] = %d"), GetTableName(), lID);
		HRESULT hResult = Open(m_oSession.GetSession(), strQuery);
		if (FAILED(hResult))
		{
			DoMesgStatusExit(_T("Error executing query.\n Error: %d. Query: %s"), hResult, strQuery);
			return FALSE;
		}

		//Проверка за селектиран запис
		if (MoveFirst() != S_OK)
		{
			DoMesgStatusExit(_T("Failed to read data from database!\n Error: %d"), hResult);
			return FALSE;
		}
		recStruct = GetRowData();

		//Затваряне на заявката и сесията
		DoMesgStatusExit();
		return TRUE;
	};

	/// <summary>
	/// Метод за модификация на запис по подадено ИД
	/// </summary>
	/// <param name="lID">Параметър за ИД, по който ще се прави редакция на запис</param>
	/// <param name="recStruct">Параметър за съответната дискова структура</param>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL UpdateWhereID(const long lID, const CStruct& recStruct)
	{
		//Отваряне на нова сесия
		if (!m_oSession.OpenSession())
		{
			return FALSE;
		}

		//Селектираме търсения запис
		CString strQuerySelectWithNolock;
		strQuerySelectWithNolock.Format(_T("SELECT * FROM %s WITH(NOLOCK) WHERE [ID] = %d"), GetTableName(), lID);

		//Извършваме заявка
		HRESULT hResult = Open(m_oSession.GetSession(), strQuerySelectWithNolock);
		if (FAILED(hResult))
		{
			DoMesgStatusExit(_T("Error executing query.\n Error: %d. Query: %s"), hResult, strQuerySelectWithNolock);
			return FALSE;
		}

		//Вземаме първия запис
		if (MoveFirst() != S_OK)
		{
			DoMesgStatusExit(_T("Fail to select data.\n Error: %d."), hResult);
			return FALSE;
		}

		//Вземаме стойността от колоната за модификация и затваряме заявката
		long lReadedUpdateCounterWithNolock = GetUpdateCounter();
		Close();

		//Начало на транзакция
		hResult = m_oSession.GetSession().StartTransaction();
		if (FAILED(hResult))
		{
			DoMesgStatusExit(_T("Failed to start transaction!.\n Error: %d. Query: %s"), hResult);
			return FALSE;
		}
		//Селект на записа със заключване
		CString strQuerySelectWithUplocl;
		strQuerySelectWithUplocl.Format(_T("SELECT * FROM %s WITH(UPDLOCK) WHERE [ID] = %d"), GetTableName(), lID);

		//Настройка на rowSet
		CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
		oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
		oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
		oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);

		//Извършване на заявка
		hResult = Open(m_oSession.GetSession(), strQuerySelectWithUplocl, &oUpdateDBPropSet);
		if (FAILED(hResult))
		{
			m_oSession.GetSession().Abort();
			DoMesgStatusExit(_T("Error executing query.\n Error: %d. Query: %s"), hResult, strQuerySelectWithNolock);
			return FALSE;
		}

		//Вземаме резултата от селекта
		hResult = MoveFirst();
		if (FAILED(hResult))
		{
			m_oSession.GetSession().Abort();
			DoMesgStatusExit(_T("Fail to select data.\n Error: %d."), hResult);
			return FALSE;
		}

		//Проверка дали настоящия Update_counter е със същата стойност като преди заключването 
		if (lReadedUpdateCounterWithNolock != GetUpdateCounter())
		{
			m_oSession.GetSession().Abort();
			DoMesgStatusExit(_T("Failed to commit transaction!"));
			return FALSE;
		}

		//Променяме данните в селектирания запис
		SetRowData(recStruct);

		//Увеличаване на брояча
		IncrementUpdateCounter();

		//Извършване на редакция
		hResult = SetData(GLOBAL_ACCESSORS_INFO_ACCESSOR_FOR_DATA);
		if (FAILED(hResult))
		{
			m_oSession.GetSession().Abort();
			DoMesgStatusExit(_T("Failed to update data!\n Error: %d."), hResult);
			return FALSE;
		}

		//Запазване на промените, затваряне на заявката и сесията
		hResult = m_oSession.GetSession().Commit();
		if (FAILED(hResult))
		{
			m_oSession.GetSession().Abort();
			DoMesgStatusExit(_T("Failed to commit data!\n Error: % d."), hResult);
			return FALSE;
		}
		DoMesgStatusExit(_T("Successfuly update data!"));
		return TRUE;
	};
	
	/// <summary>
	/// Метод за добавяне на запис
	/// </summary>
	/// <param name="recStruct">Параметър за съответната дискова стурктура</param>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL Insert(CStruct& recStruct)
	{
		//Отваряне на нова сесия
		if (!m_oSession.OpenSession())
		{
			return FALSE;
		}

		//Селектираме таблицата
		CString strQuerySelect;
		strQuerySelect.Format(_T("SELECT * FROM %s WHERE 1 = 0"), GetTableName());

		//Настройка на rowSet
		CDBPropSet oInsertDBPropSet(DBPROPSET_ROWSET);
		oInsertDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		oInsertDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
		oInsertDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
		oInsertDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_INSERT);

		//Изпълняваме заявката
		HRESULT hResult = Open(m_oSession.GetSession(), strQuerySelect, &oInsertDBPropSet);
		if (FAILED(hResult))
		{
			DoMesgStatusExit(_T("Failed to select data from database.\n Error: %d"), hResult);
			return FALSE;
		}

		//Задаваме данни, които ще се добавят към таблицата
		SetRowData(recStruct);

		//Добавяме нов запис
		hResult = __super::Insert(GLOBAL_ACCESSORS_INFO_ACCESSOR_FOR_DATA,TRUE);
		if (FAILED(hResult))
		{
			DoMesgStatusExit(_T("Failed to insert data!\n Error: %d"), hResult);
			return FALSE;	
		}

		//Залеждаме данни в буфера - аксесор
		if (MoveFirst() != S_OK)
		{
			DoMesgStatusExit(_T("Failed to read id for row!\n Error: %d"), hResult);
			return FALSE;
		}
		recStruct.lId = GetRowId();
	
		//Затваряме заявката и сесията
		DoMesgStatusExit(_T("Successfuly insert data!"));
		return TRUE;
	};

	/// <summary>
	/// Метод за изтриване на запис по ИД
	/// </summary>
	/// <param name="lID">Параметър за ИД, по който ще се изтрива запис</param>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL DeleteWhereID(const long lID)
	{
		//Отваряне на нова сесия
		if (!m_oSession.OpenSession())
		{
			return FALSE;
		}

		//Селектираме търсения запис
		CString strQuerySelect;
		strQuerySelect.Format(_T("SELECT * FROM %s WHERE [ID] = %d"), GetTableName(), lID);

		//Настройка на rowSet
		CDBPropSet oDeleteDBPropSet(DBPROPSET_ROWSET);
		oDeleteDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		oDeleteDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
		oDeleteDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
		oDeleteDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_DELETE);

		//Изпълняваме заявката
		HRESULT hResult = Open(m_oSession.GetSession(), strQuerySelect, &oDeleteDBPropSet);
		if (FAILED(hResult))
		{
			DoMesgStatusExit(_T("Failed to select data from database!\n  Error: %d"), hResult);
			return FALSE;
		}

		//Селектираме записа
		if (MoveFirst() != S_OK)
		{
			DoMesgStatusExit(_T("Failed to read data from database!\n Error: %d"), hResult);
			return FALSE;
		}

		//Изтриване на записа
		hResult = __super::Delete();
		if ((hResult))
		{
			DoMesgStatusExit(_T("Fail to delete data!\n This row is conected to another record in database!\n Error: %d"), hResult);
			return FALSE;
		}

		if (FAILED(hResult))
		{
			DoMesgStatusExit(_T("Failed to delete data!\n Error: %d"), hResult);
			return FALSE;
		}

		//Затваряме заявката и сесията
		DoMesgStatusExit(_T("Successfuly delete data!"));
		return TRUE;
	};

	/// <summary>
	/// 
	/// </summary>
	/// <param name="oTableDataArray"></param>
	/// <returns></returns>
	BOOL InsertAll(CTableDataArray<CStruct>& oTableDataArray)
	{
		//транзакции и сесия
		for (INT_PTR nIndex = 0; nIndex < oTableDataArray.GetCount(); nIndex++)
		{
			CStruct* recStruct = oTableDataArray.GetAt(nIndex);
			if (recStruct == nullptr)
			{
				DoMesgStatusExit(_T("Error all selected data!"));
				return FALSE;
			}
			Insert(*recStruct);
		}
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="oTableDataArray"></param>
	/// <returns></returns>
	BOOL UpdateAll(const CTableDataArray<CStruct>& oTableDataArray)
	{
		//транзакции и сесия
		for (INT_PTR nIndex = 0; nIndex < oTableDataArray.GetCount(); nIndex++)
		{
			CStruct* recStruct = oTableDataArray.GetAt(nIndex);
			if (recStruct == nullptr)
			{
				DoMesgStatusExit(_T("Error all selected data!"));
				return FALSE;
			}
			UpdateWhereID(recStruct->lId, *recStruct);
		}
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="oTableDataArray"></param>
	/// <returns></returns>
	BOOL DeleteAll(const CTableDataArray<CStruct>& oTableDataArray)
	{
		//транзакции и сесия
		for (INT_PTR nIndex = 0; nIndex < oTableDataArray.GetCount(); nIndex++)
		{
			CStruct* recStruct = oTableDataArray.GetAt(nIndex);
			if (recStruct == nullptr)
			{
				DoMesgStatusExit(_T("Error all selected data!"));
				return FALSE;
			}
			DeleteWhereID(recStruct->lId);
		}
	}

private:
	//Методи, които ще се имплементират от наследниците
	
	/// <summary>
	/// Достъп до името на таблицата
	/// </summary>
	/// <returns>Връща стирнг името на таблицата</returns>
	virtual CString GetTableName() = 0;

	/// <summary>
	/// Достъп до записа в аксесора
	/// </summary>
	/// <returns>Връща данните от аксесора</returns>
	virtual CStruct& GetRowData() = 0;

	/// <summary>
	/// Задава данни за запис
	/// </summary>
	/// <param name="oStruct">Променлива, която да укаже данните за запис в таблицата</param>
	virtual void SetRowData(const CStruct& oStruct) = 0;

	/// <summary>
	/// Достъп до ИД на записа
	/// </summary>
	/// <returns>Връща ИД на записа</returns>
	virtual long GetRowId() = 0;

	/// <summary>
	/// Увеличава брояча за модификация на запис от таблицата
	/// </summary>
	virtual void IncrementUpdateCounter() = 0;

	/// <summary>
	/// Достъп до брояча за модификация на запис от таблицата
	/// </summary>
	/// <returns>Връща стойността на боряча за модификация </returns>
	virtual long GetUpdateCounter() = 0;


// Overrides
// ----------------

	/// <summary>
	/// Метод, който отговаря за сигурно прекратяване на операция
	/// </summary>
	/// <param name="strErrorText">Параметър за CString съобщение за грешка</param>
	void DoMesgStatusExit(CString strErrorText = _T(""), HRESULT = S_OK, CString strQuery = _T(""))
	{
		if (!strErrorText.IsEmpty())
		{
			CString strMessage;
			strMessage.Format(strErrorText);
			AfxMessageBox(strMessage);
		}
		Close();
		m_oSession.CloseSession();
	};

// Members
// ----------------

	/// <summary>
	/// Член променлива, която отговаря за сесията
	/// </summary>
	CInitializeSession m_oSession;
};

