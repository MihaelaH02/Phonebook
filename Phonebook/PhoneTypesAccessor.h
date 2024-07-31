#pragma once

#pragma once

#include <atldbcli.h>
#include "Structures.h"
#include "EnumsStructsAccessorsInfo.h"

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
	BEGIN_ACCESSOR_MAP(CPhoneTypesAccessor, NUMBERS_OF_ACCESSORS)
		BEGIN_ACCESSOR(ACCESSOR_FOR_ID, true)
		COLUMN_ENTRY(ORDINAL_COLUMN_ID, m_recPhoneTypes.lId)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ACCESSOR_FOR_DATA, true)
		COLUMN_ENTRY(ORDINAL_COLUMN_UPDATE_COUNTED, m_recPhoneTypes.lUpdateCounter)
		COLUMN_ENTRY(ORDINAL_COLUMN_PHONE_TYPES, m_recPhoneTypes.czPhoneType)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};
