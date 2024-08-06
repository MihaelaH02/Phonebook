#pragma once

#include "CitiesData.h"
#include "Structures.h"
#include "EnumsWithFlags.h"

/////////////////////////////////////////////////////////////////////////////
// CitiesDoc.h : interface of the CCitiesDoc class
class CCitiesDoc : public CDocument
{
// Macros
// ----------------
protected:
	DECLARE_DYNCREATE(CCitiesDoc)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------


// Constructor / Destructor
// ----------------
protected: // create from serialization only
	CCitiesDoc() noexcept;
public:
	virtual ~CCitiesDoc();


// Overrides
// ----------------
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Methods
// ----------------
public:
	/// <summary>
	/// Метод за зареждане на всички градове 
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL CCitiesDoc::SelectAllCities();

	/// <summary>
	/// Селектира един запис от таблицата с градове
	/// </summary>
	/// <param name="lID">ИД, по което ще се търси запис</param>
	/// <param name="recCity">Структура, която ще съдържа намерения запис</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL SelectCity(const long lID, CITIES& recCity);

	/// <summary>
	/// Редакция на един запис от таблицата с градове
	/// </summary>
	/// <param name="lID">ИД, по което ще се търси запис за модификация</param>
	/// <param name="strCityName">Стренгов параметър с данни да името на града</param>
	/// <param name="strCityRegion">Струнгов параметър с данни за областта на града</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL UpdateCity(const CITIES& recCity);

	/// <summary>
	/// Добавяне на нов запис в таблицата с градове
	/// </summary>
	/// <param name="strCityName">Стренгов параметър с данни да името на града</param>
	/// <param name="strCityRegion">Струнгов параметър с данни за областта на града</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL InsertCity(CITIES& recCity);

	/// <summary>
	/// Изтриване на запис от таблицата с градове
	/// </summary>
	/// <param name="lId">ИД, по което ще се търси запис за изтриване</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL DeleteCity(const CITIES& recCity);

	/// <summary>
	/// Достъп до член променлива на класа
	/// </summary>
	/// <returns>Връща масива с данните от таблицата с градов</returns>
	const CCitiesArray& GetCitiesArray();

	/// <summary>
	/// Метод, който връща размера на масива с градове
	/// </summary>
	/// <returns></returns>
	INT_PTR GetCitiesArrayCount();


// Members
// ----------------
private:
	/// <summary>
	///Член променлива с за досъп до бизнес логиката
	/// </summary>
	CCitiesData m_oCitiesData;

	/// <summary>
	///Член променлива съдърщата масив с данните от таблицата с градове
	/// </summary>
	CCitiesArray m_oCitiesArray;


#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
