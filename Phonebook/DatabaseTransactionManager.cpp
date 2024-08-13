#include "pch.h"
#include "DatabaseTransactionManager.h"

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTransactionManager


// Constructor / Destructor
// ----------------
CDatabaseTransactionManager::CDatabaseTransactionManager()
{
	m_pSession = new CInitializeSession();
}

CDatabaseTransactionManager::~CDatabaseTransactionManager()
{
	if (m_pSession != nullptr)
	{
		delete m_pSession;
		m_pSession = nullptr;
	}
}


// Methods
// ----------------

CInitializeSession* CDatabaseTransactionManager::GetSession()
{
	return m_pSession;
}

BOOL CDatabaseTransactionManager::OpenSafeTransaction()
{
	if (m_pSession == nullptr)
	{
		m_pSession = new CInitializeSession();
	}

	if (!m_pSession->StartTransacion())
	{
		delete m_pSession;
		m_pSession = nullptr;
		return FALSE;
	}

	return TRUE;
}

BOOL CDatabaseTransactionManager::CloseSafeTransactoin(BOOL bFlagForError)
{
	//Затвяряне на транзакцията при подаден флаг за грешка с неуспух

	if (bFlagForError)
	{
		if (!m_pSession->RollbackTransaction())
		{
			delete m_pSession;
			m_pSession = nullptr;
			return FALSE;
		}
	}

	//Затваряне на транзакцията с успех
	else 
	{
		if (!m_pSession->CommitTransaction())
		{
			delete m_pSession;
			m_pSession = nullptr;
			return FALSE;
		}
	}

	delete m_pSession;
	m_pSession = nullptr;
	return TRUE;
}


// Overrides
// ----------------


