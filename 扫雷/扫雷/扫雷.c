// 扫雷游戏

#define _CRT_SECURE_NO_WARNINGS
#define MAX_ROW 9
#define MAX_COL 9
#define MAX_MINE_COUNT 10

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Menu()
{
	printf("==================\n");
	printf("欢迎来到扫雷游戏\n");
	printf("1.开始游戏\n");
	printf("0.退出游戏\n");
	printf("==================\n");
	int choice;
	while (1) {
		printf("请输入你的选择(1或0):");
		scanf("%d", &choice);
		if (choice == 0 || choice == 1) {
			return choice;
		}
		printf("\n你的输入有误!请重新输入\n");
		continue;
	}
	return 0;
}

// 地图初始化
void Init(char showMap[MAX_ROW][MAX_COL],
			int mineMap[MAX_ROW][MAX_COL])
{
	// showMap未翻开用*表示
	for (int row = 0; row < MAX_ROW; row++) {
		for (int col = 0; col < MAX_COL; col++) {
			showMap[row][col] = '*';
		}
	}
	srand((unsigned int) time(0));
	// mineMap 1表示该坐标位置有雷, 0表示该坐标位置无雷
	for (int row = 0; row < MAX_ROW; row++) {
		for (int col = 0; col < MAX_COL; col++) {
			mineMap[row][col] = 0;
		}
	}
	for (int mine_count = 0; mine_count < MAX_MINE_COUNT; mine_count++) {
		while (1) {
			int row = rand() % MAX_ROW;
			int col = rand() % MAX_COL;
			if (!(row >= 0 && row < MAX_ROW)
				|| !(col >= 0 && col < MAX_COL)) {
				continue;
			}
			if (mineMap[row][col] == 1) {
				continue;
			}
			mineMap[row][col] = 1;
			break;
		}
	}
}

// 打印地图
void print_Map(char showMap[MAX_ROW][MAX_COL], int mineMap[MAX_ROW][MAX_COL])
{
	printf("    ");
	for (int i = 0; i < MAX_COL; i++) {
		printf("%d ", i);
	}
	putchar('\n');
	printf("=====================\n");
	for (int row = 0; row < MAX_ROW; row++) {
		printf("%d | ", row);
		for (int col = 0; col < MAX_COL; col++) {
			printf("%c ", showMap[row][col]);
		}
		putchar('\n');
	}
	//// TODO测试地雷位置
	//for (int row = 0; row < MAX_ROW; row++) {
	//	for (int col = 0; col < MAX_COL; col++) {
	//		printf("%d ", mineMap[row][col]);
	//	}
	//	putchar('\n');
	//}
}

// 计算8个位置中地雷的个数
void MineCount(char showMap[MAX_ROW][MAX_ROW], 
				int mineMap[MAX_ROW][MAX_COL], 
				int row, int col)
{
	int count = 0;
	for (int r = row - 1; r <= row + 1; r++) {
		for (int c = col - 1; c <= col + 1; c++) {
			if (r < 0 || r >= MAX_ROW || c < 0 || c >= MAX_COL) {
				continue;
			}
			if (mineMap[r][c] == 1) {
				count++;
			}
		}
	}
	showMap[row][col] = count + '0';
}

// 用户输入翻开位置
void Input(char showMap[MAX_ROW][MAX_COL], int* row, int* col) {
	while (1) {
		printf("请输入要翻开位置坐标(例如2 1):");
		scanf("%d %d", row, col);
		if (!(*row >= 0 && *row < MAX_ROW)
			|| !(*col >= 0 && *col < MAX_COL)) {
			printf("\n你的输入有误!\n");
			continue;
		}
		if (showMap[*row][*col] != '*') {
			printf("这个位置已经翻开过了\n");
			continue;
		}
		break;
	}
}

void Game()
{
	//1.创建地图并初始化
	char showMap[MAX_ROW][MAX_COL];		// 记录位置是翻开还是未翻开, *表示未翻开
	int mineMap[MAX_ROW][MAX_COL];		// 记录地雷的位置, 1表示为地雷
	int not_mine_count = 0;				// 记录非地雷的个数
	Init(showMap, mineMap);
	while (1) {
		//2.打印地图
		print_Map(showMap, mineMap);
		//3.玩家翻开指定位置(输入坐标)并进行校验
		int row = 0, col = 0;
		Input(showMap, &row, &col);
		//4.判断是否踩雷了,如果踩雷,直接游戏结束
		if (mineMap[row][col] == 1) {
			printf("你踩到了地雷,游戏结束!\n");
			break;
		}
		not_mine_count++;
		//5.如果翻开的是最后一个位置,游戏胜利
		if (not_mine_count == MAX_ROW * MAX_COL - MAX_MINE_COUNT) {
			printf("恭喜你获得了胜利!\n");
			break;
		}
		//6.游戏未结束,翻开的格子会变成一个数字
		MineCount(showMap, mineMap, row, col);
	}
}

int main()
{
	while (1) {
		int choice = Menu();
		if (choice) {
			Game();			// 开始游戏
		}
		else if (!choice) {
			printf("goodbye! I will miss you\n");
			break;			// 退出游戏
		}
	}
	system("pause");
	return 0;
}