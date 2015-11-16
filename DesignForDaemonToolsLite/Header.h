#pragma once
#include <windows.h> // заголовочный файл, содержащий функции API
#include <tchar.h>
#include <iostream>

#define BP_MODE_ERASER 0
#define BP_MODE_NORMAL 1

HWND hButtonCancel;
HWND hButtonNext;
HWND hComboBox;


void SetPlaceButton(HWND button, char* name, HWND hWnd, int x, int y)
{
	button = CreateWindow("button", name,
		WS_CHILD |
		WS_VISIBLE,
		x, y, 80, 25, hWnd, (HMENU)10000, NULL, NULL);
}

class RactangleWithBrashAndPen
{

};

void PaintWelcomeWindow(
	const HWND& hWnd,
	const HDC& hdc, 
	const int& cxClient, 
	const int& cyClient, 
	const int& paintMode, 
	LOGFONT lf)
{
	switch (paintMode)
	{
	case 0:
	{
		HBRUSH hBrushEraser = CreateSolidBrush(RGB(255, 255, 255));
		HPEN hPenEraser = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

		SelectObject(hdc, hBrushEraser);
		SelectObject(hdc, hPenEraser);

		Rectangle(hdc, -1, cyClient - 60, cxClient + 10, cyClient + 10);
		Rectangle(hdc, 0, 0, 170, cyClient - 60);
		Rectangle(hdc, 170, 0, cxClient + 10, cyClient - 60);

		DeleteObject(hBrushEraser);
		DeleteObject(hPenEraser);
		break;
	}
	case 1:
	{
		SetPlaceButton(hButtonCancel, "Cancel", hWnd, cxClient - 110, cyClient - 40);
		SetPlaceButton(hButtonNext, "Next >", hWnd, cxClient - 210, cyClient - 40);

		hComboBox = CreateWindow("COMBOBOX", "combobox",
			WS_CHILD | WS_VISIBLE | CBS_SORT | CBS_DROPDOWNLIST,
			200, 155, 250, 500, hWnd, 0, NULL, 0);

		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Russian (Русский)");
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"English");
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"German");
		
		HBRUSH hBrushBottomPanel = CreateSolidBrush(RGB(240, 240, 240));
		HBRUSH hBrushLeftPicture = CreateSolidBrush(RGB(51, 190, 243));
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(135, 135, 135));

		SelectObject(hdc, hBrushBottomPanel);
		SelectObject(hdc, hPen);

		Rectangle(hdc, -1, cyClient - 60, cxClient + 10, cyClient + 10);

		SelectObject(hdc, hBrushLeftPicture);

		Rectangle(hdc, 0, 0, 170, cyClient - 60);

		DeleteObject(hBrushBottomPanel);
		DeleteObject(hBrushLeftPicture);
		DeleteObject(hPen);
		break;
	}
	}

	HFONT hFont = CreateFontIndirect(&lf);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(0, 0, 0));

	char str1[] = "Welcome to"; // 
	char str2[] = "DAEMON Tools Lite";
	char str3[] = "A simple tool for creating disk images and";
	char str4[] = "emulation of virtual drive.";
	char str5[] = "Language :";
	char str6[] = "Click the Next button, you agree to the terms";
	char str7[] = "License Agreement and politics";
	char str8[] = "konfdentsalnosti.";

	TextOut(hdc, 200, 20, str1, strlen(str1));
	TextOut(hdc, 200, 40, str2, strlen(str2));

	lf.lfHeight = 15;
	hFont = CreateFontIndirect(&lf);
	SelectObject(hdc, hFont);
	TextOut(hdc, 200, 90, str3, strlen(str3));
	TextOut(hdc, 200, 105, str4, strlen(str4));
	TextOut(hdc, 200, 135, str5, strlen(str5));

	TextOut(hdc, 200, 250, str6, strlen(str6));
	TextOut(hdc, 200, 265, str7, strlen(str7));
	TextOut(hdc, 200, 280, str8, strlen(str8));
}
