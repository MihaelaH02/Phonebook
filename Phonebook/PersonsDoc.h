#pragma once
#include "PersonsData.h"
#include "Structures.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsDoc.h : interface of the CCitiesDoc class

class CPersonsDoc : public CDocument
{
// Macros
// ----------------
protected:
	DECLARE_DYNCREATE(CPersonsDoc)
	DECLARE_MESSAGE_MAP()

// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPersonsDoc();
	virtual ~CPersonsDoc();

// Overrides
// ----------------
public:
	virtual BOOL OnNewDocument();

#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

// Methods
// ----------------


	/// <summary>
	/// Достъп до член променлива на класа
	/// </summary>
	/// <returns>Връща масива с данните от таблицата с градов</returns>
	const CTableDataArray<CPersonInfo>& GetPersonInfo();

// Members
// ----------------
private:
	/// <summary>
	///Член променлива с за досъп до бизнес логиката
	/// </summary>
	CPersonsData m_oPersonsData;

	/// <summary>
	///Член променлива съдърщата масив с данните от таблицата с градове
	/// </summary>
	CTableDataArray<CPersonInfo> m_oPersonsInfo;	
};
