#pragma once
#include <atldbcli.h>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// CDatabaseConnection

/// <summary>
/// Клас отговарящ за връзката към база данни
/// </summary>
class CDatabaseConnection
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	/// <summary>
	/// Копи косткруктор
	/// </summary>
	CDatabaseConnection(const CDatabaseConnection&) = delete;

private:
	CDatabaseConnection();


	~CDatabaseConnection();


// Methods
// ----------------

public:
	/// <summary>
	/// Метод за свързване с базата данни
	/// </summary>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL ConnectToDatabaseSource();

	/// <summary>
	/// Метод за затвяряне на връзката към базата данни
	/// </summary>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL CloseDatabaseSource();

	/// <summary>
	/// Метод за достъп до единствения инстанция на класа
	/// </summary>
	static CDatabaseConnection* getInstance();

	/// <summary>
	/// Метод за достъп до член променливата
	/// </summary>
	/// <returns>Връща променлива,съдържаща връзка към базата</returns>
	CDataSource& GetDataSource();


// Overrides
// ----------------


// Members
// ----------------

	/// <summary>
	/// Член променлива, съдържаща връзката към базата данни
	/// </summary>
	CDataSource m_oDataSource;

	/// <summary>
	/// Член променива указател, сочещ единствената инстанция на класа
	/// </summary>
	static CDatabaseConnection* m_pInstancePtr;
};