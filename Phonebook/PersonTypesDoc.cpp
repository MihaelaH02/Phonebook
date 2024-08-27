#include "pch.h"
#include "Phonebook.h"
#include "PersonTypesDoc.h"


/////////////////////////////////////////////////////////////////////////////
//  CPersonTypesDoc.cpp

IMPLEMENT_DYNCREATE(CPersonTypesDoc, CDocument)

BEGIN_MESSAGE_MAP(CPersonTypesDoc, CDocument)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------

CPersonTypesDoc::CPersonTypesDoc()
{
}

CPersonTypesDoc::~CPersonTypesDoc()
{
}


// Overrides
// ----------------
BOOL CPersonTypesDoc::OnNewDocument()
{
	CString strDocName;
	strDocName.Format(_T("Person types %d"), ++nPersonTypeDocCounter);
	SetTitle(strDocName);

	if (!CDocument::OnNewDocument())
	{
		return FALSE;
	}

	if (!SelectAllPersonTypesFromData())
	{
		return FALSE;
	}

	return TRUE;
}

void CPersonTypesDoc::OnCloseDocument()
{
	nPersonTypeDocCounter--;
	CDocument::OnCloseDocument();
}


// Methods
// ----------------
BOOL CPersonTypesDoc::SelectPersonType(const long lID, PERSON_TYPES& recPersonType)
{
	//Селект на записа
	if (!m_oPersonTypesData.SelectPersonTypeWhereID(lID, recPersonType))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPersonTypesDoc::UpdatePersonType(const PERSON_TYPES& recPersonType)
{
	//Редакция на записа
	if (!m_oPersonTypesData.UpdatePersonTypeWhereID(recPersonType.lId, recPersonType))
	{
		return FALSE;
	}

	//Достъпваме индекса на елемента в масива
	INT_PTR lIndex = m_oPersonTypesArray.FindIndexByElement(recPersonType, CompareId);
	if (lIndex == -1)
	{
		return FALSE;
	}

	//Промяна на стойностте на елемента на контретен иднекс
	if (!m_oPersonTypesArray.ReplaceElement(lIndex, recPersonType))
	{
		return FALSE;
	}

	//Редакция на вютата, подаване на параметър за редакция и обект, който е засегнат
	UpdateAllViews(nullptr, OPERATIONS_WITH_DATA_FLAGS_UPDATE, (CObject*)&recPersonType);
	return TRUE;
}

BOOL CPersonTypesDoc::InsertPersonType(PERSON_TYPES& recPersonType)
{
	//Добавяне на записа
	if (!m_oPersonTypesData.InsertPersonType(recPersonType))
	{
		return FALSE;
	}

	//Добавяне на елемента в масива
	m_oPersonTypesArray.AddElement(recPersonType);

	//Редакция на вютата, подаване на параметър за добавяне и обект, който е засегнат
	UpdateAllViews(nullptr, OPERATIONS_WITH_DATA_FLAGS_INSERT, (CObject*)&recPersonType);
	return TRUE;
}

BOOL CPersonTypesDoc::DeletePersonType(const PERSON_TYPES& recPersonType)
{
	//Изтриване на записа
	if (!m_oPersonTypesData.DeletePersonTypeWhereID(recPersonType.lId))
	{
		return FALSE;
	}

	//Премахване на елемента от масива
	if (!m_oPersonTypesArray.RemoveElement(recPersonType, CompareId))
	{
		return FALSE;
	}

	//Редакция на вютата, подаване на параметър за изтриване и обект, който е засегнат
	UpdateAllViews(nullptr, OPERATIONS_WITH_DATA_FLAGS_DELETE, (CObject*)&recPersonType);

	return TRUE;
}

const CPersonTypesArray& CPersonTypesDoc::GetPersonTypesArray()
{
	return m_oPersonTypesArray;
}

INT_PTR CPersonTypesDoc::GetPersonTypesArrayCount()
{
	return m_oPersonTypesArray.GetCount();
}

BOOL CPersonTypesDoc::SelectAllPersonTypesFromData()
{
	//Зареждане на данните от базата данни в масив
	if (!m_oPersonTypesData.SelectAllPersonTypes(m_oPersonTypesArray))
	{
		return FALSE;
	}

	return TRUE;
}


#ifdef _DEBUG
void CPersonTypesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonTypesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE

// CPersonTypesDoc serialization
void CPersonTypesDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}
#endif

