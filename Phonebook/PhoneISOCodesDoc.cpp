#include "pch.h"
#include "Phonebook.h"
#include "PhoneISOCodesDoc.h"


/////////////////////////////////////////////////////////////////////////////
//  CPhoneISOCodesDoc.cpp

IMPLEMENT_DYNCREATE(CPhoneISOCodesDoc, CDocument)


BEGIN_MESSAGE_MAP(CPhoneISOCodesDoc, CDocument)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CPhoneISOCodesDoc::CPhoneISOCodesDoc()
{
}

CPhoneISOCodesDoc::~CPhoneISOCodesDoc()
{
}

// Overrides
// ----------------
BOOL CPhoneISOCodesDoc::OnNewDocument()
{
	CString strDocName;
	strDocName.Format(_T("ISO Codes %d"), ++nPhoneISOCodesDocCounter);
	SetTitle(strDocName);

	if (!CDocument::OnNewDocument())
	{
		return FALSE;
	}

	if (!SelectAllPhoneISOCodesFromData())
	{
		return FALSE;
	}

	return TRUE;
}

void CPhoneISOCodesDoc::OnCloseDocument()
{
	nPhoneISOCodesDocCounter--;
	CDocument::OnCloseDocument();
}

// Methods
// ----------------
BOOL CPhoneISOCodesDoc::SelectPhoneISOCodes(const long lID, PHONE_ISO_CODES& recPhoneISOCodes)
{
	//Селект на записа
	if (!m_oPhoneISOCodesData.SelectPhoneISOCodeWhereID(lID, recPhoneISOCodes))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPhoneISOCodesDoc::UpdatePhoneISOCode(const PHONE_ISO_CODES& recPhoneISOCodes)
{
	//Редакция на записа
	if (!m_oPhoneISOCodesData.UpdatePhoneISOCodeWhereID(recPhoneISOCodes.lId, recPhoneISOCodes))
	{
		return FALSE;
	}

	//Достъпваме индекса на елемента в масива
	INT_PTR lIndex = m_oPhoneISOCodesArray.FindIndexByElement(recPhoneISOCodes, CompareId);
	if (lIndex == -1)
	{
		return FALSE;
	}

	//Промяна на стойностте на елемента на контретен иднекс
	if (!m_oPhoneISOCodesArray.ReplaceElement(lIndex, recPhoneISOCodes))
	{
		return FALSE;
	}

	//Редакция на вютата, подаване на параметър за редакция и обект, който е засегнат
	UpdateAllViews(nullptr, OPERATIONS_WITH_DATA_FLAGS_UPDATE, (CObject*)&recPhoneISOCodes);
	return TRUE;
}

BOOL CPhoneISOCodesDoc::InsertPhoneISOCode(PHONE_ISO_CODES& recPhoneISOCodes)
{
	//Добавяне на записа
	if (!m_oPhoneISOCodesData.InsertPhoneISOCode(recPhoneISOCodes))
	{
		return FALSE;
	}

	//Добавяне на елемента в масива
	m_oPhoneISOCodesArray.AddElement(recPhoneISOCodes);

	//Редакция на вютата, подаване на параметър за добавяне и обект, който е засегнат
	UpdateAllViews(nullptr, OPERATIONS_WITH_DATA_FLAGS_INSERT, (CObject*)&recPhoneISOCodes);
	return TRUE;
}

BOOL CPhoneISOCodesDoc::DeletePhoneISOCode(const PHONE_ISO_CODES& recPhoneISOCodes)
{
	//Изтриване на записа
	if (!m_oPhoneISOCodesData.DeletePhoneISOCodeWhereID(recPhoneISOCodes.lId))
	{
		return FALSE;
	}

	//Премахване на елемента от масива
	if (!m_oPhoneISOCodesArray.RemoveElement(recPhoneISOCodes, CompareId))
	{
		return FALSE;
	}

	//Редакция на вютата, подаване на параметър за изтриване и обект, който е засегнат
	UpdateAllViews(nullptr, OPERATIONS_WITH_DATA_FLAGS_DELETE, (CObject*)&recPhoneISOCodes);

	return TRUE;
}

const CPhoneISOCodesArray& CPhoneISOCodesDoc::GetPhoneISOCodesArray()
{
	return m_oPhoneISOCodesArray;
}

INT_PTR CPhoneISOCodesDoc::GetPhoneISOCodesArrayCount()
{
	return m_oPhoneISOCodesArray.GetCount();
}

BOOL CPhoneISOCodesDoc::SelectAllPhoneISOCodesFromData()
{
	//Зареждане на данните от базата данни в масив
	if (!m_oPhoneISOCodesData.SelectAllPhoneISOCodes(m_oPhoneISOCodesArray))
	{
		return FALSE;
	}

	return TRUE;
}


#ifndef _WIN32_WCE
void CPhoneISOCodesDoc::Serialize(CArchive& ar)
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


#ifdef _DEBUG
void CPhoneISOCodesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CPhoneISOCodesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG
