#pragma once
#include <atldbcli.h>
#include <typeinfo>

#include "DatabaseTransactionManager.h"
#include "TableDataArray.h"
#include "DatabaseQueryBuilder.h"

#define MSG_ERROR_EXEC_DATABASE_QUERY _T("Error executing query.\n Error: %d. Query: %s")
#define MSG_FAIL_READ_DATA_FROM_DATABASE _T("Failed to read data from database!\n Error: %d")
#define MSG_FAIL_DO_DATABASE_OPERATION _T("Failed to do operations/s!\n Error: %d.")
#define MSG_FAIL_EXEC_DATABASE_TRANSACTION _T("Faild in executing transaction! Error: %d")
#define MSG_FAIL_IN_DATABASE_DELETE_DATA_IS_CONNECTED_TO_RECORD _T("Fail to delete data!\n This row is conected to another record in database!\n Error: %d")


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
// Constants
// ----------------
	

// Constructor / Destructor
// ----------------

public:
	CBaseTable() 
	{
		//Отваряме нова сесия
		m_pSessionManager = new CInitializeSession();
		m_bIsSessonOwner = TRUE;
	}

/// <param name="oDatabaseTransactionManager">Указател към клас мениджър на сесии, който вече е отворил сесия</param>
	CBaseTable(CInitializeSession* pInitializeSession)
	{
		//Проверка за подадена сесия
		if (pInitializeSession != nullptr)
		{
			m_pSessionManager = pInitializeSession;
			m_bIsSessonOwner = FALSE;
			return;
		}

		//Отваряме нова сесия
		m_pSessionManager = new CInitializeSession();
		m_bIsSessonOwner = TRUE;
	};

	~CBaseTable()
	{
		//Проверка дали сесията е отворена в този клас
		if (!m_bIsSessonOwner)
		{
			return;
		}

		//Проверка за отворена сесия
		if (m_pSessionManager->IsSessionOpen())
		{
			m_pSessionManager->CloseSession();
		}

		//Почистване на заделената памет
		delete m_pSessionManager;
	};

// Methods
// ----------------
public:
	/// <summary>
	/// Метод за извеждане на всички записи от таблица, като резултата се записва в масив
	/// </summary>
	/// <param name="oTableArray">Параметър масив за съответната дискова структура</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectAll(CTableDataArray<CStruct>& oTableArray)
	{
		CDatabaseQueryBuilder oDatabaseQueryBuilder;
		//Извършване на заявка за селект на всички записи от съответната таблица
		CString strQuery = oDatabaseQueryBuilder
							.SelectFromTable(GetTableName())
							.Build();
												
		//Изпълниение на заявката
		HRESULT hResult = Open(m_pSessionManager->GetSession(), strQuery);
		if (FAILED(hResult))
		{
			CloseSafeQuery(MSG_ERROR_EXEC_DATABASE_QUERY, hResult, strQuery);
			return FALSE;
		}

		//Обхождане на всички записи
		while ((hResult = MoveNext()) == S_OK)
		{
			//Добавяне на елемент към масива с дании от таблицата
			CStruct recStruct = GetSelectedRowData();
			oTableArray.AddElement(recStruct);
		}

		//Проверка за всичко прочетено от ролсета
		if (hResult != DB_S_ENDOFROWSET)
		{
			CloseSafeQuery(MSG_FAIL_READ_DATA_FROM_DATABASE, hResult);
			return FALSE;
		}

		//Затваряне на заявката
		CloseSafeQuery();
		return TRUE;
	}

	/// <summary>
	/// Метод за извеждане на записи по подадено ИД
	/// </summary>
	/// <param name="lID">Параметър за ИД, по който ще се търси запис</param>
	/// <param name="oTableArray">Параметър за масив, в който ще се съхраняват селектираните данни</param>
	/// <param name="strFromToSelect">Параметър за колона, по която ще се търсят записи, по подразбиране взема колона за ИД на таблица</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectWhereID(const long lID, CTableDataArray<CStruct>& oTableArray, CString strColFromToSelect = GetIdentityCol())
	{
		//Изпълнение на заявка
		CDatabaseQueryBuilder oDatabaseQueryBuilder;

		CString strQuery = oDatabaseQueryBuilder
			.SelectFromTable(GetTableName())
			.WhereEqualLong(strColFromToSelect, lID)
			.Build();

		//Проверка за успех
		HRESULT hResult = Open(m_pSessionManager->GetSession(), strQuery);
		if (FAILED(hResult))
		{
			CloseSafeQuery(MSG_ERROR_EXEC_DATABASE_QUERY, hResult, strQuery);
			return FALSE;
		}

		//Достъп до селектираните данни
		while ((hResult = MoveNext()) == S_OK)
		{
			CStruct recStruct = GetSelectedRowData();
			oTableArray.AddElement(recStruct);
		}

		//Проверка за всичко прочетено от ролсета
		if (hResult != DB_S_ENDOFROWSET)
		{
			CloseSafeQuery(MSG_FAIL_READ_DATA_FROM_DATABASE, hResult);
			return FALSE;
		}

		//Затваряне на заявката
		CloseSafeQuery();
		return TRUE;
	}

	/// <summary>
	/// Метод за извеждане на запис по подадено ИД
	/// </summary>
	/// <param name="lID">Параметър за ИД, по който ще се търси запис</param>
	/// <param name="recCity">Параметър за структура, в която ще се съхранява открития запис</param>
	/// <param name="strFromToSelect">Параметър за колона, по която ще се търсят записи, по подразбиране взема колона за ИД на таблица</param>
	/// <returns></returns>
	BOOL SelectWhereID(const long lID, CStruct& recCity, CString strFromToSelect = GetIdentityCol())
	{
		CTableDataArray<CStruct> oCStructWithResultsArray;
		if (!SelectWhereID(lID, oCStructWithResultsArray, strFromToSelect))
		{
			return FALSE;
		}

		if (oCStructWithResultsArray.GetSize() != 1)
		{
			return FALSE;
		}
		CStruct* pStruct = oCStructWithResultsArray.GetAt(0);
		if (pStruct == nullptr)
		{
			return FALSE;
		}

		recCity = *pStruct;
		return TRUE;
	}

	/// <summary>
	/// Метод за модификация на запис по подадено ИД
	/// </summary>
	/// <param name="lID">Параметър за ИД, по който ще се прави редакция на запис</param>
	/// <param name="recStruct">Параметър за съответната дискова структура</param>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL UpdateWhereID(const long lID, const CStruct& recStruct)
	{
		CDatabaseQueryBuilder oDatabaseQueryBuilder;
		//Извършване на заявка
		CString strQuery = oDatabaseQueryBuilder
			.SelectFromTable(GetTableName())
			.NoLock()
			.WhereEqualLong(GetIdentityCol(), lID)
			.Build();

		//Извършване на заявка
		HRESULT hResult = Open(m_pSessionManager->GetSession(), strQuery);
		if (FAILED(hResult))
		{
			CloseSafeQuery(MSG_ERROR_EXEC_DATABASE_QUERY, hResult, strQuery);
			return FALSE;
		}

		//Достъп до първия запис
		if (MoveFirst() != S_OK)
		{
			CloseSafeQuery(MSG_FAIL_READ_DATA_FROM_DATABASE, hResult);
			return FALSE;
		}

		//Запазваме стойността от колоната за модификация и затваряме заявката
		long lReadedUpdateCounterWithNolock = GetSelectedRowUpdateCounter();
		Close();

		//Инстанция на клас, коюто манипулира транзакции
		CDatabaseTransactionManager oDatabaseInternalTransaction;
		//Начало на транзакция
		if (!oDatabaseInternalTransaction.OpenSafeTransaction())
		{
			CloseSafeQuery(MSG_FAIL_EXEC_DATABASE_TRANSACTION, hResult);
			return FALSE;
		}

		//Извършване на заявка
		CString strQueryWithUpdLock = oDatabaseQueryBuilder
			.SelectFromTable(GetTableName())
			.UpdLock()
			.WhereEqualLong(GetIdentityCol(), lID)
			.Build();

		//Настройка на rowSet
		CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
		oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
		oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
		oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);

		//Достъп до новата сесия на транзакцията
		CInitializeSession* pInitializeSession = oDatabaseInternalTransaction.GetSession();
		if (pInitializeSession == nullptr)
		{
			oDatabaseInternalTransaction.CloseSafeTransactoin(TRUE);
			CloseSafeQuery(MSG_FAIL_EXEC_DATABASE_TRANSACTION);
			return FALSE;
		}

		//Извършване на заявка
		hResult = Open(pInitializeSession->GetSession(), strQueryWithUpdLock, &oUpdateDBPropSet);
		if (FAILED(hResult))
		{
			oDatabaseInternalTransaction.CloseSafeTransactoin(TRUE);
			CloseSafeQuery(MSG_ERROR_EXEC_DATABASE_QUERY, hResult, strQueryWithUpdLock);
			return FALSE;
		}

		//Вземаме резултата от заявката
		hResult = MoveFirst();
		if (FAILED(hResult))
		{
			oDatabaseInternalTransaction.CloseSafeTransactoin(TRUE);
			CloseSafeQuery(MSG_FAIL_READ_DATA_FROM_DATABASE, hResult);
			return FALSE;
		}

		//Проверка дали настоящия Update_counter е със същата стойност като преди заключването 
		if (lReadedUpdateCounterWithNolock != GetSelectedRowUpdateCounter())
		{
			oDatabaseInternalTransaction.CloseSafeTransactoin(TRUE);
			CloseSafeQuery(MSG_FAIL_DO_DATABASE_OPERATION);
			return FALSE;
		}

		//Променяме данните в селектирания запис
		SetNewDataToSelectedRow(recStruct);

		//Увеличаване на брояча
		IncrementUpdateCounterOfSelectedRow();

		//Извършване на редакция
		hResult = SetData(GLOBAL_ACCESSORS_INFO_ACCESSOR_FOR_DATA);
		if (FAILED(hResult))
		{
			oDatabaseInternalTransaction.CloseSafeTransactoin(TRUE);
			CloseSafeQuery(MSG_FAIL_DO_DATABASE_OPERATION, hResult);
			return FALSE;
		}

		oDatabaseInternalTransaction.CloseSafeTransactoin();
		CloseSafeQuery();
		return TRUE;
	}
	
	/// <summary>
	/// Метод за добавяне на запис
	/// </summary>
	/// <param name="recStruct">Параметър за съответната дискова стурктура</param>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL Insert(CStruct& recStruct)
	{
		CDatabaseQueryBuilder oDatabaseQueryBuilder;
		//Извършване на заявка
		CString strQuery = oDatabaseQueryBuilder
							.SelectFromTable(GetTableName())
							.WhereNothing()
							.Build();

		//Настройка на rowSet
		CDBPropSet oInsertDBPropSet(DBPROPSET_ROWSET);
		oInsertDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		oInsertDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
		oInsertDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
		oInsertDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_INSERT);

		//Изпълнение на заявка
		HRESULT hResult = Open(m_pSessionManager->GetSession(), strQuery, &oInsertDBPropSet);
		if (FAILED(hResult))
		{
			CloseSafeQuery(MSG_FAIL_READ_DATA_FROM_DATABASE, hResult);
			return FALSE;
		}

		//Задаваме данни, които ще се добавят към таблицата
		SetNewDataToSelectedRow(recStruct);

		//Добавяме нов запис
		hResult = __super::Insert(GLOBAL_ACCESSORS_INFO_ACCESSOR_FOR_DATA,TRUE);
		if (FAILED(hResult))
		{
			CloseSafeQuery(MSG_FAIL_DO_DATABASE_OPERATION, hResult);
			return FALSE;	
		}

		//Зареждаме данни в буфера - аксесор
		if (MoveFirst() != S_OK)
		{
			CloseSafeQuery(MSG_FAIL_READ_DATA_FROM_DATABASE, hResult);
			return FALSE;
		}
		recStruct.lId = GetSelectedRowId();
	
		//Затваряме заявката
		CloseSafeQuery();
		return TRUE;
	}

	/// <summary>
	/// Метод за изтриване на запис по ИД
	/// </summary>
	/// <param name="lID">Параметър за ИД, по който ще се изтрива запис</param>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL DeleteWhereID(const long lID)
	{
		CDatabaseQueryBuilder oDatabaseQueryBuilder;
		//Извършване на заявка
		CString strQuery = oDatabaseQueryBuilder
			.SelectFromTable(GetTableName())
			.WhereEqualLong(GetIdentityCol(), lID)
			.Build();

		//Настройка на rowSet
		CDBPropSet oDeleteDBPropSet(DBPROPSET_ROWSET);
		oDeleteDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		oDeleteDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
		oDeleteDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
		oDeleteDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_DELETE);

		//Изпълняваме заявката
		HRESULT hResult = Open(m_pSessionManager->GetSession(), strQuery, &oDeleteDBPropSet);
		if (FAILED(hResult))
		{
			CloseSafeQuery(MSG_ERROR_EXEC_DATABASE_QUERY, hResult);
			return FALSE;
		}

		//Селектираме записа
		if (MoveFirst() != S_OK)
		{
			CloseSafeQuery(MSG_FAIL_READ_DATA_FROM_DATABASE, hResult);
			return FALSE;
		}

		//Изтриване на записа
		hResult = __super::Delete();
		if ((hResult))
		{
			CloseSafeQuery(MSG_FAIL_IN_DATABASE_DELETE_DATA_IS_CONNECTED_TO_RECORD, hResult);
			return FALSE;
		}

		if (FAILED(hResult))
		{
			CloseSafeQuery(MSG_FAIL_DO_DATABASE_OPERATION, hResult);
			return FALSE;
		}

		//Затваряме заявката
		CloseSafeQuery();
		return TRUE;
	}

	/// <summary>
	/// Метод за добавяне на група обекти
	/// </summary>
	/// <param name="oTableDataArray">Масив с група обекти за добавяне</param>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL InsertAll(const CTableDataArray<CStruct>& oTableDataArray)
	{
		//транзакции и сесия
		for (INT_PTR nIndex = 0; nIndex < oTableDataArray.GetCount(); nIndex++)
		{
			CStruct* recStruct = oTableDataArray.GetAt(nIndex);
			if (recStruct == nullptr)
			{
				CloseSafeQuery(MSG_FAIL_DO_DATABASE_OPERATION);
				return FALSE;
			}

			if (!Insert(*recStruct))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	/// <summary>
	/// Метод за редакция на група обекти
	/// </summary>
	/// <param name="oTableDataArray">Масив с група обекти за редакция</param>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL UpdateAll(const CTableDataArray<CStruct>& oTableDataArray)
	{
		//транзакции и сесия
		for (INT_PTR nIndex = 0; nIndex < oTableDataArray.GetCount(); nIndex++)
		{
			CStruct* recStruct = oTableDataArray.GetAt(nIndex);
			if (recStruct == nullptr)
			{
				CloseSafeQuery(MSG_FAIL_DO_DATABASE_OPERATION);
				return FALSE;
			}
			if (!UpdateWhereID(recStruct->lId, *recStruct))
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	/// <summary>
	/// Метод за изтриване на група обекти
	/// </summary>
	/// <param name="oTableDataArray">Масив с група обекти за изтриване</param>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL DeleteAll(const CTableDataArray<CStruct>& oTableDataArray)
	{
		//транзакции и сесия
		for (INT_PTR nIndex = 0; nIndex < oTableDataArray.GetCount(); nIndex++)
		{
			CStruct* recStruct = oTableDataArray.GetAt(nIndex);
			if (recStruct == nullptr)
			{
				CloseSafeQuery(MSG_FAIL_DO_DATABASE_OPERATION);
				return FALSE;
			}
			if (!DeleteWhereID(recStruct->lId))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

private:
	/// <summary>
	/// Метод бизопасно затваряне на сесия при открита грешка
	/// </summary>
	/// <param name="strErrorText">Параметър за CString съобщение за грешка</param>
	/// <param name="">Параметър за резултат на грешката</param>
	/// <param name="strQuery">Параметър за извършена заявка</param>
	void CloseSafeQuery(CString strErrorText = _T(""), HRESULT hResult = S_OK, CString strQuery = _T(""))
	{
		//При подадено съобщение за грешка да се визуализира 
		if (!strErrorText.IsEmpty())
		{
			CString strMessage;
			strMessage.Format(strErrorText, hResult, strQuery);
			AfxMessageBox(strMessage);
		}

		//Затваряне на заявка
		Close();

		//При открита грешка, провеяваме дали сесията принадлежи на този клас, ако да я затваряме
		if (m_bIsSessonOwner)
		{
			m_pSessionManager->CloseSession();
		}
	}


// Overrides
// ----------------

protected:
	/// <summary>
	/// Метод, който отпределя наименованието на колоната за ИД в таблица
	/// </summary>
	/// <returns></returns>
	static CString GetIdentityCol()
	{
		return _T("ID");
	}

	/// <summary>
	/// Достъп до името на таблицата
	/// </summary>
	/// <returns>Връща стирнг името на таблицата</returns>
	virtual CString GetTableName() = 0;

	/// <summary>
	/// Достъп до селектирания записа в аксесора
	/// </summary>
	/// <returns>Връща данните от аксесора</returns>
	virtual const CStruct& GetSelectedRowData() = 0;

	/// <summary>
	/// Задава данни за селектирания запис
	/// </summary>
	/// <param name="oStruct">Променлива, която да укаже данните за запис в таблицата</param>
	virtual void SetNewDataToSelectedRow(const CStruct& oStruct) = 0;

	/// <summary>
	/// Достъп до ИД на записа
	/// </summary>
	/// <returns>Връща ИД на записа</returns>
	virtual const long GetSelectedRowId() = 0;

	/// <summary>
	/// Увеличава брояча за модификация на селектирания запис
	/// </summary>
	virtual void IncrementUpdateCounterOfSelectedRow() = 0;

	/// <summary>
	/// Достъп до брояча за модификация на селектирания запис
	/// </summary>
	/// <returns>Връща стойността на боряча за модификация </returns>
	virtual const long GetSelectedRowUpdateCounter() = 0;


// Members
// ----------------
private:
	/// <summary>
	/// Член променлива, която отговаря за сесията
	/// </summary>
	CInitializeSession* m_pSessionManager;

	/// <summary>
	/// Член променлива флаг за указване дали сесията, която се използва в класа и принадлежи
	/// </summary>
	BOOL m_bIsSessonOwner;
};