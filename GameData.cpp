#include "GameData.h"

short A[8];
short B[8];

int Pawn(GameData& Game, int FR,int FC,int TR,int TC ){         //EN-PASSANT also here in this function


    if(Game.TurningPlayer==WHITE)
    {
        if(Game.Board[TR][TC].Code==NONE && TR==FR-1 && TC==FC)
        {
            return 1;
        }
        if(Game.Board[TR][TC].Code==NONE && Game.Board[FR-1][FC].Code==NONE && TC==FC && TR==FR-2 && FR==6)
        {
            return 1;
        }
        if(Game.Board[TR][TC].PieceColor!=Game.TurningPlayer && Game.Board[TR][TC].Code!=NONE && TR==FR-1 && TC==FC+1)
        {
            A[0]=TR;
            B[0]=TC;
            return 1;
        }
        if(Game.Board[TR][TC].PieceColor!=Game.TurningPlayer && Game.Board[TR][TC].Code!=NONE && TR==FR-1 && TC==FC-1)
        {
            A[0]=TR;
            B[0]=TC;
            return 1;
        }

        //EN-PASSANT

        if(Game.Board[FR][FC].Code==PAWN && Game.Board[FR][FC].PieceColor==Game.TurningPlayer && Game.Board[FR][FC+1].Code==PAWN
           && Game.Board[FR][FC+1].PieceColor!=Game.TurningPlayer && Game.Board[FR][FC+1].PieceColor!=NONE
            && Game.Board[TR][TC].Code==NONE && TR==FR-1 && TC==FC+1)
        {

            Game.Board[FR][FC+1].Code==NONE;
            return 1;
        }
        if(Game.Board[FR][FC].Code==PAWN && Game.Board[FR][FC].PieceColor==Game.TurningPlayer && Game.Board[FR][FC-1].Code==PAWN
           && Game.Board[FR][FC-1].PieceColor!=Game.TurningPlayer && Game.Board[TR][TC].Code==NONE && Game.Board[FR][FC+1].PieceColor!=NONE
            && TR==FR-1 && TC==FC-1)
        {

            Game.Board[FR][FC-1].Code==NONE;
            return 1;
        }
        return 0;
    }
    if(Game.TurningPlayer==BLACK)
    {
        if(Game.Board[TR][TC].Code==NONE && TR==FR+1 && TC==FC)
        {
            return 1;
        }
        if(Game.Board[TR][TC].Code==NONE && Game.Board[FR+1][FC].Code==NONE && TC==FC && TR==FR+2 && FR==1)
        {
            return 1;
        }
        if(Game.Board[TR][TC].PieceColor!=Game.TurningPlayer && Game.Board[TR][TC].Code!=NONE && TR==FR+1 && TC==FC+1)
        {
            A[0]=TR;
            B[0]=TC;
            return 1;
        }
        if(Game.Board[TR][TC].PieceColor!=Game.TurningPlayer && Game.Board[TR][TC].Code!=NONE && TR==FR+1 && TC==FC-1)
        {
            A[0]=TR;
            B[0]=TC;
            return 1;
        }

        //EN-PASSANT

        if(Game.Board[FR][FC].Code==PAWN && Game.Board[FR][FC].PieceColor==Game.TurningPlayer && Game.Board[FR][FC+1].Code==PAWN
           && Game.Board[FR][FC+1].PieceColor!=Game.TurningPlayer && Game.Board[FR][FC+1].PieceColor!=NONE
           && Game.Board[TR][TC].Code==NONE && TR==FR+1 && TC==FC+1)
        {

            Game.Board[FR][FC+1].Code==NONE;
            return 1;
        }
        if(Game.Board[FR][FC].Code==PAWN && Game.Board[FR][FC].PieceColor==Game.TurningPlayer && Game.Board[FR][FC-1].Code==PAWN
           && Game.Board[FR][FC-1].PieceColor!=Game.TurningPlayer && Game.Board[FR][FC+1].PieceColor!=NONE
           && Game.Board[TR][TC].Code==NONE && TR==FR+1 && TC==FC-1)
        {

            Game.Board[FR][FC-1].Code==NONE;
            return 1;
        }
        return 0;
    }

    return 0;

}

int Rook(GameData& Game, int i, int j, int Ni, int Nj ){

    if(i>Ni && Nj==j){         //Vertically Upward
        for(int k=i-1,x=0;k>Ni;k--,x++)
        {
            A[x]=k;
            B[x]=Nj;
            if(Game.Board[k][Nj].Code!=NONE)
            {
                return 0;
            }
        }
        if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
        {
            //Game.Board[i][j].MoveCount=1;
            return 1;
        }
        return 0;
    }

    if(i<Ni && Nj==j){        //Vertically Downward
       for(int k=i+1,x=0;k<Ni;k++,x++)
       {
            A[x]=k;
            B[x]=Nj;
            if(Game.Board[k][Nj].Code!=NONE)
            {
                return 0;
            }
       }
       if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
        {
            //Game.Board[i][j].MoveCount=1;
            return 1;
        }
        return 0;
    }

    if(i==Ni && Nj>j){         //Horizontally Rightward
        for(int k=j+1,x=0;k<Nj;k++,x++)
        {
            A[x]=Ni;
            B[x]=k;
            if(Game.Board[Ni][k].Code!=NONE)
            {
                return 0;
            }
        }
        if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
        {
            //Game.Board[i][j].MoveCount=1;
            return 1;
        }
        return 0;
    }

    if(i==Ni && Nj<j){          //Horizontally Leftward
        for(int k=j-1,x=0;k>Nj;j--,x++)
        {
            A[x]=Ni;
            B[x]=k;
            if(Game.Board[Ni][k].Code!=NONE)
            {
                return 0;
            }
        }
        if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
        {
            //Game.Board[i][j].MoveCount=1;
            return 1;
        }
        return 0;
    }


}

int Knight(GameData& Game, int i, int j, int Ni, int Nj ){

    if(Ni==i-1 && Nj==j+2)
    {
        A[0]=Ni;
        B[0]=Nj;
        if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
            return 1;
    }
    if(Ni==i-1 && Nj==j-2)
    {
        A[0]=Ni;
        B[0]=Nj;
        if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
            return 1;
    }

    if(Ni==i+1 && Nj==j+2)
    {
        A[0]=Ni;
        B[0]=Nj;
        if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
            return 1;
    }
    if(Ni==i+1 && Nj==j-2)
    {
        A[0]=Ni;
        B[0]=Nj;
        if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
            return 1;
    }

    if(Ni==i-2 && Nj==j+1)
    {
        A[0]=Ni;
        B[0]=Nj;
        if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
            return 1;
    }

    if(Ni==i-2 && Nj==j-1)
    {
        A[0]=Ni;
        B[0]=Nj;
        if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
            return 1;
    }

    if(Ni==i+2 && Nj==j+1)
    {
        A[0]=Ni;
        B[0]=Nj;
        if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
            return 1;
    }
    if(Ni==i+2 && Nj==j-1)
    {
        A[0]=Ni;
        B[0]=Nj;
        if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
            return 1;
    }

    return 0;

}

int Bishop(GameData& Game, int i, int j, int Ni, int Nj ){

    int Di=Ni-i;
    int Dj=Nj-j;
    if(i>Ni)
    {
        Di=i-Ni;
    }
    if(j>Nj)
    {
        Dj=j-Nj;
    }

    if(Di==Dj)
    {
        if(i>Ni && j<Nj)
        {
            for(int k=i-1,x=0,c=j+1;k>Ni;k--,c++,x++)
            {
                A[x]=k;
                B[x]=c;
                if(Game.Board[k][c].Code!=NONE)
                {
                    return 0;
                }
            }
            if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
            {
                return 1;
            }
        }

        if(i>Ni && j>Nj)
        {
            for(int k=i-1,x=0,c=j-1;k>Ni;k--,c--,x++)
            {
                A[x]=k;
                B[x]=c;
                if(Game.Board[k][c].Code!=NONE)
                {
                    return 0;
                }
            }
            if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
            {
                return 1;
            }
        }

        if(i<Ni && j>Nj)
        {
            for(int k=i+1,c=j-1,x=0;k<Ni;k++,c--,x++)
            {
                A[x]=k;
                B[x]=c;
                if(Game.Board[k][c].Code!=NONE)
                {
                    return 0;
                }
            }
            if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
            {
                return 1;
            }
        }

        if(i<Ni && j<Nj)
        {
            for(int k=i+1,c=j+1,x=0;k<Ni;k++,c++,x++)
            {
                A[x]=k;
                B[x]=c;
                if(Game.Board[k][c].Code!=NONE)
                {
                    return 0;
                }
            }
            if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
            {
                return 1;
            }
        }
        return 0;
    }
}

int Queen(GameData& Game, int i, int j, int Ni, int Nj ){

    int k=Rook(Game,i,j,Ni,Nj);
    int q=Bishop(Game,i,j,Ni,Nj);

    if(k==1 || q==1)
    {
        return 1;
    }
    return 0;

}

int King(GameData& Game, int i, int j, int Ni, int Nj ){       //Castling is also here in this function

    for(int k=i-1;k<=i+1;k++)
    {
        for(int p=j-1;p<=j+1;p++)
        {
            if(k==Ni && p==Nj)
            {
                if(Game.Board[Ni][Nj].PieceColor!=Game.TurningPlayer || Game.Board[Ni][Nj].Code==NONE)
                {
                    A[0]=Ni;
                    B[0]=Nj;
                    if(!isfacingCheck(Game,Game.TurningPlayer))
                    {
                        return 1;
                    }
                }
            }
        }
    }


    if(Game.Board[i][j].Code==KING && Game.Board[Ni][Nj].Code==NONE && Ni==i && Nj==j+2)
    {
        Game.Board[Ni][Nj].Code=KING;
        Game.Board[Ni][Nj].PieceColor=Game.TurningPlayer;
        Game.Board[i][j].Code=NONE;
        if(isfacingCheck(Game,Game.TurningPlayer))
        {
            Game.Board[i][j].Code=KING;
            Game.Board[i][j].PieceColor=Game.TurningPlayer;
            Game.Board[Ni][Nj].Code=NONE;
            goto K_4_King;
        }
        else
        {
            Game.Board[i][j].Code=KING;
            Game.Board[i][j].PieceColor=Game.TurningPlayer;
            Game.Board[Ni][Nj].Code=NONE;
        }
    }

    if(Game.Board[i][j].Code==KING && Ni==i && Game.Board[i][j+1].Code==NONE
       && Game.Board[i][j+2].Code==NONE
       && Game.Board[i][j+3].Code==ROOK && Nj==j+2 && isfacingCheck(Game,Game.TurningPlayer)==false)
    {
        Game.Board[i][j+1].Code=ROOK;
        Game.Board[i][j+1].PieceColor=Game.TurningPlayer;
        Game.Board[i][j+3].Code=NONE;

            return 1;

    }
    if(Game.Board[i][j].Code==KING && Ni==i && Game.Board[i][j-1].Code==NONE
       && Game.Board[i][j-2].Code==NONE
       && Game.Board[i][j-4].Code==ROOK && Nj==j-2 && isfacingCheck(Game,Game.TurningPlayer)==false)
    {
        Game.Board[i][j-1].Code=ROOK;
        Game.Board[i][j-1].PieceColor=Game.TurningPlayer;
        Game.Board[i][j-4].Code=NONE;

            return 1;

    }

    K_4_King:

    return 0;

}

bool isValidMove(GameData& Game, chessMove Move){
    // this function will return true if the move specified by the Move parameter is a valid move
    // You might make more functions to breakdown the task of this function into subtasks
    int FR, FC, TR, TC;
    int k;
    FR = Move.FromRow;
    FC = Move.FromColumn;
    TR = Move.ToRow;
    TC = Move.ToColumn;

    for(int i=0;i<8;i++)
       A[i]=B[i]=-1;
    if(Game.Board[FR][FC].Code==PAWN)
        k=Pawn(Game,FR,FC,TR,TC);
        if(k==1)
            return true;

    if(Game.Board[FR][FC].Code==KNIGHT)
        k=Knight(Game,FR,FC,TR,TC);
        if(k==1)
            return true;

    if(Game.Board[FR][FC].Code==ROOK)
        k=Rook(Game,FR,FC,TR,TC);
        if(k==1)
            return true;

    if(Game.Board[FR][FC].Code==BISHOP)
        k=Bishop(Game,FR,FC,TR,TC);
        if(k==1)
            return true;

    if(Game.Board[FR][FC].Code==QUEEN)
        k=Queen(Game,FR,FC,TR,TC);
        if(k==1)
            return true;

    if(Game.Board[FR][FC].Code==KING)
        k=King(Game,FR,FC,TR,TC);
        if(k==1)
            return true;

    for(int i=0;i<8;i++)
       A[i]=B[i]=-1;

    return false;
}

int MakeMove(GameData& Game, chessMove Move){
    //Function to make a move on the board
    // It will return 0 if the move is valid and a code of error to specify why the move is not valid otherwise

	// Following is a very simple move example. Your code will support all types of moves including pawn promotion, castling and En Passant etc. Furthermore i must also add the move in the vector of moves used for keeping history.

	if(!isValidMove(Game, Move))
        return 1;

    int FR, FC, TR,TC;
    FR = Move.FromRow;
    FC = Move.FromColumn;
    TR = Move.ToRow;
    TC = Move.ToColumn;

    if(Game.Board[FR][FC].Code==KING || Game.Board[FR][FC].Code==ROOK)
    {
        Game.Board[FR][FC].MoveCount++;
    }


    Game.Board[TR][TC].Code =
         Game.Board[FR][FC].Code;
    Game.Board[TR][TC].PieceColor =
         Game.Board[FR][FC].PieceColor;
    Game.Board[FR][FC].Code = NONE;

    if(Game.TurningPlayer == BLACK)
        Game.TurningPlayer = WHITE;
    else
        Game.TurningPlayer = BLACK;



	return 0;


}

void initGame(GameData& Game){

    for(int r = 0; r < 2; r++)
        for(int c= 0; c < 8; c++ )
            Game.Board[r][c].PieceColor = BLACK;

    for(int r = 2; r < 6; r++)
        for(int c= 0; c < 8; c++ )
            Game.Board[r][c].Code = NONE;

    for(int r = 6; r < 8; r++)
        for(int c= 0; c < 8; c++ )
            Game.Board[r][c].PieceColor = WHITE;

    /*for(int r = 0; r < 8; r++)
        for(int c= 0; c < 8; c++ )
            Game.Board[r][c].MoveCount = 0;*/


    Game.Board[0][0].Code = Game.Board[0][7].Code = ROOK;
    Game.Board[7][0].Code = Game.Board[7][7].Code = ROOK;

    Game.Board[0][1].Code = Game.Board[0][6].Code = KNIGHT;
    Game.Board[7][1].Code = Game.Board[7][6].Code = KNIGHT;

    Game.Board[0][2].Code = Game.Board[0][5].Code = BISHOP;
    Game.Board[7][2].Code = Game.Board[7][5].Code = BISHOP;

    Game.Board[0][3].Code = Game.Board[7][3].Code = QUEEN;
    Game.Board[0][4].Code = Game.Board[7][4].Code = KING;

    for(int c= 0; c < 8; c++ )
        Game.Board[1][c].Code = Game.Board[6][c].Code = PAWN;

    Game.TurningPlayer = WHITE;

    Game.MoveHistory = vector<chessMove>(1);
    return;
}

bool isfacingCheck(GameData& Game, Color Player){
    // This function must return true if player having Color Player is facing a check


    int Ni,Nj;
    chessMove Move;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(Game.Board[i][j].Code==KING && Game.Board[i][j].PieceColor==Game.TurningPlayer)
            {
                Ni=i;
                Nj=j;
            }
        }
    }


    if(Game.TurningPlayer == BLACK)
        Game.TurningPlayer = WHITE;
    else
        Game.TurningPlayer = BLACK;

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            Move.FromRow=i;
            Move.FromColumn=j;
            Move.ToRow=Ni;
            Move.ToColumn=Nj;
            if(Game.Board[i][j].PieceColor==Game.TurningPlayer)
            {
                if(isValidMove(Game,Move))
                {
                    //cout<<i<<" "<<j<<endl;
                    if(Game.TurningPlayer == BLACK)
                        Game.TurningPlayer = WHITE;
                    else
                        Game.TurningPlayer = BLACK;

                    return true;
                }
            }
        }
    }

    if(Game.TurningPlayer == BLACK)
        Game.TurningPlayer = WHITE;
    else
        Game.TurningPlayer = BLACK;

    return false;
}

bool isCheckmate(GameData& Game, Color Player){
    // This function must return true if player having Color Player is facing a checkmate

    int Ni,Nj;
    chessMove Move;

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(Game.Board[i][j].Code==KING && Game.Board[i][j].PieceColor==Game.TurningPlayer)
            {
                Ni=i;
                Nj=j;
            }
        }
    }
    int t=0,e,f;

    for(int k=Ni-1;k<=Ni+1;k++)
    {
        for(int p=Nj-1;p<=Nj+1;p++)
        {
            Move.FromRow=Ni;
            Move.FromColumn=Nj;
            Move.ToRow=k;
            Move.ToColumn=p;

            if(isValidMove(Game,Move))
            {
                e=k;
                f=p;
                if(!isfacingCheck(Game,Game.TurningPlayer))
                {
                    t=1;
                    return false;
                }
            }
        }
    }

    /*for(int a=0;a<8;a++)
    {
        for(int b=0;b<8;b++)
        {
            if(Game.Board[a][b].PieceColor==Game.TurningPlayer)
            {
                Move.FromRow=a;
                Move.FromColumn=b;
                for(int i=0,j=0;A[i]>=0;i++,j++)
                {
                    Move.ToRow=A[i];
                    Move.ToColumn=B[j];
                    if(isValidMove(Game,Move))
                    {
                        return false;
                    }
                }
            }
        }
    }*/



    /*if(Game.TurningPlayer == BLACK)
        Game.TurningPlayer = WHITE;
    else
        Game.TurningPlayer = BLACK;*/

    return false;

}


