// ɨ����Ϸ

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
		if (choice != 0 || choice != 1) {
			printf("\n�����������!����������");
			continue;
		}
		return choice;
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
	srand(unsigned int(time(0)));
	// mineMap 1��ʾ������λ������, 0��ʾ������λ������
	for (int mine_count = 0; mine_count < MAX_MINE_COUNT; mine_count++) {
		int row = rand() % MAX_ROW;
		int col = rand() % MAX_COL;
		while (1) {
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
void print_Map(char showMap[MAX_ROW][MAX_COL])
{
	for (int row = 0; row < MAX_ROW; row++) {
		for (int col = 0; col < MAX_COL; col++) {
			printf("%c ", showMap[row][col]);
		}
		putchar('\n');
	}
}

// ����8��λ���е��׵ĸ���
int MineCount(int mineMap[MAX_ROW][MAX_COL], int row, int col)
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
	return count;
}

// �û����뷭��λ��
void Input(char showMap[MAX_ROW][MAX_COL], int mineMap[MAX_ROW][MAX_COL]) {
	int row, col;
	while (1) {
		printf("������Ҫ����λ������(����2 1):");
		scanf("%d %d", &row, &col);
		if (!(row >= 0 && row < MAX_ROW)
			|| !(col >= 0 && col < MAX_COL)) {
			printf("\n�����������!\n");
			continue;
		}
		if (showMap[row][col] != '*') {
			printf("���λ���Ѿ���������\n");
			continue;
		}
		showMap[row][col] = MineCount(mineMap, row, col);
		break;
	}
}

void Game()
{
	//1.������ͼ����ʼ��
	char showMap[MAX_ROW][MAX_COL];		// ��¼λ���Ƿ�������δ����
	int mineMap[MAX_ROW][MAX_COL];		// ��¼���׵�λ��
	Init(showMap, mineMap);
	while (1) {
		//2.��ӡ��ͼ
		print_Map(showMap);
		//3.��ҷ���ָ��λ��(��������)������У��
		Input(showMap, mineMap);
		//4.�ж��Ƿ������,�������,ֱ����Ϸ����
		//5.��������������һ��λ��,��Ϸʤ��
		//6.��Ϸδ����,�����ĸ��ӻ���һ������
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
			break;			// �˳���Ϸ
		}
	}
	system("pause");
	return 0;
}