// C++ program to find the next optimal move for
// a player
#include<bits/stdc++.h>
using namespace std;
#define SIDE 3 
struct Move
{
	int row, col;
};

char player = 'x', opponent = 'o';
char board[3][3] =
	{
		{ '_', '_', '_' },
		{ '_', '_', '_' },
		{ '_', '_', '_' }
	};
// This function returns true if there are moves
// remaining on the board. It returns false if
// there are no moves left to play.
bool isMovesLeft(char board[3][3])
{
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
			if (board[i][j]=='_')
				return true;
	return false;
}
map<int,pair<int,int>>mp{

	{1,{0,0}},
	{2,{0,1}},
	{3,{0,2}},
	{4,{1,0}},
	{5,{1,1}},
	{6,{1,2}},
	{7,{2,0}},
	{8,{2,1}},
	{9,{2,2}},

} ;



void showInstructions()
{
    printf("\t\t\t  Tic-Tac-Toe\n\n");
    printf("Choose a cell numbered from 1 to 9 as below"
            " and play\n\n");
      
    printf("\t\t\t  1 | 2  | 3  \n");
    printf("\t\t\t--------------\n");
    printf("\t\t\t  4 | 5  | 6  \n");
    printf("\t\t\t--------------\n");
    printf("\t\t\t  7 | 8  | 9  \n\n");
      
    printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");
  
    return;
}
void showBoard(char board[][3])
{
    printf("\n\n");
      
    printf("\t\t\t  %c | %c  | %c  \n", board[0][0],
                             board[0][1], board[0][2]);
    printf("\t\t\t--------------\n");
    printf("\t\t\t  %c | %c  | %c  \n", board[1][0],
                             board[1][1], board[1][2]);
    printf("\t\t\t--------------\n");
    printf("\t\t\t  %c | %c  | %c  \n\n", board[2][0],
                             board[2][1], board[2][2]);
   
    return;
}
bool rowCrossed(char board[][SIDE])
{
    for (int i=0; i<SIDE; i++)
    {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] && 
            board[i][0] != '_')
            return (true);
    }
    return(false);
}
  
// A function that returns true if any of the column
// is crossed with the same player's move
bool columnCrossed(char board[][SIDE])
{
    for (int i=0; i<SIDE; i++)
    {
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i] && 
            board[0][i] != '_')
            return (true);
    }
    return(false);
}
  
// A function that returns true if any of the diagonal
// is crossed with the same player's move
bool diagonalCrossed(char board[][SIDE])
{
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] && 
        board[0][0] != '_')
        return(true);
          
    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
         board[0][2] != '_')
        return(true);
  
    return(false);
}
  
// A function that returns true if the game is over
// else it returns a false
bool gameOver(char board[][3])
{
    return(rowCrossed(board) || columnCrossed(board)
            || diagonalCrossed(board) );
}
// This is the evaluation function as discussed
// in the previous article ( http://goo.gl/sJgv68 )
int evaluate(char b[3][3])
{
	// Checking for Rows for X or O victory.
	for (int row = 0; row<3; row++)
	{
		if (b[row][0]==b[row][1] &&
			b[row][1]==b[row][2])
		{
			if (b[row][0]==player)
				return +10;
			else if (b[row][0]==opponent)
				return -10;
		}
	}

	// Checking for Columns for X or O victory.
	for (int col = 0; col<3; col++)
	{
		if (b[0][col]==b[1][col] &&
			b[1][col]==b[2][col])
		{
			if (b[0][col]==player)
				return +10;

			else if (b[0][col]==opponent)
				return -10;
		}
	}

	// Checking for Diagonals for X or O victory.
	if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
	{
		if (b[0][0]==player)
			return +10;
		else if (b[0][0]==opponent)
			return -10;
	}

	if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
	{
		if (b[0][2]==player)
			return +10;
		else if (b[0][2]==opponent)
			return -10;
	}

	// Else if none of them have won then return 0
	return 0;
}

// This is the minimax function. It considers all
// the possible ways the game can go and returns
// the value of the board
int minimax(char board[3][3], int depth, bool isMax)
{
	int score = evaluate(board);

	// If Maximizer has won the game return his/her
	// evaluated score
	if (score == 10)
		return score;

	// If Minimizer has won the game return his/her
	// evaluated score
	if (score == -10)
		return score;

	// If there are no more moves and no winner then
	// it is a tie
	if (isMovesLeft(board)==false)
		return 0;

	// If this maximizer's move
	if (isMax)
	{
		int best = -1000;

		// Traverse all cells
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				// Check if cell is empty
				if (board[i][j]=='_')
				{
					// Make the move
					board[i][j] = player;

					// Call minimax recursively and choose
					// the maximum value
					best = max( best,
						minimax(board, depth+1, !isMax) );

					// Undo the move
					board[i][j] = '_';
				}
			}
		}
		return best;
	}

	// If this minimizer's move
	else
	{
		int best = 1000;

		// Traverse all cells
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				// Check if cell is empty
				if (board[i][j]=='_')
				{
					// Make the move
					board[i][j] = opponent;

					// Call minimax recursively and choose
					// the minimum value
					best = min(best,
						minimax(board, depth+1, !isMax));

					// Undo the move
					board[i][j] = '_';
				}
			}
		}
		return best;
	}
}

// This will return the best possible move for the player
Move findBestMove(char board[3][3])
{
	int bestVal = -1000;
	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;

	// Traverse all cells, evaluate minimax function for
	// all empty cells. And return the cell with optimal
	// value.
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			// Check if cell is empty
			if (board[i][j]=='_')
			{
				// Make the move
				board[i][j] = player;

				// compute evaluation function for this
				// move.
				int moveVal = minimax(board, 0, false);

				// Undo the move
				board[i][j] = '_';

				// If the value of the current move is
				// more than the best value, then update
				// best/
				if (moveVal > bestVal)
				{
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}

	//printf("The value of the best Move is : %d\n\n",mp[bestVal].);

	return bestMove;
}

// Driver code
int main()
{


	//Move bestMove = findBestMove(board);
    int N = 9 ;

	//printf("The Optimal Move is :\n");
	//printf("ROW: %d COL: %d\n\n", bestMove.row,
	//							bestMove.col );
    int flag = 1 ; // 0 for computer and 1 for user
    int k ;
	showInstructions() ;
	std::cout<<"If you want to move firs then enter 1 otherwise enter 0"<<endl ;
	cin>>flag;
	showBoard(board) ;
    while(N--)
    {
        if( flag == 0 )
        {
			
            Move bestMove = findBestMove(board);
            board[bestMove.row][bestMove.col] = player ;
			std::cout<<"Computers move\t"<<endl;//bestMove.row<<bestMove.col<<endl ;
            showBoard(board) ;
            if(gameOver(board) )
            {
                std::cout<<player<<" HAS WON THE GAME \n" ;
                break ;
            }
            flag = 1 ;

        }
        else if( flag == 1 )
        {
            //Move bestMove = findBestMove(board);
            //board[bestMove.row][bestMove.row] = opponent 
            std::cout<<"Enter your move !\n";
			cin>>k ;

            board[mp[k].first ][mp[k].second ] = opponent ;
            showBoard(board) ;
            if(gameOver(board) )
            {
                std::cout<<opponent<<" HAS WON THE GAME \n" ;
                break ;
            }
            flag = 0 ;
        }


    }

    if( N == -1 )
        std::cout<<"Match Drawn \n"<<endl ;

	return 0;
}