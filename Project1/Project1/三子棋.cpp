//��������Ϸ
#define _CRT_SECURE_NO_WARNINGS
#define MAX_ROW 3
#define MAX_COL 3

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ��Ϸ��ʼ�˵�
int Menu()
{
	printf("--------------\n");
	printf("��ӭ������������Ϸ(����1��ʼ,����0����)\n");
	printf("1.��ʼ��Ϸ\n");
	printf("0.������Ϸ\n");
	printf("--------------\n");
	printf("���������ѡ��:");
	int choice;
	scanf("%d", &choice);
	return choice;
}

// ��ʼ������
void Init(char chessBoard[MAX_ROW][MAX_COL])
{
	for (int row = 0; row < MAX_ROW; row++) {
		for (int col = 0; col < MAX_COL; col++) {
			chessBoard[row][col] = ' ';
		}
	}
}

// ��ӡ����
void printChess(char chessBoard[MAX_ROW][MAX_COL])
{
	for (int row = 0; row < MAX_ROW; row++) {
		for (int col = 0; col < MAX_COL; col++) {
			printf("%c  ", chessBoard[row][col]);
		}
		putchar('\n');
	}
}

// �������(��X��ʾ)
void PlayerMove(char chessBoard[MAX_ROW][MAX_COL])
{
	int row_p, col_p;
	while (1) {
		printf("�������\n");
		printf("���������ӵ�����:(����0-2����, ����2 1)");
		scanf("%d %d", &row_p, &col_p);
		if (row_p < 0 || row_p > 2 || col_p < 0 || col_p > 2) {
			printf("�����������,����������");
			continue;
		}
		if (chessBoard[row_p][row_p] != ' ')
		{
			printf("���λ���Ѿ�������,����������\n");
			continue;
		}
		chessBoard[row_p][col_p] = 'X';
		break;
	}
}

// ��������(��O��ʾ)
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

// �ж��Ƿ����ӿɷ�, �ǵĻ�����1, ���ǵĻ�����0
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

// �ж���Ϸ�Ƿ����
// ����X ��ʾ���Ӯ;	����O ��ʾ����Ӯ;	����Q ��ʾƽ��
char IsGameEnd(char chessBoard[MAX_ROW][MAX_COL])
{
	// �ж����Ƿ���ͬ���Ҳ�Ϊ' '
	for (int row = 0; row < MAX_ROW; row++) {
		if (chessBoard[row][0] == chessBoard[row][1]
			&& chessBoard[row][0] == chessBoard[row][2]
			&& chessBoard[row][0] != ' ') {
			return chessBoard[row][0];
		}
	}
	// �ж����Ƿ���ͬ���Ҳ�Ϊ' '
	for (int col = 0; col < MAX_COL; col++) {
		if (chessBoard[0][col] == chessBoard[1][col]
			&& chessBoard[0][col] == chessBoard[2][col]
			&& chessBoard[0][col] != ' ') {
			return chessBoard[0][col];
		}
	}
	//�ж϶Խ����Ƿ���ͬ���Ҳ�Ϊ' '
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
	//�ж��Ƿ����ӿɷ�
	if (IsFull(chessBoard)) {
		return 'Q';
	}
	return 0;
}

// ��ʼ��Ϸ
void Game()
{
	//1.�������̲���ʼ������(ÿ��λ�ö���Ϊ�ո�)
	char chessBoard[MAX_ROW][MAX_COL];
	Init(chessBoard);
	while (1) {
		//2.��ӡ����(��һ�δ�ӡ���ǿհ�����)
		printChess(chessBoard);
		//3.�������(ͨ����������ķ�ʽ�ƶ�����)
		PlayerMove(chessBoard);
		//4.�ж���Ϸ�Ƿ����
		if (IsGameEnd(chessBoard) == 'X') {
			printf("�������̫������ѽ!\n");
			break;
		}
		else if (IsGameEnd(chessBoard) == 'O') {
			printf("����ô�����Զ��²�Ӯ��!\n");
			break;
		}
		else if (IsGameEnd(chessBoard) == 'Q') {
			printf("���ǲ�������ѽ!\n");
			break;
		}
		//5.��������(�������)
		ComputerMove(chessBoard);
		//6.�ж���Ϸ�Ƿ����
		if (IsGameEnd(chessBoard) == 'X') {
			printf("�������̫������ѽ!\n");
			break;
		}
		else if (IsGameEnd(chessBoard) == 'O') {
			printf("����ô�����Զ��²�Ӯ��!\n");
			break;
		}
		else if (IsGameEnd(chessBoard) == 'Q') {
			printf("���ǲ�������ѽ!\n");
			break;
		}
	}
}

int main()
{
	srand(unsigned int(time(0)));	//�����������
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
			printf("�����������\n");
		}
	}
	return 0;
}