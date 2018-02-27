#include "gobang.h"
#include "AIStrategy.h"
#include "utils.h"


/*
* 定义空位置所在直线上的连线情况
*/
typedef struct _point_status
{
	int count;	// 正方向，本方棋子的个数（包括当前空位)
	int block;	// 判断的棋型两边的阻塞的个数（最多两个）；可能是边界或者是其他棋子
	int secondCount;	// 另一个方向的count
	int empty;	// 除了当前空位，其他空位的相对位置
} pointStatus;

void reset(pointStatus *p) {
	p->count = 1;
	p->block = 0;
	p->empty = -1;
	p->secondCount = 0;
}

/*
* 根据一个方向的连续棋子的数目，两端是否有阻塞以及中间是否有空位来判断棋型进而打分
*/
long type(int count, int block, int empty)
{
	//没有空位
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
		//第一个是空位
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
* 只做一件事，就是修复冲四:
* 如果是单独一个冲四，则将分数将至和活三一样
* 如果是冲四活三或者双冲四，则分数和活四一样
*/
long typeToScore(long result) {
	if (result < FOUR && result >= BLOCKED_FOUR) {
		if (result >= BLOCKED_FOUR && result < (BLOCKED_FOUR + THREE)) {
			//单独冲四，意义不大
			return THREE;
		}
		else if (result >= BLOCKED_FOUR + THREE && result < BLOCKED_FOUR * 2) {
			return FOUR; //冲四活三，比双三分高，相当于自己形成活四
		}
		else {
			//双冲四 比活四分数也高                                                                 
			return FOUR * 2;
		}
	}
	return result;
}

/*
* row,col 表示当前空位的行、列
* chess 表示当前的棋子
*/
long scorePoint(int row, int col, int chess)
{
	long result = 0;
	pointStatus p;
	reset(&p);
	
	//从左向右
	for (int i = col + 1; ; i++) {
		if (i >= boardLen) {
			p.block++;
			break;
		}
		int positionStatus = checkBoard[row][i];
		if (positionStatus == EMPTY) {
			if (p.empty == -1 && i < boardLen - 1 && checkBoard[row][i + 1] == chess) {
				p.empty = p.count; //当前位置是第一个空位，下一个位置仍然存在，而且放的是本方棋子
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
	} //end for(从左至右)
	  //从右向左 
	for (int i = col - 1; ; i--) {
		if (i < 0) {
			p.block++;
			break;
		}
		int positionStatus = checkBoard[row][i];
		if (positionStatus == EMPTY) {
			if (p.empty == -1 && i > 0 && checkBoard[row][i - 1] == chess) {
				p.empty = 0; //当前位置是第一个空位，下一个位置仍然存在，而且放的是本方棋子
				continue;
			}
			else
			{
				break;
			}
		}
		if (positionStatus == chess) {
			p.secondCount++;
			p.empty != -1 && p.empty++; //注意这里，如果左边又多了己方棋子，那么empty的位置就变大了
			continue;
		}
		else {
			p.block++;
			break;
		}
	}
	//综上看来empty只能更新一次，所找的这一条线中，除了当前空位，最多仅允许一个空位
	//empty的位置是相对我们检查这条直线的最左边的偏移
	p.count += p.secondCount;
	result += type(p.count, p.block, p.empty);
	
	//纵向
	reset(&p);
	for (int i = row + 1; ; i++) {
		if (i >= boardLen) {
			p.block++;
			break;
		}
		int positionStatus = checkBoard[i][col];
		if (positionStatus == EMPTY) {
			if (p.empty == -1 && i < boardLen - 1 && checkBoard[i + 1][col] == chess) {
				p.empty = p.count; //当前位置是第一个空位，下一个位置仍然存在，而且放的是本方棋子
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
				p.empty = 0; //当前位置是第一个空位，下一个位置仍然存在，而且放的是本方棋子
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
				p.empty = p.count; //当前位置是第一个空位，下一个位置仍然存在，而且放的是本方棋子
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
				p.empty = 0; //当前位置是第一个空位，下一个位置仍然存在，而且放的是本方棋子
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
				p.empty = p.count; //当前位置是第一个空位，下一个位置仍然存在，而且放的是本方棋子
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
				p.empty = 0; //当前位置是第一个空位，下一个位置仍然存在，而且放的是本方棋子
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
* 判断指定位置(row,col)周边(distance)是否有不少于count个落子
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

//更新指定位置的分数
void update(int row, int col) {
	int comChess = (first == AI ? BLACK : WHITE);
	int humChess = (first == AI ? WHITE : BLACK);
	int cs = scorePoint(row, col, comChess);
	int hs = scorePoint(row, col, humChess);
	comScore[row][col] = cs;
	humScore[row][col] = hs;
}

//在下第一步棋之后，给所有位置都评分以初始化所有位置，后续的更新单个位置的分数，仅更新该位置附近点的分数
//仅给有邻居的空位点评分
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

//更新一个点附近的分数
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

// 整个棋局估分函数
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

// 启发式搜索函数，生成可以搜索的节点序列
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
				if (hasNeighbor(i, j, 2, 2)) { // 该节点必须有邻居
					long scoreHum = humScore[i][j];
					long scoreCom = comScore[i][j];

					coordinate c = { i,j };
					if (scoreCom >= FIVE) { //先看电脑能不能成5
						push(re, c);
						return;
					}
					else if (scoreHum >= FIVE) { //再看玩家能不能成5
						//别着急返回，因为遍历还没有完成，可能在其他地方存在电脑能够成5
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
					else if (scoreCom >= 2 * THREE) { //双三
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

	//如果能成5，是必杀棋，直接返回
	if (fives.top > -1) {
		push(re, fives.arr[0]);
		return;
	}
	//注意一个活三可以有两个位置形成活四，但是不能只考虑其中一个，要从多个中考虑更好的选择
	//所以不能碰到活四就返回第一个，应该需要考虑多个
	if (fours.top > -1) {
		connect(re, &fours);
		return;
	}
	//冲四活三
	if (blockedfours.top > -1) {
		push(re, blockedfours.arr[0]);
		return;
	}
	//双三很特殊，因为能形成双三的不一定比一个活三强
	if (twothrees.top > -1) {
		connect(connect(re, &twothrees), &threes);
		return;
	}

	connect(connect(connect(re, &threes), &twos), &neighbors);
	return;
}