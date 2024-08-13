#pragma once
#include "DefinesDialogCtrInfo.h"
#include "Messages.h"

/////////////////////////////////////////////////////////////////////////////
// CValidateStringData class

/// <summary>
/// Клас, който отговаря за валидацията на текстови и комбо бокс контрили в диалози
/// </summary>
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
	/// Метод, който проверява дали подадените данни са във валиден формат 
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се проверява</param>
	/// <param name="bValidateString">Параметър флаг, указващ дали проверяваме стринг</param>
	/// <param name="nValidLenght">Параметър за максимален размер, на който подадения текст трябва да отгвораря<param>
	/// <returns>Връща съобщение за грешката или празен стренг</returns>
	CString SendStatusMsgForValidFormat(const CString& strText, BOOL bValidateString = TRUE, const int& nValidLenght = DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_STRING);

	/// <summary>
	/// Метод, който задава само първия символ след спейс да е главна буква
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

	/// <summary>
	/// Метод за валидация на размера на подаден текст
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се валидира</param>
	/// <param name="nValidLenght">Параметър за максимален размер, на който подадения текст трябва да отгвораря</param>
	/// <returns>Връща TRUE, ако данните са с валиден размер FALSE, ако не са</returns>
	BOOL IsValidLenght(const CString& strText, const int nValidLenght);

	/// <summary>
	/// Метод за вализация дали са въведени само латински букви
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се валидира</param>
	/// <returns>Връща TRUE, ако данните са с коректни и FALSE, ако не са</returns>
	BOOL IsOnlyLatinAlpha(const CString& strText);

	/// <summary>
	/// Метода за валидация дали стренга се състои само от букви
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се валидира</param>
	/// <returns>Връща TRUE, ако данните са с коректни и FALSE, ако не са</returns>
	BOOL IsOnlyLettersCString(const CString& strText);


// Members
// ----------------
};
