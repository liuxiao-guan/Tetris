
#include "TetrisHead.h" //�����ļ��滻
extern gBackGroud backgroud1;
extern gBackGroud backgroud2;
#include "resource.h"
LRESULT CALLBACK PELouSi(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM IParam);
void onPaint(HDC hDC);
int WINAPI WinMain(HINSTANCE hIstance, HINSTANCE hPreIntance, LPTSTR lpCmdLine, int nCmdShow) {
	//��ʼ��������
	WNDCLASSEX wc;
	HWND hWnd;//���ھ��
	MSG nSg;//������Ϣ
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground =(HBRUSH)COLOR_WINDOW;//������ɫ
	wc.hCursor = NULL;//����ϵͳ��� LoadCursor(NULL,IDC_SIZEWE);
	wc.hIcon = LoadIcon(hIstance,MAKEINTRESOURCE(IDI_ICON2));//��С��ʱ��ʾ�Ĵ���ͼ��
	wc.hIconSm = NULL;//���Ͻǵ�ͼ��
	wc.hInstance = hIstance;
	wc.lpfnWndProc = PELouSi;//�ص�����(���ڴ���������ַ
	wc.lpszClassName = "Tetris";//���ں����������ظ�
	wc.lpszMenuName = NULL;//�˵���
	wc.style = CS_HREDRAW | CS_VREDRAW;
	//12����Ա

	//ע�ᴰ�ڶ���
	if (0 == RegisterClassEx(&wc)) {
		return 0;
	}
	//��������,���Դ����˵�,������
	hWnd = CreateWindowEx(WS_EX_TOPMOST, "Tetris", "����˹����", WS_OVERLAPPEDWINDOW, 100, 30, WIDTH,HEIGHT+45, NULL, NULL, hIstance, NULL);
	//��ʾ����
	ShowWindow(hWnd, nCmdShow);
	//��Ϣѭ��
	while (GetMessage(&nSg, NULL, 0, 0)) { //����������Ϣ
		TranslateMessage(&nSg);//������Ϣ�������ź�תΪ�ַ�
		DispatchMessage(&nSg);//�ַ���Ϣ
	}

	return 0;
}
LRESULT CALLBACK PELouSi(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM IParam) {
	PAINTSTRUCT pt;
	HDC hDC;
	switch (nMsg) {
	case WM_CREATE://���ڴ�������ֻ����һ�Σ���ʼ������
		OnCreate();
		break;
	case WM_TIMER:
		OnTimer1(hWnd);
		OnTimer2(hWnd);
		break;
	case WM_PAINT://���ڷ����仯ʱ
		hDC = BeginPaint(hWnd, &pt);//���ڿɲ�������ı�ʶ
		//�����ڵ�����
		onPaint(hDC);
		
		EndPaint(hWnd, &pt);
		break;
	case WM_KEYDOWN:
		switch (wParam) { ///wParam���ܼ�����Ϣ
		case VK_RETURN:
			OnReturn(hWnd);
			break;
		case VK_A://����
			backgroud1.OnLeft(hWnd);
			break;
		case VK_LEFT://����
			backgroud2.OnLeft(hWnd);
			break;
		case VK_D://����
			backgroud1.OnRight(hWnd);
			break;
		case VK_RIGHT://����
			backgroud2.OnRight(hWnd);
			break;
		case VK_W://��ת
			backgroud1.OnChangeSquare(hWnd);
			break;
		case VK_UP://��ת
			backgroud2.OnChangeSquare(hWnd);
			break;
		case VK_S://����
			OnDown1(hWnd);
			break;
		case VK_DOWN://����
			OnDown2(hWnd);
			break;
		}
		break;
	case WM_DESTROY:
		KillTimer(hWnd, DEF_TIMER);
		PostQuitMessage(0); //WM_CLOSE, WM_DESTROY, WM_QUIT�ڽ��е�����ʱͬʱ����
		break;
	}
	return DefWindowProc(hWnd, nMsg, wParam, IParam);
}


