#pragma once
#include "afxdialogex.h"
#include "Structures.h"
#include "ValidateDialogControlsData.h"
#include "Flags.h"
#include "DefinesDialogCtrInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneISOCodesDialog dialog

class CPhoneISOCodesDialog : public CDialogEx
{
// Macros
// ----------------

protected:
	DECLARE_DYNAMIC(CPhoneISOCodesDialog)
	DECLARE_MESSAGE_MAP()

// Constants
// ----------------
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ISO_CODES };
#endif

// Constructor / Destructor
// ----------------
public:
	/// <param name="lEnableControls">Параметър, който приема стойност от енюм за това кои от контролите да са активни за писане</param>
	CPhoneISOCodesDialog(LPARAM lEnableControls = ENABLE_DIALOG_CITIES_CTR_FLAG_ALL, CWnd* pParent = nullptr);

	/// <param name="recPhoneType">Параметър клас с данни, чиито стойности ще се визуализират в контролите на диалога</param>
	/// <param name="lEnableControls">Параметър, който приема стойност от енюм за това кои от контролите да са активни за писане</param>
	CPhoneISOCodesDialog(const PHONE_ISO_CODES& recPhoneType, LPARAM lEnableControls = ENABLE_DIALOG_CITIES_CTR_FLAG_ALL, CWnd* pParent = nullptr);

	virtual ~CPhoneISOCodesDialog();

// MFC Overrides
// ----------------	
private:
	virtual void DoDataExchange(CDataExchange* pDX) override;
	virtual BOOL OnInitDialog();

public:
	/// <summary>
	/// Метод за следене на промени по контрола за типове телефони
	/// </summary>
	afx_msg void OnEnChangePhoneISOCode();
	/// <summary>
	/// Метод, който управлява натискането на бутон OK
	/// </summary>
	afx_msg void OnBnClickedOk();

	/// <summary>
	/// Метод, който управлява натискането на бутон Cancel
	/// </summary>
	afx_msg void OnBnClickedCancel();


// Overrides
// ----------------


// Methods
// ----------------

public:
	/// <summary>
	/// Достъп до стойности за стринговите член променливи
	/// </summary>
	BOOL GetControlsData(PHONE_ISO_CODES& recPhoneISOCode);

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
	/// Член променлива за текстова контрола с код на държава
	/// </summary>
	CEdit m_edbPhoneISOCodes;

	/// <summary>
	/// Член променлива телефонен код за държава
	/// </summary>
	PHONE_ISO_CODES m_recPhoneISOCodes;

	/// <summary>
	/// Член променлива, която съдържа параметъра за активност на контролите
	/// </summary>
	LPARAM m_lEnableControlsParam;

	/// <summary>
	/// Инстанция на клас за верификация на данни
	/// </summary>
	CValidateDialogControlsData m_oValidateStringData;
};
