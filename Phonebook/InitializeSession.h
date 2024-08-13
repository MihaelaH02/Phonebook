#pragma once
#include <atldbcli.h>

/////////////////////////////////////////////////////////////////////////////
// CInitializeSession

/// <summary>
/// Клас отговарящ за сесисия
/// </summary>
class CInitializeSession
{

// Constants
// ----------------


// Constructor / Destructor
// ----------------

public:
	CInitializeSession();
	virtual ~CInitializeSession();


// Methods
// ----------------

public:
	/// <summary>
	/// Метод за отваряне на нова сесия
	/// </summary>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL OpenSession();

	/// <summary>
	/// Метод за затвяряне на сесията
	/// </summary>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL CloseSession();

	/// <summary>
	/// Метод за достъп до член променливата
	/// </summary>
	/// <returns>Връща променлива,съдържаща сесията</returns>
	CSession& GetSession();

	/// <summary>
	/// Метод за проверка на отворена сесия
	/// </summary>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL IsSessionOpen();

	/// <summary>
	/// Метод за отваряне на транзакция
	/// </summary>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL StartTransacion();

	/// <summary>
	/// Метод затваряне на транзакция с успех и запазване на данните
	/// </summary>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL CommitTransaction();

	/// <summary>
	/// Метод за затваряне на транзакция с неуспех и връщане на старите данни
	/// </summary>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL RollbackTransaction();


// Overrides
// ----------------


// Members
// ----------------
private:
	/// <summary>
	/// Член променлива съдържаща връзката към сесията
	/// </summary>
	CSession m_oSession;

	/// <summary>
	/// Член променлива съдържаща състояние на сесията
	/// </summary>
	bool m_bIsSessionOpen;

	/// <summary>
	/// 
	/// </summary>
	bool m_bIsTransactionOpen;
};
