#include<stdio.h>

#define WIDTH_SCREEN 82
#define HEIGHT_SCREEN 27

/* Настройки позиции рокетоок и мяча и его направления движения */
#define START_POSITION_P1_X 2
#define START_POSITION_P1_Y 14
#define START_POSITION_P2_X 78
#define START_POSITION_P2_Y 14
#define START_POSITION_BALL_X 40
#define START_POSITION_BALL_Y 14
#define START_DIRECTION_BALL_X 1
#define START_DIRECTION_BALL_Y 1
#define START_SCORE_P 0
/*  Информационное табло */
#define START_POSITION_INFORMATION 0
#define END_POSITION_INFORMATION 2
#define START_INPUT_TO_EXIT 3
#define START_PLAYER_SCORE 20



/* Коды клавиш */
#define A 97
#define Z 122
#define K 107
#define M 109
#define ENTER 10



typedef struct P1
{
    int x;
    int y;
    int score;
} P1;

typedef struct P2
{
    int x;
    int y;
    int score;
}P2;

typedef struct Ball
{
    int x;
    int y;
    // Изначально мячик движется по напрявлению первого  игрока под углом 45 градусов в направлении правого нижнего угла
    int directionX; // Направление движения мачика по иксу
    int directionY; // Направление движения мячика по игрику
    
} Ball;

// Вызывается при первой отрисовке тоесть когда значения всех переменных игры соответствуют default param
void Drow_Screen(P1 *p1, P2 *p2, Ball *ball);
void Move_Rocket(char ch, P1 *p1, P2 *p2, Ball *ball);
void Move_Ball(char ch,P1 *p1, P2 *p2, Ball *ball);

void ClearScreen();

int main() {
    
    P1 p1;
    P2 p2;
    Ball ball;
    /* Инициализируем положения рокеток и положение мяча  */
    p1.x = START_POSITION_P1_X;
    p1.y = START_POSITION_P2_Y;
    p1.score = START_SCORE_P;
    p2.x = START_POSITION_P2_X;
    p2.y = START_POSITION_P2_Y;
    p2.score = START_SCORE_P;
    ball.x = START_POSITION_BALL_X;
    ball.y = START_POSITION_BALL_Y;
    ball.directionX = START_DIRECTION_BALL_X;
    ball.directionY = START_DIRECTION_BALL_Y;
    
    
    
    
    while(1)
    {
        Drow_Screen(&p1, &p2, &ball);
        char key = getchar();
        Move_Rocket(key, &p1, &p2, &ball);
        Move_Ball(key, &p1, &p2, &ball);
        ClearScreen();
    }
    
    return 0;
}


void Drow_Screen(P1 *p1, P2 *p2, Ball *ball)
{
    for(int i = 0; i < HEIGHT_SCREEN; i++)
    {
        if((i != 0) && (i != 2) && (i != 3) && (i !=  HEIGHT_SCREEN - 1)) printf("|");
        for(int j = 0; j < WIDTH_SCREEN; j++)
        {
            if((i == 0) && j >= 1) printf("-"); // Печатаем верхную границу доски
            else if((i == 3)&& (j >= 1)) printf("-");
            else if(i == ball->y && j == ball->x) printf("o");
            else if((i == END_POSITION_INFORMATION) && (j >= 1)) printf("-");
            else if(i == 1 && j == START_INPUT_TO_EXIT) printf("Please enter ctrl + c to exit");
            else if(i == 1 && j == START_PLAYER_SCORE) printf("player1: %d  |  player2: %d        |", p1->score, p2->score);
            else if(i != 1 && i != (HEIGHT_SCREEN-1) && j == (WIDTH_SCREEN-1)/2) printf("|");
            else if(((j == p1->x) && (i == p1->y)) || ((j == p1->x) && (i == p1->y -1)) || ((j == p1->x) && (i == p1->y + 1))) printf("|");
            else if((i == HEIGHT_SCREEN - 1) && (j >= 1)) printf("-");// Печатаем нижную границу доски
            else if(i != 1 &&j == WIDTH_SCREEN -1) printf("|");
            else if(((j == p2->x) && (i == p2->y)) || ((j == p2->x) && (i == p2->y -1)) || ((j == p2->x) && (i == p2->y + 1))) printf("|");
            else printf(" ");
        }
        printf("\n");
    }
   
}

void Move_Rocket(char ch, P1 *p1, P2 *p2, Ball *ball)
{
    // Обработка движения ракетки первого игрока
    if(ch == A)
    {
        if((p1->y - 1) == 4)
        {
            p1->y = p1->y;
        }
        else
        {
            p1->y--;
        }
    }
    if(ch == Z)
    {
        if(p1->y + 1 == HEIGHT_SCREEN - 2)
        {
            p1->y = p1->y;
        }
        else
        {
        p1->y++;
        }
    }
    // Обработка движения ракетки второго игрока
    if(ch == K)
    {
        if(p2->y -1 == 4)
        {
            p2->y == p2->y;
        }
        else
        {
            p2->y--;
        }
    }
    if(ch == M)
    {
        if(p2->y + 1 == HEIGHT_SCREEN - 2)
        {
            p2->y = p2->y;
        }
        else
        {
            p2->y++;
        }
    }
}

void Move_Ball(char ch,P1 *p1, P2 *p2, Ball *ball)
{
    if(ch == ENTER)
    {
        ball->x += ball->directionX;
        ball->y += ball->directionY;
    }
    
    
}



void ClearScreen()
{
    printf("\33[0d\33[2J");
}
