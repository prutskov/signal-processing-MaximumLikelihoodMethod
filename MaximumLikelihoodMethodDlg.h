
// MaximumLikelihoodMethodDlg.h: файл заголовка
//

#pragma once
#include "Drawer.h"
#include "Signal.h"

#define FPtype double
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
	Drawer drawer3;
	FPtype A;
	FPtype bt;
	FPtype f0;
	FPtype fd;
	FPtype SNR;
	size_t N;
	size_t tau;
	FPtype referTau;
	FPtype realTau;

	ModulationType modulationType;
	CButton radioAmpl;
	CButton radioBPSK;
	CButton radioMSK;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();

	void makeResearch();
	std::vector<PointF> researchPoints;
	size_t nExperiments;
	FPtype snrLimit;
	FPtype snrStep;
	afx_msg void OnBnClickedButton2();
	Drawer drawer4;
};
