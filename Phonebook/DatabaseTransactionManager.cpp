#include "pch.h"
#include "DatabaseTransactionManager.h"

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTransactionManager


// Constructor / Destructor
// ----------------
CDatabaseTransactionManager::CDatabaseTransactionManager()
{
}

CDatabaseTransactionManager::~CDatabaseTransactionManager()
{
}


// Methods
// ----------------
BOOL CDatabaseTransactionManager::StartTransacion()
{
	if (!OpenSession())
	{
		return FALSE;
	}

	HRESULT hResult = GetSession().StartTransaction();
	if (FAILED(hResult))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDatabaseTransactionManager::CommitTransaction()
{
	HRESULT hResult = GetSession().Commit();
	if (FAILED(hResult))
	{
		return FALSE;
	}
		
	if (!CloseSession())
	{
		return FALSE;
	}

	return TRUE;
}

// Overrides
// ----------------