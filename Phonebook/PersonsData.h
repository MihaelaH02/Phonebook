#pragma once

#include "PersonsTable.h"
#include "PhoneNumbersTable.h"
#include "PersonInfo.h"
#include "EnumsWithFlags.h"
//#include "Structures.h"


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
	///Метод за селект на всички данни от таблица PHONE_TYPES от базата данни
	/// </summary>
	/// <param name="oPersonsInfo">Масив, в който ще се съхраняват прочетените данни</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectAllPersonsInfo(CTableDataArray<CPersonInfo>& oPersonsInfo);

	/// <summary>
	/// Метод за селект само на един елемент от базата данни
	/// </summary>
	/// <param name="lID">Променлива указваща ИД на запис</param>
	/// <param name="recPhoneTypes">Променлива, в която ще се запише прочетената стойност</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL SelectPersonInfoWithId(const long lID, CPersonInfo& oPersonInfo);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="oPersonInfo"></param>
	/// <returns></returns>
	BOOL ManagePersonInfo(CPersonInfo& oPersonInfo, LPARAM oOperationFlag = OPERATIONS_WITH_DATA_FLAGS_NOCHANGE);
	
private:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="recPerson"></param>
	/// <returns></returns>
	/*BOOL CPersonsData::PersonInsert(PERSONS& recPerson);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="lid"></param>
	/// <param name="recPerson"></param>
	/// <returns></returns>
	BOOL CPersonsData::PersonUpdate(const long lid, PERSONS& recPerson);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="lId"></param>
	/// <returns></returns>
	BOOL CPersonsData::PersonDelete(const long lId);*/

	/// <summary>
	/// 
	/// </summary>
	/// <param name="recPerson"></param>
	/// <returns></returns>
	BOOL ManagePersonOperations(PERSONS& recPerson, LPARAM oFlagOperation);


	/// <summary>
	/// Метод за добавяне на запис
	/// </summary>
	/// <param name="oPersonInfo">Променлива с данни, които ще се добавя</param>
	/// <returns>Метода връща TRUE при успех и FALSE при възникнала грешка</returns>
	BOOL ChoosePhoneNumbersOperation(LPARAM oFlagOperation, CPhoneNumbersArray& pPhoneNumberArray);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="oPhoneNumbersArray"></param>
	/// <returns></returns>
	BOOL ManagePhoneNumbersOperations(CPhoneNumbersMap& oPhoneNumbersArray);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="lId"></param>
	/// <param name="oPhoneNumbersArray"></param>
	/// <returns></returns>
	BOOL CPersonsData::FindAllPhoneNumbersForPerson(const long lId, const CPhoneNumbersArray& oAllPhoneNumbersArray, CPhoneNumbersArray& oPhoneNumbersArrayForPerson);


// Overrides
// ----------------


// Members
// ----------------
};

