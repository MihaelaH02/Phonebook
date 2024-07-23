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
		if (!m_oCitiesTable.SelectAll(oCitiesArray))
		{
			return FALSE;
		}
		return TRUE;
	}

	BOOL CCitiesData::SelectWhereID(const long lID, CITIES& recCity)
	{
		if (!m_oCitiesTable.SelectWhereID(lID, recCity))
		{
			return FALSE;
		}
		return TRUE;
	}

	BOOL CCitiesData::UpdateWhereID(const long lID, const CITIES& recCity)
	{
		if (!m_oCitiesTable.UpdateWhereID(lID, recCity))
		{
			return FALSE;
		}
		return TRUE;
	}

	BOOL CCitiesData::Insert(CITIES& recCity) 
	{
		if (!m_oCitiesTable.Insert(recCity))
		{
			return FALSE;
		}
		return TRUE;
	}


	BOOL CCitiesData::DeleteWhereID(const long lID) 
	{
		if (!m_oCitiesTable.DeleteWhereID(lID))
		{
			return FALSE;
		}
		return TRUE;
	}

// Overrides
// ----------------