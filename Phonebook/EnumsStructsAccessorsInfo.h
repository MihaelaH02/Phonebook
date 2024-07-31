#pragma once

enum GLOBAL_ACCESSORS_INFO
{
	NUMBERS_OF_ACCESSORS = 2,
	ACCESSOR_FOR_ID = 0,
	ACCESSOR_FOR_DATA = 1,
	ORDINAL_COLUMN_ID = 1,
	ORDINAL_COLUMN_UPDATE_COUNTED = 2,
};

enum STRUCT_CITIES_COLUMS_INFO
{
	ORDINAL_COLUMN_CITIES_NAME = 3,
	ORDINAL_COLUMN_CITIES_REGION = 4
};

enum STRUCT_PHONE_TYPES_COLUMS_INFO
{
	ORDINAL_COLUMN_PHONE_TYPES = 3,
};

enum STRUCT_PERSONS_COLUMS_INFO
{
	ORDINAL_COLUMN_PERSONS_FIRSTNAME = 3,
	ORDINAL_COLUMN_PERSONS_SECONDNAME = 4,
	ORDINAL_COLUMN_PERSONS_LASTNAME = 5,
	ORDINAL_COLUMN_PERSONS_EGN = 6,
	ORDINAL_COLUMN_PERSONS_ID_CITY = 7,
	ORDINAL_COLUMN_PERSONS_ADDRESS = 8
};

enum STRUCT_PHONE_NUMBERS_COLUMS_INFO
{
	ORDINAL_COLUMN_PHONE_NUMBERS_ID_PERSON = 3,
	ORDINAL_COLUMN_PHONE_NUMBERS_ID_PHONE_TYPE = 4,
	ORDINAL_COLUMN_PHONE_NUMBERS_PHONE = 5,
};