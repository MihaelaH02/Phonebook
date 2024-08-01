#pragma once

#pragma once

#include <atldbcli.h>
#include "Structures.h"
#include "EnumsStructsInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesAccessor

/// <summary>
/// Клас за Mapping на структура PHONE_TYPES с таблица от базата данни PHONE_TYPES
/// </summary>
class CPhoneTypesAccessor
{

	// Constructor / Destructor
	// ----------------
public:
	CPhoneTypesAccessor() {};
	virtual ~CPhoneTypesAccessor() {};


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
	PHONE_TYPES m_recPhoneTypes;

	/// <summary>
	/// Свързване на мембърите на структура PHONE_TYPES с колоните от таблица PHONE_TYPES в базата данни
	/// </summary>
	BEGIN_ACCESSOR_MAP(CPhoneTypesAccessor, GLOBAL_ACCESSORS_INFO_NUMBERS_OF_ACCESSORS)
		BEGIN_ACCESSOR(GLOBAL_ACCESSORS_INFO_ACCESSOR_FOR_ID, true)
		COLUMN_ENTRY(GLOBAL_ACCESSORS_INFO_ORDINAL_COLUMN_ID, m_recPhoneTypes.lId)
		END_ACCESSOR()

		BEGIN_ACCESSOR(GLOBAL_ACCESSORS_INFO_ACCESSOR_FOR_DATA, true)
		COLUMN_ENTRY(GLOBAL_ACCESSORS_INFO_ORDINAL_COLUMN_UPDATE_COUNTED, m_recPhoneTypes.lUpdateCounter)
		COLUMN_ENTRY(STRUCT_PHONE_TYPES_ORDER_COL_PHONE_TYPES, m_recPhoneTypes.czPhoneType)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};
