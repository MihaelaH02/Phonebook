#pragma once
#include "DefinesDialogCtrInfo.h"
/////////////////////////////////////////////////////////////////////////////
// CValidateStringData class

class CValidateDialogControlsData
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CValidateDialogControlsData();
	~CValidateDialogControlsData();


// Overrides
// ----------------


// Methods
// ----------------

public:
	/// <summary>
	/// Метод, който проверява дали стринга е във валиден формат 
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се проверява</param>
	/// <param name="strAddText">Параметър за допълнителен текст, който ще се проверява, ако е подаден</param> 
	/// <returns>Връща съобщение за грешката или празен стренг</returns>
	CString SendStatusMsgForValidFormat(const CString& strText, BOOL bValidateString = TRUE, const int& nValidLenght = DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_STRING);

	/// <summary>
	/// Метод, който задава само първия символ да е главна буква
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се модифицира</param>
	void ValidateDataUpperLetter(CString& strText);

private:
	/// <summary>
	/// Метод за валидация на празни полета
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се валидира</param>
	/// <returns>Връща TRUE, ако данните са с нулева стойност и FALSE, ако не са</returns>
	BOOL IsEmptyString(const CString& strText);


	BOOL IsValidLenght(const CString& strText, const int nValidLenght);

	/// <summary>
	/// Метода за валидация дали стренга се състои само от букви
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се валидира</param>
	/// <returns>Връща TRUE, ако данните са с коректни и FALSE, ако не са</returns>
	BOOL IsOnlyLettersCString(const CString& strText);



// Members
// ----------------
};
