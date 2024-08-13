#pragma once
#include "afxdialogex.h"
#include "Structures.h"
#include "ValidateDialogControlsData.h"
#include "Flags.h"
#include "DefinesDialogCtrInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersDialog dialog

/// <summary>
/// Диалог за изпълнение на опирации свързани с регистъра Телефонни номера
/// </summary>
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
	/// <param name="oPhoneTypesArray">Параметър масив с всчики типове телефони</param>
	/// <param name="oEnableControls">Параметър, който приема стойност флаг, за това кои от контролите да са активни за писане</param>
	CPhoneNumbersDialog(const CPhoneTypesArray& oPhoneTypesArray, LPARAM lEnableControls = ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ALL, CWnd* pParent = nullptr);


	/// <param name="oPhoneTypesArray">Параметър масив с всчики типове телефони</param>
	/// <param name="recCity">Параметър структура с телефонен номер, чиито стойности ще се визуализират в контролите на диалога</param>
	/// <param name="oEnableControls">Параметър, който приема стойност флаг, за това кои от контролите да са активни за писане</param>
	CPhoneNumbersDialog(const CPhoneTypesArray& oPhoneTypesArray, const PHONE_NUMBERS& recPhoneNumber, LPARAM lEnableControls = ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ALL, CWnd* pParent = nullptr);
	virtual ~CPhoneNumbersDialog();


// MFC Overrides
// ----------------	
protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;
	virtual BOOL OnInitDialog() override;


// MFC Message Handlers
// ----------------
private:
	/// <summary>
	/// Метод за събитие при натискане на бутон ОК в диалога
	/// </summary>
	afx_msg void OnBnClickedOk();

	/// <summary>
	/// Метод за събитие при натискане на бутон CANCEL в диалога
	/// </summary>
	afx_msg void OnBnClickedCancel();

	/// <summary>
	/// Метод, който управлява промените в контролата за телефонен номер
	/// </summary>
	afx_msg void OnEnChangePhoneNumber();

	/// <summary>
	/// Метод, който управлява промените в контролата за тип телефон
	/// </summary>
	afx_msg void OnChangeSelPhoneType();


// Overrides
// ----------------
 

// Methods
// ----------------

public:
	/// <summary>
	/// Достъп до стойности за стринговите член променливи
	/// </summary>
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

	/// <summary>
	/// Метод, който управлява началния текст в контролите за грешки при първоначална инициализация на другите контроли в диалога
	/// </summary>
	void ManageErrorMsgControlsInitValues();


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