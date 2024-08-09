#pragma once
#include <afxstr.h>

/////////////////////////////////////////////////////////////////////////////
// CQueryBuilder

#define DATABASE_QUERY_SELECT_ALL_FROM_TABLE _T("SELECT * FROM [%s] ")
#define DATABASE_QUERY_WHERE_COL_EQUAL_LONG _T("WHERE [%s] = %d ")
#define DATABASE_QUERY_WHERE_NOTHING _T("WHERE 1 = 0")
#define DATABASE_QUERY_WITH_NOLOCK _T("WITH(NOLOCK) ")
#define DATABASE_QUERY_WITH_UPDLOCK _T("WITH(UPDLOCK) ")

class CDatabaseQueryBuilder 
{
 
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
    CDatabaseQueryBuilder();
    ~CDatabaseQueryBuilder();


 // Methods
// ----------------
public:
    /// <summary>
    /// Метод за изграждане на селект от таблица
    /// </summary>
    /// <param name="strTableName">Параметър за име на таблицата</param>
    /// <returns>Връща референция към типа на класа</returns>
    CDatabaseQueryBuilder& SelectFromTable(const CString strTableName);

    /// <summary>
    /// Метод за добавяне на условие по което ще се търси в заявката
    /// </summary>
    /// <param name="columnName">Параметър за име на колона, по който ще се търси</param>
    /// <param name="value">Параметър за стойност, по който ще се тръси</param>
    /// <returns>Връща референция към типа на класа</returns>
    CDatabaseQueryBuilder& WhereEqualLong(const CString strColumnName,const long lValue);
  
    /// <summary>
    /// Метод за добавяне на NoLock към заявката 
    /// </summary>
    /// <returns>Връща референция към типа на класа</returns>
    CDatabaseQueryBuilder& NoLock();

    /// <summary>
    /// Метод за добавяне на UpdLock към заявката
    /// </summary>
    /// <returns>Връща референция към типа на класа</returns>
    CDatabaseQueryBuilder& UpdLock();

    /// <summary>
    /// Метод за добавяне на условие, по което да не се селектира нищо от таблицата
    /// </summary>
    /// <returns>Връща референция към типа на класа</returns>
    CDatabaseQueryBuilder& WhereNothing();

    /// <summary>
    /// Метод  който изгражда заявката
    /// </summary>
    /// <returns>Връща стрингова изградена заявка</returns>
    CString Build();


 // Overrides
// ----------------


// Members
// ----------------
private:
    /// <summary>
    /// Член променлива за заявка
    /// </summary>
    CString m_strQuery;
};
