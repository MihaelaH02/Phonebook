#pragma once
#include "afxdialogex.h"
#include "PersonInfo.h"
#include "EnumsWithFlags.h"
#include "AdditionInfo.h"
#include "ManageListCtr.h"
#include "EnumsListCtrColumsInfo.h"
#include "EnumsDialogCtrInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsDialog dialog

class CPersonsDialog : public CDialogEx
{
// Macros
// ----------------
	DECLARE_DYNAMIC(CPersonsDialog)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONS_DIALOG };
#endif


// Constructor / Destructor
// ----------------
public:
	/// <param name="oEnableControls">Параметър, който приема стойност от енюм за това кои от контролите да са активни за писане</param>
	CPersonsDialog(LPARAM oEnableControls = ENABLE_DIALOG_CTR_FLAG_ALL, CWnd* pParent = nullptr);

	/// <param name="oPerson">Параметър клас с данни, чиито стойности ще се визуализират в контролите на диалога</param>
	CPersonsDialog(const CPersonInfo& oPerson, const CAdditionInfo& oAdditionInfo, LPARAM oEnableControls = ENABLE_DIALOG_CTR_FLAG_ALL, CWnd* pParent = nullptr);

	virtual ~CPersonsDialog();


// MFC Overrides
// ----------------	

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	virtual BOOL OnInitDialog();


// MFC Message Handlers
// ----------------
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedEdit();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

// Overrides
// ----------------


// Methods
// ----------------
public:
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	 BOOL GetControlsData(CPersonInfo& oPersonInfo);

private:
	/// <summary>
	/// Метод, който управлява активността на контролите в диалога
	/// </summary>
	/// <param name="oEnableControls">Флаг, който определя активонстта на контролите</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL EnableControls(LPARAM oEnableControls);

	/// <summary>
	/// Метод за добавяне на елементи в комбо бокс контрола с градове
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL CPersonsDialog::AddItemsInCmbCities();

	/// <summary>
	/// Метод за зареждане на всички данни от списък с телефонни номера в лист контролата
	/// </summary>
	BOOL LoadPhoneNumbersInListCtrlFromArray();

	/// <summary>
	/// Метод за търсене на всички елементи от лист контролата по даден критерий
	/// </summary>
	/// <param name="recPerson">Структура, по която ще се търсият записи</param>
	BOOL FilterItemsFromListCtr(const PHONE_NUMBERS& recPhoneNumber);

	/// <summary>
	/// Метод за проверка, дали броя на елементите в лист контролата отговаря на данните от масива
	/// </summary>
	/// <returns>Връща TRUE при равенство и FALSE при разминаване</returns>
	BOOL IsAllPhoneNumbersLoadFromArray();

	/// <summary>
	/// Метод за сортиране на елементите в контролата по тип телефонен номер
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL SortItemsListCtr();

	/// <summary>
	/// Метод, който сравнява елементи
	/// </summary>
	/// <param name="lParam1">Асоцира се с първия елемент, който ще се сравнява</param>
	/// <param name="lParam2">Асоцира се с втори елемент, който ще се сравнява</param>
	/// <param name="lParamSort">Параметър, който приложението си генерира </param>
	/// <returns>Връща се резултат то сравнението</returns>
	int static CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	/// <summary>
	/// Метод, който записва всички презентационни данни от всички елементи тип телефонен номер в нов масив
	/// </summary>
	/// <param name="oPhoneNumbersArray">Масив с телефонни номера</param>
	/// <param name="strPhoneNumbersArrayToDisplayInListCtrl">Масив с презентационни данни на всички телефонни номера</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL ConvertAllElementsPhoneNumbersToArrayWithDisplayData(const CPhoneNumbersArray& oPhoneNumbersArray, CTableDataArray<CTableDataArray<CString>>& strPhoneNumbersArrayToDisplayInListCtrl);

	/// <summary>
	/// Метод, който записва презентационните данни на един елемент телефонен номер в нов масив
	/// </summary>
	/// <param name="recPerson">Еменет от тип структура с телефонни номера</param>
	/// <param name="strPersonArray">Масив с презентационни данни за този елемент</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL ConvertElementPhoneNumberToArrayWithDisplayData(const PHONE_NUMBERS& recPhoneNumbers, CTableDataArray<CString>& strPhoneNumbersArray);


// Members
// ----------------

	/// <summary>
	/// Член променлива за текстова контрола с име на клиент
	/// </summary>
	CEdit m_edbFirstName;

	/// <summary>
	/// Член променлива за текстова контрола с презиме на клиент
	/// </summary>
	CEdit m_edbLastName;

	/// <summary>
	/// Член променлива за текстова контрола с фамилия на клиент
	/// </summary>
	CEdit m_edbSecondName;

	/// <summary>
	/// Член променлива за текстова контрола за егн на клиент
	/// </summary>
	CEdit m_edbEGN;

	/// <summary>
	/// Член променлива за комбо бокс с градове
	/// </summary>
	CComboBox m_cmbCities;

	/// <summary>
	/// Член променлива за по-дълга текстова контрола за адрес на клиент
	/// </summary>
	CRichEditCtrl m_recAddress;

	/// <summary>
	/// Член променлива за лест контрола с телефонни номера на клиент
	/// </summary>
	CListCtrl m_lscPhoneNumbers;

	/// <summary>
	/// Член променлива от клас, който управлява операции с лист контлора 
	/// </summary>
	CListCtrlManager<PHONE_NUMBERS> m_oListCtrlManager;

	/// <summary>
	/// Член променлива за обмяна на данни с контролата за име на клиент
	/// </summary>
	CString m_strFirstName;

	/// <summary>
	/// Член променлива за обмяна на данни с контролата за презиме на клиент
	/// </summary>
	CString m_strSecondName;

	/// <summary>
	/// Член променлива за обмяна на данни с контролата за фамилия на клиент
	/// </summary>
	CString m_strLastName;

	/// <summary>
	/// Член променлива за обмяна на данни с контролата за егн на клиент
	/// </summary>
	CString m_strEGN;

	/// <summary>
	/// Член променлива за обмяна на данни с контролата за егн на клиент
	/// </summary>
	long m_lIdCity;

	/// <summary>
	/// Член променлива за обмяна на данни с контролата за егн на клиент
	/// </summary>
	CString m_strAddress;

	/// <summary>
	/// Член променлива масив, която съдържа всички телефонни номера за клиент
	/// </summary>
	CPhoneNumbersMap m_oPhoneNumbersMap;

	/// <summary>
	/// Член променлива от тип клас, който съдържа допълнителна информация
	/// </summary>
	CAdditionInfo m_oAdditionalInfo;

	/// <summary>
	/// Член променлива, която съдържа параметъра за активност на контролите
	/// </summary>
	LPARAM m_oEnableControlsParam;
	
};