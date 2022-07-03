#include<stdio.h>

// Логические константы ////////////////////////////////////

#define TRUE 1
#define FALSE 0


#define WIDTH_SCREEN 82
#define HEIGHT_SCREEN 27

/* Настройки позиции рокетоок и мяча и его направления движения */
#define START_POSITION_P1_X 2
#define START_POSITION_P1_Y 14
#define START_POSITION_P2_X 78
#define START_POSITION_P2_Y 14
#define START_POSITION_BALL_X 40
#define START_POSITION_BALL_Y 14
#define START_DIRECTION_BALL_X -1
#define START_DIRECTION_BALL_Y 1
#define START_SCORE_P 0
#define SCORE_TO_WIN 21 // Потом поменяем на 21

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
#define Q 113
#define R 114
#define ENTER 10


// Игровые объекты  ///////////////////////////////////////////////////////////

// Структура игрокв //////////////////////////////////////////////////////////
typedef struct Player
{
    int x;
    int y;
    int score;
} Player;


// Структура Мяча ///////////////////////////////////////////////////////////

typedef struct Ball
{
    int x;
    int y;
    // Изначально мячик движется по напрявлению первого  игрока под углом 45 градусов в направлении правого нижнего угла
    int directionX; // Направление движения мачика по иксу
    int directionY; // Направление движения мячика по игрику
    
} Ball;

// ///////////////////////////////////////////////////////////////////////////

// Управляет игровым процессом
void Play(char key,Player *p1, Player *p2, Ball *ball);
void EndGame(char key,Player *p1, Player *p2, Ball *ball);

// ///////////////////////////////////////////////////////////////////////////

// Функции управления игровыми объектами
void Init_Objects(Player *p1, Player *p2, Ball *ball);
void Drow_Screen(Player *p1, Player *p2, Ball *ball);
void Move_Rocket(char ch, Player *p1, Player *p2, Ball *ball);
void Move_Ball(Player *p1, Player *p2, Ball *ball);

//  ////////////////////////////////////////////////////////////////////////

// Служебные функции

// Функция очистки экрана
void ClearScreen();
//  ////////////////////////////////////////////////////////////////////////
int main() {
    
    Player p1;
    Player p2;
    Ball ball;
    /* Инициализируем положения рокеток и положение мяча  */
    Init_Objects(&p1, &p2, &ball);
    
    
    
    while(1)
    {
        Drow_Screen(&p1, &p2, &ball);
        char key = getchar();
        if(key != Q)
        {
            if((p1.score != SCORE_TO_WIN) && (p2.score != SCORE_TO_WIN)) Play(key, &p1, &p2, &ball);
            else EndGame(key, &p1, &p2, &ball);
            ClearScreen();
        }
        else
        {
            break;
        }
    }
    
    return 0;
}


void Init_Objects(Player *p1, Player *p2, Ball *ball)
{
    /* Инициализируем положения рокеток и положение мяча  */
    p1->x = START_POSITION_P1_X;
    p1->y = START_POSITION_P2_Y;
    p1->score = START_SCORE_P;
    p2->x = START_POSITION_P2_X;
    p2->y = START_POSITION_P2_Y;
    p2->score = START_SCORE_P;
    ball->x = START_POSITION_BALL_X;
    ball->y = START_POSITION_BALL_Y;
    ball->directionX = START_DIRECTION_BALL_X;
    ball->directionY = START_DIRECTION_BALL_Y;
}

void Drow_Screen(Player *p1, Player *p2, Ball *ball)
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
            else if(i == 1 && j == START_INPUT_TO_EXIT)
            {
                if(p1->score == SCORE_TO_WIN || p2->score == SCORE_TO_WIN)
                {
                    printf("Please enter r to reset q exit");
                }
                else
                {
                    printf("Please enter q to exit        ");
                }
            }
           
            else if(i == 1 && j == START_PLAYER_SCORE)
            {
                if(p1->score == SCORE_TO_WIN) printf("player1: WIN  |  player2: LOSS  |");
                else if(p2->score == SCORE_TO_WIN) printf("player1: LOSS |  player2: WIN  |");
                else printf("player1: %d  |  player2: %d      |", p1->score, p2->score);
            }
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

void Move_Rocket(char ch, Player *p1, Player *p2, Ball *ball)
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

void Move_Ball(Player *p1, Player *p2, Ball *ball)
{
    if(ball->y == HEIGHT_SCREEN - 2)
    {
        ball->directionY = (-1)*ball->directionY;
        ball->x += ball->directionX;
        ball->y += ball->directionY;
    }
    else if(ball->y == 4)
    {
        ball->directionY = (-1)*ball->directionY;
        ball->x += ball->directionX;
        ball->y += ball->directionY;
    }
    else if((ball->x == p2->x-1) && (ball->y == p2->y-1 || ball->y == p2->y || ball->y == p2->y+1))
    {
        ball->directionX = (-1)*ball->directionX;
        ball->x += ball->directionX;
        ball->y += ball->directionY;
    }
    else if((ball->x == p1->x+1) && (ball->y == p1->y-1 || ball->y == p1->y || ball->y == p1->y+1))
    {
        ball->directionX = (-1)*ball->directionX;
        ball->x += ball->directionX;
        ball->y += ball->directionY;
    }
    else if(ball->x == 0)
    {
        p2->score++;
        // Направление движения мяча выставлено в сторону проигравшего
        ball->directionX = -1;
        ball->directionY = 1;
        // Устанавливаем позицию в начало
        ball->x = START_POSITION_BALL_X;
        ball->y = START_POSITION_BALL_Y;
    }
    else if(ball->x == WIDTH_SCREEN - 1)
    {
        p1->score++;
            
        // Направление движения мяча выставлено в сторону проигравшего
        ball->directionX = 1;
        ball->directionY = 1;
            
        // Устанавливаем позицию в начало
        ball->x = START_POSITION_BALL_X;
        ball->y = START_POSITION_BALL_Y;
    }
    else
    {
        ball->x += ball->directionX;
        ball->y += ball->directionY;
    }
    
    
}


void Play(char key, Player *p1, Player *p2, Ball *ball)
{
    if(key == ENTER) Move_Ball(p1, p2, ball);
    else if(key == A || key == Z || key == K || key == M)
    {
        Move_Rocket(key,p1, p2, ball);
        Move_Ball(p1, p2, ball);
    }
}


void EndGame(char key,Player *p1, Player *p2, Ball *ball)
{
    Drow_Screen(p1, p2, ball);
    if(key == R) Init_Objects(p1, p2, ball);
}

void ClearScreen()
{
    printf("\33[0d\33[2J");
}
