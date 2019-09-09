﻿
// MaximumLikelihoodMethodDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "MaximumLikelihoodMethod.h"
#include "MaximumLikelihoodMethodDlg.h"
#include "afxdialogex.h"
#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CMaximumLikelihoodMethodDlg



CMaximumLikelihoodMethodDlg::CMaximumLikelihoodMethodDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAXIMUMLIKELIHOODMETHOD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMaximumLikelihoodMethodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRAPH1, drawer1);
}

BEGIN_MESSAGE_MAP(CMaximumLikelihoodMethodDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMaximumLikelihoodMethodDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CMaximumLikelihoodMethodDlg

BOOL CMaximumLikelihoodMethodDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий зна4чок

	// TODO: добавьте дополнительную инициализацию
	init_parameters();
	signal1 = std::make_shared<Signal<float>>(10);
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMaximumLikelihoodMethodDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMaximumLikelihoodMethodDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMaximumLikelihoodMethodDlg::init_parameters()
{
}



void CMaximumLikelihoodMethodDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}
