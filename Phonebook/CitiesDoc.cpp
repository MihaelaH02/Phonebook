#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Phonebook.h"
#endif

#include "CitiesDoc.h"
#include "CitiesData.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
//  CitiesDoc.cpp : implementation of the CCitiesDoc class

IMPLEMENT_DYNCREATE(CCitiesDoc, CDocument)

BEGIN_MESSAGE_MAP(CCitiesDoc, CDocument)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CCitiesDoc::CCitiesDoc() noexcept
{
	// TODO: add one-time construction code here

}

CCitiesDoc::~CCitiesDoc()
{
}


// Overrides
// ----------------

BOOL CCitiesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//Зареждане на данните от базата данни в масив
	if (!m_oCitiesData.SelectAll(m_oCitiesArray))
	{
		return FALSE;
	}
	return TRUE;
}

// CCitiesDoc serialization
void CCitiesDoc::Serialize(CArchive& ar)
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

// Methods
// ----------------

BOOL CCitiesDoc::SelectWhereID(const long lID, CITIES& recCity)
{
	if (!m_oCitiesData.SelectWhereID(lID, recCity))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CCitiesDoc::UpdateWhereID(const CITIES& recCity)
{
	//Редакция в базата данни
	if (!m_oCitiesData.UpdateWhereID(recCity.lId, recCity))
	{
		return FALSE;
	}

	//Редакция в масива с данни
	for (INT_PTR nIndex = 0; nIndex < m_oCitiesArray.GetCount(); nIndex++)
	{
		CITIES* pCity = m_oCitiesArray.GetAt(nIndex);
		if (pCity->lId == recCity.lId)
		{
			pCity->lUpdateCounter = recCity.lUpdateCounter;
			_tcscpy_s(pCity->szCityName, recCity.szCityName);
			_tcscpy_s(pCity->szRegion, recCity.szRegion);

			//Редакция на вютата, подаване на параметър за добавяне и обект, който е засегнат
			UpdateAllViews(nullptr, LPARAM_UPDATE, (CObject*)pCity);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CCitiesDoc::Insert(const CString& strCityName, const CString& strCityRegion)
{
	//Инициализация на нова структура с подадените данни
	CITIES recNewCity;
	_tcscpy_s(recNewCity.szCityName, strCityName);
	_tcscpy_s(recNewCity.szRegion, strCityRegion);

	if (!m_oCitiesData.Insert(recNewCity))
	{
		return FALSE;
	}

	//Добавяне на елемента в масива
	m_oCitiesArray.AddElement(recNewCity);
	CITIES* pCity = m_oCitiesArray.GetAt(m_oCitiesArray.GetCount()-1);

	//Редакция на вютата, подаване на параметър за добавяне и обект, който е засегнат
	UpdateAllViews(nullptr, LPARAM_INSERT, (CObject*)pCity);
	return TRUE;
}

BOOL CCitiesDoc::Delete(const long lId)
{
	if (!m_oCitiesData.DeleteWhereID(lId))
	{
		return FALSE;
	}

	//Премахване на елемента от масива
	m_oCitiesArray.RemoveElemetById(lId);

	//Редакция на вютата, подаване на параметър за изтриване и обект, който е засегнат
	UpdateAllViews(nullptr, LPARAM_DELETE, (CObject*)lId);
	return TRUE;
}

const CCitiesArray& CCitiesDoc::GetCitiesArray() const
{
	return m_oCitiesArray;
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CCitiesDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CCitiesDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCitiesDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCitiesDoc diagnostics

#ifdef _DEBUG
void CCitiesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCitiesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

	// CCitiesDoc commands
