#pragma once

#include <atldbcli.h>
#include "PersonTypesAccessor.h"
#include "BaseTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable

/// <summary>
/// Клас изпълняващ CRUD операции към таблица с типове клиенти, наследяващ базисния клас
/// </summary>
class CPersonTypesTable :public CBaseTable<CPersonTypesAccessor, PERSON_TYPES>
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------

public:
	CPersonTypesTable() {};
	virtual ~CPersonTypesTable() {};


// Methods
// ----------------


// Overrides
// ----------------

private:
	/// <summary>
	/// Достъп до името на таблицата
	/// </summary>
	/// <returns>Връщаш името на таблицата като CString тип</returns>
	CString GetTableName() override
	{
		return _T("PERSON_TYPES");
	}

	/// <summary>
	/// Метод за достъп до член променливата
	/// </summary>
	/// <returns>Връща структура от тип PHONE_TYPES</returns>
	const PERSON_TYPES& GetSelectedRowData() override
	{
		return m_recPersonType;
	}

	/// <summary>
	/// Метод за промяна на стойностите на член променливата
	/// </summary>
	/// <param name="recPersonTypes">Променлива от тип структура PERSON_TYPES, с чиито стойности ще се замени член променливата в класа</param>
	void SetNewDataToSelectedRow(const PERSON_TYPES& recPersonTypes) override
	{
		m_recPersonType = recPersonTypes;
	}

	/// <summary>
	/// Метод за промяна на стойност за lUpdateCounter на член променливата
	/// </summary>
	/// <param name="lUpdateCounterNew">Параметър, с който ще се замени стойноста на lUpdateCounter</param>
	void IncrementUpdateCounterOfSelectedRow() override
	{
		m_recPersonType.lUpdateCounter = m_recPersonType.lUpdateCounter++;
	}

	/// <summary>
	/// Метод за достъп до член променлива lUpdateCounter
	/// </summary>
	/// <returns>Връща член променлива lUpdateCounter</returns>
	long const GetSelectedRowUpdateCounter() override
	{
		return m_recPersonType.lUpdateCounter;
	}


// Members
// ----------------
};
