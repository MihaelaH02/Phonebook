#pragma once
#include "afxdialogex.h"
#include "Structures.h"
#include "ValidateDialogControlsData.h"
#include "Flags.h"
#include "DefinesDialogCtrInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesDialog dialog

/// <summary>
/// Диалог за изпълнение на опирации свързани с регистъра Градове
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
	/// <param name="oEnableControls">Параметър, който приема стойност флаг, за това кои от контролите да са активни за писане</param>
	CCitiesDialog(LPARAM lEnableControls = ENABLE_DIALOG_CITIES_CTR_FLAG_ALL, CWnd* pParent = nullptr);

	/// <param name="recCity">Параметър структура с градове, чиито стойности ще се визуализират в контролите на диалога</param>
	/// <param name="oEnableControls">Параметър, който приема стойност флаг, за това кои от контролите да са активни за писане</param>
	CCitiesDialog(const CITIES& recCity, LPARAM lEnableControls = ENABLE_DIALOG_CITIES_CTR_FLAG_ALL, CWnd* pParent = nullptr);

	virtual ~CCitiesDialog();


// MFC Overrides
// ----------------	
private:
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


// Overrides
// ----------------


// Methods
// ----------------

public:
	/// <summary>
	/// Достъп до данните от контролите
	/// </summary>
	/// <param name="recCity">Параметър - структура, в която ще се запазят данните от контролите</param>
	/// <returns>Връща структура от тип градове</returns>
	BOOL GetControlsData(CITIES& recCity);

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
	/// Метод за управление на активността за писане по контролите
	/// </summary>
	void EnableControls(LPARAM lEnableControls);

	/// <summary>
	/// Метод за извеждане на съобщение за грешка в статични текстови контроли за грешки
	/// </summary>
	/// <param name="strText">Параметър за текст, който ще се валидира</param>
	/// <param name="nControlaID">Контрола, в която ще се съдържа текста</param>
	void PrintErrorMsg(const CString& strText, int nControlaID);

	/// <summary>
	/// Метод за проверка, дали контролата е на фокус
	/// </summary>
	/// <param name="oControla">Контрола, която ще се проверява</param>
	/// <returns>Връща TRUE ако на фокус и FALSE, ако не е</returns>
	BOOL IsControlOnFocus(CWnd& oControla);

	/// <summary>
	/// Метод, който проверява дали е визуализирана грешка в статичните текстови контроли
	/// </summary>
	BOOL HasErrorMsg();

	/// <summary>
	/// Метод, който извършва действия за направена промяна в контрола
	/// </summary>
	/// <param name="oControla">Параметър за контрола, в която е направена промяна</param>
	/// <param name="strText">Параметър за текста, който се намира в контролата</param>
	/// <param name="nControlaIDWithErroe">Параметър ИД на контрола, в която да се извезе съобщение за грешка</param>
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
	/// Член променлива, която съдържа данните за града
	/// </summary>
	CITIES m_recCity;

	/// <summary>
	/// Член променлива, която съдържа параметъра за активност на контролите
	/// </summary>
	LPARAM m_lEnableControlsParam;

	/// <summary>
	/// Инстанция на клас за верификация на данни
	/// </summary>
	CValidateDialogControlsData m_oValidateStringData;
};
