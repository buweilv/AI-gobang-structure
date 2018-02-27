#include "gobang.h"
#include "AIStrategy.h"
#include "utils.h"


/*
* �����λ������ֱ���ϵ��������
*/
typedef struct _point_status
{
	int count;	// �����򣬱������ӵĸ�����������ǰ��λ)
	int block;	// �жϵ��������ߵ������ĸ���������������������Ǳ߽��������������
	int secondCount;	// ��һ�������count
	int empty;	// ���˵�ǰ��λ��������λ�����λ��
} pointStatus;

void reset(pointStatus *p) {
	p->count = 1;
	p->block = 0;
	p->empty = -1;
	p->secondCount = 0;
}

/*
* ����һ��������������ӵ���Ŀ�������Ƿ��������Լ��м��Ƿ��п�λ���ж����ͽ������
*/
long type(int count, int block, int empty)
{
	//û�п�λ
	if (empty <= 0) {
		if (count >= 5) return FIVE;
		if (block == 0) {
			switch (count)
			{
			case 1: return ONE;
			case 2: return TWO;
			case 3: return THREE;
			case 4: return FOUR;
			}
		}
		if (block == 1) {
			switch (count)
			{
			case 1: return BLOCKED_ONE;
			case 2: return BLOCKED_TWO;
			case 3: return BLOCKED_THREE;
			case 4: return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 1 || empty == count - 1) {
		//��һ���ǿ�λ
		if (count >= 6)
			return FIVE;
		if (block == 0) {
			switch (count)
			{
			case 2: return TWO/2;
			case 3: return THREE;
			case 4: return BLOCKED_FOUR;
			case 5: return FOUR;
			}
		}
		if (block == 1) {
			switch (count)
			{
			case 2: return BLOCKED_TWO;
			case 3: return BLOCKED_THREE;
			case 4: return BLOCKED_FOUR;
			case 5: return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 2 || empty == count - 2) {
		if (count >= 7)
			return FIVE;
		if (block == 0) {
			switch (count)
			{
			case 3: return THREE;
			case 4:
			case 5: return BLOCKED_FOUR;
			case 6: return FOUR;
			}
		}
		if (block == 1) {
			switch (count) {
			case 3: return BLOCKED_THREE;
			case 4: return BLOCKED_FOUR;
			case 5: return BLOCKED_FOUR;
			case 6: return FOUR;
			}
		}
		if (block == 2) {
			switch (count) {
			case 4:
			case 5:
			case 6: return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 3 || empty == count - 3) {
		if (count >= 8)
			return FIVE;
		if (block == 0) {
			switch (count) {
			case 4:
			case 5: return THREE;
			case 6: return BLOCKED_FOUR;
			case 7: return FOUR;
			}
		}

		if (block == 1) {
			switch (count) {
			case 4:
			case 5:
			case 6: return BLOCKED_FOUR;
			case 7: return FOUR;
			}
		}

		if (block == 2) {
			switch (count) {
			case 4:
			case 5:
			case 6:
			case 7: return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 4 || empty == count - 4) {
		if (count >= 9) {
			return FIVE;
		}
		if (block == 0) {
			switch (count) {
			case 5:
			case 6:
			case 7:
			case 8: return FOUR;
			}
		}

		if (block == 1) {
			switch (count) {
			case 4:
			case 5:
			case 6:
			case 7: return BLOCKED_FOUR;
			case 8: return FOUR;
			}
		}

		if (block == 2) {
			switch (count) {
			case 5:
			case 6:
			case 7:
			case 8: return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 5 || empty == count - 5) {
		return FIVE;
	}
	return 0;
} 

/*
* ֻ��һ���£������޸�����:
* ����ǵ���һ�����ģ��򽫷��������ͻ���һ��
* ����ǳ��Ļ�������˫���ģ�������ͻ���һ��
*/
long typeToScore(long result) {
	if (result < FOUR && result >= BLOCKED_FOUR) {
		if (result >= BLOCKED_FOUR && result < (BLOCKED_FOUR + THREE)) {
			//�������ģ����岻��
			return THREE;
		}
		else if (result >= BLOCKED_FOUR + THREE && result < BLOCKED_FOUR * 2) {
			return FOUR; //���Ļ�������˫���ָߣ��൱���Լ��γɻ���
		}
		else {
			//˫���� �Ȼ��ķ���Ҳ��                                                                 
			return FOUR * 2;
		}
	}
	return result;
}

/*
* row,col ��ʾ��ǰ��λ���С���
* chess ��ʾ��ǰ������
*/
long scorePoint(int row, int col, int chess)
{
	long result = 0;
	pointStatus p;
	reset(&p);
	
	//��������
	for (int i = col + 1; ; i++) {
		if (i >= boardLen) {
			p.block++;
			break;
		}
		int positionStatus = checkBoard[row][i];
		if (positionStatus == EMPTY) {
			if (p.empty == -1 && i < boardLen - 1 && checkBoard[row][i + 1] == chess) {
				p.empty = p.count; //��ǰλ���ǵ�һ����λ����һ��λ����Ȼ���ڣ����ҷŵ��Ǳ�������
				continue;
			}
			else
			{
				break;
			}
		}
		if (positionStatus == chess) {
			p.count++;
			continue;
		}
		else {
			p.block++;
			break;
		}
	} //end for(��������)
	  //�������� 
	for (int i = col - 1; ; i--) {
		if (i < 0) {
			p.block++;
			break;
		}
		int positionStatus = checkBoard[row][i];
		if (positionStatus == EMPTY) {
			if (p.empty == -1 && i > 0 && checkBoard[row][i - 1] == chess) {
				p.empty = 0; //��ǰλ���ǵ�һ����λ����һ��λ����Ȼ���ڣ����ҷŵ��Ǳ�������
				continue;
			}
			else
			{
				break;
			}
		}
		if (positionStatus == chess) {
			p.secondCount++;
			p.empty != -1 && p.empty++; //ע������������ֶ��˼������ӣ���ôempty��λ�þͱ����
			continue;
		}
		else {
			p.block++;
			break;
		}
	}
	//���Ͽ���emptyֻ�ܸ���һ�Σ����ҵ���һ�����У����˵�ǰ��λ����������һ����λ
	//empty��λ����������Ǽ������ֱ�ߵ�����ߵ�ƫ��
	p.count += p.secondCount;
	result += type(p.count, p.block, p.empty);
	
	//����
	reset(&p);
	for (int i = row + 1; ; i++) {
		if (i >= boardLen) {
			p.block++;
			break;
		}
		int positionStatus = checkBoard[i][col];
		if (positionStatus == EMPTY) {
			if (p.empty == -1 && i < boardLen - 1 && checkBoard[i + 1][col] == chess) {
				p.empty = p.count; //��ǰλ���ǵ�һ����λ����һ��λ����Ȼ���ڣ����ҷŵ��Ǳ�������
				continue;
			}
			else
			{
				break;
			}
		}
		if (positionStatus == chess) {
			p.count++;
			continue;
		}
		else {
			p.block++;
			break;
		}
	}
	for (int i = row - 1; ; i--) {
		if (i < 0) {
			p.block++;
			break;
		}
		int positionStatus = checkBoard[i][col];
		if (positionStatus == EMPTY) {
			if (p.empty == -1 && i > 0 && checkBoard[i - 1][col] == chess) {
				p.empty = 0; //��ǰλ���ǵ�һ����λ����һ��λ����Ȼ���ڣ����ҷŵ��Ǳ�������
				continue;
			}
			else
			{
				break;
			}
		}
		if (positionStatus == chess) {
			p.secondCount++;
			p.empty != -1 && p.empty++; 
			continue;
		}
		else {
			p.block++;
			break;
		}
	}
	p.count += p.secondCount;
	result += type(p.count, p.block, p.empty);

	//	"\"
	reset(&p);
	for (int i = 1; ; i++) {
		int x = row + i, y = col + i;
		if (x >= boardLen || y >= boardLen) {
			p.block++;
			break;
		}
		int positionStatus = checkBoard[x][y];
		if (positionStatus == EMPTY) {
			if (p.empty == -1 && (x < boardLen - 1 && y < boardLen - 1) && checkBoard[x+1][y+1] == chess) {
				p.empty = p.count; //��ǰλ���ǵ�һ����λ����һ��λ����Ȼ���ڣ����ҷŵ��Ǳ�������
				continue;
			}
			else
			{
				break;
			}
		}
		if (positionStatus == chess) {
			p.count++;
			continue;
		}
		else {
			p.block++;
			break;
		}
	}
	for (int i = 1; ; i++) {
		int x = row - i, y = col - i;
		if (x < 0 || y < 0) {
			p.block++;
			break;
		}
		int positionStatus = checkBoard[x][y];
		if (positionStatus == EMPTY) {
			if (p.empty == -1 && (x > 0 && y > 0) && checkBoard[x-1][y-1] == chess) {
				p.empty = 0; //��ǰλ���ǵ�һ����λ����һ��λ����Ȼ���ڣ����ҷŵ��Ǳ�������
				continue;
			}
			else
			{
				break;
			}
		}
		if (positionStatus == chess) {
			p.secondCount++;
			p.empty != -1 && p.empty++; 
			continue;
		}
		else {
			p.block++;
			break;
		}
	}
	p.count += p.secondCount;
	result += type(p.count, p.block, p.empty);

	// "/"
	reset(&p);
	for (int i = 1; ; i++) {
		int x = row + i, y = col - i;
		if (x<0 || y<0 || x >= boardLen || y >= boardLen) {
			p.block++;
			break;
		}
		int positionStatus = checkBoard[x][y];
		if (positionStatus == EMPTY) {
			if (p.empty == -1 && (x < boardLen - 1 && y > 0) && checkBoard[x + 1][y - 1] == chess) {
				p.empty = p.count; //��ǰλ���ǵ�һ����λ����һ��λ����Ȼ���ڣ����ҷŵ��Ǳ�������
				continue;
			}
			else
			{
				break;
			}
		}
		if (positionStatus == chess) {
			p.count++;
			continue;
		}
		else {
			p.block++;
			break;
		}
	}
	for (int i = 1; ; i++) {
		int x = row - i, y = col + i;
		if (x<0 || y<0 || x >= boardLen || y >= boardLen) {
			p.block++;
			break;
		}
		int positionStatus = checkBoard[x][y];
		if (positionStatus == EMPTY) {
			if (p.empty == -1 && (x > 0 && y < boardLen - 1) && checkBoard[x - 1][y + 1] == chess) {
				p.empty = 0; //��ǰλ���ǵ�һ����λ����һ��λ����Ȼ���ڣ����ҷŵ��Ǳ�������
				continue;
			}
			else
			{
				break;
			}
		}
		if (positionStatus == chess) {
			p.secondCount++;
			p.empty != -1 && p.empty++;
			continue;
		}
		else {
			p.block++;
			break;
		}
	}
	p.count += p.secondCount;
	result += type(p.count, p.block, p.empty);

	return typeToScore(result);
}

/*
* �ж�ָ��λ��(row,col)�ܱ�(distance)�Ƿ��в�����count������
*/
int hasNeighbor(int row, int col, int distance, int count) {
	int startX = row - distance;
	int endX = row + distance;
	int startY = col - distance;
	int endY = col + distance;
	for (int i = startX; i <= endX; i++) {
		if (i < 0) continue;
		if (i >= boardLen) break;
		for (int j = startY; j <= endY; j++) {
			if (j < 0) continue;
			if (j >= boardLen) break;
			if (row == i && col == j) continue;
			if (checkBoard[i][j] != EMPTY) {
				count--;
				if (count <= 0) return 1;
			}
		}
	}
	return 0;
}

//����ָ��λ�õķ���
void update(int row, int col) {
	int comChess = (first == AI ? BLACK : WHITE);
	int humChess = (first == AI ? WHITE : BLACK);
	int cs = scorePoint(row, col, comChess);
	int hs = scorePoint(row, col, humChess);
	comScore[row][col] = cs;
	humScore[row][col] = hs;
}

//���µ�һ����֮�󣬸�����λ�ö������Գ�ʼ������λ�ã������ĸ��µ���λ�õķ����������¸�λ�ø�����ķ���
//�������ھӵĿ�λ������
void initScore()
{
	for (int i = 0; i < boardLen; i++) {
		for (int j = 0; j < boardLen; j++) {
			comScore[i][j] = 0;
			humScore[i][j] = 0;
		}
	}
	/*
	for (int i = 0; i < boardLen; i++) {
		for (int j = 0; j < boardLen; j++) {
			if (checkBoard[i][j] == EMPTY) {
				if (hasNeighbor(i, j, 2, 2)) {
					update(i, j, ps);
				}
			}
		}
	}
	*/
}

//����һ���㸽���ķ���
void updateScore(int row, int col) {
	int radius = 8;
	// -
	for (int i = -radius; i < radius; i++) {
		int x = row;
		int y = col + i;
		if (y < 0) continue;
		if (y >= boardLen) break;
		if (checkBoard[x][y] != EMPTY) continue;
		update(x, y);
	}
	// |
	for (int i = -radius; i < radius; i++) {
		int x = row + i;
		int y = col;
		if (x < 0) continue;
		if (x >= boardLen) break;
		if (checkBoard[x][y] != EMPTY) continue;
		update(x, y);
	}
	// "\"
	for (int i = -radius; i < radius; i++) {
		int x = row + i;
		int y = col + i;
		if (x < 0 || y < 0) continue;
		if (x >= boardLen || y >= boardLen) break;
		if (checkBoard[x][y] != EMPTY) continue;
		update(x, y);
	}
	// "/"
	for (int i = -radius; i < radius; i++) {
		int x = row + i;
		int y = col - i;
		if (x < 0 || y < 0) continue;
		if (x >= boardLen || y >= boardLen) continue;
		if (checkBoard[x][y] != EMPTY) continue;
		update(x, y);
	}
}

// ������ֹ��ֺ���
long evaluate(int player) {
	long comMaxScore = -FIVE;
	long humMaxScore = -FIVE;

	for (int i = 0; i < boardLen; i++) {
		for (int j = 0; j < boardLen; j++) {
			if (checkBoard[i][j] == EMPTY) {
				comMaxScore = max(comScore[i][j], comMaxScore);
				humMaxScore = max(humScore[i][j], humMaxScore);
			}
		}
	}
	long result = (player == AI ? 1 : -1) * (comMaxScore - humMaxScore);
	return  result;
}

// ����ʽ�������������ɿ��������Ľڵ�����
void gen(coordArray *re) {
	coordArray fives = { .top = -1 };
	coordArray fours = { .top = -1 };
	coordArray blockedfours = { .top = -1 };
	coordArray twothrees = { .top = -1 };
	coordArray threes = { .top = -1 };
	coordArray twos = { .top = -1 };
	coordArray neighbors = { .top = -1 };

	for (int i = 0; i < boardLen; i++) {
		for (int j = 0; j < boardLen; j++) {
			if (checkBoard[i][j] == EMPTY) {
				if (hasNeighbor(i, j, 2, 2)) { // �ýڵ�������ھ�
					long scoreHum = humScore[i][j];
					long scoreCom = comScore[i][j];

					coordinate c = { i,j };
					if (scoreCom >= FIVE) { //�ȿ������ܲ��ܳ�5
						push(re, c);
						return;
					}
					else if (scoreHum >= FIVE) { //�ٿ�����ܲ��ܳ�5
						//���ż����أ���Ϊ������û����ɣ������������ط����ڵ����ܹ���5
						push(&fives, c);
					}
					else if (scoreCom >= FOUR) {
						unshift(&fours, c);
					}
					else if (scoreHum >= FOUR) {
						push(&fours, c);
					}
					else if (scoreCom >= BLOCKED_FOUR) {
						unshift(&blockedfours, c);
					}
					else if (scoreHum >= BLOCKED_FOUR) {
						push(&blockedfours, c);
					}
					else if (scoreCom >= 2 * THREE) { //˫��
						unshift(&twothrees, c);
					}
					else if (scoreHum >= 2 * THREE) {
						push(&twothrees, c);
					}
					else if (scoreCom >= THREE) {
						unshift(&threes, c);
					}
					else if (scoreHum >= THREE) {
						push(&threes, c);
					}
					else if (scoreCom >= TWO) {
						unshift(&twos, c);
					}
					else if (scoreHum >= TWO) {
						push(&twos, c);
					}
					else {
						push(&neighbors, c);
					}
				}
			}
		}
	}

	//����ܳ�5���Ǳ�ɱ�壬ֱ�ӷ���
	if (fives.top > -1) {
		push(re, fives.arr[0]);
		return;
	}
	//ע��һ����������������λ���γɻ��ģ����ǲ���ֻ��������һ����Ҫ�Ӷ���п��Ǹ��õ�ѡ��
	//���Բ����������ľͷ��ص�һ����Ӧ����Ҫ���Ƕ��
	if (fours.top > -1) {
		connect(re, &fours);
		return;
	}
	//���Ļ���
	if (blockedfours.top > -1) {
		push(re, blockedfours.arr[0]);
		return;
	}
	//˫�������⣬��Ϊ���γ�˫���Ĳ�һ����һ������ǿ
	if (twothrees.top > -1) {
		connect(connect(re, &twothrees), &threes);
		return;
	}

	connect(connect(connect(re, &threes), &twos), &neighbors);
	return;
}