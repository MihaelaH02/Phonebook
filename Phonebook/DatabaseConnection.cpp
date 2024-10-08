#include "pch.h"
#include <atldbcli.h>
#include <afxtempl.h>
#include "DatabaseConnection.h"

/////////////////////////////////////////////////////////////////////////////
// CDatabaseConnection

/// <summary> Начална инициализация на статична променлива</summary>
CDatabaseConnection* CDatabaseConnection::m_pInstancePtr = NULL;

// Constructor / Destructor
// ----------------

CDatabaseConnection::CDatabaseConnection()
{
}

CDatabaseConnection::~CDatabaseConnection()
{
	delete m_pInstancePtr;
	m_pInstancePtr = nullptr;
}

// Methods
// ----------------
BOOL CDatabaseConnection::ConnectToDatabaseSource()
{
	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("Mihaela"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("Phonebook"));
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	HRESULT hResult = m_oDataSource.Open(_T("SQLOLEDB.1"), &oDBPropSet);
	if (FAILED(hResult))
	{
		CString strMessage;
		strMessage.Format(_T("Unable to connect to SQL Server database. Error: %d"), hResult);
		AfxMessageBox(strMessage);
		return FALSE;
	}
	return TRUE;
}

BOOL CDatabaseConnection::CloseDatabaseSource()
{
	m_oDataSource.Close();
	return TRUE;
}

CDatabaseConnection* CDatabaseConnection::getInstance()
{
	if (m_pInstancePtr == nullptr)
	{
		m_pInstancePtr = new CDatabaseConnection();
	}
	return m_pInstancePtr;
}

CDataSource& CDatabaseConnection::GetDataSource()
{
	return m_oDataSource;
}


// Overrides
// ----------------