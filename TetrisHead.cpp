#include "TetrisHead.h"
#include <iostream>
using namespace std;

gBackGroud backgroud1(0, 0,330,30);
gBackGroud backgroud2(480, 0,330,120);

void onPaint(HDC hDC) {

	//创建兼容性DC
	HDC HMemDC = CreateCompatibleDC(hDC);
	//创建一张纸
	HBITMAP hBitmapBack = CreateCompatibleBitmap(hDC, WIDTH, HEIGHT);
	//将纸与DC关联
	SelectObject(HMemDC, hBitmapBack);
	//画出两个矩形，作为容器或游戏背景
	Rectangle(HMemDC, 0, 0, 300, HEIGHT);
	Rectangle(HMemDC, 480, 0, WIDTH, HEIGHT);

	backgroud1.PaintSquare(HMemDC);
	backgroud2.PaintSquare(HMemDC);
	backgroud1.ShowSquare2(HMemDC, 233, 27, 182);
	backgroud2.ShowSquare2(HMemDC, 0, 128, 64);
	ShowScore(HMemDC);//显示分数
	backgroud1.ShowNextSquare(HMemDC, 233, 27, 182);
	backgroud2.ShowNextSquare(HMemDC, 0, 128, 64);

	//传递将纸上的内容传给窗口
	BitBlt(hDC, 0, 0, WIDTH, HEIGHT, HMemDC, 0, 0, SRCCOPY);
	
	DeleteObject(hBitmapBack);
	DeleteDC(HMemDC);
}

//绘图与显示操作
void OnCreate() {
	srand((unsigned int)time(NULL));
	backgroud1.CreatRandomSquare();
	backgroud1.CopySquareToBack();
	
	backgroud2.CreatRandomSquare();
	backgroud2.CopySquareToBack();
	
}
void gBackGroud::PaintSquare(HDC HMemDC) {
	int i, j = 0;
	for ( i = 0; i < 20; i++) {
		for ( j = 0; j < 10; j++) {
			if (g_arryBackGroud[i][j] == 1) {
				Rectangle(HMemDC, j * 30 + x, i * 30, j * 30 + 30 + x, i * 30 + 30);
				
			}
		}
	}
	
}
void gBackGroud::CopySquareToBack() {
	int i = 0, j = 0;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 4; j++) {
			g_arryBackGroud[i][j + 3 ] = g_arrySquare[i][j];
		}
	}
	g_nSquare = nIndex;
	if (g_nSquare == 5 || g_nSquare == 6) {
		g_nLine = 0;
		g_nList = 4;
	}
	else {
		g_nLine = 0;
		g_nList = 3;
	}
}
void gBackGroud::Change1to2() {
	int i = 0, j = 0;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 10; j++) {
			if (g_arryBackGroud[i][j] == 1) {
				g_arryBackGroud[i][j] = 2;
			}
		}
	}
}
void gBackGroud::ShowSquare2(HDC HMemDC, int red, int green, int blue) {
	int i = 0, j = 0;
	HGDIOBJ holdBrush;
	HGDIOBJ hNewBrush = CreateSolidBrush(RGB(red, green, blue));
	holdBrush = SelectObject(HMemDC, hNewBrush);
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 10; j++) {
			if (g_arryBackGroud[i][j] == 2) {
				Rectangle(HMemDC, j * 30 + x, i * 30, j * 30 + 30 + x, i * 30 + 30);
			}
		}
	}
	hNewBrush = SelectObject(HMemDC, holdBrush);
	DeleteObject(hNewBrush);
}
void ShowScore(HDC HMemDC) {
	char strScore1[10] = { 0 };
	char strScore2[10] = { 0 };
	_itoa_s(backgroud1.getg_nScore() * 10, strScore1, 10);
	_itoa_s(backgroud2.getg_nScore() * 10, strScore2, 10);
	Rectangle(HMemDC, 300, 0, 480, HEIGHT);
	TextOut(HMemDC, 330, 315, "score1", strlen("score1"));
	TextOut(HMemDC, 330, 330, strScore1, strlen(strScore1));
	TextOut(HMemDC, 330, 345, "score2", strlen("score2"));
	TextOut(HMemDC, 330, 360, strScore2, strlen(strScore2));
}
void gBackGroud::ShowNextSquare(HDC HMemDC, int red, int green, int blue) {
	HGDIOBJ holdBrush;
	HGDIOBJ hNewBrush = CreateSolidBrush(RGB(red, green, blue));
	holdBrush = SelectObject(HMemDC, hNewBrush);
	if (key1 == 1) {
		CreatRandomSquare();
	}
	int i, j = 0;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 4; j++) {
			if (g_arrySquare[i][j] == 1) {
				Rectangle(HMemDC, j * 30 + locationx, i * 30 + locationy, j * 30 + 30 + locationx, i * 30 + locationy + 30);
			}
		}
	}
}

//按键消息
void OnReturn(HWND hWnd) {
	//打开定时器
	SetTimer(hWnd, DEF_TIMER, 500, NULL);
}
void OnTimer1(HWND hWnd) {
	HDC hDC = GetDC(hWnd);//内核对象要记得释放
	//key1 = 0;
	backgroud1.setkey1_0();
	if (backgroud1.CanSquareDown() == 1) {
		backgroud1.Squaredown();
		backgroud1.getg_nLineplus();
	}
	else {
		backgroud1.Change1to2();
		backgroud1.DestroyOneLine();

		if (backgroud1.CanGameOver(hWnd) == 0) {
			//游戏结束
			if (backgroud2.getg_nScore() > backgroud1.getg_nScore()) {
				MessageBox(hWnd, "Game Over,2方获胜", "提示", MB_OK);
			}
			if (backgroud2.getg_nScore() < backgroud1.getg_nScore()) {
				MessageBox(hWnd, "Game Over,1方获胜", "提示", MB_OK);
			}
			if (backgroud2.getg_nScore() == backgroud1.getg_nScore()) {
				MessageBox(hWnd, "Game Over,双方平手", "提示", MB_OK);
			}
			KillTimer(hWnd, DEF_TIMER);
			return;
		}
		
		backgroud1.setkey1_1();
		//backgroud1.CreatRandomSquare();
		backgroud1.CopySquareToBack();
	}
	onPaint(hDC);
	ReleaseDC(hWnd, hDC);
	//显示方块
}
void OnTimer2(HWND hWnd) {
	HDC hDC = GetDC(hWnd);//内核对象要记得释放
	backgroud2.setkey1_0();
	if (backgroud2.CanSquareDown() == 1) {
		backgroud2.Squaredown();
		backgroud2.getg_nLineplus();
	}
	else {
		backgroud2.Change1to2();		
		backgroud2.DestroyOneLine();

		if (backgroud2.CanGameOver(hWnd) == 0) {
			//游戏结束提示
			//MessageBox(hWnd, "Game Over", "提示", MB_OK);
			//游戏结束
			if (backgroud2.getg_nScore() > backgroud1.getg_nScore()) {
				MessageBox(hWnd, "Game Over,2方获胜", "提示", MB_OK);
			}
			if (backgroud2.getg_nScore() < backgroud1.getg_nScore()) {
				MessageBox(hWnd, "Game Over,1方获胜", "提示", MB_OK);
			}
			if (backgroud2.getg_nScore() == backgroud1.getg_nScore()) {
				MessageBox(hWnd, "Game Over,双方平手", "提示", MB_OK);
			}
			KillTimer(hWnd, DEF_TIMER);
			return;
		}
		backgroud2.setkey1_1();
		//backgroud2.CreatRandomSquare();
		backgroud2.CopySquareToBack();

	}
	onPaint(hDC);
	ReleaseDC(hWnd, hDC);
	//显示方块
}
void OnDown1(HWND hWnd) {
	OnTimer1(hWnd);
}
void OnDown2(HWND hWnd) {
	OnTimer2(hWnd);
}
void gBackGroud::OnLeft(HWND hWnd) {
	HDC hDC = GetDC(hWnd);

	if (CanSquareLeft() == 1&& CanSquareLeft1()) {

		//方块左移
		Squareleft();
		getg_nListreduce();
		//显示方块
		onPaint(hDC);
		ReleaseDC(hWnd, hDC);
	}
}
void gBackGroud::OnRight(HWND hWnd) {
	if (CanSquareRight() == 1 && CanSquareRight1() == 1) {
		HDC hDC = GetDC(hWnd);
		//方块右移
		Squareright();
		getg_nListplus() ;
		//显示方块
		onPaint(hDC);
		ReleaseDC(hWnd, hDC);
	}

}
void gBackGroud::OnChangeSquare(HWND hWnd) {
	HDC hDC = GetDC(hWnd);
	switch (get_g_nSquare()) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		if (CanSquareChange() == 1) {
			ChangeSquare();
		}
		else {
			return;
		}
		break;
	case 5://正方块
		return;
	case 6://长条形
		ChangeLineSquare();
		break;
	}
	onPaint(hDC);
	ReleaseDC(hWnd, hDC);
}

//方块的移动与变形
void gBackGroud::Squaredown() {
	int i = 0, j = 0;
	for (i = 19; i >= 0; i--) {
		for (j = 0; j < 10; j++) {
			if (g_arryBackGroud[i][j] == 1) {
				g_arryBackGroud[i + 1][j] = 1;
				g_arryBackGroud[i][j] = 0;
			}

		}
	}
}
void gBackGroud::Squareleft() {
	int i = 0, j = 0;
	for (j = 0; j < 10; j++) {
		for (i = 0; i < 20; i++) {
			if (g_arryBackGroud[i][j] == 1) {
				g_arryBackGroud[i][j] = 0;
				g_arryBackGroud[i][j - 1] = 1;
			}
		}
	}
}
void gBackGroud::Squareright() {
	int i = 0, j = 0;
	for (j = 9; j >= 0; j--) {
		for (i = 0; i < 20; i++) {
			if (g_arryBackGroud[i][j] == 1) {
				g_arryBackGroud[i][j] = 0;
				g_arryBackGroud[i][j + 1] = 1;
			}
		}
	}
}
void gBackGroud::ChangeSquare() {
	int i = 0, j = 0;

	char arrSquare[3][3] = { 0 };
	//将背景块复制到矩阵中
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			arrSquare[i][j] = g_arryBackGroud[g_nLine + i][g_nList + j];
		}
	}
	//将矩阵又转移到背景块中
	for (i = 0; i < 3; i++) {
		int temp = 2;
		for (j = 0; j < 3; j++) {
			g_arryBackGroud[g_nLine + i][g_nList + j] = arrSquare[temp][i];
			temp--;
		}
	}

}
void gBackGroud::ChangeLineSquare() {
	if (g_arryBackGroud[g_nLine][g_nList - 1] == 1) {//横着的
		//清零
		g_arryBackGroud[g_nLine][g_nList - 1] = 0;
		g_arryBackGroud[g_nLine][g_nList + 1] = 0;
		g_arryBackGroud[g_nLine][g_nList + 2] = 0;
		if (g_arryBackGroud[g_nLine + 1][g_nList] == 2) {
			//赋值
			g_arryBackGroud[g_nLine - 1][g_nList] = 1;
			g_arryBackGroud[g_nLine - 2][g_nList] = 1;
			g_arryBackGroud[g_nLine - 3][g_nList] = 1;
			g_nLine = g_nLine + 2;
		}
		if (g_arryBackGroud[g_nLine + 2][g_nList] == 2) {
			//赋值
			g_arryBackGroud[g_nLine - 1][g_nList] = 1;
			g_arryBackGroud[g_nLine - 2][g_nList] = 1;
			g_arryBackGroud[g_nLine + 1][g_nList] = 1;
			g_nLine = g_nLine + 1;
		}
		//以下是考虑一开始出现的旋转
		if (g_nLine == 0) {
			//	//赋值
			g_arryBackGroud[g_nLine + 1][g_nList] = 1;
			g_arryBackGroud[g_nLine + 2][g_nList] = 1;
			g_arryBackGroud[g_nLine + 3][g_nList] = 1;
			//标记改变
			g_nLine = g_nLine + 1;
		}

		else {
			g_arryBackGroud[g_nLine + 1][g_nList] = 1;
			g_arryBackGroud[g_nLine + 2][g_nList] = 1;
			g_arryBackGroud[g_nLine - 1][g_nList] = 1;
		}
	}
	else {//竖着
		//清零
		g_arryBackGroud[g_nLine - 1][g_nList] = 0;
		g_arryBackGroud[g_nLine + 1][g_nList] = 0;
		g_arryBackGroud[g_nLine + 2][g_nList] = 0;
		//if ( || g_arryBackGroud[g_nLine][g_nList - 2] == 2) {

		if (g_arryBackGroud[g_nLine][g_nList + 1] == 2 || g_nList == 9) {
			//判断是否有空间进行变换从竖到横
			if (g_arryBackGroud[g_nLine][g_nList - 3] == 2 || g_arryBackGroud[g_nLine][g_nList - 2] == 2 || g_arryBackGroud[g_nLine][g_nList - 1] == 2 || g_nList - 2 <= 0) {
				g_arryBackGroud[g_nLine - 1][g_nList] = 1;
				g_arryBackGroud[g_nLine + 1][g_nList] = 1;
				g_arryBackGroud[g_nLine + 2][g_nList] = 1;
				return;
			}
			//赋值
			g_arryBackGroud[g_nLine][g_nList - 1] = 1;
			g_arryBackGroud[g_nLine][g_nList - 2] = 1;
			g_arryBackGroud[g_nLine][g_nList - 3] = 1;
			//标记改变
			g_nList = g_nList - 2;
		}
		else if (g_arryBackGroud[g_nLine][g_nList + 2] == 2 || g_nList == 8) {
			if (g_arryBackGroud[g_nLine][g_nList - 2] == 2 || g_arryBackGroud[g_nLine][g_nList - 1] == 2 || g_nList - 1 <= 0) {
				g_arryBackGroud[g_nLine - 1][g_nList] = 1;
				g_arryBackGroud[g_nLine + 1][g_nList] = 1;
				g_arryBackGroud[g_nLine + 2][g_nList] = 1;
				return;
			}
			//赋值
			g_arryBackGroud[g_nLine][g_nList + 1] = 1;
			g_arryBackGroud[g_nLine][g_nList - 1] = 1;
			g_arryBackGroud[g_nLine][g_nList - 2] = 1;
			//标记改变
			g_nList = g_nList - 1;
		}
		else if (g_arryBackGroud[g_nLine][g_nList - 1] == 2 || 0 == g_nList) {
			if (g_arryBackGroud[g_nLine][g_nList + 3] == 2 || g_arryBackGroud[g_nLine][g_nList + 2] == 2 || g_arryBackGroud[g_nLine][g_nList + 1] == 2 || g_nList + 2 >= 9) {
				g_arryBackGroud[g_nLine - 1][g_nList] = 1;
				g_arryBackGroud[g_nLine + 1][g_nList] = 1;
				g_arryBackGroud[g_nLine + 2][g_nList] = 1;
				return;
			}
			//赋值
			g_arryBackGroud[g_nLine][g_nList + 1] = 1;
			g_arryBackGroud[g_nLine][g_nList + 2] = 1;
			g_arryBackGroud[g_nLine][g_nList + 3] = 1;
			//标记改变
			g_nList = g_nList + 1;
		}

		else {
			g_arryBackGroud[g_nLine][g_nList - 1] = 1;
			g_arryBackGroud[g_nLine][g_nList + 1] = 1;
			g_arryBackGroud[g_nLine][g_nList + 2] = 1;
		}

	}
	return;
}

//判断方块的移动与变形
int gBackGroud::CanSquareDown() {
	int i = 0, j = 0;
	for (j = 0; j < 10; j++) {
		if (g_arryBackGroud[19][j] == 1) {
			return 0;//遇到return 即结束函数，非程序
		}
	}
	for (i = 19; i >= 0; i--) {
		for (j = 0; j < 10; j++) {
			if (g_arryBackGroud[i][j] == 1 && g_arryBackGroud[i + 1][j] == 2)
				return 0;
		}
	}
	return 1;
}
int gBackGroud::CanSquareLeft() {
	int i = 0;
	for (i = 0; i < 20; i++) {
		if (g_arryBackGroud[i][0] == 1) {
			return 0;
		}
	}
	return 1;
}
int gBackGroud::CanSquareLeft1() {
	int i = 0, j = 0;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 10; j++) {
			if (g_arryBackGroud[i][j] == 1) {
				if (g_arryBackGroud[i][j - 1] == 2) {
					return 0;
				}
				
			}
		}
	}
	return 1;
}
int gBackGroud::CanSquareRight() {
		int i = 0;
		for (i = 0; i < 20; i++) {
			if (g_arryBackGroud[i][9] == 1) {
				return 0;
			}
		}
		return 1;
}
int gBackGroud::CanSquareRight1() {
	int i = 0, j = 0;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 10; j++) {
			if (g_arryBackGroud[i][j] == 1) {
				if (g_arryBackGroud[i][j + 1] == 2) {
					return 0;
				}

			}
		}
	}
	return 1;
}
int gBackGroud::CanSquareChange() {
	int i = 0, j = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (g_arryBackGroud[g_nLine + i][g_nList + j] == 2) {
				return 0;
			}
		}
	}
	//if (g_nList < 0 || g_nList + 2>9) {
	//	return 0;
	//}
	if (g_nList < 0) {
		g_nList = 0;
	}
	else if(g_nList + 2 > 9) {
		g_nList = 7;
	}
	return 1;
}

//其余操作

int gBackGroud::CreatRandomSquare() {
	//unsigned int nIndex = 0;
	nIndex = rand() % 7;
	//srand((unsigned int)time(NULL));

	switch (nIndex) {
	case 0:
		g_arrySquare[0][0] = 1; g_arrySquare[0][1] = 1; g_arrySquare[0][2] = 0; g_arrySquare[0][3] = 0;
		g_arrySquare[1][0] = 0; g_arrySquare[1][1] = 1; g_arrySquare[1][2] = 1; g_arrySquare[1][3] = 0;

		break;
	case 1:
		g_arrySquare[0][0] = 0; g_arrySquare[0][1] = 1; g_arrySquare[0][2] = 1; g_arrySquare[0][3] = 0;
		g_arrySquare[1][0] = 1; g_arrySquare[1][1] = 1; g_arrySquare[1][2] = 0; g_arrySquare[1][3] = 0;

		break;
	case 2:
		g_arrySquare[0][0] = 1; g_arrySquare[0][1] = 0; g_arrySquare[0][2] = 0; g_arrySquare[0][3] = 0;
		g_arrySquare[1][0] = 1; g_arrySquare[1][1] = 1; g_arrySquare[1][2] = 1; g_arrySquare[1][3] = 0;

		break;
	case 3:
		g_arrySquare[0][0] = 0; g_arrySquare[0][1] = 0; g_arrySquare[0][2] = 1; g_arrySquare[0][3] = 0;
		g_arrySquare[1][0] = 1; g_arrySquare[1][1] = 1; g_arrySquare[1][2] = 1; g_arrySquare[1][3] = 0;

		break;
	case 4:
		g_arrySquare[0][0] = 0; g_arrySquare[0][1] = 1; g_arrySquare[0][2] = 0; g_arrySquare[0][3] = 0;
		g_arrySquare[1][0] = 1; g_arrySquare[1][1] = 1; g_arrySquare[1][2] = 1; g_arrySquare[1][3] = 0;
		break;
	case 5://正方形
		g_arrySquare[0][0] = 0; g_arrySquare[0][1] = 1; g_arrySquare[0][2] = 1; g_arrySquare[0][3] = 0;
		g_arrySquare[1][0] = 0; g_arrySquare[1][1] = 1; g_arrySquare[1][2] = 1; g_arrySquare[1][3] = 0;
		break;
	case 6://长条
		g_arrySquare[0][0] = 1; g_arrySquare[0][1] = 1; g_arrySquare[0][2] = 1; g_arrySquare[0][3] = 1;
		g_arrySquare[1][0] = 0; g_arrySquare[1][1] = 0; g_arrySquare[1][2] = 0; g_arrySquare[1][3] = 0;
		break;
	}
	return nIndex;
}
void gBackGroud:: DestroyOneLine() {
	int i = 0, j = 0;
	int count = 0;
	int nTemp = 0;
	for (i = 19; i >= 0; i--) {
		for (j = 0; j < 10; j++) {
			count += g_arryBackGroud[i][j];
		}
		if (count == 20) {
			//消除一行
			for (nTemp = i - 1; nTemp >= 0; nTemp--) {
				for (j = 0; j < 10; j++) {
					g_arryBackGroud[nTemp+1][j] = g_arryBackGroud[nTemp][j];
				}
			}
			g_nScore++;
			//i = 20;//可消除多行，但效率有点低
			i=i+1;
		}
		count = 0;
	}
}
int gBackGroud::CanGameOver(HWND hWnd) {
	int j = 0;
	for (j = 0; j < 10; j++) {
		if ((g_arryBackGroud[0][j]) == 2) {
			//游戏结束提示
			//MessageBox(hWnd, "Game Over", "提示", MB_OK);
			return 0;
		}
	}
	return 1;
}
