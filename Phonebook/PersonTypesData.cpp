#include "pch.h"
#include "PersonTypesData.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonTypesData

// Constructor / Destructor
// ----------------

CPersonTypesData::CPersonTypesData()
{
}

CPersonTypesData::~CPersonTypesData()
{
}


// Methods
// ----------------
BOOL CPersonTypesData::SelectAllPersonTypes(CPersonTypesArray& oPersonTypesArray)
{
	//Инстанция на класа с табличните данни
	CPersonTypesTable oPersonTypesTable;

	if (!oPersonTypesTable.SelectAll(oPersonTypesArray))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPersonTypesData::SelectPersonTypeWhereID(const long lID, PERSON_TYPES& recPersonTypes)
{
	//Инстанция на класа с табличните данни
	CPersonTypesTable oPersonTypesTable;

	if (!oPersonTypesTable.SelectWhere(lID, recPersonTypes))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPersonTypesData::UpdatePersonTypeWhereID(const long lID, const PERSON_TYPES& recPersonTypes)
{
	//Инстанция на класа с табличните данни
	CPersonTypesTable oPersonTypesTable;

	if (!oPersonTypesTable.UpdateWhereID(lID, recPersonTypes))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPersonTypesData::InsertPersonType(PERSON_TYPES& recPersonTypes)
{
	//Инстанция на класа с табличните данни
	CPersonTypesTable oPersonTypesTable;

	if (!oPersonTypesTable.Insert(recPersonTypes))
	{
		return FALSE;
	}
	return TRUE;
}


BOOL CPersonTypesData::DeletePersonTypeWhereID(const long lID)
{
	//Инстанция на класа с табличните данни
	CPersonTypesTable oPersonTypesTable;

	if (!oPersonTypesTable.DeleteWhereID(lID))
	{
		return FALSE;
	}
	return TRUE;
}


// Overrides
// ----------------