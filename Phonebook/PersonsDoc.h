#pragma once
#include "PersonsData.h"
#include "AdditionalDBModelsPersons.h"
#include "Structures.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsDoc.h : interface of the CCitiesDoc class

/// <summary>
/// Клас документ за регистър с клиенти, наследяващ базов клас
/// </summary>
class CPersonsDoc : public CDocument
{

// Macros
// ----------------
protected:
	DECLARE_DYNCREATE(CPersonsDoc)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------


// Constructor / Destructor
// ----------------

public:
	CPersonsDoc();
	virtual ~CPersonsDoc();


// Overrides
// ----------------

public:
	/// <summary>
	/// Метод, който се изпълнява при направата на нов документ от този тип
	/// </summary>
	virtual BOOL OnNewDocument();


#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif


// Methods
// ----------------
public:
	/// <summary>
	/// Достъп до член променлива на класа
	/// </summary>
	/// <returns>Връща масива с информацията за клиенти</returns>
	CPersonsArray& GetPersons();

	/// <summary>
	/// Метод за достъп до член променливата с допълнителни данни
	/// </summary>
	/// <returns>Връща член променливата клас с допълнителни данни</returns>
	CAdditionalDBModelsPersons& GetAdditionalModels();

	/// <summary>
	/// Метод, който достъпва броя на клиентите
	/// </summary>
	/// <returns>Връща броя на елемените в масива, който съдържа информация за кленти</returns>
	INT_PTR GetPersonsArrayCount();

	/// <summary>
	/// Метод, който селектира клиеит по ид
	/// </summary>
	/// <param name="lID">Ид на клиент, по което ще се търси запис</param>
	/// <param name="oPersonDBModel">Масив с намерена информация за клиет</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL SelectPerson(const long& lID,  CPersonDBModel& oPersonDBModel);

	/// <summary>
	/// Метод за обработка на операции с информацията за клиенти
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL ProcessPerson(CPersonDBModel& oPersonDBModel,const LPARAM lOperationFlag);

private:
	/// <summary>
	/// Метод, който синхронизира напарвените промени в базата данни на елемент, по подадено ИД на клиент
	/// </summary>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL ProccesPersonInArray(PERSONS& recPerson, const LPARAM lOperationFlag, INT_PTR& lIndex);


// Members
// ----------------
private:

	/// <summary>
	///Член променлива, съдърщата масив с данните от таблицата с градове
	/// </summary>
	CPersonsArray m_oPersonsArray;

	/// <summary>
	/// Член променилва от тип клас с дъполнителни данни
	/// </summary>
	CAdditionalDBModelsPersons m_oAdditionalModels;
public:
	virtual void OnCloseDocument();
};
