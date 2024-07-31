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
BOOL CPhoneTypesData::SelectAll(CPhoneTypesArray& oPhoneTypesArray)
{
	//Инстанция на класа с табличните данни
	CPhoneTypesTable oPhoneTypesTable;

	if (!oPhoneTypesTable.SelectAll(oPhoneTypesArray))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPhoneTypesData::SelectWhereID(const long lID, PHONE_TYPES& recPhoneTypes)
{
	//Инстанция на класа с табличните данни
	CPhoneTypesTable oPhoneTypesTable;

	if (!oPhoneTypesTable.SelectWhereID(lID, recPhoneTypes))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPhoneTypesData::UpdateWhereID(const long lID, const PHONE_TYPES& recPhoneTypes)
{
	//Инстанция на класа с табличните данни
	CPhoneTypesTable oPhoneTypesTable;

	if (!oPhoneTypesTable.UpdateWhereID(lID, recPhoneTypes))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPhoneTypesData::Insert(PHONE_TYPES& recPhoneTypes)
{
	//Инстанция на класа с табличните данни
	CPhoneTypesTable oPhoneTypesTable;

	if (!oPhoneTypesTable.Insert(recPhoneTypes))
	{
		return FALSE;
	}
	return TRUE;
}


BOOL CPhoneTypesData::DeleteWhereID(const long lID)
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