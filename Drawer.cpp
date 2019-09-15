#include "stdafx.h"
#include "Drawer.h"
#include <math.h>

ULONG_PTR token1;
Drawer::Drawer()
{
	Status s;
	GdiplusStartupInput input;
	s = GdiplusStartup(&token1, &input, NULL);
	if (s != Ok)
	{
		MessageBox(L"ERROR!!!", L"GDI is not started", MB_ICONERROR);
	}
}


Drawer::~Drawer()
{
	GdiplusShutdown(token1);
}


void Drawer::DrawItem(LPDRAWITEMSTRUCT RECT)
{
	float maxY = 1;
	float maxX = 1;
	if (_points != nullptr&&_points[0].size() > 0)
	{
		maxX = 0;
		maxY = 0;
		size_t size = _points->size();
		for (size_t i = 0; i < size; ++i)
		{
			if (fabs(_points[0][i].Y) > maxY) maxY = fabs(_points[0][i].Y);
			if (_points[0][i].X > maxX) maxX = _points[0][i].X;
		}
		if (maxY == 0 || maxX == 0)
		{
			maxY = 1;
			maxX = 1;
		}
	}
	ymax = maxY + maxY / 3.f;
	ymin = -maxY - maxY / 3.f;
	step_y = ymax / 4.f;

	xmax = maxX;
	xmin = -xmax / 100.f;
	step_x = xmax / 12.f;


	Graphics gr(RECT->hDC);
	Bitmap bmp(RECT->rcItem.right, RECT->rcItem.bottom, &gr);
	Graphics grBmp(&bmp);

	FontFamily podpis_osi(L"Arial");
	Gdiplus::Font podpis(&podpis_osi, 12, FontStyleRegular, UnitPixel);

	SolidBrush brush(Color::White);
	Pen graph_pen(Color::Yellow, 1);
	Pen bottom_pen(Color::Aqua, 4);
	Pen axis_pen(Color::White, 3);
	Pen grid_pen(Color::LightGray, 1);
	grid_pen.SetDashStyle(DashStyle::DashStyleDash);

	grBmp.SetSmoothingMode(SmoothingModeAntiAlias);
	grBmp.Clear(Color::Black);

	grBmp.DrawLine(&axis_pen, X(RECT, xmin), Y(RECT, 0), X(RECT, xmax), Y(RECT, 0));
	grBmp.DrawLine(&axis_pen, X(RECT, 0), Y(RECT, ymin), X(RECT, 0), Y(RECT, ymax));

	for (float x = step_x; x <= xmax; x += step_x)
	{
		grBmp.DrawLine(&grid_pen, X(RECT, x), Y(RECT, ymin), X(RECT, x), Y(RECT, ymax));
	}
	for (float x = -step_x; x >= xmin; x -= step_x)
	{
		grBmp.DrawLine(&grid_pen, X(RECT, x), Y(RECT, ymin), X(RECT, x), Y(RECT, ymax));
	}

	for (float y = step_y; y <= ymax; y += step_y)
	{
		grBmp.DrawLine(&grid_pen, X(RECT, xmin), Y(RECT, y), X(RECT, xmax), Y(RECT, y));
	}
	for (float y = -step_y; y >= ymin; y -= step_y)
	{
		grBmp.DrawLine(&grid_pen, X(RECT, xmin), Y(RECT, y), X(RECT, xmax), Y(RECT, y));
	}

	for (float x = step_x; x <= xmax; x += step_x)
	{
		CString str;
		str.Format(_T("%.3f"), x);
		grBmp.DrawString(str, -1, &podpis, PointF(X(RECT, x), Y(RECT, 0) + 2.f), NULL, &brush);
	}
	for (float x = -step_x; x >= xmin; x -= step_x)
	{
		CString str;
		str.Format(_T("%.1f"), x);
		grBmp.DrawString(str, -1, &podpis, PointF(X(RECT, x), Y(RECT, 0) + 2.f), NULL, &brush);
	}

	for (float y = step_y; y <= ymax; y += step_y)
	{
		CString str;
		str.Format(_T("%.5f"), y);
		grBmp.DrawString(str, -1, &podpis, PointF(X(RECT, 0), Y(RECT, y) + 2.f), NULL, &brush);
	}
	for (float y = 0; y >= ymin; y -= step_y)
	{
		CString str;
		str.Format(_T("%.5f"), y);
		grBmp.DrawString(str, -1, &podpis, PointF(X(RECT, 0), Y(RECT, y) + 2.f), NULL, &brush);
	}

	if (_points != nullptr)
	{
		size_t size = _points->size();
		if (size > 1)
			for (size_t i = 0; i < size - 1; ++i)
			{
				grBmp.DrawLine(&graph_pen, X(RECT, _points[0][i].X), Y(RECT, _points[0][i].Y),
					X(RECT, _points[0][i + 1].X), Y(RECT, _points[0][i + 1].Y));
			}
	}
	gr.DrawImage(&bmp, 0, 0);
}


REAL Drawer::X(LPDRAWITEMSTRUCT RECT, float x)
{
	return (REAL)(RECT->rcItem.right) / (xmax - xmin)*((x)-xmin);
}

REAL Drawer::Y(LPDRAWITEMSTRUCT RECT, float y)
{
	return -(REAL)(RECT->rcItem.bottom) / (ymax - ymin)*((y)-ymax);
}

REAL Drawer::Width(LPDRAWITEMSTRUCT RECT, float width)
{
	return (REAL)(RECT->rcItem.right) / (xmax - xmin)*width;
}

REAL Drawer::Height(LPDRAWITEMSTRUCT RECT, float height)
{
	return (REAL)(RECT->rcItem.bottom) / (ymax - ymin)*height;
}
