// ɨ����Ϸ

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
	printf("��ӭ����ɨ����Ϸ\n");
	printf("1.��ʼ��Ϸ\n");
	printf("0.�˳���Ϸ\n");
	printf("==================\n");
	int choice;
	while (1) {
		printf("���������ѡ��(1��0):");
		scanf("%d", &choice);
		if (choice == 0 || choice == 1) {
			return choice;
		}
		printf("\n�����������!����������\n");
		continue;
	}
	return 0;
}

// ��ͼ��ʼ��
void Init(char showMap[MAX_ROW][MAX_COL],
			int mineMap[MAX_ROW][MAX_COL])
{
	// showMapδ������*��ʾ
	for (int row = 0; row < MAX_ROW; row++) {
		for (int col = 0; col < MAX_COL; col++) {
			showMap[row][col] = '*';
		}
	}
	srand((unsigned int) time(0));
	// mineMap 1��ʾ������λ������, 0��ʾ������λ������
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

// ��ӡ��ͼ
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
	//// TODO���Ե���λ��
	//for (int row = 0; row < MAX_ROW; row++) {
	//	for (int col = 0; col < MAX_COL; col++) {
	//		printf("%d ", mineMap[row][col]);
	//	}
	//	putchar('\n');
	//}
}

// ����8��λ���е��׵ĸ���
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

// �û����뷭��λ��
void Input(char showMap[MAX_ROW][MAX_COL], int* row, int* col) {
	while (1) {
		printf("������Ҫ����λ������(����2 1):");
		scanf("%d %d", row, col);
		if (!(*row >= 0 && *row < MAX_ROW)
			|| !(*col >= 0 && *col < MAX_COL)) {
			printf("\n�����������!\n");
			continue;
		}
		if (showMap[*row][*col] != '*') {
			printf("���λ���Ѿ���������\n");
			continue;
		}
		break;
	}
}

void Game()
{
	//1.������ͼ����ʼ��
	char showMap[MAX_ROW][MAX_COL];		// ��¼λ���Ƿ�������δ����, *��ʾδ����
	int mineMap[MAX_ROW][MAX_COL];		// ��¼���׵�λ��, 1��ʾΪ����
	int not_mine_count = 0;				// ��¼�ǵ��׵ĸ���
	Init(showMap, mineMap);
	while (1) {
		//2.��ӡ��ͼ
		print_Map(showMap, mineMap);
		//3.��ҷ���ָ��λ��(��������)������У��
		int row = 0, col = 0;
		Input(showMap, &row, &col);
		//4.�ж��Ƿ������,�������,ֱ����Ϸ����
		if (mineMap[row][col] == 1) {
			printf("��ȵ��˵���,��Ϸ����!\n");
			break;
		}
		not_mine_count++;
		//5.��������������һ��λ��,��Ϸʤ��
		if (not_mine_count == MAX_ROW * MAX_COL - MAX_MINE_COUNT) {
			printf("��ϲ������ʤ��!\n");
			break;
		}
		//6.��Ϸδ����,�����ĸ��ӻ���һ������
		MineCount(showMap, mineMap, row, col);
	}
}

int main()
{
	while (1) {
		int choice = Menu();
		if (choice) {
			Game();			// ��ʼ��Ϸ
		}
		else if (!choice) {
			printf("goodbye! I will miss you\n");
			break;			// �˳���Ϸ
		}
	}
	system("pause");
	return 0;
}