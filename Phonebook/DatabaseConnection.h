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
	/// <summary>
   /// Частен конструктор за класа
   /// </summary>
	CDatabaseConnection();

	/// <summary>
	/// Деструктор
	/// </summary>
	~CDatabaseConnection();


// Methods
// ----------------
public:
	/// <summary>
	/// Функция за свързване с базата данни
	/// </summary>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL ConnectToDatabaseSource();

	/// <summary>
	/// Затвяряне на връзката към базата данни
	/// </summary>
	/// <returns>Функцията връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL CloseDatabaseSource();

	/// <summary>
	/// Метод за достъп до единствения инстанция на класа
	/// </summary>
	static CDatabaseConnection* getInstance();

	/// <summary>
	/// Функция за достъп до променлива m_oDataSource
	/// </summary>
	/// <returns>Връща променлива,съдържаща връзка към базата</returns>
	CDataSource& GetDataSource();


// Overrides
// ----------------


// Members
// ----------------
	/// <summary>
	/// Променлива, съдържаща връзката към базата данни
	/// </summary>
	CDataSource m_oDataSource;

	/// <summary>
	/// Променива указател, сочещ единствената инстанция на класа
	/// </summary>
	static CDatabaseConnection* pInstancePtr;
};