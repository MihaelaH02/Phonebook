#pragma once
#include <afxwin.h>
class CPhoneTypesDoc : public CDocument
{
// Macros
// ----------------

    // Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
    virtual void AssertValid() const;
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
    virtual void Dump(CDumpContext& dc) const;
};