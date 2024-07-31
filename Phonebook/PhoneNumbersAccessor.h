#pragma once

#pragma once

#pragma once

#include <atldbcli.h>
#include "Structures.h"
#include "EnumsStructsAccessorsInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsAccessor

/// <summary>
/// Клас за Mapping на структура PHONE_NUMBERS с таблица от базата данни PHONE_NUMBERS
/// </summary>
class CPhoneNumbersAccessor
{

	// Constructor / Destructor
	// ----------------
public:
	CPhoneNumbersAccessor() {};
	virtual ~CPhoneNumbersAccessor() {};


	// Methods
	// ----------------


	// Overrides
	// ----------------

	// Members
	// ----------------
protected:
	/// <summary>
	/// Член променлива от тип структура PHONE_NUMBERS
	/// </summary>
	PHONE_NUMBERS m_recPhoneNumber;

	/// <summary>
	/// Свързване на мембърите на структура PHONE_NUMBERS с колоните от таблица PHONE_NUMBERS в базата данни
	/// </summary>
	BEGIN_ACCESSOR_MAP(CPhoneNumbersAccessor, NUMBERS_OF_ACCESSORS)
		BEGIN_ACCESSOR(ACCESSOR_FOR_ID, true)
		COLUMN_ENTRY(ORDINAL_COLUMN_ID, m_recPhoneNumber.lId)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ACCESSOR_FOR_DATA, true)
		COLUMN_ENTRY(ORDINAL_COLUMN_UPDATE_COUNTED, m_recPhoneNumber.lUpdateCounter)
		COLUMN_ENTRY(ORDINAL_COLUMN_PHONE_NUMBERS_ID_PERSON, m_recPhoneNumber.lIdPerson)
		COLUMN_ENTRY(ORDINAL_COLUMN_PHONE_NUMBERS_ID_PHONE_TYPE, m_recPhoneNumber.lIdPhoneType)
		COLUMN_ENTRY(ORDINAL_COLUMN_PHONE_NUMBERS_PHONE, m_recPhoneNumber.szPhone)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};
