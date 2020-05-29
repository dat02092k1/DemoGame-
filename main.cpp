#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "console.h"
#include <conio.h>
#include <time.h> //thư viện hỗ trợ về thời gian thực

using namespace std;

#define WIDTH  80
#define HEIGHT 30

enum stateSnake { STOP=0,UP, DOWN, LEFT, RIGHT};  // list state of Snake


bool gameOver ;

int score=0;



void drawWall()   // ham ve tuong
{
	TextColor(8 + rand() %8);

	int x=0, y=0;

     for ( x=0; x <= 90; x++ ) // the Top Wall
        {
          gotoXY (x,0);
         cout << "#" ;
     }
	for(y=0; y <= HEIGHT; y++) // the Right Wall
	{
		gotoXY(WIDTH,y);
		//cout << "|" << (char) 220 << "|" << endl;
		cout<< "#";
	}
	for(x=0; x <= WIDTH; x++) // The Low Wall
	{
		gotoXY(x, HEIGHT+1);
		//cout << "|" << (char) 220 << "|" << endl;
		cout << "#" ;
	}
	for(y=0; y <= HEIGHT; y++)
	{
		gotoXY(0,y); // The Left Wall
		//cout << "|" << (char) 220 << "|" << endl;
		cout<< "#";
	}
	gotoXY(1,WIDTH);
}

struct Coordinates //xây dựng một đối tượng điểm,Đối tượng này giúp ta lưu được tọa độ của một điểm trên trục tọa độ 2 chiều Oxy
{   // thiết lập tọa độ

    int x, y; // x la hoanh do, y la tung do
};

struct Snake // xây dừng đối tượng Snake
{
      Coordinates dot[50];
        //
      int n;  // số dot

      stateSnake pos;
};

struct Cherry // set up the bait for the Snake
{
       Coordinates s;
};

// SET UP SNAKE

void SetupSnake( Snake &snake, Cherry &cherry )
{
    //gameOver = false;
    snake.n = 1;

    snake.dot[0].x = 1;

    snake.dot[0].y = 1;

    snake.pos = RIGHT;

    cherry.s.x = 12;

    cherry.s.y = 12;
}

// SNAKE MOVE
void movingSnake( Snake &snake, Cherry &cherry )
{

      clrscr();
     // system("cls");

   /*  for ( int i=0; i <= 90; i++ ) // the Top Wall
        {
          gotoXY (i,0);
         cout << "#" ;
     } */


     TextColor(12);     // PRINT THE COLOR OF CHERRY (ColorCode_Red)

     // TextColor(8 + rand() %8);

     gotoXY(cherry.s.x, cherry.s.y);

      cout << "@";


   TextColor(13); // PRINT THE COLOR OF SNAKE

   gotoXY(snake.dot[0].x, snake.dot[0].y);

   cout << (char) 63;

     for ( int i=1; i < snake.n; i++ )
    {
     gotoXY(snake.dot[i].x, snake.dot[i].y);

      cout << "o";

     }
}

void changeTime(int &lev) {
     if (lev <  30) Sleep(200);

     if (lev >= 30 && score < 60 ) Sleep(100);

     if (lev>= 60 && score < 1000) Sleep(50);

     if (lev >= 100) Sleep(10);
}

void controlSnake(Snake &snake)  // Control the snake
{
    //int check=2;

    for ( int i = snake.n-1; i>0; i-- )

        snake.dot[i] = snake.dot[i-1];

    if (_kbhit())  // bắt sự kiện bàn phím
		{
		        char key = _getch(); // nhập dữ liệu từ bàn phím

				key = _getch();

				if (key == 72 )//move up
				{
				    snake.pos= UP;
					// check = 1;
				}
				else if (key == 80 )//move down
				{
				    snake.pos = DOWN;
					//check = 0;
				}
				else if (key == 77 )//move right
				{
				    snake.pos= RIGHT;
					//check = 2;
				}
				else if (key == 75 )//move left
				{
				    snake.pos= LEFT;

				}

		}

    if (snake.pos == DOWN) // khi ran di xuong toa do y++
    {
        snake.dot[0].y++;
    }
    else if (snake.pos == UP) // khi ran di len toa do y--
    {
        snake.dot[0].y--;
    }
    else if (snake.pos == LEFT)
    {
        snake.dot[0].x--;
    }
    else if (snake.pos == RIGHT)
    {
        snake.dot[0].x++;
    }


}

void checkScoreSnake(int mark)        // check the score
{
	TextColor(8);

	gotoXY(1,25);

	//cout<<"                                                        ";
	TextColor(8);

	gotoXY(85,17);

	cout << "You score: " << mark;
}

int solveSnake( Snake &snake, Cherry &cherry )   // Solve the problem of Snake
{
    if (snake.dot[0].x == cherry.s.x && snake.dot[0].y == cherry.s.y)
    {
        for ( int i=snake.n; i>0; i-- )

            snake.dot[i] = snake.dot[i-1];

            snake.n++;

            score += 10;

//    if (score+=10) Sleep(m++);

    cherry.s.x = rand() % WIDTH;     // random the Cherry

    cherry.s.y = rand() % HEIGHT;    // random the Cherry
    }
    // Solve when the Snake collide the boundary
    if (snake.dot[0].x <0 || snake.dot[0].x >= WIDTH) return -1;

    if (snake.dot[0].y <0 || snake.dot[0].y >= HEIGHT) return -1;

}



int main()
{

   int temp;


    srand(time(NULL));

    TextColor(15 + rand() %15);  // Random the color



    Snake snake;

    Cherry cherry;


   SetupSnake(snake, cherry);  // set up Snake

    while(5)
        {
            // appear
            movingSnake(snake,cherry);

            drawWall();

            gotoXY(WIDTH+5,2);

            cout << "WElCOME TO THE SNAKE WORLD!!" << endl;

            gotoXY(WIDTH+5, 5);

            cout << "Control: UP, DOWN, RIGHT, LEFT !!" << endl;
        // control
            controlSnake(snake);
        // solve
        temp = solveSnake(snake, cherry);

        // Game interface
        if(temp == -1) {

                // gameOver = true;

                gotoXY(WIDTH +2, 15);

        cout << "   Game Over !!! Good luck next time!!   ";

        checkScoreSnake(score);

        _getch(); // dừng màn hình để xem điểm
        break;
        }
        changeTime(score);

        // Sleep(200);
    }
    return 0;
}

/*void drawTopWall()
{
    int x = 0, y = 0;

	while (x <= 80)
	{
		gotoXY(x, y);

		cout << "||" << endl;

		x++;
	}
} */


