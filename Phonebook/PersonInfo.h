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
	/// <param name="oPersonInfo"></param>
	CPersonInfo(const CPersonInfo& oPersonInfo);

	~CPersonInfo();

// Methods
// ----------------
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="lId"></param>
	/// <returns></returns>
	void SetIdPerson(long lId);

	/// <summary>
	/// Метод за достъп до член променлива клиент
	/// </summary>
	/// <returns>Връща структура на от тип клиент</returns>
	const PERSONS& GetPerson() const;

	/// <summary>
	/// Метод за достъп до член променлива масив в телефонни номера
	/// </summary>
	/// <returns>Връща масив</returns>
	const CPhoneNumbersMap& GetPhoneNumbers() const;

	/// <summary>
	/// Метод за добавяне на клиент
	/// </summary>
	/// <param name="recPerson"></param>
	void AddPerson(PERSONS& recNewPerson);

	/// <summary>
	/// Метод за добавяне на нов телефонен номер
	/// </summary>
	/// <param name="recPhoneNumber"></param>
	/// 
	int AddPhoneNumber(CPhoneNumbersArray& oPhoneNumbersArray);

	/// <summary>
	/// Метод за добавяне на всички телефонни номера
	/// </summary>
	/// <param name="oPhoneNumbersMap"></param>
	BOOL AddAllPhoneNumbers(const CPhoneNumbersMap& oPhoneNumbersMap);

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
	/// Член променлива от тип мап, който като ключ ще съдържа записа за манипулация и като стойност това което се очаква да се направи с него
	/// </summary>
	CPhoneNumbersMap m_oPhoneNumbers;
};
