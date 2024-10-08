
// Phonebook.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Phonebook.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "CitiesDoc.h"
#include "CitiesView.h"
#include "PersonsDoc.h"
#include "PersonsView.h"
#include "DatabaseConnection.h"
#include "PhoneTypesDoc.h"
#include "PhoneTypeView.h"
#include "PhoneISOCodesDoc.h"
#include "PhoneIOSCodesView.h"
#include "PersonTypesDoc.h"
#include "PersonTypesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPhonebookApp

BEGIN_MESSAGE_MAP(CPhonebookApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CPhonebookApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW_CITIES, &CPhonebookApp::OnFileNewCities)
	ON_COMMAND(ID_FILE_NEW_PHONETYPES, &CPhonebookApp::OnFileNewPhoneTypes)
	ON_COMMAND(ID_FILE_NEW_PHONEISOCODES, &CPhonebookApp::OnFileNewPhoneISOCodes)
	ON_COMMAND(ID_FILE_NEW_PERSONTYPES, &CPhonebookApp::OnFileNewPersonTypes)
	ON_COMMAND(ID_FILE_NEW_CLIENTS, &CPhonebookApp::OnFileNewClients)

	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()



// CPhonebookApp construction

CPhonebookApp::CPhonebookApp() noexcept
{
	m_bHiColorIcons = TRUE;


	m_nAppLook = 0;
	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Phonebook.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

}

// The one and only CPhonebookApp object

CPhonebookApp theApp;
CMultiDocTemplate* pCitiesDocTemplate = nullptr;
CMultiDocTemplate* pPhoneTypesDocTemplate = nullptr;
CMultiDocTemplate* pPersonsDocTemplate = nullptr;
CMultiDocTemplate* pPersonTypesDocTemplate = nullptr;
CMultiDocTemplate* pPhoneISOCodesDocTemplate = nullptr;


// CPhonebookApp initialization

BOOL CPhonebookApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// AfxInitRichEdit2() is required to use RichEdit control
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	//Инстанция на връзката към базата данни
	CDatabaseConnection* pDatabaseConnection = CDatabaseConnection::getInstance();

	/// Отваряне на връзка с базата данни
	if (!pDatabaseConnection->ConnectToDatabaseSource())
	{
		AfxMessageBox(_T("Failed to connect to database!"));
		return FALSE;
	}

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views

	pCitiesDocTemplate = new CMultiDocTemplate(IDR_CitiesTYPE,
		RUNTIME_CLASS(CCitiesDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CCitiesView));
	if (!pCitiesDocTemplate)
		return FALSE;
	AddDocTemplate(pCitiesDocTemplate);

	pPhoneTypesDocTemplate = new CMultiDocTemplate(IDR_PhoneTypesTYPE,
		RUNTIME_CLASS(CPhoneTypesDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CPhoneTypeView));
	if (!pPhoneTypesDocTemplate)
		return FALSE;
	AddDocTemplate(pPhoneTypesDocTemplate);

	pPhoneISOCodesDocTemplate = new CMultiDocTemplate(IDR_PhoneISOCodesTYPE,
		RUNTIME_CLASS(CPhoneISOCodesDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CPhoneIOSCodesView));
	if (!pPhoneISOCodesDocTemplate)
		return FALSE;
	AddDocTemplate(pPhoneISOCodesDocTemplate);

	pPersonTypesDocTemplate = new CMultiDocTemplate(IDR_PersonTypesTYPE,
		RUNTIME_CLASS(CPersonTypesDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CPersonTypesView));
	if (!pPersonTypesDocTemplate)
		return FALSE;
	AddDocTemplate(pPersonTypesDocTemplate);

	pPersonsDocTemplate = new CMultiDocTemplate(IDR_PersonsTYPE,
		RUNTIME_CLASS(CPersonsDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CPersonsView));
	if (!pPersonsDocTemplate)
		return FALSE;
	AddDocTemplate(pPersonsDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CPhonebookApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	//Инстанция на връзката към базата данни
	CDatabaseConnection* pDatabaseConnection = CDatabaseConnection::getInstance();

	//Прекратяваме връзката към базата данни
	pDatabaseConnection->CloseDatabaseSource();

	return CWinAppEx::ExitInstance();
}

// CPhonebookApp message handlers
//

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CPhonebookApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CPhonebookApp customization load/save methods

void CPhonebookApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CPhonebookApp::LoadCustomState()
{
}

void CPhonebookApp::SaveCustomState()
{
}

// CPhonebookApp message handlers

void CPhonebookApp::OnFileNewCities()
{
	if (pCitiesDocTemplate) 
	{
		pCitiesDocTemplate->OpenDocumentFile(NULL);
	}
}

void CPhonebookApp::OnFileNewPhoneTypes()
{
	if (pPhoneTypesDocTemplate)
	{
		pPhoneTypesDocTemplate->OpenDocumentFile(NULL);
	}
}

void CPhonebookApp::OnFileNewPhoneISOCodes()
{
	if (pPhoneISOCodesDocTemplate)
	{
		pPhoneISOCodesDocTemplate->OpenDocumentFile(NULL);
	}
}

void CPhonebookApp::OnFileNewPersonTypes()
{
	if (pPersonTypesDocTemplate)
	{
		pPersonTypesDocTemplate->OpenDocumentFile(NULL);
	}
}

void CPhonebookApp::OnFileNewClients()
{
	if (pPersonsDocTemplate)
	{
		pPersonsDocTemplate->OpenDocumentFile(NULL);
	}
}
