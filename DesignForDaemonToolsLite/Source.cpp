#include <windows.h> // ������������ ����, ���������� ������� API
#include <tchar.h>
#include <iostream>
#include "Header.h"

using namespace std;

HINSTANCE hInst; //���������� ���������� ����������. �� ����� handle instance

char szAppName[] = "DAEMON Tools Lite";
char szAppTitle[] = "DAEMON Tools Lite";


/*
��������������� ���� ������ ������������ � ��������� ��������.
� ���������, ���������, ��������� ����, ������������ ��� ������ �
�������� ��������� ������ ������� ��������� ������ ����:

LRESULT CALLBACK ����������(HWND hWnd, UINT uMSg, WPARAM wParam, LPARAM lParam);

������ � ������ �������� ����� � ��������� ��������.
LPARAM � ��� ��� �������� lParam (long parameter). ������������ ������ � wparam � ��������� ��������.
LRESULT � ��������, ������������ ������� ���������� ����� ��� long.
WPARAM � ��� ��� �������� wParam (word parameter). ������������ ������ � lParam � ��������� ��������.
*/
LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// �������� ������� - ������ int main() � ���������� ����������:
int APIENTRY WinMain(HINSTANCE hInstance, // ���������� ���������� ����������
	HINSTANCE hPrevInstance, // � Win32 �� ������������
	LPSTR lpCmdLine, // ����� ��� ������� ���� � ������ ��������� ������
	int nCmdShow) // ����� ����������� ����
{
	setlocale(LC_ALL, "RUS");

	WNDCLASSEX wc; // ������ ���������, ��� ��������� � ������ ������ WNDCLASSEX
	HWND hWnd; // ������ ���������� �������� ������
	MSG msg;

	hInst = hInstance;
	wc.cbSize = sizeof(wc); // �������� ��������� (� ������)
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ���������� ������
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // .... ������� ����
	wc.style = NULL; // ����� ������ ������
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ���������� ����� ����
	wc.lpszMenuName = NULL; // ��������� �� const-������, ���������� ��� ����, ������������ ��� ������
	wc.lpszClassName = szAppName; // ��������� �� const-������, ���������� ��� ������
	wc.lpfnWndProc = (WNDPROC)WndProc; //��������� �� ������� ���������
	wc.cbClsExtra = 0; // ����� ������������� ������ ��� �������� ���������� ����������
	wc.cbWndExtra = 0; // ����� ������������� ������ � ����� ���������
	wc.hIconSm = 0;

	if (!RegisterClassEx(&wc))
	{
		// � ������ ���������� ����������� ������:
		MessageBox(NULL, _T("�� ���������� ���������������� �����!"), _T("������"), MB_OK);
		return NULL; // ����������, �������������, ������� �� WinMain
	}

	hWnd = CreateWindow(szAppName, // ��� ������
		szAppTitle, // ��� ���� (�� ��� ������)
		WS_OVERLAPPED | //������������� ���� �� ������� ��������� � ������
		WS_CAPTION | //������ ���������
		WS_SYSMENU | //���� ���� � ��� ������ ���������
		WS_THICKFRAME | //��������� �������� ����� ����
		WS_MINIMIZEBOX |
		WS_BORDER,
		//WS_OVERLAPPEDWINDOW, // ������ ����������� ������
		CW_USEDEFAULT, // ��������� ���� �� ��� � (�� ���������)
		CW_USEDEFAULT, // ������� ���� �� ��� � (��� ������ � �, �� ������ �� �����)
		500, // ������ ������ (�� ���������)
		400, // ������ ���� (��� ������ � ������, �� ������ �� �����)
		NULL, // ���������� ������������� ������ (� ��� ��� ���. ����)
		NULL, // ���������� ���� (� ��� ��� ���)
		hInst, // .... ���������� ����������
		NULL); // ������ �� ������� �� WndProc

	if (!hWnd)
	{
		// � ������ ������������� �������� ���� (�������� ��������� � ��):
		MessageBox(NULL, _T("�� ���������� ������� ����!"), _T("������"), MB_OK);
		return NULL; // ������� �� ����������
	}

	/*hWnd_button1 = CreateWindow("button", "������", WS_CHILD | WS_VISIBLE | BS_PUSHLIKE,
		390, 325, 80, 25, hWnd, (HMENU)10000, hInstance, NULL);

	hWnd_button2 = CreateWindow("button", "����� >", WS_CHILD | WS_VISIBLE | BS_PUSHLIKE,
		290, 325, 80, 25, hWnd, (HMENU)10000, hInstance, NULL);*/

	ShowWindow(hWnd, nCmdShow); //���������� ���� �� ������ ��. Ÿ ������ �������� � ����������  ������ (�� �����������  CreateWindow()). 
								//������ �������� � ����� �����������. ��� ������ ������� ���� ������ ���� ����� ���������� ��������� 
								//������� WinMain(), � � ����������� ���� ����� ��������� ���� ������
	UpdateWindow(hWnd); //�������� �� ���������� ������ �� ������ ��� ������������� ��� ��� ������������ ����������. 
						//��� �������� � �� ��� �� ���������� ����.

	while (GetMessage(&msg, // ��������� �� ��������� MSG
		NULL, // ���������� ������ 
		NULL, // �������
		NULL)) // ������� ��� ������� ���������
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT WINAPI WndProc(HWND hWnd, // ���������� ������
	UINT uMsg, // ���������, ���������� ��
	WPARAM wParam, // ���������
	LPARAM lParam) // ���������, ��� ������������ ���������
{
	setlocale(LC_ALL, "RUS");

	PAINTSTRUCT ps; //� ��������� ���������� �� ���� ��� ����������
					//RECT rect; //������������� ������� ����
	HDC hdc; // ��������� �������� ����������.
	static int cxClient; // ������ ����
	static int cyClient; // ������ ����
	static int OldcxClient; // ������ ����
	static int OldcyClient; // ������ ����
	static COLORREF selectedColorBrush;
	static COLORREF selectedColorPen;
	static int xWindow;
	static int yWindow;
	static LOGFONT lf;
		
	switch (uMsg)
	{
	case WM_CREATE:
	{		
		lf.lfHeight = 20;
		lf.lfWeight = 400;
		lf.lfOutPrecision = 3;
		lf.lfClipPrecision = 2;
		lf.lfQuality = 1;
		lf.lfPitchAndFamily = 34;
		strcpy_s(lf.lfFaceName, sizeof("Microsoft YaHei"), "Microsoft YaHei");

		cxClient = 500;
		cyClient = 400;

		/*a = CreateFigures();
		b = new ListFigure[1];

		panelMenu = new PanelMenu(cyClient);
		sight = new Sight(100, 300);

		xWindow = 300;
		yWindow = 300;

		selectedColorBrush = RGB(40, 57, 60);
		selectedColorPen = RGB(238, 238, 238);
		radius = 50;*/
		break;
	}
	case WM_PAINT:
	{		
		//cxClient = LOWORD(lParam);
		//cyClient = HIWORD(lParam);

		hdc = BeginPaint(hWnd, &ps); // ������������ �������� ���������� � ����.

		/*HBRUSH hBrushBottomPanel = CreateSolidBrush(RGB(240, 240, 240));
		HBRUSH hBrushLeftPicture = CreateSolidBrush(RGB(51, 190, 243));
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(135, 135, 135));

		SelectObject(hdc, hBrushBottomPanel);
		SelectObject(hdc, hPen);

		Rectangle(hdc, -1, cyClient - 90, cxClient, cyClient);
				
		SelectObject(hdc, hBrushLeftPicture);
		
		Rectangle(hdc, 0, 0, 170, 310);

		DeleteObject(hBrushBottomPanel);
		DeleteObject(hBrushLeftPicture);
		DeleteObject(hPen);*/

		/////////////////////////////////////////////////////////////////////////

		{
			//CHOOSEFONT cf;			

			
		}

									 /*int k = GetDeviceCaps(hdc, HORZSIZE); //������, � �����������, ����������� ������.
									 k = GetDeviceCaps(hdc, VERTSIZE); //������, � �����������, ����������� ������.
									 k = GetDeviceCaps(hdc, HORZRES); //������, � �����������, ����������� ������.
									 k = GetDeviceCaps(hdc, VERTRES); //������, � �����������, ����������� ������.
									 k = GetMapMode(hdc);
									 //SetMapMode(hdc, MM_ISOTROPIC);
									 k = GetMapMode(hdc);*/

									 /*SetMapMode(hdc, MM_ISOTROPIC);
									 SetWindowExtEx(hdc, 10, 10, NULL);
									 SetViewportExtEx(hdc, -10, -10, NULL);
									 SetViewportOrgEx(hdc, 300, 300, NULL);*/

		/*SetViewportOrgEx(hdc, xWindow, yWindow, NULL);

		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(40, 57, 60));
		SelectObject(hdc, hPen);

		Rectangle(hdc, -50, -50, 50, 50);

		MoveToEx(hdc, 0, 0, NULL);
		LineTo(hdc, 0, 10);
		MoveToEx(hdc, 0, 0, NULL);
		LineTo(hdc, 10, 0);

		DeleteObject(hPen);

		panelMenu->Paint(hdc);

		EndPaint(hWnd, &ps);*/
		break;
	}
	case WM_SIZE:
	{
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		hdc = GetDC(hWnd);	

		/*SetPlaceButton(hButtonCancel, "������", hWnd, cxClient - 110, cyClient - 40);
		SetPlaceButton(hButtonNext, "����� >", hWnd, cxClient - 210, cyClient - 40);*/

		

		PaintWelcomeWindow(hWnd, hdc, OldcxClient, OldcyClient, BP_MODE_ERASER, lf);
		PaintWelcomeWindow(hWnd, hdc, cxClient, cyClient, BP_MODE_NORMAL, lf);
		
		OldcxClient = cxClient;
		OldcyClient = cyClient;

		/*SetViewportOrgEx(hdc, xWindow, yWindow, NULL);
		b->Paint(hdc);

		panelMenu->SetCYClient(cyClient);*/
		//panelMenu->Paint(hdc);

		break;
	}
	case WM_LBUTTONDOWN:
	{
		/*HDC hdc = GetDC(hWnd);
		x = LOWORD(lParam); //����� ����������
		y = HIWORD(lParam);

		if ((x >= 0) && (x <= 140))
		{
			panelMenu->OnMenuDOWN(a, b, xWindow, yWindow, x, y, hdc);
		}
		else if (x > 140)
		{
			SetViewportOrgEx(hdc, xWindow, yWindow, NULL);
			MyEllipse* t = new MyEllipse(
				selectedColorPen,
				selectedColorBrush,
				x - radius - xWindow,
				y - radius - yWindow,
				x + radius - xWindow,
				y + radius - yWindow);
			b->AddElemToEnd(t);
			b->Paint(hdc);
			delete t;
		}

		panelMenu->Paint(hdc);*/

		break;
	}
	case WM_LBUTTONUP:
	{
		/*panelMenu->OnMenuUP();*/
	}
	case WM_MOUSEMOVE:
	{
		/*HDC hdc = GetDC(hWnd);
		x = LOWORD(lParam); //����� ����������
		y = HIWORD(lParam);

		panelMenu->OnMenuMOVE(
			b,
			xWindow, yWindow,
			cxClient, cyClient,
			x, y, hdc);

		if (x > 140)
		{
			if (sight->GetState())
			{
				sight->ChangeSight(xWindow, yWindow, x, y);
				SetViewportOrgEx(hdc, xWindow, yWindow, NULL);

				HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
				HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
				SelectObject(hdc, hBrush);
				SelectObject(hdc, hPen);

				Rectangle(hdc, 140 - xWindow, -yWindow, cxClient, cyClient);

				DeleteObject(hBrush);
				DeleteObject(hPen);

				b->Paint(hdc);
				panelMenu->Paint(hdc);
			}
		}*/

		break;
	}
	case WM_MBUTTONDOWN:
	{
		/*HDC hdc = GetDC(hWnd);
		x = LOWORD(lParam); //����� ����������
		y = HIWORD(lParam);

		if (x > 140)
		{
			sight->TurnOn();
			sight->SetCoordDown(x, y);
		}*/

		break;
	}
	case WM_MBUTTONUP:
	{
		/*sight->TurnOff();*/
		break;
	}
	case WM_DESTROY:
	{
		/*delete[] a;
		delete[] b;
		delete panelMenu;*/
		PostQuitMessage(NULL); // ���������� WinMain() ��������� WM_QUIT
		break;
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}