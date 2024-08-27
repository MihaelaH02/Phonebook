#pragma once
#include "afxdialogex.h"
#include "PersonDBModel.h"
#include "Flags.h"
#include "AdditionalDBModelsPersons.h"
#include "ManageListCtr.h"
#include "ListCtrlColumnsInfo.h"
#include "DefinesDialogCtrInfo.h"
#include "PhoneNumbersDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsDialog dialog

/// <summary>
/// Клас диалог за регистър с клиенти, който налседява базов клас
/// </summary>
class CPersonsDialog : public CDialog
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
	/// <param name="oAdditionModels">Параметър клас с допълнителни данни</param>
	/// <param name="lEnableControls">Параметър, който приема стойност от енюм за това кои от контролите да са активни за писане</param>
	CPersonsDialog(const CAdditionalDBModelsPersons& oAdditionModels, LPARAM lEnableControls = ENABLE_DIALOG_PERSON_CTR_FLAG_ALL, CWnd* pParent = nullptr);

	/// <param name="oPerson">Параметър клас с данни, чиито стойности ще се визуализират в контролите на диалога</param>
	/// <param name="oAdditionInfo">Параметър клас с допълнителни данни</param>
	/// <param name="lEnableControls">Параметър, който приема стойност от енюм за това кои от контролите да са активни за писане</param>
	CPersonsDialog(CPersonDBModel& oPerson, const CAdditionalDBModelsPersons& oAdditionModels, LPARAM lEnableControls = ENABLE_DIALOG_PERSON_CTR_FLAG_ALL, CWnd* pParent = nullptr);

	virtual ~CPersonsDialog();


// MFC Overrides
// ----------------	

protected:
	virtual void DoDataExchange(CDataExchange* pDX) override; 
	virtual BOOL OnInitDialog() override;


// MFC Message Handlers
// ----------------
public:
	/// <summary>
	/// Метод, който упрвлява натискането на бутон ОК
	/// </summary>
	afx_msg void OnBnClickedOk();
	
	/// <summary>
	/// Метод, който управлява натискането на бутон Cancel
	/// </summary>
	afx_msg void OnBnClickedCancel();

	/// <summary>
	/// Метод, който управлява действия свързани с дясно натискане на бутона на мишката
	/// </summary>
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

	/// <summary>
	/// Метод, който управлява действия свързани с визуализацията на контекстно меню
	/// </summary>
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	/// <summary>
	/// Метод, който управлява действия свързани с двойно дясно натискане на бутон на мишката
	/// </summary>
	afx_msg void OnDblRButtonListCtrl(NMHDR* pNMHDR, LRESULT* pResult);

	/// <summary>
	/// Метод, който управлява действия свързани с натискане на бутон от клавиатурата
	/// </summary>
	afx_msg void OnKeyDownListCtrl(NMHDR* pNMHDR, LRESULT* pResult);

	/// <summary>
	/// Метод за преглед на елемент от лист контролата
	/// </summary>
	afx_msg void ViewPhoneNumberInfo();

	/// <summary>
	/// Метод за добавяне на елемент в лист контролата
	/// </summary>
	afx_msg void InsertPhoneNumber();

	/// <summary>
	/// Метод за редакция на елемент в лист контролата
	/// </summary>
	afx_msg void UpdatePhoneNumber();

	/// <summary>
	/// Метод за изтриване на елемент в лист контролата
	/// </summary>
	afx_msg void DeletePhoneNumber();

	/// <summary>
	/// Метод, който филтрира телефонните номера по тип
	/// </summary>
	afx_msg void FilterPhoneNumbersByType();

	/// <summary>
	/// Метод, който търси даден телефонен номер по номер
	/// </summary>
	afx_msg void FindPhoneNumber();

	/// <summary>
	/// Метод за зареждане на всички телефонни номера
	/// </summary>
	afx_msg void ReloadPhoneNumbers();

	/// <summary>
	/// Метод за следене на промени по контрола за име
	/// </summary>
	afx_msg void OnEnChangeFirtsname();

	/// <summary>
	/// Метод за следене на промени по контрола за презиме
	/// </summary>
	afx_msg void OnEnChangeSecondname();

	/// <summary>
	/// Метод за следене на промени по контрола за фамилия
	/// </summary>
	afx_msg void OnEnChangeLastname();

	/// <summary>
	/// Метод за следене на промени по контрола за егн
	/// </summary>
	afx_msg void OnEnChangeEgn();

	/// <summary>
	/// Метод за следене на промени по контрола за градове
	/// </summary>
	afx_msg void OnCbnSelchangeCities();

	/// <summary>
	/// Метод за следене на промени по контрола за адрес
	/// </summary>
	afx_msg void OnEnChangeAddress();

	/// <summary>
	/// Метод за следене на промени по контрола за тепове клиенти
	/// </summary>
	afx_msg void OnCbnSelchangePersonsTypes();

	/// <summary>
	/// Метод за следене на изтриване на елемент по лист контрола за телефонин номера
	/// </summary>
	afx_msg void OnDeleteItemListCtrl(NMHDR* pNMHDR, LRESULT* pResult);

	/// <summary>
	/// Метод за следене на промени по елементи в лист контрола за телефонин номера
	/// </summary>
	afx_msg void OnChangeItemListCtrl(NMHDR* pNMHDR, LRESULT* pResult);


// Overrides
// ----------------


// Methods
// ----------------

public:
	/// <summary>
	/// Метод за достъп до данните в контролите в диалога
	/// </summary>
	/// <param name="oPersonDBModel">Параметър клас, който ще съдържа данните</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL GetControlsData(CPersonDBModel& oPersonDBModel);

private:
	/// <summary>
	/// Метод, който управлява активността на контролите в диалога
	/// </summary>
	/// <param name="lEnableControls">Флаг, който определя активонстта на контролите</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL EnableControls(LPARAM lEnableControls);

	/// <summary>
	/// Метод за добавяне на елементи в комбо бокс контрола с градове
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL AddItemsInCmbCities();

	/// <summary>
	/// Метод за добавяне на елементи в комбо бокс контрола с типове
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL AddItemsInCmbTypes();

	/// <summary>
	/// Метод за зареждане на всички данни от списък с телефонни номера в лист контролата
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL LoadPhoneNumbersInListCtrlFromArray();

	/// <summary>
	/// Метод за търсене на всички елементи от лист контролата по даден критерий
	/// </summary>
	/// <param name="strListCtrElementToFind">Параметър за стойност,която се търси</param>
	/// <param name="strListCtrElementToFind">Параметър за колона в която ще се търси стойността</param>
	BOOL FilterItemsFromListCtrByCol(const CString& strListCtrElementToFind, LPARAM lColName);

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
	/// <param name="lParamSort">Параметър, който предава указател към настоящия диалог </param>
	/// <returns>Връща се резултат то сравнението</returns>
	int static CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	/// <summary>
	/// Метод, който записва всички презентационни данни от всички елементи тип телефонен номер в нов масив
	/// </summary>
	/// <param name="oPhoneNumbersArray">Масив с телефонни номера</param>
	/// <param name="oRowDataListCtrla">Масив с презентационни данни на всички телефонни номера</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL SetColumnDisplayDataArray(const CPhoneNumbersArray& oPhoneNumbersArray, CTypedPtrDataArray<CRowDataListCtrl<PHONE_NUMBERS>>& oRowDataListCtrla);

	/// <summary>
	/// Метод, който записва презентационните данни на един елемент телефонен номер в нов масив
	/// </summary>
	/// <param name="oRowDataListCtrla">Масив с презентационни данни за този елемент</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL SetColumnDisplayData(CRowDataListCtrl<PHONE_NUMBERS>& oRowDataListCtrla);

	/// <summary>
	/// Метод, който управлява началния текст в контролите за грешки при първоначална инициализация на другите контроли в диалога
	/// </summary>
	void ManageErrorMsgControlsInitValues();

	/// <summary>
	/// Метод, който управлява валидацията на текста в контроли със стрингови данни
	/// </summary>
	/// <param name="oControla">Параметър за контрола, чиито текст ще се валидира</param>
	/// <param name="strText">Параметър за текст, койото ще се валидира</param>
	/// <param name="nControlaIDWithError">Параметър за контрола, в която ще се визуализира грешката</param>
	void DoOnEnChangeStringEdbControla(CWnd& oControla, CString& strText, int nControlaIDWithError);

	/// <summary>
	/// Метод за проверка, дали контролата е на фокус
	/// </summary>
	/// <param name="oControla">Контрола, която ще се проверява</param>
	/// <returns>Връща TRUE ако на фокус и FALSE ,ако не е</returns>
	BOOL IsControlOnFocus(CWnd& oControla);

	/// <summary>
	/// Метод за извеждане на съобщение в контрола
	/// </summary>
	/// <param name="nControlaIDWithError">Параметър за контрола, в която ще се визуализира грешката</param>
	/// <param name="strText">Параметър за текст, койото ще се валидира</param>
	/// <param name="nMaxValidLenght">Параметър за максимална дължина на текста, ако е добавен</param>
	/// <param name="bValidateString">Параметър флаг за валидация на стренг</param>
	void PrintErrorMsg(int nControlaID, const CString& strControlaTextToCheck, BOOL bValidateString = TRUE, const int& nMaxValidLenght = DIALOG_CTR_TEXT_BOX_MAX_LENGTH_ENTERED_STRING);

	/// <summary>
	/// Метод, който проверява дали е намерена грешка по въведеното в контролите
	/// </summary>
	BOOL HasErrorMsg();

	/// <summary>
	/// Метод, който следи дали има грешка в една контрола
	/// </summary>
	/// <param name="nControlaIDWithError">Параметър за контрола, в която ще се визуализира грешката</param>
	/// <returns>Връща TRUE ако е открита грешка и FALSE, ако не е</returns>
	BOOL HasErrorInOneControla(const int& nControlaErrorMsgID);

	/// <summary>
	/// Метод, който преоблазува текста то всички тектови контрили във валиден
	/// </summary>
	void ValidateEdbControlsText();


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
	CEdit m_edbAddress;

	/// <summary>
	/// Член променлива за комбо бокс с типове
	/// </summary>
	CComboBox m_cmbTypes;

	/// <summary>
	/// Член променлива за лест контрола с телефонни номера на клиент
	/// </summary>
	CListCtrl m_lscPhoneNumbers;

	/// <summary>
	/// Член променлива от клас, който управлява операции с лист контлора 
	/// </summary>
	CListCtrlManager<PHONE_NUMBERS> m_oListCtrlManager;

	/// <summary>
	/// Член променилна, която съдържа данни за клиент
	/// </summary>
	PERSONS m_recPerson;

	/// <summary>
	/// Член променлива мап, която съдържа всички телефонни номера за клиент
	/// </summary>
	CPhoneNumbersMap m_oPhoneNumbersOperationsMap;

	/// <summary>
	/// Член променлива от тип клас, която съдържа допълнителна информация
	/// </summary>
	CAdditionalDBModelsPersons m_oAdditionalModels;

	/// <summary>
	/// Член променлива, която съдържа параметъра за активност на контролите
	/// </summary>
	LPARAM m_lEnableControlsParam;

	/// <summary>
	/// Инстанция на клас за верификация на данни
	/// </summary>
	CValidateDialogControlsData m_oValidateStringData;
};