#include "pch.h"
#include "ValidateStringData.h"

/////////////////////////////////////////////////////////////////////////////
// CValidateStringData class

// Constants
// ----------------
 

// Constructor / Destructor
// ----------------

CValidateStringData::CValidateStringData() 
{
	//Задаване на начална стойност, на флага за валидация на данните
	m_bFlagHasError = true;
}

CValidateStringData::~CValidateStringData() 
{
}


// Overrides
// ----------------


// Methods
// ----------------

CString CValidateStringData::SendStatusMsgForValidStringFormat(const CString& strText)
{
	//Проверка за празни полета
	if (IsEmptyString(strText))
	{
		m_bFlagHasError = TRUE;
		return _T("Filed can not be empty!");
	}

	//Проверка дали са въведени само букви
	if (!IsOnlyLettersCString(strText))
	{
		m_bFlagHasError = TRUE;
		return _T("Field must contain only letters!");
	}

	//Не е открита грешка
	m_bFlagHasError = FALSE;
	return _T("");
}

const BOOL CValidateStringData::IsFinedError() const
{
	return m_bFlagHasError;
}


void CValidateStringData::ValidateDataUpperLetter(CString& strText)
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

BOOL CValidateStringData::IsEmptyString(const CString& strText)
{
	//Проверка, дали подадения стринг е празен
	if (strText.IsEmpty())
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CValidateStringData::IsOnlyLettersCString(const CString& strText)
{
	//Флаг, който следи за въведена поне една буква
	bool bFlagOneFinedLetter = false;

	//Цикъл, който преминава през всички символи на стринга
	for (int nIndex = 0; nIndex < strText.GetLength(); ++nIndex)
	{
		//Проверка дали символа е беква
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
	if (bFlagOneFinedLetter)
	{
		return TRUE;
	}
}