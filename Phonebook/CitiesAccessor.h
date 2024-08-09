#pragma once

#include <atldbcli.h>
#include "Structures.h"
#include "EnumsStructsInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesAccessor

/// <summary>
/// Клас за Mapping на структура CITIES с таблица от базата данни CITIES
/// </summary>
class CCitiesAccessor
{

// Constructor / Destructor
// ----------------
public:
	CCitiesAccessor() {};
	virtual ~CCitiesAccessor() {};


// Methods
// ----------------


// Overrides
// ----------------
		

// Members
// ----------------
protected:
	/// <summary>
	/// Член променлива от тип структура CITIES
	/// </summary>
	CITIES m_recCities;

	/// <summary>
	/// Свързване на мембърите на структура Cities с колоните от таблица Cities в базата данни
	/// </summary>
	BEGIN_ACCESSOR_MAP(CCitiesAccessor, GLOBAL_ACCESSORS_INFO_NUMBERS_OF_ACCESSORS)
		BEGIN_ACCESSOR(GLOBAL_ACCESSORS_INFO_ACCESSOR_FOR_ID, true)
			COLUMN_ENTRY(GLOBAL_ACCESSORS_INFO_ORDINAL_COLUMN_ID, m_recCities.lId)
		END_ACCESSOR()

		BEGIN_ACCESSOR(GLOBAL_ACCESSORS_INFO_ACCESSOR_FOR_DATA, true)
			COLUMN_ENTRY(GLOBAL_ACCESSORS_INFO_ORDINAL_COLUMN_UPDATE_COUNTED, m_recCities.lUpdateCounter)
			COLUMN_ENTRY(STRUCT_CITIES_ORDER_COL_CITT_NAME, m_recCities.szCityName)
			COLUMN_ENTRY(STRUCT_CITIES_ORDER_COL_REGION, m_recCities.szRegion)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};