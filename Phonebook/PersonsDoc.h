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
	/// <returns>Връща масива с информацията за клиенти</returns>
	const CTableDataArray<CPersonInfo>& GetPersonInfo();

	/// <summary>
	/// Метод, който достъпва броя на клиентите
	/// </summary>
	/// <returns>Връща броя на елемените в масива с информация на кленти</returns>
	int GetPersonsArrayElementsCount();

	/// <summary>
	/// Метод, който селектира клиеит по ид
	/// </summary>
	/// <param name="lID">Ид на клиент по което ще се търсят данни</param>
	/// <param name="oPersonInfo">Масив с намерена ииформация за клиет</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL SelectPersonInfoWithId(const long lID, CPersonInfo& oPersonInfo);

	/// <summary>
	/// Метод за обработка на операции с информацията за клиенти
	/// </summary>
	BOOL ManagePersonInfo(CPersonInfo& oPersonInfo, LPARAM oOperationFlag);


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
