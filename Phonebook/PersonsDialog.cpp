// PersonsDialog.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "afxdialogex.h"
#include "PersonsDialog.h"
#include "AdditionInfo.h"


// CPersonsDialog dialog

IMPLEMENT_DYNAMIC(CPersonsDialog, CDialogEx)

CPersonsDialog::CPersonsDialog(LPARAM oEnableControls /*= ENABLE_CONTROLS_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PERSONS_DIALOG, pParent)
{
	SecureZeroMemory(this, sizeof(*this));
}

CPersonsDialog::CPersonsDialog(const CPersonInfo& oPersonInfo, const CAdditionInfo& oAdditionInfo, LPARAM oEnableControls /*= ENABLE_CONTROLS_FLAG_ALL*/, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PERSONS_DIALOG, pParent) 
{
	//Подаваме всички данни за клиент към член променливите, които съхраняват съответните данни
	PERSONS recPerson = oPersonInfo.GetPerson();
	m_strFirstName = recPerson.szFirstName;
	m_strSecondName = recPerson.szSecondName;
	m_strLastName = recPerson.szLastName;
	m_strEGN = recPerson.szEGN;
	m_nIdCity = recPerson.lIdCity;
	m_strAddress = recPerson.szAddress;

	//Подаваме данни към масивите, съхраняващи съответните данни
	//m_oPhoneNumbersArray = oPersonInfo.GetPhoneNumbers();
	//m_oCitiesArray = oAdditionInfo.GetAllCities();
	//m_oPhoneTypesArray = oAdditionInfo.GetAllPhoneTypes();
}

CPersonsDialog::~CPersonsDialog()
{
}

void CPersonsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PERSONS_FIRTSNAME, m_edbFirstName);
	DDX_Control(pDX, IDC_EDB_PERSONS_SECONDNAME, m_edbSecondName);
	DDX_Control(pDX, IDC_EDB_PERSONS_LASTNAME, m_edbLastName);
	DDX_Control(pDX, IDC_EDB_PERSONS_EGN, m_edbEGN);
	DDX_Control(pDX, IDC_CMB_PERSONS_CITIES, m_cmbCities);
	DDX_Control(pDX, IDC_REC_PERSONS_ADDRESS, m_recAddress);
	DDX_Control(pDX, IDC_LSC_PHONE_NUMBERS, m_lscPhoneNumbers);
}

BOOL CPersonsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Задаване на максимална дължина на полетата
	//m_edbName.SetLimitText(MAX_LENGTH_STRING);
	//m_edbRegion.SetLimitText(MAX_LENGTH_STRING);

	//Задаване на стойности за контролите
	m_edbFirstName.SetWindowTextW(m_strFirstName);
	m_edbSecondName.SetWindowTextW(m_strSecondName);
	m_edbLastName.SetWindowTextW(m_strLastName);
	m_edbEGN.SetWindowTextW(m_strEGN);

	if (AddItemsInCmbCities())
	{
		return;
	}

	int nIndexCity = m_cmbCities.GetItemData(m_nIdCity);
	m_cmbCities.SetCurSel(nIndexCity);

	m_recAddress.SetWindowTextW(m_strAddress);

	//Промяна на активността на контролите, според подадения параметър
	//EnableControls(m_oEnableControlsParam);

	//Напълни лист контролата

	return TRUE;
}

BEGIN_MESSAGE_MAP(CPersonsDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_PHONE_NUMBERS_ADD, &CPersonsDialog::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BTN_PHONE_NUMBERS_EDIT, &CPersonsDialog::OnBnClickedEdit)
	ON_BN_CLICKED(IDC_BTN_PHONE_NUMBERS_DELETE, &CPersonsDialog::OnBnClickedDelete)
	ON_BN_CLICKED(IDOK, &CPersonsDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPersonsDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CPersonsDialog message handlers


void CPersonsDialog::OnBnClickedAdd()
{
	// TODO: Add your control notification handler code here
}


void CPersonsDialog::OnBnClickedEdit()
{
	// TODO: Add your control notification handler code here
}


void CPersonsDialog::OnBnClickedDelete()
{
	// TODO: Add your control notification handler code here
}


void CPersonsDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CPersonsDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


BOOL CPersonsDialog::AddItemsInCmbCities()
{
	for (INT_PTR nIndex = 0; nIndex < m_oCitiesArray.GetCount(); nIndex++)
	{
		CITIES* pCities = m_oCitiesArray.GetAt(nIndex);

		if (pCities == nullptr)
		{
			return FALSE;
		}
		CString strTextToAdd;
		strTextToAdd.Format(_T("%s - %s"), pCities->szCityName, pCities->szRegion);

		int nIndexRow = m_cmbCities.AddString(strTextToAdd);
		m_cmbCities.SetItemData(nIndexRow, pCities->lId);
	}
	return TRUE;
}

BOOL CPersonsDialog::AddItemsInListCtrPhoneNumbers()
{

}