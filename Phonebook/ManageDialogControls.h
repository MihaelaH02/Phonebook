#pragma once

#include "ValidateStringData.h"

/////////////////////////////////////////////////////////////////////////////
// CManageDialogControls class

class CManageDialogControls
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CManageDialogControls(CDialog& oDialog);
	~CManageDialogControls();


// Overrides
// ----------------


// Methods
// ----------------

public:

	/// <summary>
	/// Метод, който проверява за подадени грешки в контролата
	/// </summary>
	/// <param name="strText">Текста, който ще се манипулира</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех </returns>
	BOOL ManageValidationInControls(CString& strText);

// Members
// ----------------


	/// <summary>
	/// 
	/// </summary>
	CDialog m_oDialog;
};