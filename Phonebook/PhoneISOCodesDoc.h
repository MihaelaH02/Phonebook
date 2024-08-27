#pragma once

#include "PhoneISOCodesData.h"
#include "Structures.h"
#include "Flags.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneISOCodesDoc

class CPhoneISOCodesDoc : public CDocument
{
// Macros
// ----------------
protected:
	DECLARE_DYNCREATE(CPhoneISOCodesDoc)
	DECLARE_MESSAGE_MAP()

// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPhoneISOCodesDoc();
	virtual ~CPhoneISOCodesDoc();

// Overrides
// ----------------


// Methods
// ----------------

	/// <summary>
	/// Селектира един запис от таблицата с кодове за държави
	/// </summary>
	/// <param name="lID">ИД, по което ще се търси запис</param>
	/// <param name="recPhoneISOCodes">Структура, която ще съдържа намерения запис</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL SelectPhoneISOCodes(const long lID, PHONE_ISO_CODES& recPhoneISOCodes);

	/// <summary>
	/// Редакция на един запис от таблицата с кодове за държави
	/// </summary>
	/// <param name="recPhoneISOCodes">Параметър за запис за модификация</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL UpdatePhoneISOCode(const PHONE_ISO_CODES& recPhoneISOCodes);

	/// <summary>
	/// Добавяне на нов запис в таблицата с кодове за държави
	/// </summary>
	/// <param name="recPhoneISOCodes">Параметър за запис за добавяне</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL InsertPhoneISOCode(PHONE_ISO_CODES& recPhoneISOCodes);

	/// <summary>
	/// Изтриване на запис от таблицата с кодове за държави
	/// </summary>
	/// <param name="recPhoneISOCodes">Параметър за запис за изтриване</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL DeletePhoneISOCode(const PHONE_ISO_CODES& recPhoneISOCodes);

	/// <summary>
	/// Достъп до член променлива на класа
	/// </summary>
	/// <returns>Връща масива с данните от таблицата с кодове за държави</returns>
	const CPhoneISOCodesArray& GetPhoneISOCodesArray();

	/// <summary>
	/// Метод, за достъп до размера на масива с кодове за държави
	/// </summary>
	/// <returns></returns>
	INT_PTR GetPhoneISOCodesArrayCount();

private:
	/// <summary>
	/// Метод за селект на всички кодове за държави
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспух</returns>
	BOOL SelectAllPhoneISOCodesFromData();


// Members
// ----------------
private:
	/// <summary>
	///Член променлива с за досъп до бизнес логиката
	/// </summary>
	CPhoneISOCodesData m_oPhoneISOCodesData;

	/// <summary>
	///Член променлива съдърщата масив с данните от таблицата с кодове с държави
	/// </summary>
	CPhoneISOCodesArray m_oPhoneISOCodesArray;


#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar); 
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument() override;

public:
	virtual void OnCloseDocument();
};
