// PhoneTypesDoc.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "PhoneTypesDoc.h"


/////////////////////////////////////////////////////////////////////////////
//  CPhoneTypesDoc.cpp : implementation of the CCitiesDoc class

IMPLEMENT_DYNCREATE(CPhoneTypesDoc, CDocument)


BEGIN_MESSAGE_MAP(CPhoneTypesDoc, CDocument)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CPhoneTypesDoc::CPhoneTypesDoc()
{
}

CPhoneTypesDoc::~CPhoneTypesDoc()
{
}


// Overrides
// ----------------
BOOL CPhoneTypesDoc::OnNewDocument()
{
	CString strDocName;
	strDocName.Format(_T("Phone types %d"), ++nPhoneTypeDocCounter);
	SetTitle(strDocName);

	if (!CDocument::OnNewDocument())
	{
		return FALSE;
	}

	if (!SelectAllPhoneTypesFromData())
	{
		return FALSE;
	}

	return TRUE;
}

void CPhoneTypesDoc::OnCloseDocument()
{
	nPhoneTypeDocCounter--;
	CDocument::OnCloseDocument();
}

#ifndef _WIN32_WCE

void CPhoneTypesDoc::Serialize(CArchive& ar)
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


// Methods
// ----------------
BOOL CPhoneTypesDoc::SelectPhoneType(const long lID, PHONE_TYPES& recPhoneType)
{
	//Селект на записа
	if (!m_oPhoneTypesData.SelectPhoneTypeWhereID(lID, recPhoneType))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPhoneTypesDoc::UpdatePhoneType(const PHONE_TYPES& recPhoneType)
{
	//Редакция на записа
	if (!m_oPhoneTypesData.UpdatePhoneTypeWhereID(recPhoneType.lId, recPhoneType))
	{
		return FALSE;
	}

	//Достъпваме индекса на елемента в масива
	INT_PTR lIndex = m_oPhoneTypesArray.FindIndexByElement(recPhoneType, CompareId);
	if (lIndex == -1)
	{
		return FALSE;
	}

	//Промяна на стойностте на елемента на контретен иднекс
	if (!m_oPhoneTypesArray.ReplaceElement(lIndex, recPhoneType))
	{
		return FALSE;
	}

	//Редакция на вютата, подаване на параметър за редакция и обект, който е засегнат
	UpdateAllViews(nullptr, OPERATIONS_WITH_DATA_FLAGS_UPDATE, (CObject*)&recPhoneType);
	return TRUE;
}

BOOL CPhoneTypesDoc::InsertPhoneType(PHONE_TYPES& recPhoneType)
{
	//Добавяне на записа
	if (!m_oPhoneTypesData.InsertPhoneType(recPhoneType))
	{
		return FALSE;
	}

	//Добавяне на елемента в масива
	m_oPhoneTypesArray.AddElement(recPhoneType);

	//Редакция на вютата, подаване на параметър за добавяне и обект, който е засегнат
	UpdateAllViews(nullptr, OPERATIONS_WITH_DATA_FLAGS_INSERT, (CObject*)&recPhoneType);
	return TRUE;
}

BOOL CPhoneTypesDoc::DeletePhoneType(const PHONE_TYPES& recPhoneType)
{
	//Изтриване на записа
	if (!m_oPhoneTypesData.DeletePhoneTypeWhereID(recPhoneType.lId))
	{
		return FALSE;
	}

	//Премахване на елемента от масива
	if (!m_oPhoneTypesArray.RemoveElement(recPhoneType, CompareId))
	{
		return FALSE;
	}

	//Редакция на вютата, подаване на параметър за изтриване и обект, който е засегнат
	UpdateAllViews(nullptr, OPERATIONS_WITH_DATA_FLAGS_DELETE, (CObject*)&recPhoneType);

	return TRUE;
}

const CPhoneTypesArray& CPhoneTypesDoc::GetPhoneTypesArray()
{
	return m_oPhoneTypesArray;
}

INT_PTR CPhoneTypesDoc::GetPhoneTypesArrayCount()
{
	return m_oPhoneTypesArray.GetCount();
}

BOOL CPhoneTypesDoc::SelectAllPhoneTypesFromData()
{
	//Зареждане на данните от базата данни в масив
	if (!m_oPhoneTypesData.SelectAllPhoneTypes(m_oPhoneTypesArray))
	{
		return FALSE;
	}

	return TRUE;
}


// CPhoneTypesDoc diagnostics

#ifdef _DEBUG
void CPhoneTypesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CPhoneTypesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

