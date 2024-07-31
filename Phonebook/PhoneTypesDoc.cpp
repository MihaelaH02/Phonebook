#include "pch.h"
#include "PhoneTypesDoc.h"


void CPhoneTypesDoc::AssertValid() const
{
	CDocument::AssertValid();

	// TODO: Add your specialized code here and/or call the base class
}


BOOL CPhoneTypesDoc::OnNewDocument()
{
	// TODO: Add your specialized code here and/or call the base class

	return CDocument::OnNewDocument();
}


void CPhoneTypesDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}


void CPhoneTypesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);

	// TODO: Add your specialized code here and/or call the base class
}
