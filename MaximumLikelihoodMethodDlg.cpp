
// MaximumLikelihoodMethodDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "MaximumLikelihoodMethod.h"
#include "MaximumLikelihoodMethodDlg.h"
#include "afxdialogex.h"
#include <memory>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CMaximumLikelihoodMethodDlg



CMaximumLikelihoodMethodDlg::CMaximumLikelihoodMethodDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAXIMUMLIKELIHOODMETHOD_DIALOG, pParent)
	, A(1)
	, bt(9600)
	, f0(25000)
	, fd(250000)
	, N(100)
	, tau(50)
	, SNR(-1)
	, referTau(0)
	, realTau(0)
	, nExperiments(50)
	, snrLimit(20)
	, snrStep(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMaximumLikelihoodMethodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRAPH1, drawer1);
	DDX_Text(pDX, IDC_A, A);
	DDX_Text(pDX, IDC_BT, bt);
	DDX_Text(pDX, IDC_F0, f0);
	DDX_Text(pDX, IDC_FD, fd);
	DDX_Text(pDX, IDC_N, N);
	DDX_Control(pDX, IDC_GRAPH2, drawer2);
	DDX_Text(pDX, IDC_TAU, tau);
	DDX_Text(pDX, IDC_TAU2, SNR);
	DDX_Text(pDX, IDC_TAU_S, referTau);
	DDX_Text(pDX, IDC_TAU_S2, realTau);
	DDX_Control(pDX, IDC_GRAPH3, drawer3);
	DDX_Control(pDX, IDC_RADIO1, radioAmpl);
	DDX_Control(pDX, IDC_RADIO2, radioBPSK);
	DDX_Control(pDX, IDC_RADIO3, radioMSK);
	DDX_Text(pDX, IDC_A2, nExperiments);
	DDX_Text(pDX, IDC_A3, snrLimit);
	DDX_Text(pDX, IDC_A4, snrStep);
	DDX_Control(pDX, IDC_GRAPH4, drawer4);
}

BEGIN_MESSAGE_MAP(CMaximumLikelihoodMethodDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMaximumLikelihoodMethodDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &CMaximumLikelihoodMethodDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMaximumLikelihoodMethodDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CMaximumLikelihoodMethodDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_BUTTON2, &CMaximumLikelihoodMethodDlg::OnBnClickedButton2)
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
	srand(static_cast<unsigned int>(time(NULL)));
	radioAmpl.SetCheck(BST_CHECKED);
	modulationType = ModulationType::Amplitude;
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


void CMaximumLikelihoodMethodDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	SignalParameter<FPtype> param = { N, A, f0, bt, fd };
	param._modulType = modulationType;
	signal1 = std::make_shared<Signal<FPtype>>(param);
	param._SNR = SNR;
	signal2 = std::make_shared<Signal<FPtype>>(signal1.get(), param, tau);
	referTau = signal2->getReferenceTau();
	auto maxCorr = signal2->getCorrelation(signal1.get());
	realTau = signal2->getTau();

	drawer1._points = signal1->getSignalPoints();
	drawer2._points = signal2->getSignalPoints();

	drawer3.isHasNegative = false;
	drawer3._points = signal2->getCorrelationPoints();

	drawer1.Invalidate();
	drawer2.Invalidate();
	drawer3.Invalidate();

	UpdateData(FALSE);
}


void CMaximumLikelihoodMethodDlg::OnBnClickedRadio1()
{
	modulationType = ModulationType::Amplitude;
}


void CMaximumLikelihoodMethodDlg::OnBnClickedRadio2()
{
	modulationType = ModulationType::BPSK;
}


void CMaximumLikelihoodMethodDlg::OnBnClickedRadio3()
{
	modulationType = ModulationType::MSK;
}

void CMaximumLikelihoodMethodDlg::makeResearch()
{
	researchPoints.clear();

	FPtype snrMax = snrLimit;
	FPtype snrMin = -snrLimit;

	ofstream file("log.txt");
	SignalParameter<FPtype> param1 = { N, A, f0, bt, fd };
	param1._modulType = modulationType;
	SignalParameter<FPtype> param2 = { N, A, f0, bt, fd };
	param2._modulType = modulationType;


	for (FPtype snr = snrMin; snr < snrMax; snr += snrStep)
	{
		param2._SNR = snr;

		FPtype count = 0;
		for (size_t iter = 0; iter < nExperiments; ++iter)
		{
			signal1 = std::make_shared<Signal<FPtype>>(param1);
			signal2 = std::make_shared<Signal<FPtype>>(signal1.get(), param2, tau);
			FPtype tauRef = signal2->getReferenceTau();
			auto maxCorr = signal2->getCorrelation(signal1.get());
			FPtype tauReal = signal2->getTau();
			FPtype left = tauRef - 1.0 / bt / 2.0;
			FPtype right = tauRef + 1.0 / bt / 2.0;
			if ((tauReal >= left) &&
				(tauReal <= right))
			{
				++count;
			}
		}

		PointF point(snr, float(count) / nExperiments);
		file << point.X << "  " << point.Y << std::endl;
		researchPoints.emplace_back(point);
	}
	file.close();
}


void CMaximumLikelihoodMethodDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	drawer4.isHasNegative = false;
	drawer4.isHasNegativeX = true;
	makeResearch();
	drawer4._points = &researchPoints;
	drawer4.Invalidate();
}
