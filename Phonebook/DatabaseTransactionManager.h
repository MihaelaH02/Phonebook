#pragma once
#include "InitializeSession.h"

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTransactionManager

class CDatabaseTransactionManager: public CInitializeSession
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CDatabaseTransactionManager();
	~CDatabaseTransactionManager();


// Methods
// ----------------
public:
	BOOL StartTransacion();
	BOOL CommitTransaction();

// Overrides
// ----------------

// Members
// ----------------
};