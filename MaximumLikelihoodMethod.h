
// MaximumLikelihoodMethod.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CMaximumLikelihoodMethodApp:
// Сведения о реализации этого класса: MaximumLikelihoodMethod.cpp
//

class CMaximumLikelihoodMethodApp : public CWinApp
{
public:
	CMaximumLikelihoodMethodApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMaximumLikelihoodMethodApp theApp;
