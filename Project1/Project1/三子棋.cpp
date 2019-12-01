//三子棋游戏
#define _CRT_SECURE_NO_WARNINGS
#define MAX_ROW 3
#define MAX_COL 3

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 游戏开始菜单
int Menu()
{
	printf("--------------\n");
	printf("欢迎来到三子棋游戏(输入1开始,输入0结束)\n");
	printf("1.开始游戏\n");
	printf("0.结束游戏\n");
	printf("--------------\n");
	printf("请输入你的选择:");
	int choice;
	scanf("%d", &choice);
	return choice;
}

// 初始化棋盘
void Init(char chessBoard[MAX_ROW][MAX_COL])
{
	for (int row = 0; row < MAX_ROW; row++) {
		for (int col = 0; col < MAX_COL; col++) {
			chessBoard[row][col] = ' ';
		}
	}
}

// 打印棋盘
void printChess(char chessBoard[MAX_ROW][MAX_COL])
{
	for (int row = 0; row < MAX_ROW; row++) {
		for (int col = 0; col < MAX_COL; col++) {
			printf("%c  ", chessBoard[row][col]);
		}
		putchar('\n');
	}
}

// 玩家落子(以X表示)
void PlayerMove(char chessBoard[MAX_ROW][MAX_COL])
{
	int row_p, col_p;
	while (1) {
		printf("玩家落子\n");
		printf("请输入落子的坐标:(输入0-2的数, 例如2 1)");
		scanf("%d %d", &row_p, &col_p);
		if (row_p < 0 || row_p > 2 || col_p < 0 || col_p > 2) {
			printf("你的输入有误,请重新输入");
			continue;
		}
		if (chessBoard[row_p][row_p] != ' ')
		{
			printf("这个位置已经有子了,请重新输入\n");
			continue;
		}
		chessBoard[row_p][col_p] = 'X';
		break;
	}
}

// 电脑落子(以O表示)
void ComputerMove(char chessBoard[MAX_ROW][MAX_COL])
{
	while (1) {
		int row_c = rand() % 3;
		int col_c = rand() % 3;
		if (chessBoard[row_c][col_c] != ' ') {
			continue;
		}
		chessBoard[row_c][col_c] = 'O';
		break;
	}	
}

// 判断是否无子可放, 是的话返回1, 不是的话返回0
int IsFull(char chessBoard[MAX_ROW][MAX_COL])
{
	for (int row = 0; row < MAX_ROW; row++) {
		for (int col = 0; col < MAX_COL; col++) {
			if (chessBoard[row][col] != ' ')
				return 0;
		}
	}
	return 1;
}

// 判断游戏是否结束
// 返回X 表示玩家赢;	返回O 表示电脑赢;	返回Q 表示平局
char IsGameEnd(char chessBoard[MAX_ROW][MAX_COL])
{
	// 判断行是否相同并且不为' '
	for (int row = 0; row < MAX_ROW; row++) {
		if (chessBoard[row][0] == chessBoard[row][1]
			&& chessBoard[row][0] == chessBoard[row][2]
			&& chessBoard[row][0] != ' ') {
			return chessBoard[row][0];
		}
	}
	// 判断列是否相同并且不为' '
	for (int col = 0; col < MAX_COL; col++) {
		if (chessBoard[0][col] == chessBoard[1][col]
			&& chessBoard[0][col] == chessBoard[2][col]
			&& chessBoard[0][col] != ' ') {
			return chessBoard[0][col];
		}
	}
	//判断对角线是否相同并且不为' '
	if (chessBoard[0][0] == chessBoard[1][1]
		&& chessBoard[0][0] == chessBoard[2][2]
		&& chessBoard[0][0] != ' ') {
		return chessBoard[0][0];
	}
	if (chessBoard[2][0] == chessBoard[1][1]
		&& chessBoard[2][0] == chessBoard[2][0]
		&& chessBoard[2][0] != ' ') {
		return chessBoard[2][0];
	}
	//判断是否无子可放
	if (IsFull(chessBoard)) {
		return 'Q';
	}
	return 0;
}

// 开始游戏
void Game()
{
	//1.创建棋盘并初始化棋盘(每个位置都设为空格)
	char chessBoard[MAX_ROW][MAX_COL];
	Init(chessBoard);
	while (1) {
		//2.打印棋盘(第一次打印的是空白棋盘)
		printChess(chessBoard);
		//3.玩家落子(通过输入坐标的方式制定坐标)
		PlayerMove(chessBoard);
		//4.判断游戏是否结束
		if (IsGameEnd(chessBoard) == 'X') {
			printf("你真的是太厉害了呀!\n");
			break;
		}
		else if (IsGameEnd(chessBoard) == 'O') {
			printf("你怎么连电脑都下不赢呢!\n");
			break;
		}
		else if (IsGameEnd(chessBoard) == 'Q') {
			printf("你们不相上下呀!\n");
			break;
		}
		//5.电脑落子(随机落子)
		ComputerMove(chessBoard);
		//6.判断游戏是否结束
		if (IsGameEnd(chessBoard) == 'X') {
			printf("你真的是太厉害了呀!\n");
			break;
		}
		else if (IsGameEnd(chessBoard) == 'O') {
			printf("你怎么连电脑都下不赢呢!\n");
			break;
		}
		else if (IsGameEnd(chessBoard) == 'Q') {
			printf("你们不相上下呀!\n");
			break;
		}
	}
}

int main()
{
	srand(unsigned int(time(0)));	//设置随机种子
	while (1) {
		int choice = Menu();
		if (choice == 1) {
			Game();
		}
		else if (choice == 0) {
			printf("goodbye,i will miss you!");
			break;
		}
		else {
			printf("你的输入有误\n");
		}
	}
	return 0;
}