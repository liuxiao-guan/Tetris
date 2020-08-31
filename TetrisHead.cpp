#include "TetrisHead.h"
#include <iostream>
using namespace std;

gBackGroud backgroud1(0, 0,330,30);
gBackGroud backgroud2(480, 0,330,120);

void onPaint(HDC hDC) {

	//����������DC
	HDC HMemDC = CreateCompatibleDC(hDC);
	//����һ��ֽ
	HBITMAP hBitmapBack = CreateCompatibleBitmap(hDC, WIDTH, HEIGHT);
	//��ֽ��DC����
	SelectObject(HMemDC, hBitmapBack);
	//�����������Σ���Ϊ��������Ϸ����
	Rectangle(HMemDC, 0, 0, 300, HEIGHT);
	Rectangle(HMemDC, 480, 0, WIDTH, HEIGHT);

	backgroud1.PaintSquare(HMemDC);
	backgroud2.PaintSquare(HMemDC);
	backgroud1.ShowSquare2(HMemDC, 233, 27, 182);
	backgroud2.ShowSquare2(HMemDC, 0, 128, 64);
	ShowScore(HMemDC);//��ʾ����
	backgroud1.ShowNextSquare(HMemDC, 233, 27, 182);
	backgroud2.ShowNextSquare(HMemDC, 0, 128, 64);

	//���ݽ�ֽ�ϵ����ݴ�������
	BitBlt(hDC, 0, 0, WIDTH, HEIGHT, HMemDC, 0, 0, SRCCOPY);
	
	DeleteObject(hBitmapBack);
	DeleteDC(HMemDC);
}

//��ͼ����ʾ����
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

//������Ϣ
void OnReturn(HWND hWnd) {
	//�򿪶�ʱ��
	SetTimer(hWnd, DEF_TIMER, 500, NULL);
}
void OnTimer1(HWND hWnd) {
	HDC hDC = GetDC(hWnd);//�ں˶���Ҫ�ǵ��ͷ�
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
			//��Ϸ����
			if (backgroud2.getg_nScore() > backgroud1.getg_nScore()) {
				MessageBox(hWnd, "Game Over,2����ʤ", "��ʾ", MB_OK);
			}
			if (backgroud2.getg_nScore() < backgroud1.getg_nScore()) {
				MessageBox(hWnd, "Game Over,1����ʤ", "��ʾ", MB_OK);
			}
			if (backgroud2.getg_nScore() == backgroud1.getg_nScore()) {
				MessageBox(hWnd, "Game Over,˫��ƽ��", "��ʾ", MB_OK);
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
	//��ʾ����
}
void OnTimer2(HWND hWnd) {
	HDC hDC = GetDC(hWnd);//�ں˶���Ҫ�ǵ��ͷ�
	backgroud2.setkey1_0();
	if (backgroud2.CanSquareDown() == 1) {
		backgroud2.Squaredown();
		backgroud2.getg_nLineplus();
	}
	else {
		backgroud2.Change1to2();		
		backgroud2.DestroyOneLine();

		if (backgroud2.CanGameOver(hWnd) == 0) {
			//��Ϸ������ʾ
			//MessageBox(hWnd, "Game Over", "��ʾ", MB_OK);
			//��Ϸ����
			if (backgroud2.getg_nScore() > backgroud1.getg_nScore()) {
				MessageBox(hWnd, "Game Over,2����ʤ", "��ʾ", MB_OK);
			}
			if (backgroud2.getg_nScore() < backgroud1.getg_nScore()) {
				MessageBox(hWnd, "Game Over,1����ʤ", "��ʾ", MB_OK);
			}
			if (backgroud2.getg_nScore() == backgroud1.getg_nScore()) {
				MessageBox(hWnd, "Game Over,˫��ƽ��", "��ʾ", MB_OK);
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
	//��ʾ����
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

		//��������
		Squareleft();
		getg_nListreduce();
		//��ʾ����
		onPaint(hDC);
		ReleaseDC(hWnd, hDC);
	}
}
void gBackGroud::OnRight(HWND hWnd) {
	if (CanSquareRight() == 1 && CanSquareRight1() == 1) {
		HDC hDC = GetDC(hWnd);
		//��������
		Squareright();
		getg_nListplus() ;
		//��ʾ����
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
	case 5://������
		return;
	case 6://������
		ChangeLineSquare();
		break;
	}
	onPaint(hDC);
	ReleaseDC(hWnd, hDC);
}

//������ƶ������
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
	//�������鸴�Ƶ�������
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			arrSquare[i][j] = g_arryBackGroud[g_nLine + i][g_nList + j];
		}
	}
	//��������ת�Ƶ���������
	for (i = 0; i < 3; i++) {
		int temp = 2;
		for (j = 0; j < 3; j++) {
			g_arryBackGroud[g_nLine + i][g_nList + j] = arrSquare[temp][i];
			temp--;
		}
	}

}
void gBackGroud::ChangeLineSquare() {
	if (g_arryBackGroud[g_nLine][g_nList - 1] == 1) {//���ŵ�
		//����
		g_arryBackGroud[g_nLine][g_nList - 1] = 0;
		g_arryBackGroud[g_nLine][g_nList + 1] = 0;
		g_arryBackGroud[g_nLine][g_nList + 2] = 0;
		if (g_arryBackGroud[g_nLine + 1][g_nList] == 2) {
			//��ֵ
			g_arryBackGroud[g_nLine - 1][g_nList] = 1;
			g_arryBackGroud[g_nLine - 2][g_nList] = 1;
			g_arryBackGroud[g_nLine - 3][g_nList] = 1;
			g_nLine = g_nLine + 2;
		}
		if (g_arryBackGroud[g_nLine + 2][g_nList] == 2) {
			//��ֵ
			g_arryBackGroud[g_nLine - 1][g_nList] = 1;
			g_arryBackGroud[g_nLine - 2][g_nList] = 1;
			g_arryBackGroud[g_nLine + 1][g_nList] = 1;
			g_nLine = g_nLine + 1;
		}
		//�����ǿ���һ��ʼ���ֵ���ת
		if (g_nLine == 0) {
			//	//��ֵ
			g_arryBackGroud[g_nLine + 1][g_nList] = 1;
			g_arryBackGroud[g_nLine + 2][g_nList] = 1;
			g_arryBackGroud[g_nLine + 3][g_nList] = 1;
			//��Ǹı�
			g_nLine = g_nLine + 1;
		}

		else {
			g_arryBackGroud[g_nLine + 1][g_nList] = 1;
			g_arryBackGroud[g_nLine + 2][g_nList] = 1;
			g_arryBackGroud[g_nLine - 1][g_nList] = 1;
		}
	}
	else {//����
		//����
		g_arryBackGroud[g_nLine - 1][g_nList] = 0;
		g_arryBackGroud[g_nLine + 1][g_nList] = 0;
		g_arryBackGroud[g_nLine + 2][g_nList] = 0;
		//if ( || g_arryBackGroud[g_nLine][g_nList - 2] == 2) {

		if (g_arryBackGroud[g_nLine][g_nList + 1] == 2 || g_nList == 9) {
			//�ж��Ƿ��пռ���б任��������
			if (g_arryBackGroud[g_nLine][g_nList - 3] == 2 || g_arryBackGroud[g_nLine][g_nList - 2] == 2 || g_arryBackGroud[g_nLine][g_nList - 1] == 2 || g_nList - 2 <= 0) {
				g_arryBackGroud[g_nLine - 1][g_nList] = 1;
				g_arryBackGroud[g_nLine + 1][g_nList] = 1;
				g_arryBackGroud[g_nLine + 2][g_nList] = 1;
				return;
			}
			//��ֵ
			g_arryBackGroud[g_nLine][g_nList - 1] = 1;
			g_arryBackGroud[g_nLine][g_nList - 2] = 1;
			g_arryBackGroud[g_nLine][g_nList - 3] = 1;
			//��Ǹı�
			g_nList = g_nList - 2;
		}
		else if (g_arryBackGroud[g_nLine][g_nList + 2] == 2 || g_nList == 8) {
			if (g_arryBackGroud[g_nLine][g_nList - 2] == 2 || g_arryBackGroud[g_nLine][g_nList - 1] == 2 || g_nList - 1 <= 0) {
				g_arryBackGroud[g_nLine - 1][g_nList] = 1;
				g_arryBackGroud[g_nLine + 1][g_nList] = 1;
				g_arryBackGroud[g_nLine + 2][g_nList] = 1;
				return;
			}
			//��ֵ
			g_arryBackGroud[g_nLine][g_nList + 1] = 1;
			g_arryBackGroud[g_nLine][g_nList - 1] = 1;
			g_arryBackGroud[g_nLine][g_nList - 2] = 1;
			//��Ǹı�
			g_nList = g_nList - 1;
		}
		else if (g_arryBackGroud[g_nLine][g_nList - 1] == 2 || 0 == g_nList) {
			if (g_arryBackGroud[g_nLine][g_nList + 3] == 2 || g_arryBackGroud[g_nLine][g_nList + 2] == 2 || g_arryBackGroud[g_nLine][g_nList + 1] == 2 || g_nList + 2 >= 9) {
				g_arryBackGroud[g_nLine - 1][g_nList] = 1;
				g_arryBackGroud[g_nLine + 1][g_nList] = 1;
				g_arryBackGroud[g_nLine + 2][g_nList] = 1;
				return;
			}
			//��ֵ
			g_arryBackGroud[g_nLine][g_nList + 1] = 1;
			g_arryBackGroud[g_nLine][g_nList + 2] = 1;
			g_arryBackGroud[g_nLine][g_nList + 3] = 1;
			//��Ǹı�
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

//�жϷ�����ƶ������
int gBackGroud::CanSquareDown() {
	int i = 0, j = 0;
	for (j = 0; j < 10; j++) {
		if (g_arryBackGroud[19][j] == 1) {
			return 0;//����return �������������ǳ���
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

//�������

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
	case 5://������
		g_arrySquare[0][0] = 0; g_arrySquare[0][1] = 1; g_arrySquare[0][2] = 1; g_arrySquare[0][3] = 0;
		g_arrySquare[1][0] = 0; g_arrySquare[1][1] = 1; g_arrySquare[1][2] = 1; g_arrySquare[1][3] = 0;
		break;
	case 6://����
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
			//����һ��
			for (nTemp = i - 1; nTemp >= 0; nTemp--) {
				for (j = 0; j < 10; j++) {
					g_arryBackGroud[nTemp+1][j] = g_arryBackGroud[nTemp][j];
				}
			}
			g_nScore++;
			//i = 20;//���������У���Ч���е��
			i=i+1;
		}
		count = 0;
	}
}
int gBackGroud::CanGameOver(HWND hWnd) {
	int j = 0;
	for (j = 0; j < 10; j++) {
		if ((g_arryBackGroud[0][j]) == 2) {
			//��Ϸ������ʾ
			//MessageBox(hWnd, "Game Over", "��ʾ", MB_OK);
			return 0;
		}
	}
	return 1;
}
