#include <ncurses.h>
#include <time.h>

#define FIELD_SIZE 15
#define SNAKE_INIT_SIZE 3
#define SNAKE_MAX_SIZE 200

typedef struct {
	int x;
	int y;
}Position;

typedef struct {
	Position pos;
}SnakeBodyPart;

typedef struct {
	Position pos;
}Food;

const char SNAKE_HEAD_CHAR = 'H';
const char SNAKE_CHAR = 'S';
const char FOOD_CHAR = 'F';

enum direction { 
	right = 0,
	up = 1,
	left = 2, 
	down = 3, 
};
/*
	-1 -> SNAKE
	0 -> NOTHING
	1 -> FOOD
*/
int field[FIELD_SIZE][FIELD_SIZE];
SnakeBodyPart snake[SNAKE_MAX_SIZE];
int snakeSize = SNAKE_INIT_SIZE;
enum direction snakeDirection;
Food food;

int isDirectionAllowed(enum direction direction) {
	if ( direction == left && snakeDirection == right) {
		return false;
	}
	if ( direction == right && snakeDirection == left) {
		return false;
	}
	if ( direction == up && snakeDirection == down) {
		return false;
	}
	if ( direction == down && snakeDirection == up) {
		return false;
	}
	return true;
}

void snakeMove() {
	char keyPressed;

	keyPressed = getch();

	switch (keyPressed) {
		case KEY_UP:
			if ( isDirectionAllowed(up) ) {
				snakeDirection = up;
			}
		case KEY_DOWN:
			if ( isDirectionAllowed(down) ) {
				snakeDirection = down;
			}
		case KEY_LEFT:
			if ( isDirectionAllowed(left) ) {
				snakeDirection = left;
			}
		case KEY_RIGHT:
			if ( isDirectionAllowed(right) ) {
				snakeDirection = right;
			}
	}
}

int checkFoodCol() {
	int i;

	for ( i = 0; i < snakeSize; i++ ) {
		if ( food.pos.x == snake[i].pos.x && food.pos.y == snake[i].pos.y ) {
			return true;
		}
	}
	return false;
}

//generates food at random position
void generateFood() {
	int i;
	do {
		food.pos.x = rand()%FIELD_SIZE;
		food.pos.y = rand()%FIELD_SIZE;
	}while ( checkFoodCol() );
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

/*
	iterates through the field and checks if the snake
	is at that position, if so, then sets the field value to 0
*/
void recreateField() {
	int posX, posY, k;

	for ( posX = 0; posX < FIELD_SIZE; posX++ ) {
		for ( posY = 0; posY < FIELD_SIZE; posY++ ) {
			for ( k = 0; k < snakeSize; k++ ) {
				if ( posX == snake[k].pos.x && posY == snake[k].pos.y ) {
					field[posX][posY] = -1;
				}
			}
		}
	}
}

void printField() {
	int i, j;
	printw(" ---------------\n");
	for ( i = 0; i < FIELD_SIZE; i++ ) {
		printw("|");
		for ( j = 0; j < FIELD_SIZE; j++ ) {
			if ( field[i][j] == 0 ) {
				printw(" ");
			}
			else if ( field[i][j] == -1 ) {
				printw("S");
			}
			else if ( field[i][j] == 1 ) {
				printw("F");
			}
		}
		printw("|\n");
	}
	printw(" ---------------\n");
	refresh();
}

int gameLoop() {
	while(1){
		clear();
		recreateField();
		printField();
		snakeMove();
		usleep(200000);
	}
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

	gameInit();
	gameLoop();

	refresh();			/* Print it on to the real screen */
	endwin();			/* End curses mode		  */

	return 0;
}