#pragma once
#include "InitializeSession.h"

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTransactionManager

/// <summary>
/// Клас за управление на сесия и транцакции
/// </summary>
class CDatabaseTransactionManager
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------

public:
	CDatabaseTransactionManager();

	~CDatabaseTransactionManager();


// Methods
// ----------------

public:
	/// <summary>
	/// Метод за достъп до сесията, в която се изпълнява транзакцията
	/// </summary>
	/// <returns><Връща указател към клас, който съдържа сесията/returns>
	CInitializeSession* GetSession();

	/// <summary>
	/// Метод за отваряне на транзакция
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при открита грешка</returns>
	BOOL OpenSafeTransaction();

	/// <summary>
	/// Метод за затваряне на гранзакция
	/// </summary>
	/// <param name="bFlagForError">Параметър за флаг, който указва дали има</param>
	/// <returns>Връща TRUE при успех и FALSE при открита грешка</returns>
	BOOL CloseSafeTransactoin(BOOL bFlagForError = FALSE);


// Overrides
// ----------------


// Members
// ----------------
	
/// <summary>
/// Член променлива, кято съдържа указател към клас манипулиращ сесия
/// </summary>
CInitializeSession* m_pSession;
};