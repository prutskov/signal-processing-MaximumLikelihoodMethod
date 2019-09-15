
// MaximumLikelihoodMethodDlg.h: файл заголовка
//

#pragma once
#include "Drawer.h"
#include "Signal.h"

#define FPtype float
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
public:
	std::vector<PointF> *vector;

	afx_msg void OnBnClickedButton1();

	std::shared_ptr<Signal<FPtype>> signal1, signal2;
	Drawer drawer1;
	Drawer drawer2;
	FPtype A;
	FPtype bt;
	FPtype f0;
	FPtype fd;
	FPtype SNR;
	size_t N;
	size_t tau;
};
