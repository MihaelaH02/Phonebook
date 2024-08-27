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
	CString strDocName;
	strDocName.Format(_T("Person %d"), ++nPersonsDocCounter);
	SetTitle(strDocName);

	if (!CDocument::OnNewDocument())
	{
		return FALSE;
	}

	///Променлива за досъп до бизнес логиката
	CPersonsData oPersonsData;

	//Зареждане на клиенти от базата данни в масив
	if (!oPersonsData.SelectAllPersons(m_oPersonsArray))
	{
		return FALSE;
	}

	//Зареждане на допълнителнита данните от базата данни в масив
	if (!oPersonsData.LoadAdditionalModels(m_oAdditionalModels))
	{
		return FALSE;
	}

	return TRUE;
}

void CPersonsDoc::OnCloseDocument()
{
	nPersonsDocCounter--;
	CDocument::OnCloseDocument();
}

CPersonsArray& CPersonsDoc::GetPersons()
{
	return m_oPersonsArray;
}

INT_PTR CPersonsDoc::GetPersonsArrayCount()
{
	return m_oPersonsArray.GetCount();
}

CAdditionalDBModelsPersons& CPersonsDoc::GetAdditionalModels()
{
	return m_oAdditionalModels;
}

BOOL CPersonsDoc::SelectPerson(const long& lID, CPersonDBModel& oPersonDBModel)
{
	///Променлива за досъп до бизнес логиката
	CPersonsData oPersonsData;

	//Селект на клиент и информацията за него по ид
	if (!oPersonsData.SelectPersonDataByPersonId(lID, oPersonDBModel))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CPersonsDoc::ProcessPerson(CPersonDBModel& oPersonDBModel, const LPARAM lOperationFlag)
{
	///Променлива за досъп до бизнес логиката
	CPersonsData oPersonsData;

	//Ивършване на операции в зависимост от флага
	if (!oPersonsData.DoOperationWithPerson(oPersonDBModel, lOperationFlag))
	{
		return FALSE;
	}

	//Копие на клиента, преди дабъде променен
	PERSONS recPeroson = oPersonDBModel.GetPerson();

	//Достъпваме индекса на елемента в масива
	INT_PTR lIndex = m_oPersonsArray.FindIndexByElement(recPeroson, CompareId);

	//Обновяване на засегнатия елемент в масива с данни за клиенти
	if(!ProccesPersonInArray(recPeroson, lOperationFlag, lIndex))
	{
		return FALSE;
	}

	//Обновяване на информацията за клиент във вюто, при изтрит елемент се подават сатрите данни
	UpdateAllViews(nullptr, lOperationFlag, (CObject*)&recPeroson);

	return TRUE;
}

BOOL CPersonsDoc::ProccesPersonInArray(PERSONS& recPerson, const LPARAM lOperationFlag, INT_PTR& lIndex)
{
	switch (lOperationFlag)
	{
	//При подаване на флаг за прочетен елемент, да не се изпълнява операция
	case OPERATIONS_WITH_DATA_FLAGS_READED:
	break;

	//При подаване на флаг за добавяне, да се добави елемента от масива с клиенти
	case OPERATIONS_WITH_DATA_FLAGS_INSERT:
	{
		if (m_oPersonsArray.AddElement(recPerson) == -1)
		{
			return FALSE;
		}
	}
	break;

	//При подаване на флаг за редакция, да се редактира елемента от масива с клиенти
	case OPERATIONS_WITH_DATA_FLAGS_UPDATE:
	{
		if (!m_oPersonsArray.ReplaceElement(lIndex, recPerson))
		{
			return FALSE;
		}
	}
	break;

	//При подаване на флаг за изтриване, да се прелахне елемента от масива с клиенти
	case OPERATIONS_WITH_DATA_FLAGS_DELETE:
	{
		if (!m_oPersonsArray.RemoveElement(recPerson, CompareId))
		{
			return FALSE;
		}
	}
	break;

	//При подаден грешен флаг
	default:
	{
		return FALSE;
	}
	break;
	}

	return TRUE;
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
