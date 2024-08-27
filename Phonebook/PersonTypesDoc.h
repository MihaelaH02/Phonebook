#pragma once

#include "PersonTypesData.h"
#include "Structures.h"
#include "Flags.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonTypesDoc.h

/// <summary>
/// Клас документ за регистър с типове телефони, наследяващ базов клас
/// </summary>
class CPersonTypesDoc : public CDocument
{

// Macros
// ----------------

protected:
	DECLARE_DYNCREATE(CPersonTypesDoc)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------


// Constructor / Destructor
// ----------------

public:
	CPersonTypesDoc();

	virtual ~CPersonTypesDoc();


// Overrides
// ----------------


// Methods
// ----------------

public:
	/// <summary>
	/// Селектира един запис от таблицата с типове телефони
	/// </summary>
	/// <param name="lID">ИД, по което ще се търси запис</param>
	/// <param name="recPersonType">Структура, която ще съдържа намерения запис</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL SelectPersonType(const long lID, PERSON_TYPES& recPersonType);

	/// <summary>
	/// Редакция на един запис от таблицата с типове телефони
	/// </summary>
	/// <param name="recPersonType">Параметър за запис за модификация</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL UpdatePersonType(const PERSON_TYPES& recPersonType);

	/// <summary>
	/// Добавяне на нов запис в таблицата с типове телфони
	/// </summary>
	/// <param name="recPersonType">Параметър за запис за добавяне</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL InsertPersonType(PERSON_TYPES& recPersonType);

	/// <summary>
	/// Изтриване на запис от таблицата с типове телфони
	/// </summary>
	/// <param name="recPersonType">Параметър запис за изтриване</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL DeletePersonType(const PERSON_TYPES& recPersonType);

	/// <summary>
	/// Достъп до член променлива на класа
	/// </summary>
	/// <returns>Връща масива с данните от таблицата с тиове телефони</returns>
	const CPersonTypesArray& GetPersonTypesArray();

	/// <summary>
	/// Метод, за достъп до размера на масива
	/// </summary>
	/// <returns>Връща броя на елементите в масива</returns>
	INT_PTR GetPersonTypesArrayCount();

private:
	/// <summary>
	/// Метод за селект на всички елементи
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL SelectAllPersonTypesFromData();


// Members
// ----------------

private:
	/// <summary>
	///Член променлива с за досъп до бизнес логиката
	/// </summary>
	CPersonTypesData m_oPersonTypesData;

	/// <summary>
	///Член променлива съдърщата масив с данните от таблицата с типове телефони
	/// </summary>
	CPersonTypesArray m_oPersonTypesArray;


protected:
	virtual BOOL OnNewDocument();
public:
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	virtual void OnCloseDocument();
};
