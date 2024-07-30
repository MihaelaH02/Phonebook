#pragma once
//Енумерация за указване кои полета да се активират в диалога
enum ENABLE_DIALOG_CONTROLS_FLAG
{
	ENABLE_CONTROLS_FLAG_ALL,
	ENABLE_CONTROLS_FLAG_NONE,
	ENABLE_CONTROLS_FLAG_ONLY_REGION,
	ENABLE_CONTROLS_FLAG_ONLY_NAME
};

//Енумерация за указване на извършена опреция за вюто
enum OPERATIONS_WITH_DATA_FLAGS
{
	LPARAM_INSERT = 1,
	LPARAM_UPDATE = 2,
	LPARAM_DELETE = 3
};

//Енумерация за указване на броя колони и тяхната поредност в лист контролата
enum VIEW_LIST_CONTROLA_COUNT_OF_COLUMS
{
	LIST_CONTROL_NUMBER_COLUMN_CITY_REGION = 0,
	LIST_CONTROL_NUMBER_COLUMN_CITY_NAME = 1
};
