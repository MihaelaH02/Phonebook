#pragma once
#include "afxdialogex.h"

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
	CCitiesDialog(CWnd* pParent = nullptr, const CString& strCityName = NULL, const CString& strRegion = NULL, BOOL bEnableControls = TRUE);
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
	/// Метод хандлер, който управлява фокуса в контролата за име
	/// </summary>
	void OnEnKillfocusName();

	/// <summary>
	/// Метод хандлер, който управлява фокуса в контролата за област
	/// </summary>
	void OnEnKillfocusRegion();

	/// <summary>
	/// Метод за забрана за писане по контролите
	/// </summary>
	void EnableControls(BOOL bEnableControls);

	/// <summary>
	/// Метод, който проверява дали стринга е във валиден формат 
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се проверява</param>
	/// <returns>Връща съобщение за грешката или празен стренг</returns>
	CString SendStatusMsgForValidStringFormat(const CString& strText);

	/// <summary>
	/// Метод, който задава само първия символ да е главна буква
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се модифицира</param>
	void ValidateDataUpperLetter(CString& strText);

	/// <summary>
	/// Метод за валидация на празни полета
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се валидира</param>
	/// <returns>Връща TRUE, ако данните са с нулева стойност и FALSE, ако не са</returns>
	BOOL IsEmptyString(const CString& strText);

	/// <summary>
	/// Метода за валидация дали стренга се състои само от букви
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се валидира</param>
	/// <returns>Връща TRUE, ако данните са с коректни и FALSE, ако не са</returns>
	BOOL IsOnlyLettersCString(const CString& strText);


// Members
// ----------------
private:
	CEdit m_edbName;
	CEdit m_edbRegion;
	CString m_strName;
	CString m_strRegion;
	BOOL m_bEnableControls;
};
