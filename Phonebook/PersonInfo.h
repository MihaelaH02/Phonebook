#pragma once

#include "Structures.h"
#include "EnumsWithFlags.h"
/////////////////////////////////////////////////////////////////////////////
// CPersonInfo

class CPersonInfo
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPersonInfo();

	/// <summary>
	/// Копи параметризиран конструктор
	/// </summary>
	CPersonInfo(const PERSONS& recPerson, const CPhoneNumbersMap& recPhoneNumbers);

	/// <summary>
	/// Копи параметризиран конструктор
	/// </summary>
	/// <param name="oPersonInfo">Параметър за подаден клас с данни</param>
	CPersonInfo(const CPersonInfo& oPersonInfo);

	~CPersonInfo();

	bool operator==(const CPersonInfo& other)  {
		return GetPerson().lId == other.GetPerson().lId;
	}
// Methods
// ----------------
public:
	/// <summary>
	/// Метод, който задава ИД на клиент
	/// </summary>
	/// <param name="lId">Параметър за ИД, което ще се зададе</param>
	void SetIdPerson(const long lId);

	/// <summary>
	/// Метод за достъп до член променлива клиент
	/// </summary>
	/// <returns>Връща структура на от тип клиент</returns>
	const PERSONS& GetPerson() const;

	/// <summary>
	/// Метод за достъп до член променлива масив в телефонни номера
	/// </summary>
	/// <returns>Връща мап с групи телефонни номера</returns>
	CPhoneNumbersMap& GetPhoneNumbers();

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const CPhoneNumbersMap& GetPhoneNumbers() const;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="recPerson"></param>
	/// <param name="oPhoneNumbersMap"></param>
	/// <returns></returns>
	BOOL AddPersonInfo(const PERSONS& recPerson, const CPhoneNumbersMap& oPhoneNumbersMap);

	/// <summary>
	/// Метод за добавяне на клиент
	/// </summary>
	/// <param name="recPerson">Параметър за клиент, който ще се добавя</param>
	void AddPerson(const PERSONS& recNewPerson);

	/// <summary>
	/// Метод за добавяне на нов телефонен номер
	/// </summary>
	/// <param name="recPhoneNumber">Параметър за тип телефон, който ще се добавя</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL AddPhoneNumber(const PHONE_NUMBERS& recPhoneNumbers);

	/// <summary>
	/// Метод за добавяне на всички телефонни номера
	/// </summary>
	/// <param name="oPhoneNumbersMap">Параметър за мап, който ще се добавя</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL AddAllPhoneNumbers(const CPhoneNumbersMap& oPhoneNumbersMap);

	/// <summary>
	/// Метод за примахване на всички телефонин номера от групите
	/// </summary>
	void RemoveAllPhoneNumbers();

	/// <summary>
	/// Метод, който задава ИД на вскички телефонни номера след добавен клиент
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL CheckAndConnectAllPhoneNumbersWithPersonId();


// Overrides
// ----------------


// Members
// ----------------
private:
	/// <summary>
	//Член променлива от тип структура с клиенти
	/// </summary>
	PERSONS m_recPerson;

	/// <summary>
	/// Член променлива от тип мап с групи телефонни номера
	/// </summary>
	CPhoneNumbersMap m_oPhoneNumbers;
};
