#include<bits/stdc++.h>
using namespace std;

#define COMPUTER 1
#define HUMAN 2

#define SIDE 3

#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

void showBoard(char board[][SIDE])
{
    printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t-----------\n");
    printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t-----------\n");
    printf("\t\t\t %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

void showInstructions()
{
    cout<<"\nChoose a cell numbered from 1 to 9 to play in the respective position\n"<<endl;

    printf("\t\t\t 1 | 2 | 3 \n");
    printf("\t\t\t-----------\n");
    printf("\t\t\t 4 | 5 | 6 \n");
    printf("\t\t\t-----------\n");
    printf("\t\t\t 7 | 8 | 9 \n");
}

void initialise(char board[][SIDE])
{
    // Initially declaring all the values to *
    for(int i=0; i<SIDE; i++) 
    {
        for(int j=0; j<SIDE; j++) 
        {
            board[i][j] = '*';
        }  
    }   
}

void declareWinner(int whoseTurn)
{
    if(whoseTurn == COMPUTER)
        cout<<"The COMPUTER has WON!!"<<endl;
    else
        cout<<"The HUMAN has WON!!"<<endl;
}

bool rowCrossed(char board[][SIDE])
{
    if((board[0][0] == board[0][1]) && (board[0][1] == board[0][2]) && (board[0][0] != '*'))
        return true;

    else if((board[1][0] == board[1][1]) && (board[1][1] == board[1][2]) && (board[1][0] != '*'))
        return true;

    else if((board[2][0] == board[2][1]) && (board[2][1] == board[2][2]) && (board[2][0] != '*'))
        return true;
    
    else
        return false;    
}

bool columnCrossed(char board[][SIDE])
{
    if((board[0][0] == board[1][0]) && (board[1][0] == board[2][0]) && (board[0][0] != '*'))
        return true;

    else if((board[0][1] == board[1][1]) && (board[1][1] == board[2][1]) && (board[0][1] != '*'))
        return true;

    else if((board[0][2] == board[1][2]) && (board[1][2] == board[2][2]) && (board[0][2] != '*'))
        return true;
    
    else
        return false;
}

bool diagonalCrossed(char board[][SIDE])
{
    if((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) && (board[0][0] != '*'))
        return true;

    else if((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]) && (board[0][2] != '*'))
        return true;
    
    else
        return false;
}

bool gameOver(char board[][SIDE])
{
    return(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board));
}

int minimax(char board[][SIDE], int depth, bool isAI)
{
    int score = 0;
    int bestScore = 0;
    if(gameOver(board) == true)
    {
        if(isAI == true)
            return INT_MIN;
        else if(isAI == false)
            return INT_MAX;
    }
    else
    {
        if(depth < 9)
        {
            if(isAI == true)
            {
                bestScore = INT_MIN;
                for(int i=0; i<SIDE; i++)
                {
                    for(int j=0; j<SIDE; j++)
                    {
                        if(board[i][j] == '*')
                        {
                            board[i][j] = COMPUTERMOVE; 
                            score = minimax(board, depth+1, false);
                            board[i][j] = '*';
                            if(score > bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;                
            }
            else
            {
                bestScore = INT_MAX;
                for(int i=0; i<SIDE; i++)
                {
                    for(int j=0; j<SIDE; j++)
                    {
                        if(board[i][j] == '*')
                        {
                            board[i][j] = HUMANMOVE;
                            score = minimax(board, depth+1, true);
                            board[i][j] = '*';
                            if(score < bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
        }
        else
        {
            return 0;
        }
    }
}

int bestMove(char board[][SIDE], int moveIndex)
{
    int x = -1, y = -1;
    int score = 0, bestScore = INT_MIN;
    for(int i=0; i<SIDE; i++)
    {
        for(int j=0; j<SIDE; j++)
        {
            if(board[i][j] == '*')
            {
                board[i][j] = COMPUTERMOVE;
                score = minimax(board, moveIndex+1, false);
                board[i][j] = '*';
                if(score > bestScore)
                {
                    bestScore = score;
                    x = i; 
                    y = j;
                }
            }
        }
    }
    return x*3+y;
}

void playTTT(int whoseTurn)
{
    char board[SIDE][SIDE];
    int moveIndex = 0, x = 0, y = 0;

    initialise(board);
    showInstructions();

    while((gameOver(board)==false) && (moveIndex != SIDE*SIDE))
    {
        int n;
        if(whoseTurn==COMPUTER)
        {
            n = bestMove(board, moveIndex);
            x = n/SIDE;
            y = n%SIDE;
            board[x][y] = COMPUTERMOVE;
            cout<<"COMPUTER has played "<<COMPUTERMOVE<<" in cell "<<n+1<<endl;
            showBoard(board);
            moveIndex++;
            whoseTurn = HUMAN;
        }
        else if(whoseTurn = HUMAN)
        {
            cout<<"You can insert in the following positions : ";
            for(int i=0; i<SIDE; i++)
                for(int j=0; j<SIDE; j++)
                    if(board[i][j] == '*')
                        cout<<(i*3+j)+1<<" ";
            printf("\nEnter the position : ");
            cin>>n;
            n--;
            x = n/SIDE;
            y = n%SIDE;
            if((board[x][y] == '*') && (n<9 && n>=0))
            {
                board[x][y] = HUMANMOVE;
                cout<<"\nHUMAN has played "<<HUMANMOVE<<" in cell "<<n+1<<endl<<endl;
                showBoard(board);
                moveIndex++;
                whoseTurn = COMPUTER;
            }
            else if((board[x][y]!='*') && (n<9 && n>=0))
            {
                cout<<"The position is occupied please select any one place from available places"<<endl;
            }
            else if(n<0 || n>8)
            {
                cout<<"Invalid Position"<<endl;
            }
        }
    }

    if((gameOver(board) == false) && (moveIndex == SIDE*SIDE))
        cout<<"Its A DRAW!\n";
    else
    {
        if(whoseTurn == COMPUTER)
            whoseTurn  = HUMAN;
        else if(whoseTurn == HUMAN)
            whoseTurn  = COMPUTER;
            
        declareWinner(whoseTurn);
    }
}

int main()
{
    cout<<"_________________               _________________                         _________________                             "<<endl;
    cout<<"|               |               |               |                         |               |                             "<<endl;
    cout<<"|_____     _____|               |_____     _____|                         |_____     _____|                             "<<endl;
    cout<<"      |    |                          |    |                                    |    |                                  "<<endl;
    cout<<"      |    |                          |    |                                    |    |                                  "<<endl;
    cout<<"      |    |   __                     |    |                                    |    |                                  "<<endl;
    cout<<"      |    |  /_/   _________         |    |      ____       _________          |    |    __________     _________      "<<endl;
    cout<<"      |    |   _   |   ______|        |    |     / _  \\     |   ______|         |    |   |   ____   |   |   ___   |    "<<endl;
    cout<<"      |    |  | |  |  |               |    |    / /_\\  \\    |  |                |    |   |  |    |  |   |    _____|   "<<endl;
    cout<<"      |    |  | |  |  |______         |    |   / /___\\  \\   |  |______          |    |   |  |____|  |   |   |______   "<<endl;
    cout<<"      |____|  |_|  |_________|        |____|  /_/     \\ _\\  |_________|         |____|   |__________|   |__________|  "<<endl;
    char cont = 'y';
    do{
        char choice;
        cout<<"\n\nDo you want to start first ? (Enter 'y' for Yes and 'n' for No)   -->  ";
        cin>>choice;

        switch (choice)
        {
        case 'y':
            playTTT(HUMAN);
            break;
        case 'n':
            playTTT(COMPUTER);
            break;        
        default:
            cout<<"Invalid Input";
            break;
        }

        cout<<"\n\nDo you want to quit the game? (Enter 'y' for Yes and 'n' for No)  -->  ";
        cin>>cont;

    }while (cont == 'n');
    return 0;    
}