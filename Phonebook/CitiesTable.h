#pragma once
#include <atldbcli.h>
#include "CitiesAccessor.h"
#include "BaseTable.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

/// <summary>
/// Клас изпълняващ CRUD операции към таблица с градове наследяващ базисния клас
/// </summary>
class CCitiesTable :public CBaseTable<CCitiesAccessor, CITIES>
{

// Constants
// ----------------


// Constructor / Destructor
// ----------------

public:
	CCitiesTable() {};
	virtual ~CCitiesTable() {};


// Methods
// ----------------


// Overrides
// ----------------

private:
	/// <summary>
	/// Метод за достъп до името на таблицата с градове
	/// </summary>
	/// <returns>Връщаш името на таблицата като CString тип</returns>
	CString GetTableName() override
	{
		return _T("CITIES");
	}

	/// <summary>
	/// Метод за достъп до член променливата в клас CCitiesAccessor
	/// </summary>
	/// <returns>Връща структура от тип CITIES</returns>
	const CITIES& GetSelectedRowData() override
	{
		return m_recCities;
	}

	/// <summary>
	/// Метод за промяна на стойностите на член променливата в клас CCitiesAccessor
	/// </summary>
	/// <param name="recCity">Променлива от тип структура CITIES, с чиито стойности ще се замени член променливата</param>
	void SetNewDataToSelectedRow(const CITIES& recCity) override
	{
		m_recCities = recCity;
	}

	/// <summary>
	/// Метод за увеличаване на стойност за lUpdateCounter на член променливата в клас CCitiesAccessor
	/// </summary>
	/// <param name="lUpdateCounterNew">Параметър, с който ще се замени стойноста в lUpdateCounter</param>
	void IncrementUpdateCounterOfSelectedRow() override
	{
		m_recCities.lUpdateCounter = m_recCities.lUpdateCounter++;
	}

	/// <summary>
	/// Метод за достъп до член променлива lUpdateCounter в клас CCitiesAccessor
	/// </summary>
	/// <returns>Връща член променлива lUpdateCounter</returns>
	long const GetSelectedRowUpdateCounter() override
	{
		return m_recCities.lUpdateCounter;
	}

// Members
// ----------------
};