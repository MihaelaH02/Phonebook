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
	/// Метод за забрана за писане по контролите
	/// </summary>
	/// <param name="bBooleanFlag">Приема TRUE-FALSE, в зависимост дали контролите трябва да са активни или не</param>
	void EnableControls(BOOL bBooleanFlag);


// Members
// ----------------
public:
	CString m_strName;
	CString m_strRegion;
private:
	CEdit m_edbName;
	CComboBox m_cmbRegion;
};
