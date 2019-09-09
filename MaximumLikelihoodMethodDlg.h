
// MaximumLikelihoodMethodDlg.h: файл заголовка
//

#pragma once
#include "Drawer.h"
#include "Signal.h"

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

	void init_parameters();
	afx_msg void OnBnClickedOk();
	std::shared_ptr<Signal<float>> signal1;
	Drawer drawer1;
};
