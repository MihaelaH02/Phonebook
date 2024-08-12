#pragma once

#include "Structures.h"
#include "EnumsWithFlags.h"
/////////////////////////////////////////////////////////////////////////////
// CPersonDBModel

class CPersonDBModel
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPersonDBModel();

	/// <summary>
	/// Копи параметризиран конструктор
	/// </summary>
	CPersonDBModel(const PERSONS& recPerson, const CPhoneNumbersMap& oPhoneNumbers);

	/// <summary>
	/// Копи параметризиран конструктор
	/// </summary>
	/// <param name="oPersonDBModel">Параметър за подаден клас с данни</param>
	CPersonDBModel(const CPersonDBModel& oPersonDBModel);

	~CPersonDBModel();

	bool operator==(const CPersonDBModel& oPersonDBModelToCmp)  {
		return GetPerson().lId == oPersonDBModelToCmp.GetPerson().lId;
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
	/// <param name="oPhoneNumbersOperationsMap"></param>
	/// <returns></returns>
	BOOL AddPersonInfo(const PERSONS& recPerson, const CPhoneNumbersMap& oPhoneNumbersOperationsMap);

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
	/// <param name="oPhoneNumbersOperationsMap">Параметър за мап, който ще се добавя</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL AddAllPhoneNumbers(const CPhoneNumbersMap& oPhoneNumbersOperationsMap);

	/// <summary>
	/// Метод за примахване на всички телефонин номера от групите
	/// </summary>
	void RemoveAllPhoneNumbers();

	/// <summary>
	/// Метод, който задава ИД на вскички телефонни номера след добавен клиент
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL SetPhoneNumbersPersonId();


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
