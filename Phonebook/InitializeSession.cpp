#include "pch.h"
#include <atldbcli.h>
#include <afxtempl.h>
#include "InitializeSession.h"
#include "DatabaseConnection.h"

#define ERROR_FAIL_OPEN_SESSION _T("Unable to open session. Error: %d")


/////////////////////////////////////////////////////////////////////////////
// CInitializeSession


// Constructor / Destructor
// ----------------

CInitializeSession::CInitializeSession() 
{
	OpenSession();
	m_bIsTransactionOpen = false;
}

CInitializeSession::~CInitializeSession() 
{
	if (IsSessionOpen())
	{
		CloseSession();
	}
}


// Methods
// ----------------

BOOL CInitializeSession::OpenSession()
{
	//Проверка за вече отворена сесия
	if (IsSessionOpen())
	{
		return TRUE;
	}

	//Връзка към базата данни
	CDatabaseConnection* pDatabaseConnection = CDatabaseConnection::getInstance();
	if (pDatabaseConnection == nullptr)
	{
		return FALSE;
	}

	//Отваряне на сесия
	HRESULT hResult = m_oSession.Open(pDatabaseConnection->GetDataSource());
	if (FAILED(hResult))
	{
		CString strMessage;
		strMessage.Format(ERROR_FAIL_OPEN_SESSION, hResult);
		AfxMessageBox(strMessage);
		CloseSession();
		return FALSE;
	}

	m_bIsSessionOpen = TRUE;
	return TRUE;
}

BOOL CInitializeSession::CloseSession()
{
	if (!IsSessionOpen())
	{
		return FALSE;
	}

	m_oSession.Close();
	m_bIsSessionOpen = FALSE;
	return TRUE;
}

CSession& CInitializeSession::GetSession()
{
	return m_oSession;
}

BOOL CInitializeSession::IsSessionOpen()
{
	return m_bIsSessionOpen;
}

BOOL CInitializeSession::StartTransacion()
{
	//Проверка за отворена сесия
	if (!IsSessionOpen())
	{
		if (!OpenSession())
		{
			return FALSE;
		}
	}

	if (m_bIsTransactionOpen)
	{
		return TRUE;
	}

	//Започване на пранзакция
	HRESULT hResult = GetSession().StartTransaction();
	if (FAILED(hResult))
	{
		return FALSE;
	}

	m_bIsTransactionOpen = true;
	return TRUE;
}

BOOL CInitializeSession::CommitTransaction()
{
	//Проверка за отворена сесия
	if (!IsSessionOpen())
	{
		return FALSE;
	}

	//Проверка за открита грешка или не отрорена транзакция
	HRESULT hResult = GetSession().Commit();
	if (hResult == XACT_E_NOTRANSACTION || FAILED(hResult))
	{
		return FALSE;
	}

	if (!CloseSession())
	{
		return FALSE;
	}

	m_bIsTransactionOpen = false;
	return TRUE;
}

BOOL CInitializeSession::RollbackTransaction()
{
	//Проверка за отворена сесия
	if (!IsSessionOpen())
	{
		return FALSE;
	}

	//Проверка за открита грешка или не отрорена транзакция
	HRESULT hResult = GetSession().Abort();
	if (hResult == XACT_E_NOTRANSACTION || FAILED(hResult))
	{
		return FALSE;
	}

	if (!CloseSession())
	{
		return FALSE;
	}

	m_bIsTransactionOpen = false;
	return TRUE;
}


// Overrides
// ----------------