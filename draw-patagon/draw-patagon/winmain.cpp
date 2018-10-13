#include <windows.h>
#include <math.h>
#define PI 3.14159265358979

BOOLEAN InitWindow(HINSTANCE hInstance, int nCmdShow);									//初始化窗口函数声明
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);		//消息处理函数声明
void calpata(LPPOINT lpPata, LPPOINT lpPata2, POINT org);								//计算大小五边形顶点坐标函数声明

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;										//定义消息变量

	InitWindow(hInstance, nCmdShow);				//初始化窗口
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);						//消息循环
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

BOOLEAN InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;														//定义窗口句柄
	TCHAR szWindowClass[] = L"PATAGON";								//定义窗口类名称
	TCHAR szTitle[] = L"等边五边形";								//定义窗口标题
	WNDCLASS WndClass;												//定义窗口类
	WndClass.cbClsExtra = 0;										//无窗口类扩展
	WndClass.cbWndExtra = 0;										//无窗口实例扩展
	WndClass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));	//背景为白色
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//窗口采用箭头光标
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//采用缺省图标
	WndClass.hInstance = hInstance;									//当前应用程序句柄
	WndClass.lpfnWndProc = WndProc;									//窗口处理函数
	WndClass.lpszClassName = szWindowClass;							//窗口类名称
	WndClass.lpszMenuName = NULL;									//无窗口菜单
	WndClass.style = 0;												//窗口类型为缺省类型

	if (!RegisterClass(&WndClass))		//注册窗口
		return FALSE;
	hWnd = CreateWindow(
		szWindowClass,					//窗口类名
		szTitle,						//标题名
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,					//窗口左上角坐标
		0,
		CW_USEDEFAULT,					//采用缺省的宽度和高度
		0,
		NULL,							//无父窗口
		NULL,							//无主菜单
		hInstance,						//当前实例句柄
		NULL);							//不要此参数
	if (!hWnd)
		return FALSE;
	ShowWindow(hWnd, nCmdShow);			//显示窗口
	UpdateWindow(hWnd);					//更新并绘制用户区
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)			//消息处理函数
{
	HDC hDC;								//定义设备环境句柄
	HBRUSH hBrush;							//定义画刷句柄
	HPEN hPen;								//定义画笔句柄
	PAINTSTRUCT PtStr;						//定义包含绘图信息的结构体变量
	RECT clientRect;						//定义客户区矩形结构体变量
	POINT lpPata[5];						//大五边形的顶点坐标
	POINT lpPata2[5];						//小五边形的顶点坐标
	POINT org;								//定义原点结构体变量
	POINT lptrg[3];							//定义三角形的三个端点
	switch (message)
	{
	case WM_PAINT:											//处理绘图消息
		hDC = BeginPaint(hWnd, &PtStr);						//获得设备环境指针
		GetClientRect(hWnd, &clientRect);					//获取客户区矩形
		//计算原点坐标
		org.x = (clientRect.left + clientRect.right) / 2;
		org.y = (clientRect.top + clientRect.bottom) / 2;
		calpata(lpPata, lpPata2, org);										//计算五边形端点

		//用不同颜色的画刷填充各个区域
		hPen = (HPEN)GetStockObject(NULL_PEN);				//定义虚画笔							
		hBrush = CreateSolidBrush(RGB(120, 120, 120));		//定义画刷
		SelectObject(hDC, hPen);							//将画笔选入设备环境
		SelectObject(hDC, hBrush);							//将画刷选入设备环境
		Polygon(hDC, lpPata2, 5);							//填充小五边形
		DeleteObject(hBrush);								//删除画刷
		hBrush = CreateSolidBrush(RGB(45, 90, 90));
		SelectObject(hDC, hBrush);
		lptrg[0] = lpPata[0]; lptrg[1] = lpPata2[2]; lptrg[2] = lpPata2[3];
		Polygon(hDC, lptrg, 3);								//填充三角形
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
		DeleteObject(hPen);									//删除画笔

		//用不同颜色的画笔连接不相邻的各点
		hPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
		SelectObject(hDC, hPen);
		MoveToEx(hDC, lpPata[0].x, lpPata[0].y, NULL);		//移动至第一个点
		LineTo(hDC, lpPata[2].x, lpPata[2].y);				//向第三个点画一条直线
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

		//绘制等边五边形
		hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));		//定义红色画笔
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);		//定义虚画刷
		SelectObject(hDC, hPen);							//将画笔选入设备环境
		SelectObject(hDC, hBrush);							//将画刷选入设备环境
		Polygon(hDC, lpPata, 5);							//绘制正五边形
		DeleteObject(hPen);									//删除画笔
		DeleteObject(hBrush);								//删除画刷

		EndPaint(hWnd, &PtStr);								//删除设备环境句柄
		break;
	case WM_DESTROY:										//关闭窗口
		PostQuitMessage(0);
		break;
	default:												//默认消息处理
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void calpata(LPPOINT lpPata, LPPOINT lpPata2, POINT org)
{
	int i;
	double dist = 180.0;						//五边形中心到顶点的距离
	double theta = 72.0;						//旋转角
	double mult = 1 - 0.5 / sin(54 * PI / 180);	//小五边形乘数因子
	for (i = 0; i < 5; i++)
	{
		lpPata[i].x = org.x + (long)(sin(theta * i * PI / 180) * dist);
		lpPata[i].y = org.y - (long)(cos(theta * i * PI / 180) * dist);
		lpPata2[i].x = org.x + (long)(sin(theta * i * PI / 180) * dist * mult);
		lpPata2[i].y = org.y + (long)(cos(theta * i * PI / 180) * dist * mult);
	}
}