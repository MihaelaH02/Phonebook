#include "pch.h"
#include "PhoneTypesData.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesData

// Constructor / Destructor
// ----------------

CPhoneTypesData::CPhoneTypesData()
{
}

CPhoneTypesData::~CPhoneTypesData()
{
}


// Methods
// ----------------
BOOL CPhoneTypesData::SelectAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray)
{
	//Инстанция на класа с табличните данни
	CPhoneTypesTable oPhoneTypesTable;

	if (!oPhoneTypesTable.SelectAll(oPhoneTypesArray))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPhoneTypesData::SelectPhoneTypeWhereID(const long lID, PHONE_TYPES& recPhoneTypes)
{
	//Инстанция на класа с табличните данни
	CPhoneTypesTable oPhoneTypesTable;

	if (!oPhoneTypesTable.SelectWhere(lID, recPhoneTypes))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPhoneTypesData::UpdatePhoneTypeWhereID(const long lID, const PHONE_TYPES& recPhoneTypes)
{
	//Инстанция на класа с табличните данни
	CPhoneTypesTable oPhoneTypesTable;

	if (!oPhoneTypesTable.UpdateWhereID(lID, recPhoneTypes))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPhoneTypesData::InsertPhoneType(PHONE_TYPES& recPhoneTypes)
{
	//Инстанция на класа с табличните данни
	CPhoneTypesTable oPhoneTypesTable;

	if (!oPhoneTypesTable.Insert(recPhoneTypes))
	{
		return FALSE;
	}
	return TRUE;
}


BOOL CPhoneTypesData::DeletePhoneTypeWhereID(const long lID)
{
	//Инстанция на класа с табличните данни
	CPhoneTypesTable oPhoneTypesTable;

	if (!oPhoneTypesTable.DeleteWhereID(lID))
	{
		return FALSE;
	}
	return TRUE;
}


// Overrides
// ----------------