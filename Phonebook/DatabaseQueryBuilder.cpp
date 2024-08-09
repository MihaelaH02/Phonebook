#include "pch.h"
#include "DatabaseQueryBuilder.h"

/////////////////////////////////////////////////////////////////////////////
// CDatabaseQueryBuilder


// Constructor / Destructor
// ----------------
CDatabaseQueryBuilder::CDatabaseQueryBuilder()
    :m_strQuery("")
{

}

CDatabaseQueryBuilder::~CDatabaseQueryBuilder()
{

}

// Methods
// ----------------
CDatabaseQueryBuilder& CDatabaseQueryBuilder::SelectFromTable(const CString strTableName)
{
    CString strQuery;
    strQuery.Format(DATABASE_QUERY_SELECT_ALL_FROM_TABLE, strTableName);
    m_strQuery += strQuery;
    return *this;
}

CDatabaseQueryBuilder& CDatabaseQueryBuilder::WhereEqualLong(const CString strColumnName, const long lValue)
{
    CString strQuery;
    strQuery.Format(DATABASE_QUERY_WHERE_COL_EQUAL_LONG, strColumnName, lValue);
    m_strQuery += strQuery;
    return *this;
}

CDatabaseQueryBuilder& CDatabaseQueryBuilder::NoLock()
{
    m_strQuery += DATABASE_QUERY_WITH_NOLOCK;
    return *this;
}

CDatabaseQueryBuilder& CDatabaseQueryBuilder::UpdLock()
{
    m_strQuery += DATABASE_QUERY_WITH_UPDLOCK;
    return *this;
}

CDatabaseQueryBuilder& CDatabaseQueryBuilder::WhereNothing()
{
    m_strQuery += DATABASE_QUERY_WHERE_NOTHING;
    return *this;
}

CString CDatabaseQueryBuilder::Build()
{
    return m_strQuery;
}


// Overrides
// ----------------