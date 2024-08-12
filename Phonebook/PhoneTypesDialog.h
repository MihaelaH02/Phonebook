#pragma once
#include "afxdialogex.h"
#include "Structures.h"
#include "CValidateDialogControlsData.h"
#include "EnumsWithFlags.h"
#include "DefinesDialogCtrInfo.h"

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
	CPhoneTypesDialog(LPARAM lEnableControls = ENABLE_DIALOG_CITIES_CTR_FLAG_ALL, CWnd* pParent = nullptr);

	CPhoneTypesDialog(const PHONE_TYPES& recPhoneType, LPARAM lEnableControls = ENABLE_DIALOG_CITIES_CTR_FLAG_ALL, CWnd* pParent = nullptr);

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
	afx_msg void OnEnChangeEdbPhoneTypes();


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
	void EnableControls(LPARAM lEnableControls);

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
	void PrintErrorMsg(const CString& strText, int nControlaID);

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
	CEdit m_edbPhoneType;

	/// <summary>
	/// 
	/// </summary>
	PHONE_TYPES m_recPhoneType;

	/// <summary>
	/// Член променлива, която съдържа параметъра за активност на контролите
	/// </summary>
	LPARAM m_lEnableControlsParam;

	/// <summary>
	/// Инстанция на клас за верификация на данни
	/// </summary>
	CValidateDialogControlsData m_oValidateStringData;
};
