#pragma once
#include "afxdialogex.h"
#include "Structures.h"
#include "ValidateStringData.h"
#include "EnumsWithFlags.h"
#include "EnumsDialogCtrInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersDialog dialog

class CPhoneNumbersDialog : public CDialog
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CPhoneNumbersDialog)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PHONE_NUMBERS };
#endif


// Constructor / Destructor
// ----------------
public:
	CPhoneNumbersDialog(const CPhoneTypesArray& oPhoneTypesArray, LPARAM lEnableControls = ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ALL, CWnd* pParent = nullptr); 
	CPhoneNumbersDialog(const CPhoneTypesArray& oPhoneTypesArray, const PHONE_NUMBERS& recPhoneNumber, LPARAM lEnableControls = ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ALL, CWnd* pParent = nullptr);
	virtual ~CPhoneNumbersDialog();


// MFC Overrides
// ----------------	
protected:
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
	/// <returns>Връща TRUE при успех и FALSE при открита грешка</returns>
	 BOOL GetControlsData(PHONE_NUMBERS& recPhoneNumber);

	/// <summary>
	/// Метод за забрана за писане по контролите
	/// </summary>
	void EnableControls(LPARAM lEnableControls);

	/// <summary>
	/// Метод, който довабя елементи в комбо бокса с телефонни номера
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при открита грешка</returns>
	BOOL AddItemsInCmbPhoneNumber();

// Members
// ----------------
private:
	/// <summary>
	/// Член променлива за текстова контрола с име на град
	/// </summary>
	CEdit m_edbPhoneNumber;

	/// <summary>
	/// Член променлива за текстова контрола за област
	/// </summary>
	CComboBox m_cmbPhoneType;

	/// <summary>
	/// Член променлива за обмяна на данни с контролата за име на град
	/// </summary>
	CString m_strPhoneNumber;

	/// <summary>
	/// Член променлива за обмяна на данни с контролата за област
	/// </summary>
	long m_lPhoneType;

	/// <summary>
	/// Член променлива масив, която съдържа всички типове телефони
	/// </summary>
	CPhoneTypesArray m_oPhoneTypesArray;

	/// <summary>
	/// Член променлива, която съдържа параметъра за активност на контролите
	/// </summary>
	LPARAM m_lEnableControlsParam;

	/// <summary>
	/// Инстанция на клас за верификация на данни
	/// </summary>
	CValidateStringData m_oValidateStringData;
};