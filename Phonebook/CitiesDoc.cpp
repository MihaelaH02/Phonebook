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
}

CCitiesDoc::~CCitiesDoc()
{
}


// Overrides
// ----------------

BOOL CCitiesDoc::OnNewDocument()
{
	SetTitle(_T("Cities"));

	if (!CDocument::OnNewDocument())
	{
		return FALSE;
	}

	//Зареждане на данните от базата данни в масив
	if(!SelectAllCities())
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

BOOL CCitiesDoc::SelectCity(const long lID, CITIES& recCity)
{
	if (!m_oCitiesData.SelectCityWhereID(lID, recCity))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CCitiesDoc::UpdateCity(const CITIES& recCity)
{
	//Редакция в базата данни
	if (!m_oCitiesData.UpdateCityWhereID(recCity.lId, recCity))
	{
		return FALSE;
	}

	//Редакция в масива с данни
	for (INT_PTR nIndex = 0; nIndex < m_oCitiesArray.GetCount(); nIndex++)
	{
		//Превъщаме указател от масива в променлива от тип структура с градове
		CITIES* pCurrentCityFromArray = m_oCitiesArray.GetAt(nIndex);
		if (pCurrentCityFromArray == nullptr)
		{
			return FALSE;
		}

		//Търсим ИД на текущия елемент от масива дали отговаря на подадения, който трябва да се редактира
		if (pCurrentCityFromArray->lId == recCity.lId)
		{
			//Редактираме стойностите на елемента в масива, с тези на подадения като пакаметър структура
			*pCurrentCityFromArray = recCity;

			//Редакция на вютата, подаване на параметър за редакция и обект, който е засегнат
			UpdateAllViews(nullptr, OPERATIONS_WITH_DATA_FLAGS_UPDATE, (CObject*) pCurrentCityFromArray);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CCitiesDoc::InsertCity(CITIES& recCity)
{
	if (!m_oCitiesData.InsertCity(recCity))
	{
		return FALSE;
	}

	//Добавяне на елемента в масива
	m_oCitiesArray.AddElement(recCity);

	//Редакция на вютата, подаване на параметър за добавяне и обект, който е засегнат
	UpdateAllViews(nullptr, OPERATIONS_WITH_DATA_FLAGS_INSERT, (CObject*)&recCity);
	return TRUE;
}

BOOL CCitiesDoc::DeleteCity(const CITIES& recCity)
{

	if (!m_oCitiesData.DeleteCityWhereID(recCity.lId))
	{
		return FALSE;
	}

	//Премахване на елемента от масива
	m_oCitiesArray.RemoveElement(recCity, CompareId);

	//Редакция на вютата, подаване на параметър за изтриване и обект, който е засегнат
	UpdateAllViews(nullptr, OPERATIONS_WITH_DATA_FLAGS_DELETE, (CObject*)&recCity);

	return TRUE;
}

const CCitiesArray& CCitiesDoc::GetCitiesArray()
{
	return m_oCitiesArray;
}

INT_PTR CCitiesDoc::GetCitiesArrayCount()
{
	return m_oCitiesArray.GetCount();
}

BOOL CCitiesDoc::SelectAllCities()
{
	//Зареждане на данните от базата данни в масив
	if (!m_oCitiesData.SelectAllCities(m_oCitiesArray))
	{
		return FALSE;
	}

	return TRUE;
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