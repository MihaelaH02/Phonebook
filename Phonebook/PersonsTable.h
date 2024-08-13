#pragma once
#include <atldbcli.h>
#include "PersonsAccessor.h"
#include "BaseTable.h"
#include "InitializeSession.h"

/////////////////////////////////////////////////////////////////////////////
// CPhersonsTable

/// <summary>
/// Клас изпълняващ CRUD операции към таблица с клиенти наследяващ базисния клас
/// </summary>
class CPersonsTable :public CBaseTable<CPersonsAccessor, PERSONS>
{

// Constants
// ----------------


// Constructor / Destructor
// ----------------

public:

	CPersonsTable()
	{

	}

	/// <param name="oDatabaseTransactionManager">Параметър указател към клас управляващ сесии</param>
	CPersonsTable(CInitializeSession* pDatabaseSession)
		:CBaseTable(pDatabaseSession)
	{
	}

	virtual ~CPersonsTable() 
	{
	}


// Methods
// ----------------


// Overrides
// ----------------

private:
	/// <summary>
	/// Достъп до името на таблицата с клиенти
	/// </summary>
	/// <returns>Връщаш името на таблицата като CString тип</returns>
	CString GetTableName() override
	{
		return _T("PERSONS");
	}

	
	/// <summary>
	/// Метод за достъп до член променливата в клас CPersonsAccessor
	/// </summary>
	/// <returns>Връща структура от тип PERSONS</returns>
	const PERSONS& GetSelectedRowData() override
	{
		return m_recPersons;
	}

	/// <summary>
	/// Метод за промяна на стойностите на член променливата в клас CPersonsAccessor
	/// </summary>
	/// <param name="recPerson">Променлива от тип структура PERSONS, с чиито стойности ще се замени член променливата</param>
	void SetNewDataToSelectedRow(const PERSONS& recPerson) override
	{
		m_recPersons = recPerson;
	}

	/// <summary>
	/// Метод за промяна на стойност за lUpdateCounter на член променливата в клас CPersonsAccessor
	/// </summary>
	/// <param name="lUpdateCounterNew">Параметър, с който ще се замени стойноста в lUpdateCounter</param>
	void IncrementUpdateCounterOfSelectedRow() override
	{
		m_recPersons.lUpdateCounter = m_recPersons.lUpdateCounter++;
	}

	/// <summary>
	/// Метод за достъп до член променлива lUpdateCounter в клас CPersonsAccessor
	/// </summary>
	/// <returns>Връща член променлива lUpdateCounter</returns>
	long const GetSelectedRowUpdateCounter() override
	{
		return m_recPersons.lUpdateCounter;
	}

// Members
// ----------------
};