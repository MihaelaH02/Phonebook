#include "pch.h"
#include <atldbcli.h>
#include <afxtempl.h>
#include "InitializeSession.h"
#include "DatabaseConnection.h"


/////////////////////////////////////////////////////////////////////////////
// CInitializeSession


// Constructor / Destructor
// ----------------

CInitializeSession::CInitializeSession() 
{
	OpenSession();
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
		strMessage.Format(_T("Unable to open session. Error: %d"), hResult);
		AfxMessageBox(strMessage);
		CloseSession();
		return FALSE;
	}

	return TRUE;
}

BOOL CInitializeSession::CloseSession()
{
	if (IsSessionOpen())
	{
		m_oSession.Close();
	}

	return TRUE;
}

CSession& CInitializeSession::GetSession()
{
	return m_oSession;
}

BOOL CInitializeSession::IsSessionOpen()
{
	if (m_oSession.m_spOpenRowset == nullptr)
	{
		return FALSE;
	}
	return TRUE;
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

	//Започване на пранзакция
	HRESULT hResult = GetSession().StartTransaction();
	if (FAILED(hResult))
	{
		return FALSE;
	}

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

	return TRUE;
}


// Overrides
// ----------------