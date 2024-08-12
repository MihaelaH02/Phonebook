#pragma once
#include "afxdialogex.h"
#include "Structures.h"
#include "CValidateDialogControlsData.h"
#include "EnumsWithFlags.h"
#include "DefinesDialogCtrInfo.h"

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
	afx_msg void OnEnChangePhoneNumber();
	afx_msg void OnCbnSelchangePhoneType();


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

	/// <summary>
	/// Метод за проверка, дали контролата е на фокус
	/// </summary>
	/// <param name="oControla">Контрола, която ще се проверява</param>
	/// <returns>Връща TRUE ако на фокус и FALSE ,ако не е</returns>
	BOOL IsControlOnFocus(CWnd& oControla);

	/// <summary>
	/// Метод за извеждане на съобщение в контрола
	/// </summary>
	/// <param name="strText">Контрола, чийто текст ще се валидира</param>
	/// <param name="nControlaID">Контрола, в която ще се съдържа текста</param>
	void PrintErrorMsg(int nControlaID, const CString& strErrorMsg = _T("NULL"));

	/// <summary>
	/// Метод, който проверява дали е намерена грешка по въведеното в контролите
	/// </summary>
	BOOL HasErrorMsg();


// Members
// ----------------
private:
	/// <summary>
	/// Член променлива за текстова контрола с име на град
	/// </summary>
	CEdit m_edbPhoneNumber;

	/// <summary>
	/// Член променлива за комбо бокс за тип телефон
	/// </summary>
	CComboBox m_cmbPhoneType;

	/// <summary>
	/// Член променлива, която съдържа данни за телефонен номер
	/// </summary>
	PHONE_NUMBERS m_recPhoneNumber;

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
	CValidateDialogControlsData m_oValidateStringData;
};