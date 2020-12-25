
/*************************************************************************************************/
/***************************** RANDOM SUDOKU GENERATOR *******************************************/
/*************************************************************************************************/
/****************************** BY : VAIBHAV CHOUDHARY *******************************************/
/*************************************************************************************************/

#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>

using namespace std;
#define N 9

// SUDOKU GRID 9 * 9
int grid[N][N];
int ans[N][N];
int puzz[N][N];

// FUNCTION DECLARATION
void initialize();
bool randomSudoku();
unordered_set<int> generate_set();
bool get_RC(int &row, int &col);
bool isSafe(int i, int j, int num);
bool isSafe_Box(int row, int col, int num);
bool isSafe_RC(int row, int col, int num);
void Special_print(int grid[N][N]);
int count_Solution(int & ans);
void make_empty();
void make_more_empty();
void play_game();
void copy_grid(int grid[N][N], int (&ans)[N][N]);
void SetColor(int ForgC);
bool check_solved(int grid[N][N], int ans[N][N]);
void gotoxy(pair<int, int>);
void move_pos(char c, pair<int, int>& pos);
void move_up(pair<int, int>& pos);
void move_down(pair<int, int>& pos);
void move_left(pair<int, int>& pos);
void move_right(pair<int, int>& pos);
void clearscreen();

// MAIN DRIVER FUNCTION
int main()
{
    SetConsoleTitle("SUDOKU");
    initialize();
    randomSudoku();
    copy_grid(grid, ans);
    make_empty();
    make_more_empty();
    copy_grid(grid, puzz);
    play_game();
    system("pause");
    return 0;
}
// END OF MAIN

// RANDOM SUDOKU GENERATOR
bool randomSudoku()
{
    unordered_set<int> random_number = generate_set();
    int i, j;
    if(get_RC(i, j))
    {
        for (int num : random_number)
        {
            if (isSafe(i, j, num))
            {
                grid[i][j] = num;
                if (randomSudoku())
                    return true;
                else
                    grid[i][j] = 0;
            }
        }
    }
    else
        return true;
    return false;
}

// GENERATE RANDOM SET OF 9 VALUES
unordered_set<int> generate_set()
{
    srand(time(0));
    unordered_set<int> s;
    while(s.size() != 9)
    {
        int n = rand() % 9 + 1;
        s.insert(n);
    }
    return s;
}

// RETURNS EMPTY CELL AND ITS ROW AND COLUMN VALUE IF FOUND
bool get_RC(int &row, int &col)
{
    for (row = 0; row < N; row++)
    for (col = 0; col < N; col++)
        if (grid[row][col] == 0)
            return true;
    return false;
}

//FLICKER FREE SCREEN CLEARING
void clearscreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

// MAKING EMPTY GRID
void initialize()
{
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
        grid[i][j] = 0;
}

// CHECK FOR REDUNDANCY
bool isSafe(int i, int j, int num)
{
    return isSafe_RC(i, j, num) && isSafe_Box(i, j, num);
}

// CHECKS ROW AND COLUMNS FOR REDUNDANCY
bool isSafe_RC(int row, int col, int num)
{
    for (int i = 0; i < N; i++)
    {
        if (grid[row][i] == num)
                return false;
        if (grid[i][col] == num)
                return false;
    }
    return true;
}

// CHECKS 3 * 3 BOXES FOR REDUNDANCY
bool isSafe_Box(int row, int col, int num)
{
    int boxx = row / 3;
    int boxy = col / 3;

    for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
    {
        if (grid[boxx * 3 + i][boxy * 3 + j] == num)
            return false;
    }
    return true;
}

// FOR PRINTING GRID
void Special_print(int grid[N][N])
{
    system("color F1");
    SetColor(8);
    int j;
    cout << "\n\n";
    for (int i = 0; i < N; i++) {
        cout << "\t\t\t\t\t|";
        if ((i) % 3)
            cout << "-----------|-----------|-----------|\n\t\t\t\t\t||";
        else
            cout << "===========|===========|===========|\n\t\t\t\t\t||";
        for (int j = 0; j < N; j++)
        {
            if (j % 3 == 0)
                cout << "\b\b| ";
            if (grid[i][j]) {
                if (puzz[i][j]) {
                    SetColor(0);
                    cout << grid[i][j];
                    SetColor(8);
                }
                else {
                    SetColor(1);
                    cout << grid[i][j];
                    SetColor(8);
                }
            }
            else
                cout << " ";
            cout << " | ";
            if (j == N - 1)
                cout << "\b\b| ";
        }
        cout << "\b\n";
    }
    cout << "\t\t\t\t\t|===========|===========|===========|";
    cout << "\n\n\tINSTRUCTIONS : \n\t1 . USE A S D F TO MOVE.\n\t2 . USE DIGITS 1 - 9 TO FILL VALUES.\n\t3 . PRESS 0 TO EMPTY CELL\n\t";
}

// RETURNS NUMBER OF SOLUTIONS
int count_Solution(int & ans)
{
    int i, j;

    if (get_RC(i, j))
    {
        for (int num = 1; num <= N; num++)
        {
            if (isSafe(i, j, num))
            {
                grid[i][j] = num;
                int prev = ans;
                ans = count_Solution(ans);
                    grid[i][j] = 0;
            }
        }
    }
    else
        ans++;
    return ans;
}

// CLEARS CELLS
void make_empty()
{
    srand(time(0));
    int i = 0, j = 0;
    while(grid[i][j] == 0)
    {
        i = rand() % 9;
        j = rand() % 9;
    }
    int val = grid[i][j];
    grid[i][j] = 0;
    int a = 0;
    if (count_Solution(a) == 1)
        make_empty();
    else
        grid[i][j] = val;
}

// CLEARS MORE CELLS
void make_more_empty()
{
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    {
        int a = 0;
        int val = grid[i][j];
        grid[i][j] = 0;
        if(count_Solution(a) == 1)
            continue;
        else
            grid[i][j] = val;
    }
}

//COPY ONE GRID TO ANOTHER
void copy_grid(int grid[N][N], int (&ans)[N][N])
{
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
        ans[i][j] = grid[i][j];
}
//SETS FONT COLOR
void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

//CHECK IF CUDOKU IS SOLVED COMPLETELY
bool check_solved(int grid[N][N], int ans[N][N])
{
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
        if (grid[i][j] != ans[i][j])
            return false;
    return true;
}

//GAME CONTROLLER FUNCTION
void play_game()
{
    pair <int, int> pos{0,0};
    while (!check_solved(grid, ans))
    {
        clearscreen();
        Special_print(grid);
        SetColor(4);
        gotoxy(pos);
        char c;
        c = _getch();
        if (c == 'a' || c == 'w' || c == 's' || c == 'd' || c == 'A' || c == 'W' || c == 'S' || c == 'D')
        {
            move_pos(c, pos);
        }
        else if (c >= '0' && c <= '9')
        {
            if(!puzz[pos.second][pos.first])
                grid[pos.second][pos.first] = c - '0';
        }
    }
    cout << "\n\n \t\t\t\t\t CONGRATULATIONS!!!! YOU WON";
    char c = getchar();
        return;
}

//CHANGES CURSOR POSITION
void gotoxy(pair<int, int> pos)
{
    COORD coord;
    coord.X = pos.first * 4 + 42;
    coord.Y = pos.second * 2 + 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//DIRECTING FUNCTION TO MOVE POINTER
void move_pos(char c, pair<int, int>& pos)
{
    if(toupper(c) == 'A')
        move_left(pos);
    if(toupper(c) == 'W')
        move_up(pos);
    if(toupper(c) == 'D')
        move_right(pos);
    if(toupper(c) == 'S')
        move_down(pos);
}

//MOVES POINTER UP
void move_up(pair<int, int>& pos)
{
    if (pos.second != 0)
        --pos.second;
    else
        pos.second = 8;
        gotoxy(pos);
}

//MOVES POINTER DOWN
void move_down(pair<int, int>& pos)
{
    if (pos.second != 8)
        ++pos.second;
    else
        pos.second = 0;
        gotoxy(pos);
}

// MOVES POINTER TO LEFT
void move_left(pair<int, int>& pos)
{
    if (pos.first != 0)
        --pos.first;
    else
        pos.first = 8;
        gotoxy(pos);
}

// MOVES POINTER TO RIGHT
void move_right(pair<int, int>& pos)
{
    if (pos.first != 8)
        ++pos.first;
    else
        pos.first = 0;
        gotoxy(pos);
}


