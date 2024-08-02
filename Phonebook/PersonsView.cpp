// PersonsView.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "PersonsView.h"


// CPersonsView

IMPLEMENT_DYNCREATE(CPersonsView, CListView)

CPersonsView::CPersonsView()
{

}

CPersonsView::~CPersonsView()
{
}

BEGIN_MESSAGE_MAP(CPersonsView, CListView)
END_MESSAGE_MAP()


// CPersonsView diagnostics

#ifdef _DEBUG
void CPersonsView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonsView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPersonsView message handlers
