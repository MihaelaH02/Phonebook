#pragma once

/////////////////////////////////////////////////////////////////////////////
// CValidateStringData class

class CValidateStringData
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CValidateStringData();
	~CValidateStringData();


// Overrides
// ----------------


// Methods
// ----------------

public:
	/// <summary>
	/// Метод, който проверява дали стринга е във валиден формат 
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се проверява</param>
	/// <returns>Връща съобщение за грешката или празен стренг</returns>
	CString SendStatusMsgForValidStringFormat(const CString& strText);

	/// <summary>
	/// Метод, който задава само първия символ да е главна буква
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се модифицира</param>
	void ValidateDataUpperLetter(CString& strText);

	/// <summary>
	/// Метод, който връща дали е открита грешка
	/// </summary>
	/// <returns>Връща TRUE при открита грешка и FALSE при липса на такава</returns>
	const BOOL IsFinedError() const;

private:
	/// <summary>
	/// Метод за валидация на празни полета
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се валидира</param>
	/// <returns>Връща TRUE, ако данните са с нулева стойност и FALSE, ако не са</returns>
	BOOL IsEmptyString(const CString& strText);

	/// <summary>
	/// Метода за валидация дали стренга се състои само от букви
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се валидира</param>
	/// <returns>Връща TRUE, ако данните са с коректни и FALSE, ако не са</returns>
	BOOL IsOnlyLettersCString(const CString& strText);



// Members
// ----------------
private:
	BOOL m_bFlagHasError;
};
