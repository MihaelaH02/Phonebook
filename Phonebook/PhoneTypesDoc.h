#pragma once

#include "PhoneTypesData.h"
#include "Structures.h"
#include "Flags.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDoc.h : interface of the CCitiesDoc class

/// <summary>
/// Клас документ за регистър с типове телефони, наследяващ базов клас
/// </summary>
class CPhoneTypesDoc : public CDocument
{

// Macros
// ----------------

protected:
	DECLARE_DYNCREATE(CPhoneTypesDoc)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------


// Constructor / Destructor
// ----------------

public:
	CPhoneTypesDoc();

	virtual ~CPhoneTypesDoc();


// Overrides
// ----------------


// Methods
// ----------------

public:

	/// <summary>
	/// Селектира един запис от таблицата с типове телефони
	/// </summary>
	/// <param name="lID">ИД, по което ще се търси запис</param>
	/// <param name="recPhoneType">Структура, която ще съдържа намерения запис</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL SelectPhoneType(const long lID, PHONE_TYPES& recPhoneType);

	/// <summary>
	/// Редакция на един запис от таблицата с типове телефони
	/// </summary>
	/// <param name="recPhoneType">запис за модификация</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL UpdatePhoneType(const PHONE_TYPES& recPhoneType);

	/// <summary>
	/// Добавяне на нов запис в таблицата с типове телфони
	/// </summary>
	/// <param name="strCityName">Стренгов параметър с данни да името на града</param>
	/// <param name="strCityRegion">Струнгов параметър с данни за областта на града</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL InsertPhoneType(PHONE_TYPES& recPhoneType);

	/// <summary>
	/// Изтриване на запис от таблицата с типове телфони
	/// </summary>
	/// <param name="recPhoneType"> запис за изтриване</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL DeletePhoneType(const PHONE_TYPES& recPhoneType);

	/// <summary>
	/// Достъп до член променлива на класа
	/// </summary>
	/// <returns>Връща масива с данните от таблицата с тиове телефони</returns>
	const CPhoneTypesArray& GetPhoneTypesArray();

	/// <summary>
	/// Метод, за достъп до размера на масива с типове телефони
	/// </summary>
	/// <returns></returns>
	INT_PTR GetPhoneTypesArrayCount();

private:
	/// <summary>
	/// Метод за селект на всички типове телефонни номера 
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL SelectAllPhoneTypesFromData();


	// Members
	// ----------------
private:
	/// <summary>
	///Член променлива с за досъп до бизнес логиката
	/// </summary>
	CPhoneTypesData m_oPhoneTypesData;

	/// <summary>
	///Член променлива съдърщата масив с данните от таблицата с типове телефони
	/// </summary>
	CPhoneTypesArray m_oPhoneTypesArray;


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
};
