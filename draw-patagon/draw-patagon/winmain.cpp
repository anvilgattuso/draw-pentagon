#include <windows.h>
#include <math.h>
#define PI 3.14159265358979

BOOLEAN InitWindow(HINSTANCE hInstance, int nCmdShow);									//��ʼ�����ں�������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);		//��Ϣ����������
void calpata(LPPOINT lpPata, LPPOINT lpPata2, POINT org);								//�����С����ζ������꺯������

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;										//������Ϣ����

	InitWindow(hInstance, nCmdShow);				//��ʼ������
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);						//��Ϣѭ��
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

BOOLEAN InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;														//���崰�ھ��
	TCHAR szWindowClass[] = L"PATAGON";								//���崰��������
	TCHAR szTitle[] = L"�ȱ������";								//���崰�ڱ���
	WNDCLASS WndClass;												//���崰����
	WndClass.cbClsExtra = 0;										//�޴�������չ
	WndClass.cbWndExtra = 0;										//�޴���ʵ����չ
	WndClass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));	//����Ϊ��ɫ
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//���ڲ��ü�ͷ���
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//����ȱʡͼ��
	WndClass.hInstance = hInstance;									//��ǰӦ�ó�����
	WndClass.lpfnWndProc = WndProc;									//���ڴ�����
	WndClass.lpszClassName = szWindowClass;							//����������
	WndClass.lpszMenuName = NULL;									//�޴��ڲ˵�
	WndClass.style = 0;												//��������Ϊȱʡ����

	if (!RegisterClass(&WndClass))		//ע�ᴰ��
		return FALSE;
	hWnd = CreateWindow(
		szWindowClass,					//��������
		szTitle,						//������
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,					//�������Ͻ�����
		0,
		CW_USEDEFAULT,					//����ȱʡ�Ŀ�Ⱥ͸߶�
		0,
		NULL,							//�޸�����
		NULL,							//�����˵�
		hInstance,						//��ǰʵ�����
		NULL);							//��Ҫ�˲���
	if (!hWnd)
		return FALSE;
	ShowWindow(hWnd, nCmdShow);			//��ʾ����
	UpdateWindow(hWnd);					//���²������û���
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)			//��Ϣ������
{
	HDC hDC;								//�����豸�������
	HBRUSH hBrush;							//���廭ˢ���
	HPEN hPen;								//���廭�ʾ��
	PAINTSTRUCT PtStr;						//���������ͼ��Ϣ�Ľṹ�����
	RECT clientRect;						//����ͻ������νṹ�����
	POINT lpPata[5];						//������εĶ�������
	POINT lpPata2[5];						//С����εĶ�������
	POINT org;								//����ԭ��ṹ�����
	POINT lptrg[3];							//���������ε������˵�
	switch (message)
	{
	case WM_PAINT:											//�����ͼ��Ϣ
		hDC = BeginPaint(hWnd, &PtStr);						//����豸����ָ��
		GetClientRect(hWnd, &clientRect);					//��ȡ�ͻ�������
		//����ԭ������
		org.x = (clientRect.left + clientRect.right) / 2;
		org.y = (clientRect.top + clientRect.bottom) / 2;
		calpata(lpPata, lpPata2, org);										//��������ζ˵�

		//�ò�ͬ��ɫ�Ļ�ˢ����������
		hPen = (HPEN)GetStockObject(NULL_PEN);				//�����黭��							
		hBrush = CreateSolidBrush(RGB(120, 120, 120));		//���廭ˢ
		SelectObject(hDC, hPen);							//������ѡ���豸����
		SelectObject(hDC, hBrush);							//����ˢѡ���豸����
		Polygon(hDC, lpPata2, 5);							//���С�����
		DeleteObject(hBrush);								//ɾ����ˢ
		hBrush = CreateSolidBrush(RGB(45, 90, 90));
		SelectObject(hDC, hBrush);
		lptrg[0] = lpPata[0]; lptrg[1] = lpPata2[2]; lptrg[2] = lpPata2[3];
		Polygon(hDC, lptrg, 3);								//���������
		hBrush = CreateSolidBrush(RGB(200, 150, 150));
		SelectObject(hDC, hBrush);
		lptrg[0] = lpPata[0]; lptrg[1] = lpPata[1]; lptrg[2] = lpPata2[2];
		Polygon(hDC, lptrg, 3);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(150, 200, 150));
		SelectObject(hDC, hBrush);
		lptrg[0] = lpPata[1]; lptrg[1] = lpPata2[1]; lptrg[2] = lpPata2[2];
		Polygon(hDC, lptrg, 3);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(150, 150, 200));
		SelectObject(hDC, hBrush);
		lptrg[0] = lpPata[1]; lptrg[1] = lpPata[2]; lptrg[2] = lpPata2[1];
		Polygon(hDC, lptrg, 3);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(200, 150, 100));
		SelectObject(hDC, hBrush);
		lptrg[0] = lpPata[2]; lptrg[1] = lpPata2[0]; lptrg[2] = lpPata2[1];
		Polygon(hDC, lptrg, 3);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(50, 200, 150));
		SelectObject(hDC, hBrush);
		lptrg[0] = lpPata[2]; lptrg[1] = lpPata[3]; lptrg[2] = lpPata2[0];
		Polygon(hDC, lptrg, 3);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(150, 50, 180));
		SelectObject(hDC, hBrush);
		lptrg[0] = lpPata[3]; lptrg[1] = lpPata2[4]; lptrg[2] = lpPata2[0];
		Polygon(hDC, lptrg, 3);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(40, 100, 160));
		SelectObject(hDC, hBrush);
		lptrg[0] = lpPata[3]; lptrg[1] = lpPata[4]; lptrg[2] = lpPata2[4];
		Polygon(hDC, lptrg, 3);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(160, 40, 100));
		SelectObject(hDC, hBrush);
		lptrg[0] = lpPata[4]; lptrg[1] = lpPata2[3]; lptrg[2] = lpPata2[4];
		Polygon(hDC, lptrg, 3);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(200, 250, 200));
		SelectObject(hDC, hBrush);
		lptrg[0] = lpPata[4]; lptrg[1] = lpPata[0]; lptrg[2] = lpPata2[3];
		Polygon(hDC, lptrg, 3);
		DeleteObject(hBrush);
		DeleteObject(hPen);									//ɾ������

		//�ò�ͬ��ɫ�Ļ������Ӳ����ڵĸ���
		hPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
		SelectObject(hDC, hPen);
		MoveToEx(hDC, lpPata[0].x, lpPata[0].y, NULL);		//�ƶ�����һ����
		LineTo(hDC, lpPata[2].x, lpPata[2].y);				//��������㻭һ��ֱ��
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
		SelectObject(hDC, hPen);
		MoveToEx(hDC, lpPata[2].x, lpPata[2].y, NULL);
		LineTo(hDC, lpPata[4].x, lpPata[4].y);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 0));
		SelectObject(hDC, hPen);
		MoveToEx(hDC, lpPata[4].x, lpPata[4].y, NULL);
		LineTo(hDC, lpPata[1].x, lpPata[1].y);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 255));
		SelectObject(hDC, hPen);
		MoveToEx(hDC, lpPata[1].x, lpPata[1].y, NULL);
		LineTo(hDC, lpPata[3].x, lpPata[3].y);
		DeleteObject(hPen);
		hPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 255));
		SelectObject(hDC, hPen);
		MoveToEx(hDC, lpPata[3].x, lpPata[3].y, NULL);
		LineTo(hDC, lpPata[0].x, lpPata[0].y);
		DeleteObject(hPen);

		//���Ƶȱ������
		hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));		//�����ɫ����
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);		//�����黭ˢ
		SelectObject(hDC, hPen);							//������ѡ���豸����
		SelectObject(hDC, hBrush);							//����ˢѡ���豸����
		Polygon(hDC, lpPata, 5);							//�����������
		DeleteObject(hPen);									//ɾ������
		DeleteObject(hBrush);								//ɾ����ˢ

		EndPaint(hWnd, &PtStr);								//ɾ���豸�������
		break;
	case WM_DESTROY:										//�رմ���
		PostQuitMessage(0);
		break;
	default:												//Ĭ����Ϣ����
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void calpata(LPPOINT lpPata, LPPOINT lpPata2, POINT org)
{
	int i;
	double dist = 180.0;						//��������ĵ�����ľ���
	double theta = 72.0;						//��ת��
	double mult = 1 - 0.5 / sin(54 * PI / 180);	//С����γ�������
	for (i = 0; i < 5; i++)
	{
		lpPata[i].x = org.x + (long)(sin(theta * i * PI / 180) * dist);
		lpPata[i].y = org.y - (long)(cos(theta * i * PI / 180) * dist);
		lpPata2[i].x = org.x + (long)(sin(theta * i * PI / 180) * dist * mult);
		lpPata2[i].y = org.y + (long)(cos(theta * i * PI / 180) * dist * mult);
	}
}