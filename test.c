#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>

// TODO Currently these need to be 5,3. Some code has fixed stuff for that **BAD**
#define GB_WIDTH 	6
#define GB_HEIGHT 	3
#define GB_LEFTPAD	10
#define GB_TOPPAD	5
#define GB_COLS		10
#define GB_ROWS		10
#define DIFFICULTY	10 // The higher the number the easier the game

#define SetBit(A,k)     ( A |= (1 << (k)) )
#define ClearBit(A,k)   ( A &= ~(1 << (k)) )
#define TestBit(A,k)    ( A & (1 << (k)) )

struct CURRPOS {
	int x,y;
	int coly, colx;
};

int mines[GB_ROWS];

// MOVE TO HEADER FILE
void MyMove(struct CURRPOS c);
void DrawGameBoard(int rows, int cols);
void GenerateMineFeild(int xx, int yy);
void Debug_PrintMineField();



int main(int argc, char *argv[]) {
	int ch, row,col;
	struct CURRPOS currpos;
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);
	getmaxyx(stdscr,row,col);
	mvprintw(row-1,0,"Move around game board, press SPACE to select your space");
	DrawGameBoard(GB_ROWS, GB_COLS);
	refresh();
	currpos.x = GB_TOPPAD + 2;
	currpos.y = GB_LEFTPAD + 3;
	currpos.coly = 1;
	currpos.colx = 1;
	MyMove(currpos);
	for(;;) {
		ch = getch();
		if(ch == 27 || ch == 'q' || ch == 'Q') {
			break;
		}
		if(ch == KEY_UP) {
			if(currpos.colx > 1) {
				currpos.x = currpos.x - 3;
				currpos.colx = currpos.colx-1;
			}
			MyMove(currpos);
		}
		if(ch == KEY_DOWN) {
			if(currpos.colx < GB_ROWS) {
				currpos.x = currpos.x + 3;
				currpos.colx = currpos.colx +1;
			}
			MyMove(currpos);
		}
		if(ch == KEY_LEFT) {
                        if(currpos.coly > 1) {
                                currpos.y = currpos.y - 6;
                                currpos.coly = currpos.coly-1;
                        }
                        MyMove(currpos);
		}
		if(ch == KEY_RIGHT) {
                        if(currpos.coly < GB_COLS) {
                                currpos.y = currpos.y + 6;
                                currpos.coly = currpos.coly+1;
                        }
                        MyMove(currpos);
		}
		if(ch == ' ') {
			GenerateMineFeild(currpos.colx, currpos.coly);
			Debug_PrintMineField();
		}
	}
	endwin();

	return 0;
}
void DrawGameBoard(int rows, int cols) {
	const int width=GB_WIDTH; // TODO Probably don't need to be like this, compiler will probably fix it though
	const int height=GB_HEIGHT;
	const int toppadding=GB_TOPPAD;
	const int leftpadding=GB_LEFTPAD;

	int totalwidth = width * cols + 2;
	int totalheight = height * rows;
	int count, y, x, i;

	// print top
	count = totalwidth -2;
	while(--count > 0) {
		mvprintw(toppadding,count + leftpadding,"_");
	}
	i=toppadding +1;
	for(x=0; x<rows;x++) {
		for(y=0; y < cols; y++) {
			mvprintw(i+2,y*width + leftpadding +1,"_____");
			mvprintw(i,y*width + leftpadding,"|");
			mvprintw(i+1,y*width + leftpadding,"|");
			mvprintw(i+2,y*width + leftpadding,"|");
		}
		mvprintw(i,y*width + leftpadding,"|");
		mvprintw(i+1,y*width + leftpadding,"|");
		mvprintw(i+2,y*width + leftpadding,"|");
		i=i+height;
	}
}
// x,y should not have a mine.
void GenerateMineFeild(int xx, int yy) {
	time_t t;
	int x,y;
	srand((unsigned) time(&t));
	for(x=0; x<GB_ROWS; x++) {
		for(y=0; y<GB_COLS; y++) {
			if(rand() % DIFFICULTY == 0)
				SetBit(mines[x], y);
			else
				ClearBit(mines[x], y);
			if(x+1==xx && y+1==yy) ClearBit(mines[x], y); // Make sure the selected area does not have a mine
		}
	}
}
void Debug_PrintMineField() {
	int x,y;
        for(x=0; x<GB_ROWS; x++) {
                for(y=0; y<GB_COLS; y++) {
			if(TestBit(mines[x], y)) {
				mvprintw(x+30,y,"*");
			}
			else {
				mvprintw(x+30,y,"O");
			}
		}
	}
}
void MyMove(struct CURRPOS c) {
	move(c.x, c.y);
}
