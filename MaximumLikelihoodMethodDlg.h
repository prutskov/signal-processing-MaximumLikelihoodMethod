﻿
// MaximumLikelihoodMethodDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CMaximumLikelihoodMethodDlg
class CMaximumLikelihoodMethodDlg : public CDialogEx
{
// Создание
public:
	CMaximumLikelihoodMethodDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAXIMUMLIKELIHOODMETHOD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
