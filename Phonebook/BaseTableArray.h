#pragma once
#include<afxtempl.h>

/// <summary>
/// Темплейтен клас, изпълняващ операции с масиви от структури
/// </summary>
/// <typeparam name="CStruct">Дискова структура, по която ще се създава масив</typeparam>
template<class CStruct>
class CBaseTableArray
{
public:
	/// <summary>
	/// Конструктор
	/// </summary>
	CBaseTableArray() {};

	/// <summary>
	/// Деструктор
	/// </summary>
	~CBaseTableArray() 
	{
		//Освобождаване на заделеното място
		DeleteAllElements();
	};
	
	/// <summary>
	/// Изтриване на елемент
	/// </summary>
	/// <param name="nIndex">Индекс на елемент в масива</param>
	void DeleteElement(INT_PTR nIndex) {
		CStruct* pStruct = m_oArray.GetAt(i);
		if (pStruct != nullptr)
		{
			delete pStruct;
			m_oArray.RemoveAt(nIndex);
		}
	}

	/// <summary>
	/// Достъп до елемент в масива
	/// </summary>
	/// <param name="nIndex">Индекс на елемент в масива</param>
	/// <returns>Връща указател към елемент от масива</returns>
	CStruct* GetElement(INT_PTR nIndex) {
		CStruct* pStruct = m_oArray.GetAt(nIndex);
		if (pStruct != nullptr)
		{
			return pStruct;
		}
	}

	/// <summary>
	/// Изтриване на всички елементи
	/// </summary>
	void DeleteAllElements() {
		for (INT_PTR nIndex = 0; nIndex <m_oArray.GetCount(); ++nIndex)
		{
			CStruct* pStruct = m_oArray.GetAt(nIndex);
			if (pStruct != nullptr)
			{
				delete pStruct;
			}
		}
		m_oArray.RemoveAll();
	}

	/// <summary>
	/// Достъп до масива
	/// </summary>
	/// <returns>Масив мембър на класа</returns>
	CTypedPtrArray<CPtrArray, CStruct*>* GetArray() {
		if (&m_oArray != nullptr) 
		{
			return &m_oArray;
		}
	}
private:
	/// <summary>
	/// Променлива масив
	/// </summary>
	CTypedPtrArray<CPtrArray, CStruct*> m_oArray;
};