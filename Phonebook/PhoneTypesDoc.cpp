// PhoneTypesDoc.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "PhoneTypesDoc.h"

/*
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
	if (!CDocument::OnNewDocument())
	{
		return FALSE;
	}

	//Зареждане на данните от базата данни в масив
	if (!m_oPhoneTypesData.SelectAll(m_oPhoneTypesArray))
	{
		return FALSE;
	}
	return TRUE;
}

#ifndef _WIN32_WCE
// CPhoneTypesDoc serialization

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
	if (!m_oPhoneTypesData.SelectWhereID(lID, recPhoneType))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPhoneTypesDoc::UpdatePhoneType(const PHONE_TYPES& recPhoneType)
{
	//Редакция в базата данни
	if (!m_oPhoneTypesData.UpdateWhereID(recPhoneType.lId, recPhoneType))
	{
		return FALSE;
	}

	//Редакция в масива с данни
	for (INT_PTR nIndex = 0; nIndex < m_oPhoneTypesArray.GetCount(); nIndex++)
	{
		//Превъщаме указател от масива в променлива от тип структура с градове
		PHONE_TYPES* pCurrentPhoneTypeFromArray = m_oPhoneTypesArray.GetAt(nIndex);
		if (pCurrentPhoneTypeFromArray == nullptr)
		{
			return FALSE;
		}

		//Търсим ИД на текущия елемент от масива дали отговаря на подадения, който трябва да се редактира
		if (pCurrentPhoneTypeFromArray->lId == recPhoneType.lId)
		{
			//Редактираме стойностите на елемента в масива, с тези на подадения като пакаметър структура
			*pCurrentPhoneTypeFromArray = recPhoneType;

			//Редакция на вютата, подаване на параметър за редакция и обект, който е засегнат
			UpdateAllViews(nullptr, OPERATIONS_WITH_DATA_FLAGS_UPDATE, (CObject*)pCurrentPhoneTypeFromArray);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPhoneTypesDoc::Insert(PHONE_TYPES& recPhoneType)
{
	if (!m_oPhoneTypesData.Insert(recPhoneType))
	{
		return FALSE;
	}

	//Добавяне на елемента в масива
	m_oPhoneTypesArray.AddElement(recPhoneType);

	//Редакция на вютата, подаване на параметър за добавяне и обект, който е засегнат
	UpdateAllViews(nullptr, OPERATIONS_WITH_DATA_FLAGS_INSERT, (CObject*)&recPhoneType);
	return TRUE;
}

BOOL CPhoneTypesDoc::Delete(const PHONE_TYPES& recPhoneType)
{

	if (!m_oPhoneTypesData.DeleteWhereID(recPhoneType.lId))
	{
		return FALSE;
	}

	//Премахване на елемента от масива
	m_oPhoneTypesArray.RemoveElement(recPhoneType);

	//Редакция на вютата, подаване на параметър за изтриване и обект, който е засегнат
	UpdateAllViews(nullptr, OPERATIONS_WITH_DATA_FLAGS_DELETE, (CObject*)&recPhoneType);

	return TRUE;
}

const CPhoneTypesArray& CPhoneTypesDoc::GetPhoneTypesArray()
{
	return m_oPhoneTypesArray;
}

INT_PTR CPhoneTypesDoc::GetPhoneTypesArrayElementsCount()
{
	return m_oPhoneTypesArray.GetCount();
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

*/