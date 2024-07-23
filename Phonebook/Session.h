#pragma once


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
	/// <returns>Функцията връща променлива от тип сесията при успех и хвърля грешки при неуспех</returns>
	BOOL OpenSession();

	/// <summary>
	/// Затвяряне на сесията
	/// </summary>
	BOOL CloseSession();

	/// <summary>
	/// Функция за достъп до променлива m_oSession
	/// </summary>
	/// <returns>Връща променлива,съдържаща сесията</returns>
	CSession& GetSession();


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
