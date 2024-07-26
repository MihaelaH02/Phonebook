#pragma once
#include "afxdialogex.h"
#include "ValidateStringData.h"

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
	CCitiesDialog(CWnd* pParent = nullptr, const CString& strCityName = _T(""), const CString& strRegion = _T(""), BOOL bEnableControls = TRUE);
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
	/// <param name="strCityName">Параметър за име на град</param>
	/// <param name="strRegion">Параметър за област</param>
	void GetControlsData(CString& strCityName, CString& strRegion);

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
	/// Инстанция на клас заверификация на данни
	/// </summary>
	CValidateStringData m_oValidateStringData;
};
