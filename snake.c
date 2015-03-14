#include <ncurses.h>
#include <time.h>

#define FIELD_SIZE 15
#define SNAKE_INIT_SIZE 3
#define SNAKE_CHAR S
#define SNAKE_HEAD_CHAR H
#define SNAKE_MAX_SIZE 200

typedef struct {
	int x;
	int y;
}Positions;

typedef struct {
	Position pos;
}SnakeBodyPart;

typedef struct {
	Position pos;
}Food;

/*
	-1 -> SNAKE
	0 -> NOTHING
	1 -> FOOD
*/
int field[FIELD_SIZE][FIELD_SIZE];
SnakeBodyPart snake[SNAKE_MAX_SIZE];
int snakeSize = SNAKE_INIT_SIZE;
Food food;

void move() {

}

void checkFoodCol() {

}

//generates food at random position
void generateFood() {
	do {
		food.pos.x = rand()%FIELD_SIZE;
		food.pos.y = rand()%FIELD_SIZE;
	}while ( food.pos.x == snake.pos.x && food.pos.y == snake.pos.y );
}

void checkWallCol() {

}

void snakeGrowth() {

}

void gameInit() {
	int i, j;
	
	for ( i = 0; i < FIELD_SIZE; ++i) 	{
		for ( j = 0; j < FIELD_SIZE; j++ ) {
			field[i][j] = 0;
		}
	}

	for ( i = 0; i < SNAKE_INIT_SIZE; i++ ) {
		snake[i].pos.x = 4 - i;
		snake[i].pos.y = 1;
	}

	generateFood();
}

void printField() {

}

int gameLoop() {

}

int main() {
	int ch;

	srand(time(0));

	initscr();			/* Start curses mode 		  */
	keypad(stdscr, TRUE);
	//makes sure that getchar doesn't wait for input
	//if a key is pressed it reads it
	nodelay(stdscr, TRUE);
	noecho();

	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

	return 0;

	return 0;
}