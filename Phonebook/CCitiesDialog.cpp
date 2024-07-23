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

CCitiesDialog::CCitiesDialog(const CString& strCityName, const CString& strRegion)
{
	//Задаване на стойности за контролите
	m_edbName.SetWindowTextW(strCityName);
	//m_edbRegion.SetWindowTextW(strRegion);

	int nIndex = m_cmbRegion.AddString(strRegion);
	m_cmbRegion.SetCurSel(nIndex);
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

	//Активираме контролите за писане
	EnableControls(TRUE);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CCitiesDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CCitiesDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCitiesDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// MFC Message Handlers
// ----------------

void CCitiesDialog::OnBnClickedOk()
{
	
	if (ValidateStringData()) 
	{
		CDialog::OnOK();
	}
}


void CCitiesDialog::OnBnClickedCancel()
{
	//Зануляване на член променливите
	m_edbName.Clear();
	m_cmbRegion.Clear();

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

BOOL CCitiesDialog::ValidateStringData()
{

	//int nIndex = m_cmbRegion.GetCurSel();
	//m_cmbRegion.GetLBText(nIndex, m_strRegion);

	//смени цветове, стилове големина на буквите
	//Проверка за празни полета
	/*if (m_edbName.Clear() || m_cmbRegion.Clear())
	{
		SetDlgItem(IDC_STATIC, myString);
		IDC_STT_CITIES_NAME_ERROR_MSG.SetWindowText("Field can not be empty!");
		IDC_STT_CITIES_REGION_ERROR_MSG.SetWindowText("Field can not be empty!");
		return FALSE;
	}*/

	//Проверка дали са въведени само букви 
	/*if (m_strName)
	{
		//IDC_STT_CITIES_NAME_ERROR_MSG.SetWindowText("Field must contain only letters!");
		return FALSE;
	}

	//Проверка дали са въведени само букви 
	if (m_strRegion)
	{
		//IDC_STT_CITIES_REGION_ERROR_MSG.SetWindowText("Field must contain only letters!");
		return FALSE;
	}*/

	//Направи пълвата буква да е главна преди да се предадат данните нататъка
	return TRUE;
}

void CCitiesDialog::GetControlsData(CString& strCityName , CString& strRegion)
{
	m_edbName.GetWindowTextW(strCityName);
	m_cmbRegion.GetWindowTextW(strRegion);
}