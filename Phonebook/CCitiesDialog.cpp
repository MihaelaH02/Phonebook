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

CCitiesDialog::CCitiesDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CITIES_DIALOG, pParent)
{
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
	DDX_Control(pDX, IDC_CMB_CITIES_REGION, m_cmbRegion);
	//DDV_MaxChars(pDX, m_edbName, 128);
	//DDV_MaxChars(pDX, m_cmbRegion, 128);

}

BOOL CCitiesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Задаване на стойности в контролите
	
	if (m_strRegion.IsEmpty() || m_strName.IsEmpty())
	{
		return TRUE;
		
	}
	m_edbName.SetWindowTextW(m_strName);
	int nIndex = m_cmbRegion.AddString(m_strRegion);
	m_cmbRegion.SetCurSel(nIndex);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CCitiesDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CCitiesDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCitiesDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// MFC Message Handlers
// ----------------

//Проверки за 0, за вече въведена стойност!!!!!!!!!
void CCitiesDialog::OnBnClickedOk()
{
	//Предаване на стойностите в контролите
	m_edbName.GetWindowText(m_strName);

	//int nIndex = m_cmbRegion.GetCurSel();
	//m_cmbRegion.GetLBText(nIndex, m_strRegion);
	m_cmbRegion.GetWindowText(m_strRegion);

	CDialog::OnOK();
}


void CCitiesDialog::OnBnClickedCancel()
{
	//Зануляване на член променливите
	m_strName.Empty();
	m_strRegion.Empty();
	m_edbName.Clear();
	m_cmbRegion.Clear();

	//Активиране на контролите за писане по тях
	EnableControls(TRUE);

	CDialog::OnCancel();
}


// Overrides
// ----------------


// Methods
// ---------------

void CCitiesDialog::EnableControls(BOOL bBooleanFlag)
{
		m_edbName.EnableWindow(bBooleanFlag);
		m_cmbRegion.EnableWindow(bBooleanFlag);
}


