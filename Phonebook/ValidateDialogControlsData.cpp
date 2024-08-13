#include "pch.h"
#include "ValidateDialogControlsData.h"

/////////////////////////////////////////////////////////////////////////////
// CValidateStringData class

// Constants
// ----------------
 

// Constructor / Destructor
// ----------------

CValidateDialogControlsData::CValidateDialogControlsData() 
{
}

CValidateDialogControlsData::~CValidateDialogControlsData() 
{
}


// Overrides
// ----------------


// Methods
// ----------------

CString CValidateDialogControlsData::SendStatusMsgForValidFormat(const CString& strText, BOOL bValidateString, const int& nValidLenght)
{
	//Проверка за празни полета
	if (IsEmptyString(strText))
	{
		return ERRROR_MSG_VALIDATION_EMPTY_FIELD;
	}

	//Проверка дали въведения текст отговаря на максималната дължина на полета 
	if (!IsValidLenght(strText, nValidLenght))
	{
		CString strErrorMsg;
		strErrorMsg.Format(ERRROR_MSG_VALIDATION_MAX_SYMBOLS, nValidLenght);
		return strErrorMsg;
	}

	if (bValidateString && !IsOnlyLatinAlpha(strText))
	{
		return ERRROR_MSG_VALIDATION_UNKNOW_SYMBOLS;
	}

	//Проверка дали са въведени само букви
	if (bValidateString && !IsOnlyLettersCString(strText))
	{
		return ERROR_MSG_VALIDATION_ONLY_LETTERS;
	}

	//Не е открита грешка
	return _T("");
}

void CValidateDialogControlsData::ValidateDataUpperLetter(CString& strText)
{
	//Променлива, която проверява колко празни символа имаме преди въведените букви
	int nFindStartSpaces = 0;

	//Цикъл, който брои колко са спейсовете преди началото на буквите
	for (int nIndex = 0; nIndex < strText.GetLength(); ++nIndex)
	{
		if (isspace(strText[nIndex]))
		{
			nFindStartSpaces++;
			continue;
		}
		break;
	}

	//Премахваме спейсовете само в началото, ако има такива
	if (nFindStartSpaces != NULL)
	{
		strText.Mid(nFindStartSpaces);
	}

	//Превръщаме първата буква в главна, ако първата буква е малка
	if (islower(strText[0]))
	{
		strText.SetAt(0, towupper(strText[0]));
	}

	//Цикъл, който ще премине през всеки символ на текста за проверка дали е главна
	for (int nIndex = 1; nIndex < strText.GetLength(); ++nIndex)
	{
		//Ако се открие такава, се превръща в малка
		if (isupper(strText[nIndex]))
		{
			strText.SetAt(nIndex, towlower(strText[nIndex]));
		}

		//Ако имаме някоко думи, буквата след спейса да стане главна
		if (isspace(strText[nIndex]))
		{
			strText.SetAt(++nIndex, towupper(strText[nIndex]));
		}
	}
}

BOOL CValidateDialogControlsData::IsEmptyString(const CString& strText)
{
	//Проверка, дали подадения стринг е празен
	if (strText.IsEmpty() || strText == "0")
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CValidateDialogControlsData::IsValidLenght(const CString& strText, const int nValidLenght)
{
	if (strText.GetLength() >= nValidLenght)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CValidateDialogControlsData::IsOnlyLatinAlpha(const CString& strText)
{
	//Обход на всички букви от текста
	for (int nChar = 0; nChar < strText.GetLength(); ++nChar)
	{
		TCHAR szChar = strText[nChar];

		//Проверка дали са от латинската азб,ка
		if (!((szChar >= _T('A') && szChar <= _T('Z')) ||
			(szChar >= _T('a') && szChar <= _T('z'))))
		{
			return FALSE; 
		}
	}

	return TRUE;
}

BOOL CValidateDialogControlsData::IsOnlyLettersCString(const CString& strText)
{
	//Флаг, който следи за въведена поне една буква
	bool bFlagOneFinedLetter = false;

	//Цикъл, който преминава през всички символи на стринга
	for (int nIndex = 0; nIndex < strText.GetLength(); ++nIndex)
	{
		//Проверка дали символа е буква
		if (isalpha(strText[nIndex]))
		{
			bFlagOneFinedLetter = true;
		}
		//Ако е символа е различен от символ или спийс
		else if (!isspace(strText[nIndex]))
		{
			return FALSE;
		}
	}

	//При открита поне една буква, е не само спейсове
	if (!bFlagOneFinedLetter)
	{
		return FALSE;
	}

	return TRUE;

}