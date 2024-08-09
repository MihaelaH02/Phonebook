// PersonsDoc.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "PersonsDoc.h"

/////////////////////////////////////////////////////////////////////////////
//  CPersonsDoc.cpp : implementation of the CCitiesDoc class

IMPLEMENT_DYNCREATE(CPersonsDoc, CDocument)

BEGIN_MESSAGE_MAP(CPersonsDoc, CDocument)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------

CPersonsDoc::CPersonsDoc()
{
}

CPersonsDoc::~CPersonsDoc()
{
}


// Overrides
// ----------------
BOOL CPersonsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
	{
		return FALSE;
	}

	//Зареждане на клиенти от базата данни в масив
	if (!m_oPersonsData.SelectAllPersonsInfo(m_oPersonsInfo))
	{
		return FALSE;
	}

	//Зареждане на допълнителнита данните от базата данни в масив
	if (!m_oPersonsData.LoadAllAdditionalPersonInfo(m_oAdditionalInfo))
	{
		return FALSE;
	}

	return TRUE;
}

CTableDataArray<CPersonInfo>& CPersonsDoc::GetPersonInfo()
{
	return m_oPersonsInfo;
}

INT_PTR CPersonsDoc::GetPersonsInfoArrayElementsCount()
{
	return m_oPersonsInfo.GetCount();
}

 BOOL CPersonsDoc::GetAllPersons(CPersonsArray& oPersonsArray)
{
	for (INT_PTR lIndex = 0; lIndex < m_oPersonsInfo.GetCount(); lIndex++)
	{
		CPersonInfo* pPersonInfo = m_oPersonsInfo.GetAt(lIndex);
		if (pPersonInfo == nullptr)
		{
			return FALSE;
		}

		if (oPersonsArray.AddElement(pPersonInfo->GetPerson()) == -1)
		{
			return FALSE;
		}

	}
	return TRUE;
}

CAdditionPersonInfo& CPersonsDoc::GetAdditionalPersonInfo()
{
	return m_oAdditionalInfo;
}

BOOL CPersonsDoc::SelectPersonInfoWithIdFromDatabase(const long lID, CPersonInfo& oPersonInfo)
{
	//Селект на клиент и информацията за него по ид
	if (!m_oPersonsData.SelectPersonInfoWithPersonId(lID, oPersonInfo))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPersonsDoc::ManagePersonInfo(CPersonInfo& oPersonInfo, const LPARAM lOperationFlag)
{
	//Указател към старите данни
	CPersonInfo* pPersonInfoData = &oPersonInfo;

	//Ивършване на операции в зависимост от флага
	if (!m_oPersonsData.DoOperationWithPersonInfo(oPersonInfo, lOperationFlag))
	{
		return FALSE;
	}

	//Обновяване на засегнатия елемент в масива с данни за клиенти
	if (!RenewElementInPersonInfoArray(oPersonInfo, lOperationFlag))
	{
		return FALSE;
	}

	//Достъпваме индекса на променения елемент
	INT_PTR lIndexRenewElementInPersonsInfoArray = FindIndexOfElementInPersonsInfoArrayByPersonId(oPersonInfo.GetPerson().lId);

	if (lIndexRenewElementInPersonsInfoArray != -1)
	{
		//Достъпваме обновения елемент ако не е бил изтрит
		pPersonInfoData = m_oPersonsInfo.GetAt(lIndexRenewElementInPersonsInfoArray);
	}

	//Обновяване на информацията за клиент във вюто, при изтрит елемент се подават сатрите данни
	UpdateAllViews(nullptr, lOperationFlag, (CObject*)&pPersonInfoData->GetPerson());

	return TRUE;
}

BOOL CPersonsDoc::GetPersonInfoByPersonId(const long LId, CPersonInfo& oPersonInfo)
{
	//Нямираме индекса на елемнта по ИД на клиент в масива с клиенски данни
	INT_PTR lIndex = FindIndexOfElementInPersonsInfoArrayByPersonId(LId);
	if (lIndex == -1)
	{
		return FALSE;
	} 

	//Достъпваме цялата информация за открития клиент
	CPersonInfo* pFindPersonInfo =  m_oPersonsInfo.GetAt(lIndex);
	if (pFindPersonInfo == nullptr)
	{
		return FALSE;
	}

	//Задаваме нови стойности на подадения параметър
	if (!oPersonInfo.AddPersonInfo(pFindPersonInfo->GetPerson(), pFindPersonInfo->GetPhoneNumbers()))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsDoc::RenewElementInPersonInfoArray(CPersonInfo& oPersonInfoToBeRenewInArray,const  LPARAM lOperationFlag)
{
	//Ако сме подали флаг за изтриване, да се прелахне елемента от масива с клиентски данни
	if (lOperationFlag == OPERATIONS_WITH_DATA_FLAGS_DELETE)
	{
		if (!m_oPersonsInfo.RemoveElement(oPersonInfoToBeRenewInArray))
		{
			return FALSE;
		}

		return TRUE;
	}

	//Добавяне или редактиране на елемент в клиентския масив
	if (!ManageInsertUpdateElementInPersonsInfoArray(oPersonInfoToBeRenewInArray))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsDoc::ManageInsertUpdateElementInPersonsInfoArray(const CPersonInfo& oNewDataPersonInfo) 
{
	//Търси се в масива с клиентки данни клиент с ИД на подаден елемент за обновление
	INT_PTR lIndexOfElement = FindIndexOfElementInPersonsInfoArrayByPersonId(oNewDataPersonInfo.GetPerson().lId);

	if(lIndexOfElement != -1)
	{
		m_oPersonsInfo.ReplaceDataOfElementByIndex(lIndexOfElement, oNewDataPersonInfo);
		return TRUE;
	}

	//Ако елемента не присъства в масива с клиентски данни да се добави
	if (m_oPersonsInfo.AddElement(oNewDataPersonInfo) == -1)
	{
		return FALSE;
	}

	return TRUE;
}

INT_PTR CPersonsDoc::FindIndexOfElementInPersonsInfoArrayByPersonId(const long lId)
{
	for (INT_PTR lIndex = 0; lIndex < m_oPersonsInfo.GetCount(); lIndex++)
	{
		//Достъп до текущ елемент
		CPersonInfo* oPersonInfo = m_oPersonsInfo.GetAt(lIndex);

		//Сравнение на ид на двата клиента
		if (oPersonInfo->GetPerson().lId == lId)
		{
			return lIndex;
		}
	}

	//Връщаме -1 при липса на клиент в масива с подадено ИД
	return -1;
}


// CPersonsDoc diagnostics

#ifdef _DEBUG
void CPersonsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CPersonsDoc serialization

void CPersonsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}
#endif


// CPersonsDoc commands
