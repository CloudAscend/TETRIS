#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>

char form[7][4][8] =
{
	{ { 1,0,1,1,1,2,1,3 },{ 0,1,1,1,2,1,3,1 },{ 1,0,1,1,1,2,1,3 },{ 0,1,1,1,2,1,3,1 } },
	{ { 1,1,2,1,1,2,2,2 },{ 1,1,2,1,1,2,2,2 },{ 1,1,2,1,1,2,2,2 },{ 1,1,2,1,1,2,2,2 } },
	{ { 2,1,0,2,1,2,1,1 },{ 1,0,1,1,2,1,2,2 },{ 2,1,0,2,1,2,1,1 },{ 1,0,1,1,2,1,2,2 } },
	{ { 0,1,1,1,1,2,2,2 },{ 2,0,2,1,1,1,1,2 },{ 0,1,1,1,1,2,2,2 },{ 2,0,2,1,1,1,1,2 } },
	{ { 1,0,1,1,1,2,2,2 },{ 0,1,1,1,2,1,0,2 },{ 1,0,2,0,2,1,2,2 },{ 2,1,2,2,1,2,0,2 } },
	{ { 2,0,2,1,2,2,1,2 },{ 0,1,0,2,1,2,2,2 },{ 1,0,2,0,1,1,1,2 },{ 0,1,1,1,2,1,2,2 } },
	{ { 0,1,1,1,2,1,1,2 },{ 2,0,2,1,2,2,1,1 },{ 1,1,1,2,0,2,2,2 },{ 1,0,1,1,1,2,2,1 } },
};

int tetris[21][12];
int bag[7];
int bagCount = 0;
int form_kind;
int next_kind;
int hold_kind = -1;
int rotate_kind;
int screen_x, screen_y;
int score;
int level;
int boss = 10000; //테스트용
int isHolding = 0;

void CurrentXY(int x, int y);
void CursorOff(void);
void CursorOn(void);
void Color(int i);
void Print_form();
void Print_Boss();
void Delete_form();
void Print_next();
void Delete_next();
void Update_Bag();
void Print_hold();
void Delete_hold();
void Initial();
int  Check_board(int location_x, int location_y);
void Print_data();
void Move_data(int row);
int  Check_line2(int row);
void Check_line();
void Write_board();
int  Go_down();
int  Select(void);
void Timing(void);
void ChangeScore(int i);
void ChangeLevel(int i);
void ChangeBoss(int i);

int Ingame();
void Ending();
void Title();

int main() { //타이틀

	Title();
	Ingame();
	//printf("13123123123123");

	/*if (score == 1)
		for (int i = 0; i < 200; i++) {
			for (int j = 0; j < 200; j++) {
				CurrentXY(i, j);
				printf(" ");
			}
		}

	do {
		CurrentXY(45, 24);
		printf("THE END");
		Ending();
	} while (not _kbhit());*/

	return 0;
}

void Title() {
	CursorOff();
	Color(15);
	CurrentXY(35, 10);
	printf("□□□  □□□  □□□  □□    □□□    □□");
	CurrentXY(35, 11);
	printf("  □    □        □    □  □    □    □");
	CurrentXY(35, 12);
	printf("  □    □□□    □    □□      □    □□□");
	CurrentXY(35, 13);
	printf("  □    □        □    □  □    □        □");
	CurrentXY(35, 14);
	printf("  □    □□□    □    □  □  □□□  □□");

	CurrentXY(43, 17);
	printf("□      □□□  □□□  □□□");
	CurrentXY(43, 18);
	printf("□        □    □      □");
	CurrentXY(43, 19);
	printf("□        □    □□□  □□□");
	CurrentXY(43, 20);
	printf("□        □    □      □");
	CurrentXY(43, 21);
	printf("□□□  □□□  □      □□□");

	do {
		CurrentXY(50, 24);
		printf("Press any key");
	} while (not _kbhit());

	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 15; j++) {
			CurrentXY(35 + i, 10 + j);
			printf(" ");
		}
	}
}

int Ingame() { //인게임
	int chk, chk2;

	CursorOff();
	Initial();

	do {
		screen_y = 0;
		screen_x = 4;
		Delete_next();
		form_kind = next_kind;
		Update_Bag();
		rotate_kind = 0;
		isHolding = 0;

		Print_next();
		Print_form();
		Print_Boss();

		Color(16);
		chk = Check_board(screen_x, screen_y);
		chk2 = Check_board(screen_x, screen_y + 1);

		if (chk == FALSE && chk2 == TRUE) {
			Write_board();
			Check_line();
			break;
		}
		else if (chk == TRUE && chk2 == TRUE)
			break;

		do {
			Timing();
		} while (Select());

	} while (1);

	CursorOn();

	return 0;
}

/*void Ending() { //엔딩
	CursorOff();

	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 200; j++) {
			CurrentXY(i, j);
			printf(" ");
		}
	}

	for (int i = 0; i < 21; i++) {
		CurrentXY(30, i);
		printf("│");

		CurrentXY(52, i);
		printf("│");
	}

	CurrentXY(30, 20);
	printf("└");
	for (int j = 1; j < 11; j++) {
		CurrentXY(30 + j * 2, 20);
		printf("─");
	}
	CurrentXY(52, 20);
	printf("┘");

	do {
		screen_y = 0;
		screen_x = 4;

		for (int i = 0; i < 4; i++) {

			CurrentXY(30 + (screen_x + form[form_kind][rotate_kind][i * 2]) * 2,
				screen_y + form[form_kind][rotate_kind][i * 2 + 1]);

			printf(");
			printf("
		}

		Print_form();
		Write_board();
		Check_line();

		Timing();


	} while (1);

	CursorOn();

	return 0;
}*/

void Update_Bag() {
	if (bagCount == 0) {
		for (int j = 0; j < 7; j++) {
			bag[j] = j;
		}
		bagCount = 7;
		for (int i = 0; i < 20; i++) /* N번 교환 */
		{
			int a = rand() % 7;
			int b = rand() % 7;

			int tmp = bag[a];
			bag[a] = bag[b];
			bag[b] = tmp;
		}
	}
	next_kind = bag[bagCount - 1];
	bagCount--;
}

void Print_Boss() {
	Color(12);
	CurrentXY(86, 3);
	printf("모시깽 보스");
	CurrentXY(83, 5);
	printf("↖               ↗");
	CurrentXY(85, 6);
	printf("▶ _-------_ ◀");
	CurrentXY(85, 7);
	printf(" ¶         ¶  ");
	CurrentXY(85, 8);
	printf("¶ __   ___  ¶  ");
	CurrentXY(85, 9);
	printf("¶ ▼    ▼  ¶  ");
	CurrentXY(85, 10);
	printf("↘    △     ↙  ");
	CurrentXY(85, 11);
	printf("↙--______---¶  ");
	CurrentXY(84, 12);
	printf("¶            ¶");
	CurrentXY(80, 13);
	printf("◈<¶        ▣<=) ¶");
	CurrentXY(83, 14);
	printf("¶              ¶");
	CurrentXY(84, 15);
	printf("¶            ¶");
	CurrentXY(84, 16);
	printf("  ¶¶¶¶¶¶");
	CurrentXY(84, 18);
	printf("보스의 기분 : ");
	if (boss > 7500) {
		level = 1;
		printf("기본");
	}
	else if (boss > 5000) {
		level = 2;
		printf("약간 화남");
	}
	else if (boss > 2500) {
		level = 3;
		printf("화남");
	}
	else if (boss > 0) {
		level = 4;
		printf("극대노");
	}
	CurrentXY(86, 20);
	printf("체력 : %d", boss);
	Color(15);
}

void Color(int color) { //글씨 색깔 변경 함수
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CurrentXY(int x, int y) {
	COORD Location;
	Location.X = x;
	Location.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Location);
}

void CursorOff(void) {
	CONSOLE_CURSOR_INFO Information;
	Information.dwSize = 1;
	Information.bVisible = FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Information);
}

void CursorOn(void) {
	CONSOLE_CURSOR_INFO Information;

	Information.dwSize = 20;
	Information.bVisible = TRUE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Information);
}

void Print_form() {
	Color(6);
	for (int i = 0; i < 4; i++) {

		CurrentXY(30 + (screen_x + form[form_kind][rotate_kind][i * 2]) * 2,
			screen_y + form[form_kind][rotate_kind][i * 2 + 1]);

		tetris[screen_y + form[form_kind][rotate_kind][i * 2 + 1]]
			[screen_x + form[form_kind][rotate_kind][i * 2]] = 1;

		printf("□");
	}
	Color(15);
}

void Print_next() {
	Color(13);
	for (int i = 0; i < 4; i++) {

		CurrentXY(10 + (form[next_kind][0][i * 2]) * 2,
			form[next_kind][0][i * 2 + 1] + 10);
		printf("□");
	}
	Color(15);
}

void Delete_next() {
	for (int i = 0; i < 4; i++) {

		CurrentXY(10 + (form[next_kind][0][i * 2]) * 2,
			form[next_kind][0][i * 2 + 1] + 10);
		printf(" ");
	}
	Color(15);
}

void Print_hold() {
	Color(11);
	for (int i = 0; i < 4; i++) {

		CurrentXY(10 + (form[hold_kind][0][i * 2]) * 2,
			form[hold_kind][0][i * 2 + 1] + 18);
		printf("□");
	}
	Color(15);
}

void Delete_hold() {
	Color(15);
	for (int i = 0; i < 4; i++) {

		CurrentXY(10 + (form[hold_kind][0][i * 2]) * 2,
			form[hold_kind][0][i * 2 + 1] + 18);
		printf(" ");
	}
}

void Delete_form() {
	Color(15);
	for (int i = 0; i < 4; i++) {

		CurrentXY(30 + (screen_x + form[form_kind][rotate_kind][i * 2]) * 2,
			screen_y + form[form_kind][rotate_kind][i * 2 + 1]);

		tetris[screen_y + form[form_kind][rotate_kind][i * 2 + 1]]
			[screen_x + form[form_kind][rotate_kind][i * 2]] = 0;

		printf(" ");
	}
}


void Initial() {
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 12; j++) {
			if (i == 20 || j == 0 || j == 11)
				tetris[i][j] = 3;
			else
				tetris[i][j] = 0;
		}
	}

	for (int i = 0; i < 21; i++) {
		CurrentXY(30, i);
		printf("│");

		CurrentXY(52, i);
		printf("│");
	}

	CurrentXY(30, 20);
	printf("└");
	for (int j = 1; j < 11; j++) {
		CurrentXY(30 + j * 2, 20);
		printf("─");
	}
	CurrentXY(52, 20);
	printf("┘");

	CurrentXY(12, 8);
	printf("NEXT");

	CurrentXY(12, 16);
	printf("HOLD");

	srand((unsigned int)time(NULL));

	ChangeScore(10000);
	Update_Bag();
}

void ChangeLevel(int i) {
	level = i;
	CurrentXY(10, 4);
	printf("레벨 : %d", level);
}

void ChangeScore(int i) {
	boss = i;
}

int Check_board(int location_x, int location_y) {
	int temp = 0;

	for (int i = 0; i < 4; i++) {
		temp = tetris[location_y + form[form_kind][rotate_kind][i * 2 + 1]]
			[location_x + form[form_kind][rotate_kind][i * 2]];

		if (temp > 1) return TRUE;
	}
	return FALSE;
}

void Print_data() {
	Color(6);
	for (int i = 0; i < 20; i++) {
		for (int j = 1; j < 11; j++) {
			if (tetris[i][j] == 2) {
				CurrentXY(30 + j * 2, i);
				printf("□");
			}
			else {
				CurrentXY(30 + j * 2, i);
				printf(" ");
			}
		}
	}
	Color(15);
}

void Move_data(int row) {
	for (int i = row - 1; i >= 0; i--)
		for (int j = 1; j < 11; j++)
			tetris[i + 1][j] = tetris[i][j];
}

int Check_line2(int row) {
	int chk = 0;
	int j;

	for (j = 1; j < 11; j++) chk += tetris[row][j];

	if (chk == 20) return TRUE;
	else return FALSE;
}

void Check_line() {
	int rst;

	for (int i = screen_y; i < screen_y + 4; i++) {
		rst = Check_line2(i);

		if (rst == TRUE) {
			Move_data(i);
			Print_data();
			ChangeScore(boss - (100 + rand() % 100));
			i--;
		}
	}
}

void Write_board() {
	for (int i = 0; i < 4; i++) {
		tetris[screen_y + form[form_kind][rotate_kind][i * 2 + 1]]
			[screen_x + form[form_kind][rotate_kind][i * 2]] = 2;
	}
}

int Go_down() {
	int chk2;

	chk2 = Check_board(screen_x, screen_y + 1);

	if (chk2 == TRUE) {
		Write_board();
		Check_line();
		return TRUE;
	}

	Delete_form();
	screen_y++;
	Print_form();
	return FALSE;
}

int Select(void) {
	int chk1;
	int prev_rotate;
	int new_rotate;
	int rtn_value;

	if (GetAsyncKeyState(0x43)) { // C키
		if (isHolding == 0)
		{
			isHolding = 1;
			Delete_form();
			screen_y = 0;
			int hold = hold_kind;
			Delete_hold();
			hold_kind = form_kind;
			if (hold == -1)
			{
				Delete_next();
				form_kind = next_kind;
				next_kind = rand() % 7;
				rotate_kind = 0;
				Print_next();
			}
			else
			{
				form_kind = hold;
			}

			Print_hold();
			Print_form();
			return TRUE;
		}
	}

	if (GetAsyncKeyState(VK_LEFT)) {

		chk1 = Check_board(screen_x - 1, screen_y);

		if (chk1 == FALSE) {
			Delete_form();
			screen_x--;
			Print_form();
			return TRUE;
		}
	}

	if (GetAsyncKeyState(VK_RIGHT)) {
		chk1 = Check_board(screen_x + 1, screen_y);

		if (chk1 == FALSE) {
			Delete_form();
			screen_x++;
			Print_form();
			return TRUE;
		}
	}

	if (GetAsyncKeyState(VK_UP)) {
		prev_rotate = rotate_kind;

		if (rotate_kind == 3) rotate_kind = 0;
		else				rotate_kind++;

		new_rotate = rotate_kind;

		chk1 = Check_board(screen_x, screen_y);

		if (chk1 == FALSE) {
			rotate_kind = prev_rotate;
			Delete_form();

			rotate_kind = new_rotate;
			Print_form();
			return TRUE;
		}
		else {
			rotate_kind = prev_rotate;
		}
	}

	if (GetAsyncKeyState(VK_CONTROL)) {
		prev_rotate = rotate_kind;

		if (rotate_kind == 0) rotate_kind = 3;
		else				rotate_kind--;

		new_rotate = rotate_kind;

		chk1 = Check_board(screen_x, screen_y);

		if (chk1 == FALSE) {
			rotate_kind = prev_rotate;
			Delete_form();

			rotate_kind = new_rotate;
			Print_form();
			return TRUE;
		}
		else {
			rotate_kind = prev_rotate;
		}
	}

	if (GetAsyncKeyState(VK_SPACE)) {
		while (!Go_down());
		return FALSE;
	}

	rtn_value = Go_down();

	if (rtn_value == TRUE) return FALSE;
	else return TRUE;
}

void Timing(void) {
	DWORD				thisTickCount;
	static DWORD		lastTickCount = 0;
	DWORD				delay = 400 / (level / 2 + 1);

	thisTickCount = GetTickCount();

	while (1) {
		if ((thisTickCount - lastTickCount) > delay) {
			lastTickCount = thisTickCount;
			return;
		}

		thisTickCount = GetTickCount();
	}
}