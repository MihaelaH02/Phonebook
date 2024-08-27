#pragma once

#include "CitiesData.h"
#include "Structures.h"
#include "Flags.h"

/////////////////////////////////////////////////////////////////////////////
// CitiesDoc.h : interface of the CCitiesDoc class

/// <summary>
/// Клас документ за регистър с градове, наследяващ базов клас
/// </summary>
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

protected:
	CCitiesDoc() noexcept;
public:
	virtual ~CCitiesDoc();


// Overrides
// ----------------
public:
	/// <summary>
	/// Метод, който се изпълнява при направата на нов документ от този тип
	/// </summary>
	virtual BOOL OnNewDocument() override;

	virtual void Serialize(CArchive& ar) override;
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif 

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Methods
// ----------------

public:
	/// <summary>
	/// Метод за селект на един запис от таблицата с градове
	/// </summary>
	/// <param name="lID">Параметър за ИД, по което ще се търси запис</param>
	/// <param name="recCity">Параметър - структура, която ще съдържа намерения запис</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL SelectCity(const long lID, CITIES& recCity);

	/// <summary>
	/// Метод за редакция на един запис от таблицата с градове
	/// </summary>
	/// <param name="lID">Параметъл за ИД, по което ще се търси запис за модификация</param>
	/// <param name="recCity">Параметър - структура, която ще съдържа записа с промени</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL UpdateCity(const CITIES& recCity);

	/// <summary>
	/// Метод за добавяне на нов запис в таблицата с градове
	/// </summary>
	/// <param name="recCity">Параметър - структура, която ще съдържа новия запис</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL InsertCity(CITIES& recCity);

	/// <summary>
	/// Метод заиИзтриване на запис от таблицата с градове
	/// </summary>
	/// <param name="recCity">Параметър - структура, която ще съдържа записа за изтриване</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL DeleteCity(const CITIES& recCity);

	/// <summary>
	/// Метод за достъп до член променлива на класа
	/// </summary>
	/// <returns>Връща масива с данните от таблицата с градов</returns>
	const CCitiesArray& GetCitiesArray();

	/// <summary>
	/// Метод, който връща размера на масива с градове
	/// </summary>
	/// <returns></returns>
	INT_PTR GetCitiesArrayCount();

private:
	/// <summary>
	/// Метод за зареждане на всички градове
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL CCitiesDoc::SelectAllCities();


// Members
// ----------------
private:
	/// <summary>
	///Член променлива с за досъп до бизнес логиката на таблица градове
	/// </summary>
	CCitiesData m_oCitiesData;

	/// <summary>
	///Член променлива, съдържаща масив с данните от таблицата с градове
	/// </summary>
	CCitiesArray m_oCitiesArray;


#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual void OnCloseDocument();
};
