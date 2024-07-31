#pragma once
#include <atldbcli.h>
#include "PhoneNumbersAccessor.h"
#include "BaseTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable

/// <summary>
/// Клас изпълняващ CRUD операции към таблица с градове наследяващ базисния клас
/// </summary>

class CPhoneNumbersTable :public CBaseTable<CPhoneNumbersAccessor, PHONE_NUMBERS>
{
	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
public:
	CPhoneNumbersTable() {};
	virtual ~CPhoneNumbersTable() {};


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
		return _T("PHONE_NUMBERS");
	}

	/// <summary>
	/// Метод за достъп до член променливата в клас CPhoneNumbersAccessor
	/// </summary>
	/// <returns>Връща структура от тип PHONE_NUMBERS</returns>
	PHONE_NUMBERS GetRowData() override
	{
		return m_recPhoneNumber;
	}

	/// <summary>
	/// Метод за промяна на стойностите на член променливата в клас CPhoneNumbersAccessorer
	/// </summary>
	/// <param name="recPhoneNumbers">Променлива от тип структура PHONE_NUMBERS, с чиито стойности ще се замени член променливата</param>
	void SetRowData(const PHONE_NUMBERS& recPhoneNumbers) override
	{
		m_recPhoneNumber = recPhoneNumbers;
	}

	/// <summary>
	/// Метод за достъп до ИД на записа
	/// </summary>
	/// <returns>Връща ИД на записа</returns>
	long GetRowId() override
	{
		return m_recPhoneNumber.lId;
	}

	/// <summary>
	/// Метод за промяна на стойност за lUpdateCounter на член променливата в клас CPhoneNumbersAccessor
	/// </summary>
	/// <param name="lUpdateCounterNew">Параметър, с който ще се замени стойноста в lUpdateCounter</param>
	void IncrementUpdateCounter() override
	{
		m_recPhoneNumber.lUpdateCounter = m_recPhoneNumber.lUpdateCounter++;
	}

	/// <summary>
	/// Метод за достъп до член променлива lUpdateCounter в клас CPhoneNumbersAccessor
	/// </summary>
	/// <returns>Връща член променлива lUpdateCounter</returns>
	long GetUpdateCounter() override
	{
		return m_recPhoneNumber.lUpdateCounter;
	}

	// Members
	// ----------------
};
