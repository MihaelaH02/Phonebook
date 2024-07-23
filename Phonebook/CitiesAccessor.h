#pragma once

#include <atldbcli.h>
#include "Structures.h"

#define	ACCESSOR_FOR_ID 0
#define	ACCESSOR_FOR_DATA 1

#define NUMBERS_OF_ACCESSORS 2
#define ORDINAL_COLUMN_ID 1
#define ORDINAL_COLUMN_UPDATE_COUNTED 2
#define ORDINAL_COLUMN_CITY_NAME 3
#define	ORDINAL_COLUMN_REGION 4

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
	BEGIN_ACCESSOR_MAP(CCitiesAccessor, NUMBERS_OF_ACCESSORS)
		BEGIN_ACCESSOR(ACCESSOR_FOR_ID, true)
			COLUMN_ENTRY(ORDINAL_COLUMN_ID, m_recCities.lId)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ACCESSOR_FOR_DATA, true)
			COLUMN_ENTRY(ORDINAL_COLUMN_UPDATE_COUNTED, m_recCities.lUpdateCounter)
			COLUMN_ENTRY(ORDINAL_COLUMN_CITY_NAME, m_recCities.szCityName)
			COLUMN_ENTRY(ORDINAL_COLUMN_REGION, m_recCities.szRegion)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};