// PersonsDoc.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "PersonsDoc.h"

/////////////////////////////////////////////////////////////////////////////
//  CPersonsDoc.cpp : implementation of the CCitiesDoc class

IMPLEMENT_DYNCREATE(CPersonsDoc, CDocument)

BEGIN_MESSAGE_MAP(CPersonsDoc, CDocument)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------

CPersonsDoc::CPersonsDoc()
{
}

CPersonsDoc::~CPersonsDoc()
{
}


// Overrides
// ----------------
BOOL CPersonsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
	{
		return FALSE;
	}

	//Зареждане на данните от базата данни в масив
	if (!m_oPersonsData.SelectAllPersonsInfo(m_oPersonsInfo))
	{
		return FALSE;
	}

	return TRUE;
}

const CTableDataArray<CPersonInfo>& CPersonsDoc::GetPersonInfo()
{
	return m_oPersonsInfo;
}

INT_PTR CPersonsDoc::GetPersonsArrayElementsCount()
{
	return m_oPersonsInfo.GetCount();
}

BOOL CPersonsDoc::SelectPersonInfoWithId(const long lID, CPersonInfo& oPersonInfo)
{
	//Селект на клиент и информацията за него по ид
	if (!m_oPersonsData.SelectPersonInfoWithId(lID, oPersonInfo))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPersonsDoc::ManagePersonInfo(CPersonInfo& oPersonInfo, LPARAM oOperationFlag)
{
	//Ивършване на операции в зависимост от флага
	if (!m_oPersonsData.ManagePersonInfo(oPersonInfo, oOperationFlag))
	{
		return FALSE;
	}
	return TRUE;
}


// CPersonsDoc diagnostics

#ifdef _DEBUG
void CPersonsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CPersonsDoc serialization

void CPersonsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}
#endif


// CPersonsDoc commands
