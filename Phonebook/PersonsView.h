#pragma once


// CPersonsView view

class CPersonsView : public CListView
{
	DECLARE_DYNCREATE(CPersonsView)

protected:
	CPersonsView();           // protected constructor used by dynamic creation
	virtual ~CPersonsView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


