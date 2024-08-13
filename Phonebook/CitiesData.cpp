#include "pch.h"
#include "CitiesData.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData


// Constructor / Destructor
// ----------------

CCitiesData::CCitiesData()
{
}

CCitiesData::~CCitiesData()
{
}


// Methods
// ----------------

BOOL CCitiesData::SelectAllCities(CCitiesArray& oCitiesArray)
{
	//Инстанция на класа с табличните данни
	CCitiesTable oCitiesTable;

	if (!oCitiesTable.SelectAll(oCitiesArray))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CCitiesData::SelectCityWhereID(const long& lID, CITIES& recCity)
{
	//Инстанция на класа с табличните данни
	CCitiesTable oCitiesTable;

	if (!oCitiesTable.SelectWhere(lID, recCity))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CCitiesData::UpdateCityWhereID(const long& lID, const CITIES& recCity)
{
	//Инстанция на класа с табличните данни
	CCitiesTable oCitiesTable;

	if (!oCitiesTable.UpdateWhereID(lID, recCity))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CCitiesData::InsertCity(CITIES& recCity) 
{
	//Инстанция на класа с табличните данни
	CCitiesTable oCitiesTable;

	if (!oCitiesTable.Insert(recCity))
	{
		return FALSE;
	}
	return TRUE;
}


BOOL CCitiesData::DeleteCityWhereID(const long& lID) 
{
	//Инстанция на класа с табличните данни
	CCitiesTable oCitiesTable;

	if (!oCitiesTable.DeleteWhereID(lID))
	{
		return FALSE;
	}
	return TRUE;
}

// Overrides
// ----------------