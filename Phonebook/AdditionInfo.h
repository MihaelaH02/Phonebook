#pragma once
#pragma once

#include "Structures.h"
#include "CitiesDoc.h"
//#include "PhoneTypesDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CAdditionInfo
class CAdditionInfo
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
public:
	CAdditionInfo();

	~CAdditionInfo();

// Methods
// ----------------

public:
	const CCitiesArray GetAllCities() const;
	const CPhoneTypesArray GetAllPhoneTypes() const ;

// Overrides
// ----------------


// Members
// ----------------
};

