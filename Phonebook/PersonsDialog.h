#pragma once
#include "afxdialogex.h"
#include "PersonInfo.h"
#include "EnumsWithFlags.h"
#include "AdditionInfo.h"


// CPersonsDialog dialog

class CPersonsDialog : public CDialogEx
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CPersonsDialog)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONS_DIALOG };
#endif


// Constructor / Destructor
// ----------------
public:
	/// <param name="oEnableControls">Параметър, който приема стойност от енюм за това кои от контролите да са активни за писане</param>
	CPersonsDialog(LPARAM oEnableControls = ENABLE_DIALOG_CTR_FLAG_ALL, CWnd* pParent = nullptr);

	/// <param name="oPerson">Параметър клас с данни, чиито стойности ще се визуализират в контролите на диалога</param>
	CPersonsDialog(const CPersonInfo& oPerson, const CAdditionInfo& oAdditionInfo, LPARAM oEnableControls = ENABLE_DIALOG_CTR_FLAG_ALL, CWnd* pParent = nullptr);

	virtual ~CPersonsDialog();


// MFC Overrides
// ----------------	

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	virtual BOOL OnInitDialog();


// MFC Message Handlers
// ----------------
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedEdit();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

// Overrides
// ----------------


// Methods
// ----------------
private:
	BOOL AddItemsInCmbCities();
	BOOL AddItemsInListCtrPhoneNumbers();

// Members
// ----------------

	/// <summary>
	/// Член променлива за текстова контрола с име на клиент
	/// </summary>
	CEdit m_edbFirstName;

	/// <summary>
	/// Член променлива за текстова контрола с презиме на клиент
	/// </summary>
	CEdit m_edbLastName;

	/// <summary>
	/// Член променлива за текстова контрола с фамилия на клиент
	/// </summary>
	CEdit m_edbSecondName;

	/// <summary>
	/// Член променлива за текстова контрола за егн на клиент
	/// </summary>
	CEdit m_edbEGN;

	/// <summary>
	/// Член променлива за комбо бокс с градове
	/// </summary>
	CComboBox m_cmbCities;

	/// <summary>
	/// Член променлива за по-дълга текстова контрола за адрес на клиент
	/// </summary>
	CRichEditCtrl m_recAddress;

	/// <summary>
	/// Член променлива за лест контрола с телефонни номера на клиент
	/// </summary>
	CListCtrl m_lscPhoneNumbers;

	/// <summary>
	/// Член променлива за обмяна на данни с контролата за име на клиент
	/// </summary>
	CString m_strFirstName;

	/// <summary>
	/// Член променлива за обмяна на данни с контролата за презиме на клиент
	/// </summary>
	CString m_strSecondName;

	/// <summary>
	/// Член променлива за обмяна на данни с контролата за фамилия на клиент
	/// </summary>
	CString m_strLastName;

	/// <summary>
	/// Член променлива за обмяна на данни с контролата за егн на клиент
	/// </summary>
	CString m_strEGN;

	/// <summary>
	/// Член променлива за обмяна на данни с контролата за егн на клиент
	/// </summary>
	int m_nIdCity;

	/// <summary>
	/// Член променлива за обмяна на данни с контролата за егн на клиент
	/// </summary>
	CString m_strAddress;

	/// <summary>
	/// Член променлива масив, която съдържа всички телефонни номера за клиент
	/// </summary>
	CPhoneNumbersArray m_oPhoneNumbersArray;

	/// <summary>
	/// Променлива, която съдържа всички градове
	/// </summary>
	CCitiesArray m_oCitiesArray;

	/// <summary>
	/// Променлива, която съдържа всчики типове телефони
	/// </summary>
	CPhoneTypesArray m_oPhoneTypesArray;

	/// <summary>
	/// Член променлива, която съдържа параметъра за активност на контролите
	/// </summary>
	LPARAM m_oEnableControlsParam;
	
};