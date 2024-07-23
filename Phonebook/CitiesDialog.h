#pragma once
#include "afxdialogex.h"

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
	CCitiesDialog(CWnd* pParent = nullptr);   // standard constructor
	CCitiesDialog(const CString& strCityName, const CString& strRegion);
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

	/// <summary>
	/// Метод за забрана за писане по контролите
	/// </summary>
	/// <param name="bBooleanFlag">Приема TRUE-FALSE, в зависимост дали контролите трябва да са активни или не</param>
	void EnableControls(BOOL bBooleanFlag);

private:
	/// <summary>
	/// Метод за валидация на данни
	/// </summary>
	/// <returns>Връща TRUE, ако са валидни данните и FALSE</returns>
	BOOL ValidateStringData();

// Members
// ----------------
private:
	CEdit m_edbName;
	CComboBox m_cmbRegion;
};
