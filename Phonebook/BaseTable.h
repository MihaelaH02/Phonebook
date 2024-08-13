#pragma once
#include <atldbcli.h>
#include <typeinfo>

#include "DatabaseTransactionManager.h"
#include "TypePtrDataArray.h"
#include "DatabaseQueryBuilder.h"
#include "Structures.h"

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

	/// <summary>
	/// Параметризиран контруктор
	/// </summary>
	/// <param name="pInitializeSession">Параметър за обект опериращ със сесии</param>
	CBaseTable(CInitializeSession* pInitializeSession)
	{
		//Проверка за подадена сесия
		if (pInitializeSession != nullptr)
		{
			m_pSessionManager = pInitializeSession;
			m_bIsSessonOwner = false;
			return;
		}

		//Отваряме нова сесия, ако не е била отворена
		m_pSessionManager = new CInitializeSession();
		m_bIsSessonOwner = true;
	};

	~CBaseTable()
	{
		//Проверка дали сесията е принадлежи и е била отворена в този клас
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
	BOOL SelectAll(CTypedPtrDataArray<CStruct>& oTableArray)
	{
		//Инстанция към клас, който констуира заявка
		CDatabaseQueryBuilder oDatabaseQueryBuilder;

		//Извършване на заявка за селект на всички записи от съответната таблица
		CString strQuery = oDatabaseQueryBuilder
			.Select()
			.FromTable(GetTableName())
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
			if (oTableArray.AddElement(recStruct) == -1)
			{
				return FALSE;
			}
		}

		//Проверка дали всичко е прочетено от ролсета
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
	/// <param name="strFromToSelect">Параметър за колона, по която ще се търсят записи, по подразбиране взема колона за ИД на таблицата</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectWhere(const long& lID, CTypedPtrDataArray<CStruct>& oTableArray, CString strColFromToSelect = GetIdentityCol())
	{
		//Инстанция към клас, който констуира заявка
		CDatabaseQueryBuilder oDatabaseQueryBuilder;

		//Извършване на заявка за селект на всички записи от съответната таблица по подадената колона, като параметър
		CString strQuery = oDatabaseQueryBuilder
			.Select()
			.FromTable(GetTableName())
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
			if (oTableArray.AddElement(recStruct) == -1)
			{
				return FALSE;
			}
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
	/// <returns></returns>
	BOOL SelectWhere(const long& lID, CStruct& recCity)
	{
		//Инстанция на масив, в който ще се съхранява селектираното
		CTypedPtrDataArray<CStruct> oCStructWithResultsArray;

		//Извършване на селект
		if (!SelectWhere(lID, oCStructWithResultsArray, GetIdentityCol()))
		{
			return FALSE;
		}

		//Проверка за празен масив
		if (oCStructWithResultsArray.GetSize() != 1)
		{
			return FALSE;
		}

		//Инстнация на структура, която съдържа единствения открит елемент
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
	BOOL UpdateWhereID(const long& lID, const CStruct& recStruct)
	{
		//Инстанция към клас, който констуира заявка
		CDatabaseQueryBuilder oDatabaseQueryBuilder;

		//Извършване на заявка
		CString strQuery = oDatabaseQueryBuilder
			.Select()
			.FromTable(GetTableName())
			.NoLock()
			.WhereEqualLong(GetIdentityCol(), lID)
			.Build();

		//Проверка за успех на заявката
		HRESULT hResult = Open(m_pSessionManager->GetSession(), strQuery);
		if (FAILED(hResult))
		{
			CloseSafeQuery(MSG_ERROR_EXEC_DATABASE_QUERY, hResult, strQuery);
			return FALSE;
		}

		//Достъп до селектирания запис
		if (MoveFirst() != S_OK)
		{
			CloseSafeQuery(MSG_FAIL_READ_DATA_FROM_DATABASE, hResult);
			return FALSE;
		}

		//Проверка дали записа в базата данни не съдържа същата информация, като тази с която искаме да редактираме
		if (CompareAll(GetSelectedRowData(), recStruct) == 0)
		{
			return TRUE;
		}

		//Запазваме стойността от колоната за модификация и затваряме заявката
		long lReadedUpdateCounterWithNolock = GetSelectedRowUpdateCounter();
		Close();

		//Начало на транзакция
		if (!m_pSessionManager->StartTransacion())
		{
			CloseSafeQuery(MSG_FAIL_EXEC_DATABASE_TRANSACTION);
			return FALSE;
		}

		//Извършване на заявка със заключване на селектирания запис
		oDatabaseQueryBuilder.Clear();
		CString strQueryWithUpdLock = oDatabaseQueryBuilder
			.Select()
			.FromTable(GetTableName())
			.UpdLock()
			.WhereEqualLong(GetIdentityCol(), lID)
			.Build();

		//Настройка на rowSet
		CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
		oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
		oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
		oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);

		//Извършване на заявка
		hResult = Open(m_pSessionManager->GetSession(), strQueryWithUpdLock, &oUpdateDBPropSet);
		if (FAILED(hResult))
		{
			m_pSessionManager->RollbackTransaction();
			CloseSafeQuery(MSG_ERROR_EXEC_DATABASE_QUERY, hResult, strQueryWithUpdLock);
			return FALSE;
		}

		//Вземаме резултата от заявката
		hResult = MoveFirst();
		if (FAILED(hResult))
		{
			m_pSessionManager->RollbackTransaction();
			CloseSafeQuery(MSG_FAIL_READ_DATA_FROM_DATABASE, hResult);
			return FALSE;
		}

		//Проверка дали настоящия Update_counter е със същата стойност като преди заключването 
		if (lReadedUpdateCounterWithNolock != GetSelectedRowUpdateCounter())
		{
			m_pSessionManager->RollbackTransaction();
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
			m_pSessionManager->RollbackTransaction();
			CloseSafeQuery(MSG_FAIL_DO_DATABASE_OPERATION, hResult);
			return FALSE;
		}

		//Затваряне на транзакцията с успех, ако принадлежи на класа
		if (m_bIsSessonOwner)
		{
			m_pSessionManager->CommitTransaction();
		}
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
		//Инстанция към клас, който констуира заявка
		CDatabaseQueryBuilder oDatabaseQueryBuilder;

		//Извършване на заявка - селект на таблица, без да се селектират никакви данни
		CString strQuery = oDatabaseQueryBuilder
			.Select(_T(" "))
			.TopRows()
			.FromTable(GetTableName())
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
		hResult = __super::Insert(GLOBAL_ACCESSORS_INFO_ACCESSOR_FOR_DATA, TRUE);
		if (FAILED(hResult))
		{
			CloseSafeQuery(MSG_FAIL_DO_DATABASE_OPERATION, hResult);
			return FALSE;
		}

		//Зареждаме добавените данни в буфера
		if (MoveFirst() != S_OK)
		{
			CloseSafeQuery(MSG_FAIL_READ_DATA_FROM_DATABASE, hResult);
			return FALSE;
		}

		//Задаване на нова стойност за записа, който съдържа данните за добавяне, вкючително и новогенерирано ИД
		recStruct = GetSelectedRowData();

		//Затваряме заявката
		CloseSafeQuery();
		return TRUE;
	}

	/// <summary>
	/// Метод за изтриване на запис по ИД
	/// </summary>
	/// <param name="lID">Параметър за ИД, по който ще се изтрива запис</param>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL DeleteWhereID(const long& lID)
	{
		//Инстанция към клас, който констуира заявка
		CDatabaseQueryBuilder oDatabaseQueryBuilder;

		//Извършване на заявка
		CString strQuery = oDatabaseQueryBuilder
			.Select()
			.FromTable(GetTableName())
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

		//Достъпваме селектирания запис
		if (MoveFirst() != S_OK)
		{
			CloseSafeQuery(MSG_FAIL_READ_DATA_FROM_DATABASE, hResult);
			return FALSE;
		}

		//Извършване на изтриване на записа
		hResult = __super::Delete();
		if (hResult < 0)
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
	BOOL InsertAll(const CTypedPtrDataArray<CStruct>& oTableDataArray)
	{
		if (!ProccessOperationsAll(oTableDataArray, OPERATIONS_WITH_DATA_FLAGS_INSERT))
		{
			return FALSE;
		}
		return TRUE;
	}

	/// <summary>
	/// Метод за редакция на група обекти
	/// </summary>
	/// <param name="oTableDataArray">Масив с група обекти за редакция</param>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL UpdateAll(const CTypedPtrDataArray<CStruct>& oTableDataArray)
	{
		if (!ProccessOperationsAll(oTableDataArray, OPERATIONS_WITH_DATA_FLAGS_UPDATE))
		{
			return FALSE;
		}

		return TRUE;
	}

	/// <summary>
	/// Метод за изтриване на група обекти
	/// </summary>
	/// <param name="oTableDataArray">Масив с група обекти за изтриване</param>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL DeleteAll(const CTypedPtrDataArray<CStruct>& oTableDataArray)
	{
		if (!ProccessOperationsAll(oTableDataArray, OPERATIONS_WITH_DATA_FLAGS_DELETE))
		{
			return FALSE;
		}
		return TRUE;
	}

private:
	/// <summary>
	/// Метод бизопасно затваряне на заявка и сесия при открита грешка
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

	/// <summary>
	/// Метод за извършване на операции в базата данни с група обекти
	/// </summary>
	/// <param name="oTableDataArray">Параметър за масив с група обекти за обработка</param>
	/// <param name="oFlagOperation">Параметър за флаг, по който се очаква облаботката</param>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL ProccessOperationsAll(const CTypedPtrDataArray<CStruct>& oTableDataArray, LPARAM oFlagOperation)
	{
		//Начало на транзакция
		if (!m_pSessionManager->StartTransacion())
		{
			CloseSafeQuery(MSG_FAIL_EXEC_DATABASE_TRANSACTION);
			return FALSE;
		}

		//Обход на всички елементи
		for (INT_PTR nIndex = 0; nIndex < oTableDataArray.GetCount(); nIndex++)
		{
			//Достъп до тукещ елемент
			CStruct* pStruct = oTableDataArray.GetAt(nIndex);
			if (pStruct == nullptr)
			{
				m_pSessionManager->RollbackTransaction();
				CloseSafeQuery(MSG_FAIL_DO_DATABASE_OPERATION);
				return FALSE;
			}

			//Извършване на опирация според подадената в базата данни
			switch (oFlagOperation)
			{
			case OPERATIONS_WITH_DATA_FLAGS_INSERT:
			{
				if (!Insert(*pStruct))
				{
					m_pSessionManager->RollbackTransaction();
					return FALSE;
				}
			}
			break;

			case OPERATIONS_WITH_DATA_FLAGS_UPDATE:
			{
				if (!UpdateWhereID(pStruct->lId, *pStruct))
				{
					m_pSessionManager->RollbackTransaction();
					return FALSE;
				}
			}
			break;

			case OPERATIONS_WITH_DATA_FLAGS_DELETE:
			{
				if (!DeleteWhereID(pStruct->lId))
				{
					m_pSessionManager->RollbackTransaction();
					return FALSE;
				}
			}
			break;

			default:
			{
				return FALSE;
			}
			}
		}

		//Затваряне на транзакцията с успех, ако принадлежи на класа
		if (m_bIsSessonOwner)
		{
			m_pSessionManager->CommitTransaction();
		}

		return TRUE;
	}


// Overrides
// ----------------

protected:
	/// <summary>
	/// Метод, който отпределя наименованието на колоната за ИД в таблица
	/// </summary>
	/// <returns></returns>
	virtual CString GetIdentityCol()
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
	bool m_bIsSessonOwner;

};