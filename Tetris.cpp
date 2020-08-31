
#include "TetrisHead.h" //纯粹文件替换
extern gBackGroud backgroud1;
extern gBackGroud backgroud2;
#include "resource.h"
LRESULT CALLBACK PELouSi(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM IParam);
void onPaint(HDC hDC);
int WINAPI WinMain(HINSTANCE hIstance, HINSTANCE hPreIntance, LPTSTR lpCmdLine, int nCmdShow) {
	//初始化窗口类
	WNDCLASSEX wc;
	HWND hWnd;//窗口句柄
	MSG nSg;//窗口消息
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground =(HBRUSH)COLOR_WINDOW;//背景颜色
	wc.hCursor = NULL;//加载系统光标 LoadCursor(NULL,IDC_SIZEWE);
	wc.hIcon = LoadIcon(hIstance,MAKEINTRESOURCE(IDI_ICON2));//最小化时显示的窗口图标
	wc.hIconSm = NULL;//左上角的图标
	wc.hInstance = hIstance;
	wc.lpfnWndProc = PELouSi;//回调函数(窗口处理函数）地址
	wc.lpszClassName = "Tetris";//窗口函数，不能重复
	wc.lpszMenuName = NULL;//菜单名
	wc.style = CS_HREDRAW | CS_VREDRAW;
	//12个成员

	//注册窗口对象
	if (0 == RegisterClassEx(&wc)) {
		return 0;
	}
	//创建窗口,可以创建菜单,副窗口
	hWnd = CreateWindowEx(WS_EX_TOPMOST, "Tetris", "俄罗斯方块", WS_OVERLAPPEDWINDOW, 100, 30, WIDTH,HEIGHT+45, NULL, NULL, hIstance, NULL);
	//显示窗口
	ShowWindow(hWnd, nCmdShow);
	//消息循环
	while (GetMessage(&nSg, NULL, 0, 0)) { //持续接收消息
		TranslateMessage(&nSg);//翻译消息，将电信号转为字符
		DispatchMessage(&nSg);//分发信息
	}

	return 0;
}
LRESULT CALLBACK PELouSi(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM IParam) {
	PAINTSTRUCT pt;
	HDC hDC;
	switch (nMsg) {
	case WM_CREATE://窗口创建初期只产生一次，初始化数据
		OnCreate();
		break;
	case WM_TIMER:
		OnTimer1(hWnd);
		OnTimer2(hWnd);
		break;
	case WM_PAINT://窗口发生变化时
		hDC = BeginPaint(hWnd, &pt);//窗口可操作区域的标识
		//画窗口的内容
		onPaint(hDC);
		
		EndPaint(hWnd, &pt);
		break;
	case WM_KEYDOWN:
		switch (wParam) { ///wParam接受键盘消息
		case VK_RETURN:
			OnReturn(hWnd);
			break;
		case VK_A://左移
			backgroud1.OnLeft(hWnd);
			break;
		case VK_LEFT://左移
			backgroud2.OnLeft(hWnd);
			break;
		case VK_D://右移
			backgroud1.OnRight(hWnd);
			break;
		case VK_RIGHT://右移
			backgroud2.OnRight(hWnd);
			break;
		case VK_W://旋转
			backgroud1.OnChangeSquare(hWnd);
			break;
		case VK_UP://旋转
			backgroud2.OnChangeSquare(hWnd);
			break;
		case VK_S://下移
			OnDown1(hWnd);
			break;
		case VK_DOWN://下移
			OnDown2(hWnd);
			break;
		}
		break;
	case WM_DESTROY:
		KillTimer(hWnd, DEF_TIMER);
		PostQuitMessage(0); //WM_CLOSE, WM_DESTROY, WM_QUIT在进行点叉操作时同时进行
		break;
	}
	return DefWindowProc(hWnd, nMsg, wParam, IParam);
}


