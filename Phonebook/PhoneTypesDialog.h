#pragma once
#include "afxdialogex.h"
#include "Structures.h"
#include "ValidateStringData.h"
#include "EnumsWithFlags.h"
#include "EnumsDialogCtrInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDialog dialog

class CPhoneTypesDialog : public CDialog
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CPhoneTypesDialog)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONE_TYPES_DIALOG };
#endif


// Constructor / Destructor
// ----------------
public:
	CPhoneTypesDialog(LPARAM oEnableControls = ENABLE_DIALOG_CITIES_CTR_FLAG_ALL, CWnd* pParent = nullptr);

	CPhoneTypesDialog(const PHONE_TYPES& recPhoneType, LPARAM oEnableControls = ENABLE_DIALOG_CITIES_CTR_FLAG_ALL, CWnd* pParent = nullptr);

	virtual ~CPhoneTypesDialog();


// MFC Overrides
// ----------------	
private:
	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	virtual BOOL OnInitDialog() override;


// MFC Message Handlers
// ----------------
private:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();


// Overrides
// ----------------


// Methods
// ----------------
public:
	/// <summary>
	/// Достъп до стойности за стринговите член променливи
	/// </summary>
	/// <returns>Връща структура от тип градове</returns>
	BOOL GetControlsData(PHONE_TYPES& recPhoneType);

	/// <summary>
	/// Метод за забрана за писане по контролите
	/// </summary>
	void EnableControls(LPARAM oEnableControls);


// Members
// ----------------
private:
	/// <summary>
	/// Член променлива за текстова контрола с име на град
	/// </summary>
	CEdit m_edbPhoneType;

	/// <summary>
	/// 
	/// </summary>
	CString m_strPhoneType;

	/// <summary>
	/// Член променлива, която съдържа параметъра за активност на контролите
	/// </summary>
	LPARAM m_oEnableControlsParam;
};
