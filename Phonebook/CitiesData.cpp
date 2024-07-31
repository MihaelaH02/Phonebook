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
	BOOL CCitiesData::SelectAll(CCitiesArray& oCitiesArray)
	{
		//Инстанция на класа с табличните данни
		CCitiesTable oCitiesTable;

		if (!oCitiesTable.SelectAll(oCitiesArray))
		{
			return FALSE;
		}
		return TRUE;
	}

	BOOL CCitiesData::SelectWhereID(const long lID, CITIES& recCity)
	{
		//Инстанция на класа с табличните данни
		CCitiesTable oCitiesTable;

		if (!oCitiesTable.SelectWhereID(lID, recCity))
		{
			return FALSE;
		}
		return TRUE;
	}

	BOOL CCitiesData::UpdateWhereID(const long lID, const CITIES& recCity)
	{
		//Инстанция на класа с табличните данни
		CCitiesTable oCitiesTable;

		if (!oCitiesTable.UpdateWhereID(lID, recCity))
		{
			return FALSE;
		}
		return TRUE;
	}

	BOOL CCitiesData::Insert(CITIES& recCity) 
	{
		//Инстанция на класа с табличните данни
		CCitiesTable oCitiesTable;

		if (!oCitiesTable.Insert(recCity))
		{
			return FALSE;
		}
		return TRUE;
	}


	BOOL CCitiesData::DeleteWhereID(const long lID) 
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