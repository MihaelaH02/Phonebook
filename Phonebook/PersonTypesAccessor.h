#pragma once

#include <atldbcli.h>
#include "Structures.h"
#include "StructsInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CpersonTypeAccessor

/// <summary>
/// Клас за Mapping на структура PERSON_TYPES с таблица от базата данни PERSON_TYPES
/// </summary>
class CPersonTypesAccessor
{

// Constructor / Destructor
// ----------------

public:
	CPersonTypesAccessor() {};
	virtual ~CPersonTypesAccessor() {};


// Methods
// ----------------


// Overrides
// ----------------


// Members
// ----------------

protected:
	/// <summary>
	/// Член променлива от тип структура PHONE_TYPES
	/// </summary>
	PERSON_TYPES m_recPersonType;

	/// <summary>
	/// Свързване на мембърите на структура PERSON_TYPES с колоните от таблица PERSON_TYPES в базата данни
	/// </summary>
	BEGIN_ACCESSOR_MAP(CPersonTypesAccessor, GLOBAL_ACCESSORS_INFO_NUMBERS_OF_ACCESSORS)
		BEGIN_ACCESSOR(GLOBAL_ACCESSORS_INFO_ACCESSOR_FOR_ID, true)
		COLUMN_ENTRY(ACCESSORS_COLUMNS_INFO_ORDINAL_COLUMN_ID, m_recPersonType.lId)
		END_ACCESSOR()

		BEGIN_ACCESSOR(GLOBAL_ACCESSORS_INFO_ACCESSOR_FOR_DATA, true)
		COLUMN_ENTRY(ACCESSORS_COLUMNS_INFO_ORDINAL_COLUMN_UPDATE_COUNTED, m_recPersonType.lUpdateCounter)
		COLUMN_ENTRY(STRUCT_PHONE_TYPES_ORDER_COL_PHONE_TYPES, m_recPersonType.czPersonType)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};
