#pragma once

#pragma once
#include <atldbcli.h>
#include "PhoneTypesAccessor.h"
#include "BaseTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable

/// <summary>
/// Клас изпълняващ CRUD операции към таблица с градове наследяващ базисния клас
/// </summary>

class CPhoneTypesTable :public CBaseTable<CPhoneTypesAccessor, PHONE_TYPES>
{
	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
public:
	CPhoneTypesTable() {};
	virtual ~CPhoneTypesTable() {};


	// Methods
	// ----------------


	// Overrides
	// ----------------

private:
	/// <summary>
	/// Достъп до името на таблицата с телефонни номера
	/// </summary>
	/// <returns>Връщаш името на таблицата като CString тип</returns>
	CString GetTableName() override
	{
		return _T("PHONE_TYPES");
	}

	/// <summary>
	/// Метод за достъп до член променливата в клас CPhoneTypesAccessor
	/// </summary>
	/// <returns>Връща структура от тип PHONE_TYPES</returns>
	PHONE_TYPES GetRowData() override
	{
		return m_recPhoneTypes;
	}

	/// <summary>
	/// Метод за промяна на стойностите на член променливата в клас CPhoneTypesAccessor
	/// </summary>
	/// <param name="recPhoneTypes">Променлива от тип структура PHONE_TYPES, с чиито стойности ще се замени член променливата</param>
	void SetRowData(const PHONE_TYPES& recPhoneTypes) override
	{
		m_recPhoneTypes = recPhoneTypes;
	}

	/// <summary>
	/// Метод за достъп до ИД на записа
	/// </summary>
	/// <returns>Връща ИД на записа</returns>
	long GetRowId() override
	{
		return m_recPhoneTypes.lId;
	}

	/// <summary>
	/// Метод за промяна на стойност за lUpdateCounter на член променливата в клас CPhoneTypesAccessor
	/// </summary>
	/// <param name="lUpdateCounterNew">Параметър, с който ще се замени стойноста в lUpdateCounter</param>
	void IncrementUpdateCounter() override
	{
		m_recPhoneTypes.lUpdateCounter = m_recPhoneTypes.lUpdateCounter++;
	}

	/// <summary>
	/// Метод за достъп до член променлива lUpdateCounter в клас CPhoneTypesAccessor
	/// </summary>
	/// <returns>Връща член променлива lUpdateCounter</returns>
	long GetUpdateCounter() override
	{
		return m_recPhoneTypes.lUpdateCounter;
	}

	// Members
	// ----------------
};
