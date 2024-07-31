#pragma once

#include "Structures.h"

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
	/// Параметризиран конструктор
	/// </summary>
	CPersonInfo(const PERSONS& recPerson, const CPhoneNumbersArray& recPhoneNumbers);

	~CPersonInfo();

// Methods
// ----------------
public:
	/// <summary>
	/// Метод за достъп до член променлива клиент
	/// </summary>
	/// <returns>Връща структура на от тип клиент</returns>
	const PERSONS GetPerson() const;

	/// <summary>
	/// Метод за достъп до член променлива масив в телефонни номера
	/// </summary>
	/// <returns>Връща масив</returns>
	const CPhoneNumbersArray GetPhoneNumbers() const;

	/// <summary>
	/// Метод за търсене на телефонен номер в масива
	/// </summary>
	/// <param name="recPhoneNumber">Параметър от тип структрура с телефонни номера, който ще се търси в масива</param>
	/// <returns>Връща се индекса на открития елемент в масива или -1 при липса на елемент</returns>
	int FindPhoneNumber(const PHONE_NUMBERS& recPhoneNumber);

	/// <summary>
	/// Метод за добавяне на клиент
	/// </summary>
	/// <param name="recPerson"></param>
	void AddPerson(PERSONS& recNewPerson);

	/// <summary>
	/// Метод за добавяне на нов телефонен номер
	/// </summary>
	/// <param name="recPhoneNumber"></param>
	void AddPhoneNumber(PHONE_NUMBERS& recNewPhoneNumber);


	//void RemovePhoneNumber(PHONE_NUMBERS& recPhoneNumber);
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
	/// Член променлива от тип масив с телефонни номера
	/// </summary>
	CPhoneNumbersArray m_oPhoneNumbers;
};
