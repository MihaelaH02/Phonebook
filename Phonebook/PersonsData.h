#pragma once

#include "PersonsTable.h"
#include "PhoneNumbersTable.h"
#include "PersonInfo.h"
#include "EnumsWithFlags.h"
#include "AdditionPersonInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsData

class CPersonsData
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CPersonsData();
	virtual ~CPersonsData();


// Methods
// ----------------
public:
	/// <summary>
	///Метод за селект на всички данни от таблици PERSONS и PHONE_NUMBERS от базата данни
	/// </summary>
	/// <param name="oPersonsInfo">Масив, от тип клас с данни за клиент, в който ще се съхраняват прочетените данни</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectAllPersonsInfo(CTableDataArray<CPersonInfo>& oPersonsInfo);

	/// <summary>
	/// Метод за селект само на един клиент с телефонните му номера от базата данни
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <param name="recPhoneTypes">Променлива, в която ще се запише прочетената стойност</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectPersonInfoWithPersonId(const long lID, CPersonInfo& oPersonInfo);

	/// <summary>
	/// Меттод, който управлява операциите с данните на клиент и телефонните му номера към базата данни 
	/// </summary>
	/// <param name="oPersonInfo">Клас, оти тип данни за клиент в всички негови данни за обработка</param>
	/// <param name="oOperationFlag">Параметър за флаг, по който ще се избира опирация на клиент</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL DoOperationWithPersonInfo(CPersonInfo& oPersonInfo, LPARAM lOperationFlag = OPERATIONS_WITH_DATA_FLAGS_READED);
	
	/// <summary>
	/// Метод, който управлява операциите с данни само на клиент към базата данни
	/// </summary>
	/// <param name="pInitializeSession">Параметър указател към сесия</param>
	/// <param name="oPersonInfo">Клас, оти тип данни за клиент в всички негови данни за обработка</param>
	/// <param name="oFlagOperation">Парамътър за флаг на опирация</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL ManagePersonInfoOperations(CInitializeSession* pInitializeSession, CPersonInfo& oPersonInfo, LPARAM lFlagOperation);

	/// <summary>
	/// Метод, който управлява операциите с данни на група телефонни номера към базата данни
	/// </summary>
	/// <param name="oPhoneNumbersTable">Параметър за табличен клас</param>
	/// <param name="oPhoneNumbersArray">Параметър за мап с всички групи телефонни номера</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL ManagePhoneNumbersOperations(CPhoneNumbersTable& oPhoneNumbersTable, const CPhoneNumbersMap& oPhoneNumbersArray);

	/// <summary>
	/// Метод за изпълнение на операция на група телефонин номера по подаден флаг
	/// </summary>
	/// <param name="oPhoneNumbersTable">Параметър за табличен клас</param>
	/// <param name="oFlagOperation">Параметър за флаг на опирация</param>
	/// <param name="pPhoneNumberArray">Параметър за група телефонни номера</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL ChoosePhoneNumbersOperation(CPhoneNumbersTable& oPhoneNumbersTable,LPARAM lFlagOperation, const CPhoneNumbersArray& pPhoneNumberArray);

	/// <summary>
	/// Метод, който намира всички телефонни номера за подаден клиент
	/// </summary>
	/// <param name="lId">Параметър за ИД на клиент, по който ще се търсият телефонни номера</param>
	/// <param name="oPhoneNumbersArray"></param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL CPersonsData::FindAllPhoneNumbersForPerson(const long lId, const CPhoneNumbersArray& oAllPhoneNumbersArray, CPhoneNumbersArray& oPhoneNumbersArrayForPerson);

	/// <summary>
	/// Метод за имплементация на клас с допълнтелни данни
	/// </summary>
	/// <param name="oAdditionalPersonInfo">Обект, който ще съхранямва заредените данни от други таблици</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL LoadAllAdditionalPersonInfo(CAdditionPersonInfo& oAdditionalPersonInfo);


// Overrides
// ----------------


// Members
// ----------------
};

