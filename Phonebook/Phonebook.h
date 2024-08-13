
// Phonebook.h : main header file for the Phonebook application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPhonebookApp:
// See Phonebook.cpp for the implementation of this class
//

class CPhonebookApp : public CWinAppEx
{
public:
	CPhonebookApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileNewCities();
	afx_msg void OnFileNewPhoneTypes();
	afx_msg void OnFileNewClients();
};

extern CPhonebookApp theApp;
extern CMultiDocTemplate* pCitiesDocTemplate;
extern CMultiDocTemplate* pPhoneTypesDocTemplate;
extern CMultiDocTemplate* pPersonsDocTemplate;
