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

// Overrides
// ----------------
BOOL CPersonsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
	{
		return FALSE;
	}
	return TRUE;

	//Зареждане на данните от базата данни в масив
	if (!m_oPersonsData.SelectAllPersonsInfo(m_oPersonsInfo));
	{
		return FALSE;
	}

	return TRUE;
}

CPersonsDoc::~CPersonsDoc()
{
}

const CTableDataArray<CPersonInfo>& CPersonsDoc::GetPersonInfo()
{
	return m_oPersonsInfo;
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
