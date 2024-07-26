#include "pch.h"
#include "Phonebook.h"
#include "afxdialogex.h"
#include "CitiesDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesDialog 

IMPLEMENT_DYNAMIC(CCitiesDialog, CDialog)

// Constructor / Destructor
// ----------------

CCitiesDialog::CCitiesDialog(CWnd* pParent /*=nullptr*/,const CString& strCityName /*=_T("")*/, const CString& strRegion /*=_T("")*/, BOOL bEnableControls /*TRUE*/)
	: CDialog(IDD_CITIES_DIALOG, pParent)
{
	//При подаване на параметри, стринговите член променливи да приемат стойността им
	if (strCityName && strRegion)
	{
		m_strName = strCityName;
		m_strRegion = strRegion;
	}
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
	if (m_strName && m_strRegion)
	{
		m_edbName.SetWindowTextW(m_strName);
		m_edbRegion.SetWindowTextW(m_strRegion);
	}

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
	//Ако не е бил фонусиран нито един едит бокс да се визуализира грешка за празни полета
	GetDlgItem(IDC_STT_CITIES_NAME_ERROR_MSG)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STT_CITIES_REGION_ERROR_MSG)->ShowWindow(SW_SHOW);

	//Проверка за визуалиризано съобщение за грешка
	if (!m_oValidateStringData.IsFinedError())
	{
		//Превръщаме въведените данни в коректи с валидатора
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
	//Проверка дали контролата е на фокус
	if (GetFocus()->m_hWnd != m_edbName.m_hWnd)
	{
		return;
	}

	//Вземаме данните от котролата
	m_edbName.GetWindowTextW(m_strName);

	//Визуализираме съобщение за грешка, ако е намерена такава, от класа валидатор
	CString strResivedMgs = m_oValidateStringData.SendStatusMsgForValidStringFormat(m_strName);
	SetDlgItemText(IDC_STT_CITIES_NAME_ERROR_MSG, strResivedMgs);

	//Правим статичния текст за грешката видим
	GetDlgItem(IDC_STT_CITIES_NAME_ERROR_MSG)->ShowWindow(SW_SHOW);
}

void CCitiesDialog::OnEnChangeRegion()
{
	//Проверка дали контролата е на фокус
	if (GetFocus()->m_hWnd != m_edbRegion.m_hWnd)
	{
		return;
	}

	//Времаме данните от котролата
	m_edbRegion.GetWindowTextW(m_strRegion);

	//Визуализираме съобщение за грешка, ако е намерена такава с класа валидатор
	CString strResivedMgs = m_oValidateStringData.SendStatusMsgForValidStringFormat(m_strRegion);
	SetDlgItemText(IDC_STT_CITIES_REGION_ERROR_MSG, strResivedMgs);

	//Правим статичния текст за грешката видим
	GetDlgItem(IDC_STT_CITIES_REGION_ERROR_MSG)->ShowWindow(SW_SHOW);
}

void CCitiesDialog::GetControlsData(CString& strCityName , CString& strRegion)
{
	strCityName = m_strName;
	strRegion = m_strRegion;
}
