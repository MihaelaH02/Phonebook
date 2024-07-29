#include "pch.h"
#include "Phonebook.h"
#include "afxdialogex.h"
#include "CitiesDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesDialog 

IMPLEMENT_DYNAMIC(CCitiesDialog, CDialog)

// Constructor / Destructor
// ----------------
CCitiesDialog::CCitiesDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CITIES_DIALOG, pParent)
{
	m_strName = "";
	m_strRegion = "";
	//Инициализация на член променливи
	m_bFlagEnableControls = TRUE;
}

CCitiesDialog::CCitiesDialog(const CITIES& recCity, BOOL bEnableControls /*=TRUE*/, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CITIES_DIALOG, pParent)
{
	//При подаване на параметри, стринговите член променливи да приемат стойности от подадената структура
	m_strName = recCity.szCityName;
	m_strRegion = recCity.szRegion;

	//Задаване на член променливата флаг, за активност на контролите, да е със стойност подадената
	m_bFlagEnableControls = bEnableControls;
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
	m_edbName.SetWindowTextW(m_strName);
	m_edbRegion.SetWindowTextW(m_strRegion);

	//Активираме или деактивираме контролите за писане
	EnableControls(m_bFlagEnableControls);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CCitiesDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CCitiesDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCitiesDialog::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDB_CITIES_NAME, &CCitiesDialog::OnEnChangeName)
	ON_EN_CHANGE(IDC_EDB_CITIES_REGION, &CCitiesDialog::OnEnChangeRegion)
END_MESSAGE_MAP()


// MFC Message Handlers
// ----------------

void CCitiesDialog::OnBnClickedOk()
{
	//Ако контролите за диалога са в режим на четене
	if (!m_bFlagEnableControls)
	{
		CDialog::OnOK();
	}

	//Визуализация на контролите, съдържащи грешки
	GetDlgItem(IDC_STT_CITIES_NAME_ERROR_MSG)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STT_CITIES_REGION_ERROR_MSG)->ShowWindow(SW_SHOW);

	//Проверка за визуалиризано съобщение за грешка
	if (!m_oValidateStringData.IsFinedError())
	{
		//Превръщаме въведените данни в коректни с валидатора
		m_oValidateStringData.ValidateDataUpperLetter(m_strName);
		m_oValidateStringData.ValidateDataUpperLetter(m_strRegion);

		CDialog::OnOK();
	}
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
	//Проверка за фокус на контролата
	if (!IsControlOnFocus(m_edbName))
	{
		return;
	}

	//Вземаме данните от котролата
	m_edbName.GetWindowTextW(m_strName);

	//Извеждаме подходящо съобщение за грешка
	PrintErrorMsg(m_strName, IDC_STT_CITIES_NAME_ERROR_MSG);
}

void CCitiesDialog::OnEnChangeRegion()
{
	//Проверка за фокус на контролата
	if (!IsControlOnFocus(m_edbRegion))
	{
		return;
	}

	//Времаме данните от котролата
	m_edbRegion.GetWindowTextW(m_strRegion);
	
	//Извеждаме подходящо съобщение за грешка
	PrintErrorMsg(m_strRegion, IDC_STT_CITIES_REGION_ERROR_MSG);
}

CITIES& CCitiesDialog::GetControlsData()
{
	//Задаване на нова структура, която съдържа данните от конторлите
	CITIES recCity;
	_tcscpy_s(recCity.szCityName, m_strName);
	_tcscpy_s(recCity.szRegion, m_strRegion);

	return recCity;
}

BOOL CCitiesDialog::IsEnteredDataDiferent()
{
	//Променливи за новите стойности
	/*CString strNewName, strNewRegion;

	//Вземаме данните от котролата
	m_edbName.GetWindowTextW(strNewName);
	m_edbRegion.GetWindowTextW(strNewRegion);

	for (int i = 0; i < str.GetLength(); ++i)
	{
		if (!islower(str[i]))
		{
			return false;
		}
	}*/

	return FALSE;
}

BOOL CCitiesDialog::IsControlOnFocus(CWnd& oControla)
{
	//Проверка дали контролата е на фокус
	if (GetFocus()->m_hWnd != oControla.m_hWnd)
	{
		return FALSE;
	}

	return TRUE;
}

void CCitiesDialog::PrintErrorMsg(const CString& strText, int nControlaID)
{
	//Визуализираме съобщение за грешка, ако е намерена такава с класа валидатор
	CString strResivedMgs = m_oValidateStringData.SendStatusMsgForValidStringFormat(strText);

	//Задаване на съобщението, като текст в подадената контрола
	SetDlgItemText(nControlaID, strResivedMgs);

	//Правим контролата видима
	GetDlgItem(nControlaID)->ShowWindow(SW_SHOW);
}