#pragma once
#include "afxdialogex.h"
#include "Structures.h"
#include "ValidateStringData.h"
#include "EnumsWithFlags.h"
#include "EnumsDialogCtrInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesDialog dialog

/// <summary>
/// Диалог за изпълнение на опирации свързани със структура Градове
/// </summary>
class CCitiesDialog : public CDialog
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CCitiesDialog)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------

 #ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CITIES_DIALOG };
#endif
 

// Constructor / Destructor
// ----------------
public:
	/// <param name="oEnableControls">Параметър, който приема стойност от енюм за това кои от контролите да са активни за писане</param>
	CCitiesDialog(LPARAM oEnableControls = ENABLE_DIALOG_CTR_FLAG_ALL, CWnd* pParent = nullptr);

	/// <param name="recCity">Параметър структура с градове, чиито стойности ще се визуализират в контролите на диалога</param>
	CCitiesDialog(const CITIES& recCity, LPARAM oEnableControls = ENABLE_DIALOG_CTR_FLAG_ALL, CWnd* pParent = nullptr);
	virtual ~CCitiesDialog();


// MFC Overrides
// ----------------	
private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();


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
	CITIES& GetControlsData();

private:
	/// <summary>
	/// Метод, който управлява промените в контролата за име
	/// </summary>
	void OnEnChangeName();

	/// <summary>
	/// Метод, който управлява промените в контролата за област
	/// </summary>
	void OnEnChangeRegion();

	/// <summary>
	/// Метод за забрана за писане по контролите
	/// </summary>
	void EnableControls(LPARAM oEnableControls);

	/// <summary>
	/// Метод за извеждане на съобщение в контрола
	/// </summary>
	/// <param name="strText">Контрола, чийто текст ще се валидира</param>
	/// <param name="nControlaID">Контрола, в която ще се съдържа текста</param>
	void PrintErrorMsg(const CString& strText, int nControlaID);

	/// <summary>
	/// Метод за проверка, дали контролата е на фокус
	/// </summary>
	/// <param name="oControla">Контрола, която ще се проверява</param>
	/// <returns>Връща TRUE ако на фокус и FALSE ,ако не е</returns>
	BOOL IsControlOnFocus(CWnd& oControla);

	/// <summary>
	/// Метод, който проверява дали е намерена грешка по въведеното в контролите
	/// </summary>
	BOOL HasErrorMsg();

	/// <summary>
	/// Метод, който извършва действия за направена промяна в контрола
	/// </summary>
	/// <param name="oControla">Параметър за контрола, в която е направена промяна</param>
	/// <param name="strText">Параметър за текста, който се намира в контролата</param>
	/// <param name="nControlaIDWithErroe">Параметър ИД на контрола, в която да се извезе со.ъобщение за грешка</param>
	void DoOnEnChangeEdbControla(CWnd& oControla, CString& strText, int nControlaIDWithErroe);


// Members
// ----------------
private:
	/// <summary>
	/// Член променлива за текстова контрола с име на град
	/// </summary>
	CEdit m_edbName;

	/// <summary>
	/// Член променлива за текстова контрола за област
	/// </summary>
	CEdit m_edbRegion;

	/// <summary>
	/// Член променлива за обмяна на данни с контролата за име на град
	/// </summary>
	CString m_strName;

	/// <summary>
	/// Член променлива за обмяна на данни с контролата за област
	/// </summary>
	CString m_strRegion;

	/// <summary>
	/// Член променлива, която съдържа параметъра за активност на контролите
	/// </summary>
	LPARAM m_oEnableControlsParam;

	/// <summary>
	/// Инстанция на клас за верификация на данни
	/// </summary>
	CValidateStringData m_oValidateStringData;
};
