#pragma once
#include "afxdialogex.h"
#include "Structures.h"
#include "ManageDialogControls.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesDialog dialog

#define MAX_LENGTH_STRING 128

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
	CCitiesDialog(CWnd* pParent = nullptr);
	CCitiesDialog(const CITIES& recCity, BOOL bEnableControls = TRUE, CWnd* pParent = nullptr);
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
private:


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
	/// Метод хандлер, който управлява промените в контролата за име
	/// </summary>
	void OnEnChangeName();

	/// <summary>
	/// Метод хандлер, който управлява промените в контролата за област
	/// </summary>
	void OnEnChangeRegion();

	/// <summary>
	/// Метод за забрана за писане по контролите
	/// </summary>
	void EnableControls(BOOL bEnableControls);

	/// <summary>
	/// Метод за извеждане на съобщение в контрола
	/// </summary>
	/// <param name="strText">Контрола, чиийто текст ще се валидира</param>
	/// <param name="nControlaID">Контрола, в която ще се съдържа текста</param>
	void PrintErrorMsg(const CString& strText, int nControlaID);

	/// <summary>
	/// Метод за проверка, дали контролата е на фокус
	/// </summary>
	/// <param name="oControla">Контрола, която ще се проверява</param>
	/// <returns>Връща TRUE ако на фокус и FALSE ,ако не е</returns>
	BOOL IsControlOnFocus(CWnd& oControla);

	/// <summary>
	/// Метод за проверка, дали са въведени нови данни
	/// </summary>
	/// <returns>При направена редакция в някоя от контролите се връща TRUE, а при липса на такава FALSE</returns>
	BOOL IsEnteredDataDiferent();


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
	/// Флаг за активация или деактивация на контролите
	/// </summary>
	BOOL m_bFlagEnableControls;

	/// <summary>
	/// Инстанция на клас за верификация на данни
	/// </summary>
	CValidateStringData m_oValidateStringData;
};
