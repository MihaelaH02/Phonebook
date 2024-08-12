#pragma once
#include "TypePtrDataArray.h"

/////////////////////////////////////////////////////////////////////////////
// CMergeDisplayDataListCtrl

/// <summary>
/// Клас който обединява данните на обект структура и съответно презентационните данни за лист контрола
/// </summary>
/// <typeparam name="Type">Обект, чиито данни ще се визуализират</typeparam>
template<class Type>
class CRowDataListCtrl
{

// Constructor / Destructor
// ----------------
public:
	CRowDataListCtrl()
	{

	}

	CRowDataListCtrl(const Type& oType, const CTypedPtrDataArray<CString>& oArrayWithDataToDisplay)
		: m_oTypeData(oType),
	{
		m_oArrayWithDataToDisplay.SetDisplayData(oArrayWithDataToDisplay);
	}

	~CRowDataListCtrl()
	{

	}

// Methods
// ----------------


// Overrides
// ----------------
public:
	/// <summary>
	/// Метод, който добавя данни към член променилва обект
	/// </summary>
	/// <param name="oType">Параметър за обект, чиито данни ще се присвояват</param>
	void SetData(const Type& oType)
	{
		m_oTypeData = oType;
	}

	/// <summary>
	/// Метод, който добавя един елемент към масива с презентационни данни
	/// </summary>
	/// <param name="strOneElemnt">Параметър за стрингов елемен, който ще се добавя</param>
	/// <returns>Връща TRUE при успех и FALSE при неуспех</returns>
	BOOL AddElementToDisplayData(const CString& strOneElemnt)
	{
		if (m_oArrayWithDataToDisplay.AddElement(strOneElemnt) == -1)
		{
			return FALSE;
		}
		return TRUE;
	}

	/// <summary>
	/// Метод за достъп до член променива с данни за обекта
	/// </summary>
	/// <returns>Връща референция към обекта</returns>
	const Type& GetData() const 
	{
		return m_oTypeData;
	}

	/// <summary>
	/// Метод за достъп до член променлива масив с презентационни данни
	/// </summary>
	/// <returns>Връща референция към масива</returns>
	const CTypedPtrDataArray<CString>& GetDisplayData() const
	{
		return m_oArrayWithDataToDisplay;
	}

private:
	void SetDisplayData(const CTypedPtrDataArray<CString>& oArrayWithDataToDisplay)
	{
		m_oArrayWithDataToDisplay.AddAllElements(oArrayWithDataToDisplay);
	}

// Members
// ----------------
private:
	/// <summary>
	/// Член променлива, която съдържа всички данните за обекта
	/// </summary>
	Type m_oTypeData;

	/// <summary>
	/// Член променлива масив, който съдържа само презентационни данни на обекта
	/// </summary>
	CTypedPtrDataArray<CString> m_oArrayWithDataToDisplay;
};