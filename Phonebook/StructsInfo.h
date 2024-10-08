#pragma once

//Указване на максимален размер на член променливи в структури с тип на данните TCHAR
#define STRUCT_MEMBER_SIZE_TYPE_TCHAR  128
#define STRUCT_MEMBER_SIZE_TYPE_TCHAR_FOR_PERSON_EGN  16
#define STRUCT_MEMBER_SIZE_TYPE_TCHAR_FOR_PHONE_NUMBER  16
<<<<<<< Updated upstream
=======
#define STRUCT_MEMBER_SIZE_TYPE_TCHAR_FOR_PHONE_ISO_CODES 4
>>>>>>> Stashed changes

//Енумерация за опредеяне глобана информация свързана с аксесори
enum GLOBAL_ACCESSORS_INFO
{
	GLOBAL_ACCESSORS_INFO_NUMBERS_OF_ACCESSORS = 2,
	GLOBAL_ACCESSORS_INFO_ACCESSOR_FOR_ID = 0,
	GLOBAL_ACCESSORS_INFO_ACCESSOR_FOR_DATA = 1,
};

//Енумерация за опредеяне глобана информация свързана с колони на аксесори
enum ACCESSORS_COLUMNS_INFO
{
	ACCESSORS_COLUMNS_INFO_ORDINAL_COLUMN_ID = 1,
	ACCESSORS_COLUMNS_INFO_ORDINAL_COLUMN_UPDATE_COUNTED = 2,
};

//Енумерации за опредеяне на последователността на презентационните данни от съотвените таблици
enum STRUCT_CITIES_ORDER_COL
{
	STRUCT_CITIES_ORDER_COL_CITT_NAME = 3,
	STRUCT_CITIES_ORDER_COL_REGION = 4
};

enum STRUCT_PHONE_TYPES_ORDER_COL
{
	STRUCT_PHONE_TYPES_ORDER_COL_PHONE_TYPES = 3,
};

enum STRUCT_PERSONS_ORDER_COL
{
	STRUCT_PERSONS_ORDER_COL_FIRSTNAME = 3,
	STRUCT_PERSONS_ORDER_COL_SECONDNAME = 4,
	STRUCT_PERSONS_ORDER_COL_LASTNAME = 5,
	STRUCT_PERSONS_ORDER_COL_EGN = 6,
	STRUCT_PERSONS_ORDER_COL_ID_CITY = 7,
	STRUCT_PERSONS_ORDER_COL_ADDRESS = 8,
	STRUCT_PERSONS_ORDER_COL_ID_PERSON_TYPE = 9
};

enum STRUCT_PHONE_NUMBERS_ORDER_COL
{
	STRUCT_PHONE_NUMBERS_ORDER_COL_ID_PERSON = 3,
	STRUCT_PHONE_NUMBERS_ORDER_COL_ID_PHONE_TYPE = 4,
	STRUCT_PHONE_NUMBERS_ORDER_COL_NUMBERS_PHONE = 5,
	STRUCT_PHONE_NUMBERS_ORDER_COL_NUMBERS_ISO_CODES = 6

};