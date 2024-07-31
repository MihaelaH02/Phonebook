#pragma once
#include <atldbcli.h>
#include "PersonsAccessor.h"
#include "BaseTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPhersonsTable

/// <summary>
/// Клас изпълняващ CRUD операции към таблица с градове наследяващ базисния клас
/// </summary>

class CPersonsTable :public CBaseTable<CPersonsAccessor, PERSONS>
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPersonsTable() {};
	virtual ~CPersonsTable() {};


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
	PERSONS GetRowData() override
	{
		return m_recPersons;
	}

	/// <summary>
	/// Метод за промяна на стойностите на член променливата в клас CPersonsAccessor
	/// </summary>
	/// <param name="recPerson">Променлива от тип структура PERSONS, с чиито стойности ще се замени член променливата</param>
	void SetRowData(const PERSONS& recPerson) override
	{
		m_recPersons = recPerson;
	}

	/// <summary>
	/// Метод за достъп до ИД на записа
	/// </summary>
	/// <returns>Връща ИД на записа</returns>
	long GetRowId() override
	{
		return m_recPersons.lId;
	}

	/// <summary>
	/// Метод за промяна на стойност за lUpdateCounter на член променливата в клас CPersonsAccessor
	/// </summary>
	/// <param name="lUpdateCounterNew">Параметър, с който ще се замени стойноста в lUpdateCounter</param>
	void IncrementUpdateCounter() override
	{
		m_recPersons.lUpdateCounter = m_recPersons.lUpdateCounter++;
	}

	/// <summary>
	/// Метод за достъп до член променлива lUpdateCounter в клас CPersonsAccessor
	/// </summary>
	/// <returns>Връща член променлива lUpdateCounter</returns>
	long GetUpdateCounter() override
	{
		return m_recPersons.lUpdateCounter;
	}

// Members
// ----------------
};
#pragma once
