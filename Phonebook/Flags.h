#pragma once

//Енумерация за указване кои полета да се активират в съответния диалог 
enum ENABLE_DIALOG_CITIES_CTR_FLAG
{
	ENABLE_DIALOG_CITIES_CTR_FLAG_ALL,
	ENABLE_DIALOG_CITIES_CTR_FLAG_NONE,
	ENABLE_DIALOG_CITIES_CTR_FLAG_ONLY_REGION,
	ENABLE_DIALOG_CITIES_CTR_FLAG_ONLY_NAME
};

enum ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG
{
	ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ALL,
	ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_NONE,
	ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ONLY_PHONE_NUMBER,
	ENABLE_DIALOG_PHONE_NUMBERS_CTR_FLAG_ONLY_PHONE_TYPE
};

enum ENABLE_DIALOG_PHONE_TYPES_CTR_FLAG
{
	ENABLE_DIALOG_PERSON_CTR_FLAG_ALL,
	ENABLE_DIALOG_PERSON_CTR_FLAG_NONE
};

//Енумерация за указване на извършена опреция
enum OPERATIONS_WITH_DATA_FLAGS
{
	OPERATIONS_WITH_DATA_FLAGS_READED,
	OPERATIONS_WITH_DATA_FLAGS_INSERT,
	OPERATIONS_WITH_DATA_FLAGS_UPDATE,
	OPERATIONS_WITH_DATA_FLAGS_DELETE,
};


