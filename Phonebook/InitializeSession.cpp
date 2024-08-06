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
}

CInitializeSession::~CInitializeSession() 
{
}


// Methods
// ----------------

BOOL CInitializeSession::OpenSession()
{
	//Връзка към базата данни
	CDatabaseConnection* pCDatabaseConnection = CDatabaseConnection::getInstance();

	//Отваряне на сесия
	HRESULT hResult = m_oSession.Open(pCDatabaseConnection->GetDataSource());
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
	m_oSession.Close();
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

// Overrides
// ----------------