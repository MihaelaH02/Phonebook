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
	/// Функция за отваряне на нова сесия
	/// </summary>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL OpenSession();

	/// <summary>
	/// Затвяряне на сесията
	/// </summary>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL CloseSession();

	/// <summary>
	/// Функция за достъп до променлива m_oSession
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
	/// Променлива съдържаща връзката към сесията
	/// </summary>
	CSession m_oSession;
};
