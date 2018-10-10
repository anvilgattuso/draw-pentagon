#include <windows.h>

long WINAPI WndProc(HWND hWnd, UINT iMessage, UINT wParam, LONG lParam);			//��Ϣ����������

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG Message;										//������Ϣ����
	HWND hWnd;										//���崰�ھ��
	WNDCLASS WndClass;									//���崰����
	WndClass.cbClsExtra = 0;								//�޴�������չ
	WndClass.cbWndExtra = 0;								//�޴���ʵ����չ
	WndClass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));	//����Ϊ��ɫ
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);			//���ڲ��ü�ͷ���
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			//����ȱʡͼ��
	WndClass.hInstance = hInstance;						//��ǰӦ�ó�����
	WndClass.lpfnWndProc = WndProc;						//���ڴ�����
	WndClass.lpszClassName = L"SIN";						//����������
	WndClass.lpszMenuName = NULL;							//�޴��ڲ˵�
	WndClass.style = 0;									//��������Ϊȱʡ����

	if (!RegisterClass(&WndClass))						//ע�ᴰ��
	{
		MessageBeep(0);
		return FALSE;
	}

	hWnd = CreateWindow(L"PATAGON",							//��������
		L"�ȱ������",			//������
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,						//�������Ͻ�����
		0,
		CW_USEDEFAULT,						//����ȱʡ�Ŀ�Ⱥ͸߶�
		0,
		NULL,							//�޸�����
		NULL,							//�����˵�
		hInstance,						//��ǰʵ�����
		NULL);							//��Ҫ�˲���
	ShowWindow(hWnd, nCmdShow);							//��ʾ����
	UpdateWindow(hWnd);								//���²������û���

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);						//��Ϣѭ��
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

long WINAPI WndProc(HWND hWnd, UINT iMessage, UINT wParam, LONG lParam)			//��Ϣ������
{
	HDC hDC;											//�����豸�������
	HBRUSH hBrush;										//���廭ˢ���
	HPEN hPen;											//���廭�ʾ��
	PAINTSTRUCT PtStr;									//���������ͼ��Ϣ�Ľṹ�����
	switch (iMessage)
	{
	case WM_PAINT:										//�����ͼ��Ϣ
		hDC = BeginPaint(hWnd, &PtStr);						//����豸����ָ��
		
		EndPaint(hWnd, &PtStr);							//ɾ���豸�������
		break;
	case WM_DESTROY:									//�رմ���
		PostQuitMessage(0);
		break;
	default:
		return(DefWindowProc(hWnd, iMessage, wParam, lParam));
	}
	return 0;
}