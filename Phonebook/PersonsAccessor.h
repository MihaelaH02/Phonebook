#pragma once

#pragma once

#include <atldbcli.h>
#include "Structures.h"
#include "StructsInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsAccessor

/// <summary>
/// Клас за Mapping на структура PERSONS с таблица от базата данни PERSONS
/// </summary>
class CPersonsAccessor
{

// Constructor / Destructor
// ----------------

public:
	CPersonsAccessor() {};
	virtual ~CPersonsAccessor() {};


// Methods
// ----------------


// Overrides
// ----------------


// Members
// ----------------

protected:
	/// <summary>
	/// Член променлива от тип структура PERSONS
	/// </summary>
	PERSONS m_recPersons;

	/// <summary>
	/// Свързване на мембърите на структура PERSONS с колоните от таблица PERSONS в базата данни
	/// </summary>
	BEGIN_ACCESSOR_MAP(CPersonsAccessor, GLOBAL_ACCESSORS_INFO_NUMBERS_OF_ACCESSORS)
		BEGIN_ACCESSOR(GLOBAL_ACCESSORS_INFO_ACCESSOR_FOR_ID, true)
		COLUMN_ENTRY(ACCESSORS_COLUMNS_INFO_ORDINAL_COLUMN_ID, m_recPersons.lId)
		END_ACCESSOR()

		BEGIN_ACCESSOR(GLOBAL_ACCESSORS_INFO_ACCESSOR_FOR_DATA, true)
		COLUMN_ENTRY(ACCESSORS_COLUMNS_INFO_ORDINAL_COLUMN_UPDATE_COUNTED, m_recPersons.lUpdateCounter)
		COLUMN_ENTRY(STRUCT_PERSONS_ORDER_COL_FIRSTNAME, m_recPersons.szFirstName)
		COLUMN_ENTRY(STRUCT_PERSONS_ORDER_COL_SECONDNAME, m_recPersons.szSecondName)
		COLUMN_ENTRY(STRUCT_PERSONS_ORDER_COL_LASTNAME, m_recPersons.szLastName)
		COLUMN_ENTRY(STRUCT_PERSONS_ORDER_COL_EGN, m_recPersons.szEGN)
		COLUMN_ENTRY(STRUCT_PERSONS_ORDER_COL_ID_CITY, m_recPersons.lIdCity)
		COLUMN_ENTRY(STRUCT_PERSONS_ORDER_COL_ADDRESS, m_recPersons.szAddress)
		COLUMN_ENTRY(STRUCT_PERSONS_ORDER_COL_ID_PERSON_TYPE, m_recPersons.lIdPersonType)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};