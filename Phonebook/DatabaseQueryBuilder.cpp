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
CDatabaseQueryBuilder& CDatabaseQueryBuilder::Select(const CString& strToSelect)
{
    CString strQuery;
    strQuery.Format(DATABASE_QUERY_SELECT, strToSelect);
    m_strQuery += strQuery;
    return *this;
}

CDatabaseQueryBuilder& CDatabaseQueryBuilder::FromTable(const CString& strTableName)
{
    CString strQuery;
    strQuery.Format(DATABASE_QUERY_FROM, strTableName);
    m_strQuery += strQuery;
    return *this;
}

CDatabaseQueryBuilder& CDatabaseQueryBuilder::WhereEqualLong(const CString& strColumnName, const long& lValue)
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

CDatabaseQueryBuilder& CDatabaseQueryBuilder::TopRows(const int& nNumberOfRowsToSelect)
{
    CString strQuery;
    strQuery.Format(DATABASE_QUERY_TOP_ROWS, nNumberOfRowsToSelect);
    m_strQuery += strQuery;
    return *this;
}

CString CDatabaseQueryBuilder::Build()
{
    return m_strQuery;
}

void CDatabaseQueryBuilder::Clear()
{
    m_strQuery = "";
}


// Overrides
// ----------------