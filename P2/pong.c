
//  gcc pong.c -o pong -lncurses

#include <ncurses.h>
#include <unistd.h>

#define DELAY 50000

int main(int argc, char *argv[]) {
	
	int height, width;
	getmaxyx(stdscr,width,height);
	
	WINDOW *win = newwin(width,height,0,0);

	int x = 5, y = 0;
	int max_y = 25, max_x = 80;
	int next_x = 0;
	int directionx = 1;
	int next_y = 0;
	int directiony = 1;

	int xc = 20, yc = 10;
	int ch = 0;

	initscr();
	noecho();
	cbreak();
	curs_set(FALSE);
	nodelay(stdscr, TRUE);
	box(stdscr,'|','-');
	
	while(1) {
		clear();
		mvprintw(y, x, "o");
		mvprintw(yc, xc, "x");
		refresh(win);

		ch = getch();
		if (ch == 'o')
			xc -= 1;
		else if (ch == 'p')
			xc += 1;
		
		usleep(DELAY);

		next_x = x + directionx;
		next_y = y + directiony;

		if (next_x >= max_x || next_x < 0) {
			directionx*= -1;
		} else {
			x+= directionx;
		}

		if (next_y >= max_y || next_y < 0) {
			directiony*= -1;
		} else {
			y+= directiony;
		}
	}

	endwin();
}
