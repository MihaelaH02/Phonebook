	// CCitiesDialog.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "afxdialogex.h"
#include "CitiesDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesDialog 

IMPLEMENT_DYNAMIC(CCitiesDialog, CDialog)

// Constructor / Destructor
// ----------------

CCitiesDialog::CCitiesDialog(CWnd* pParent /*=nullptr*/,const CString& strCityName /*=NULL*/, const CString& strRegion /*=NULL*/, BOOL bEnableControls /*TRUE*/)
	: CDialog(IDD_CITIES_DIALOG, pParent)
{
	//При подаване на параметри, стринговите член променливи да приемат стойността им
	if (strCityName && strRegion)
	{
		m_strName = strCityName;
		m_strRegion = strRegion;
	}
	m_bEnableControls = bEnableControls;
}

CCitiesDialog::~CCitiesDialog()
{
}


// MFC Overrides
// ----------------

void CCitiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_CITIES_NAME, m_edbName);
	DDX_Control(pDX, IDC_EDB_CITIES_REGION, m_edbRegion);
}

BOOL CCitiesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Задаване на максимална дължина на полетата
	m_edbName.SetLimitText(MAX_LENGTH_STRING);
	m_edbRegion.SetLimitText(MAX_LENGTH_STRING);

	//Задаване на стойности за контролите, ако стринговите член променливи не са нелеви
	if (m_strName && m_strRegion)
	{
		m_edbName.SetWindowTextW(m_strName);
		m_edbRegion.SetWindowTextW(m_strRegion);
	}

	//Активираме или деактивираме контролите за писане
	EnableControls(m_bEnableControls);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CCitiesDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CCitiesDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCitiesDialog::OnBnClickedCancel)
	ON_EN_KILLFOCUS(IDC_EDB_CITIES_NAME, &CCitiesDialog::OnEnKillfocusName)
	ON_EN_KILLFOCUS(IDC_EDB_CITIES_REGION, &CCitiesDialog::OnEnKillfocusRegion)
	ON_EN_CHANGE(IDC_EDB_CITIES_NAME, &CCitiesDialog::OnEnChangeName)
	ON_EN_CHANGE(IDC_EDB_CITIES_REGION, &CCitiesDialog::OnEnChangeRegion)
END_MESSAGE_MAP()


// MFC Message Handlers
// ----------------

void CCitiesDialog::OnBnClickedOk()
{
	//Превръщаме въведените данни в коректи
	ValidateDataUpperLetter(m_strName);
	ValidateDataUpperLetter(m_strRegion);

	CDialog::OnOK();
}


void CCitiesDialog::OnBnClickedCancel()
{
	CDialog::OnCancel();
}
// Overrides
// ----------------


// Methods
// ---------------

void CCitiesDialog::EnableControls(BOOL bEnableControls)
{
	m_edbName.EnableWindow(bEnableControls);
	m_edbRegion.EnableWindow(bEnableControls);
}

void CCitiesDialog::OnEnChangeName()
{
	//Времаме данните от котролата
	m_edbName.GetWindowTextW(m_strName);

	//Визуализираме съобщение за грешка, ако е намерена такава
	CString strResivedMgs = SendStatusMsgForValidStringFormat(m_strName);
	SetDlgItemText(IDC_STT_CITIES_NAME_ERROR_MSG, strResivedMgs);
}

void CCitiesDialog::OnEnChangeRegion()
{
	//Времаме данните от котролата
	m_edbRegion.GetWindowTextW(m_strRegion);

	//Визуализираме съобщение за грешка, ако е намерена такава
	CString strResivedMgs = SendStatusMsgForValidStringFormat(m_strRegion);
	SetDlgItemText(IDC_STT_CITIES_REGION_ERROR_MSG, strResivedMgs);
}

CString CCitiesDialog::SendStatusMsgForValidStringFormat(const CString& strText)
{
	//Проверка за празни полета
	if (IsEmptyString(strText))
	{
		return _T("Filed can not be empty!");
	}

	//Проверка дали са въведени само букви
	if (!IsOnlyLettersCString(strText))
	{
		return _T("Field must contain only letters!");
	}

	//Не е открита грешка
	return _T("");
}

void CCitiesDialog::OnEnKillfocusName()
{	
	//Променлива, която съдържа текста от контролата
	CString strErrorMsg;
	//strErrorMsg.SetTextColor(RGB(255, 0, 0));
	GetDlgItemText(IDC_STT_CITIES_NAME_ERROR_MSG, strErrorMsg);

	//Проверка е визуалиризано съобщение за грешка
	if(!IsEmptyString(strErrorMsg))
	{
		m_edbName.SetFocus();
	}
}

void CCitiesDialog::OnEnKillfocusRegion()
{
	//Променлива, която съдържа текста от контролата
	CString strErrorMsg;
	//strErrorMsg.SetTextColor(RGB(255, 0, 0));
	GetDlgItemText(IDC_STT_CITIES_REGION_ERROR_MSG, strErrorMsg);

	//Проверка е визуалиризано съобщение за грешка
	if (!IsEmptyString(strErrorMsg))
	{
		m_edbRegion.SetFocus();
	}
}

void CCitiesDialog::GetControlsData(CString& strCityName , CString& strRegion)
{
	strCityName = m_strName;
	strRegion = m_strRegion;
}

void CCitiesDialog::ValidateDataUpperLetter(CString& strText) 
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
	//Премахваме спейсовете само в началото
	strText.Mid(nFindStartSpaces);

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

BOOL CCitiesDialog::IsEmptyString(const CString& strText)
{
	//Проверка, дали подадения стринг е празен
	if (strText.IsEmpty())
	{
		return TRUE;
	}
	return FALSE;

	//Проверка дали не са въведени само спейсове
	for (int nIndex = 0; nIndex < strText.GetLength(); ++nIndex)
	{
		if (!isspace(strText[nIndex]))
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CCitiesDialog::IsOnlyLettersCString(const CString& strText)
{
	//Цикъл, който преминава през всички символи на стринга
	for (int nIndex = 0; nIndex < strText.GetLength(); ++nIndex)
	{
		//Ако се открие семвол, който не не буква или спейс
		if (!isalpha(strText[nIndex]) && !isspace(strText[nIndex]))
		{
			return FALSE;
		}
	}
	return TRUE;
}