#include <windows.h> // заголовочный файл, содержащий функции API
#include <tchar.h>
#include <iostream>
#include "Header.h"

using namespace std;

HINSTANCE hInst; //дескриптор экземпляра приложения. От фразы handle instance

char szAppName[] = "DAEMON Tools Lite";
char szAppTitle[] = "DAEMON Tools Lite";


/*
Вспомогательные типы данных используются в некоторых функциях.
В частности, параметры, описанные ниже, используются при работе с
функцией обратного вызова оконной процедуры такого вида:

LRESULT CALLBACK ИмяФункции(HWND hWnd, UINT uMSg, WPARAM wParam, LPARAM lParam);

Работа с данной функцией будет в следующих разделах.
LPARAM – тип для описания lParam (long parameter). Используются вместе с wparam в некоторых функциях.
LRESULT – значение, возвращаемое оконной процедурой имеет тип long.
WPARAM – тип для описания wParam (word parameter). Используются вместе с lParam в некоторых функциях.
*/
LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Основная функция - аналог int main() в консольном приложении:
int APIENTRY WinMain(HINSTANCE hInstance, // дескриптор экземпляра приложения
	HINSTANCE hPrevInstance, // в Win32 не используется
	LPSTR lpCmdLine, // нужен для запуска окна в режиме командной строки
	int nCmdShow) // режим отображения окна
{
	setlocale(LC_ALL, "RUS");

	WNDCLASSEX wc; // создаём экземпляр, для обращения к членам класса WNDCLASSEX
	HWND hWnd; // создаём дескриптор будущего окошка
	MSG msg;

	hInst = hInstance;
	wc.cbSize = sizeof(wc); // величина структуры (в байтах)
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // дескриптор значка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // .... курсора мыши
	wc.style = NULL; // стиль класса окошка
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Дескриптор кисти фона
	wc.lpszMenuName = NULL; // указатель на const-строку, содержащюю имя меню, применяемого для класса
	wc.lpszClassName = szAppName; // указатель на const-строку, содержащюю имя класса
	wc.lpfnWndProc = (WNDPROC)WndProc; //Указатель на оконную процедуру
	wc.cbClsExtra = 0; // число освобождаемых байтов при создании экземпляра приложения
	wc.cbWndExtra = 0; // число освобождаемых байтов в конце структуры
	wc.hIconSm = 0;

	if (!RegisterClassEx(&wc))
	{
		// в случае отсутствия регистрации класса:
		MessageBox(NULL, _T("Не получилось зарегистрировать класс!"), _T("Ошибка"), MB_OK);
		return NULL; // возвращаем, следовательно, выходим из WinMain
	}

	hWnd = CreateWindow(szAppName, // имя класса
		szAppTitle, // имя окна (то что сверху)
		WS_OVERLAPPED | //Перекрывающее окно со строкой заголовка и рамкой
		WS_CAPTION | //Строка заголовка
		WS_SYSMENU | //Меню окна в его строке заголовка
		WS_THICKFRAME | //Установка размеров рамки окна
		WS_MINIMIZEBOX |
		WS_BORDER,
		//WS_OVERLAPPEDWINDOW, // режимы отображения окошка
		CW_USEDEFAULT, // положение окна по оси х (по умолчанию)
		CW_USEDEFAULT, // позиция окна по оси у (раз дефолт в х, то писать не нужно)
		500, // ширина окошка (по умолчанию)
		400, // высота окна (раз дефолт в ширине, то писать не нужно)
		NULL, // дескриптор родительского окошка (у нас нет род. окон)
		NULL, // дескриптор меню (у нас его нет)
		hInst, // .... экземпляра приложения
		NULL); // ничего не передаём из WndProc

	if (!hWnd)
	{
		// в случае некорректного создания окна (неверные параметры и тп):
		MessageBox(NULL, _T("Не получилось создать окно!"), _T("Ошибка"), MB_OK);
		return NULL; // выходим из приложения
	}

	/*hWnd_button1 = CreateWindow("button", "Отмена", WS_CHILD | WS_VISIBLE | BS_PUSHLIKE,
		390, 325, 80, 25, hWnd, (HMENU)10000, hInstance, NULL);

	hWnd_button2 = CreateWindow("button", "Далее >", WS_CHILD | WS_VISIBLE | BS_PUSHLIKE,
		290, 325, 80, 25, hWnd, (HMENU)10000, hInstance, NULL);*/

	ShowWindow(hWnd, nCmdShow); //отображает окно на экране ПК. Её первый параметр – дескриптор  окошка (он возвращался  CreateWindow()). 
								//Второй параметр – стиль отображения. При первом запуске окна должен быть равен последнему параметру 
								//функции WinMain(), а в последующие разы можно вписывать свои данные
	UpdateWindow(hWnd); //отвечает за обновления окошка на экране при сворачиваниях или при динамической информации. 
						//Его параметр – всё тот же дескриптор окна.

	while (GetMessage(&msg, // указатель на структуру MSG
		NULL, // дескриптор окошка 
		NULL, // фильтры
		NULL)) // фильтры для выборки сообщений
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT WINAPI WndProc(HWND hWnd, // дескриптор окошка
	UINT uMsg, // сообщение, посылаемое ОС
	WPARAM wParam, // параметры
	LPARAM lParam) // сообщений, для последующего обращения
{
	setlocale(LC_ALL, "RUS");

	PAINTSTRUCT ps; //в структуре информация об окне для прорисовки
					//RECT rect; //прямоугольная область окна
	HDC hdc; // Объявляем контекст устройства.
	static int cxClient; // Ширина окна
	static int cyClient; // Высота окна
	static int OldcxClient; // Ширина окна
	static int OldcyClient; // Высота окна
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

		hdc = BeginPaint(hWnd, &ps); // Присоединяем контекст устройства к окну.

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

									 /*int k = GetDeviceCaps(hdc, HORZSIZE); //Ширина, в миллиметрах, физического экрана.
									 k = GetDeviceCaps(hdc, VERTSIZE); //Ширина, в миллиметрах, физического экрана.
									 k = GetDeviceCaps(hdc, HORZRES); //Ширина, в миллиметрах, физического экрана.
									 k = GetDeviceCaps(hdc, VERTRES); //Ширина, в миллиметрах, физического экрана.
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

		/*SetPlaceButton(hButtonCancel, "Отмена", hWnd, cxClient - 110, cyClient - 40);
		SetPlaceButton(hButtonNext, "Далее >", hWnd, cxClient - 210, cyClient - 40);*/

		

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
		x = LOWORD(lParam); //узнаём координаты
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
		x = LOWORD(lParam); //узнаём координаты
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
		x = LOWORD(lParam); //узнаём координаты
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
		PostQuitMessage(NULL); // отправляем WinMain() сообщение WM_QUIT
		break;
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}