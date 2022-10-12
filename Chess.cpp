#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>

#include "GameData.cpp"
//#include "Player.cpp"

using namespace std;

struct Chess{
    GameData GameState;
    string PlayerNames[2];
    bool GameActive = false;
} Game;

string getPlayerinfo(){
    string Name="";
    cout<< "\nEnter Player Name\n";
    do{
        cin.clear();
        fflush(stdin);
        getline(cin, Name);
    }while(Name.length() == 0);
    return Name;
}

int SaveGame(){
    // If we have an active game then save it for future along with player names
    // The function will ask the user to specify a file name and save the entire game into it

   ofstream out("Data.txt");

    out<<Game.PlayerNames[0]<<endl<<Game.PlayerNames[1]<<endl;
   //if(!out)
   // return -1;

   for(int i = 0;i< 8;i++  )
   {
       for(int j =0 ; j< 8 ;j++)
       {
        out<<Game.GameState.Board[i][j].PieceColor<<" "<<Game.GameState.Board[i][j].Code<<" ";
       }
        out<<endl;
   }

   out.close();

    return 0;
}

int LoadGame(){
    // The function will ask the user to specify a file name and save the entire game into it

    ifstream load;
    load.open("Data.txt");
    if(load.fail())
    {
        cout<<"File not found";
        return -2;
    }

    load>>Game.PlayerNames[0]>>Game.PlayerNames[1];

    int n,m;
    for(int i = 0 ; i< 8;i++)
    {
        for(int j=0;j<8;j++)
        {
            load >> n;
            //cout<<n<<" ";
            switch(n)
            {
                case 0:
                {
                    Game.GameState.Board[i][j].PieceColor = BLACK;
                    //cout<<Game.GameState.Board[i][j].PieceColor<<" ";
                    break;
                }
                case 1:
                {
                    Game.GameState.Board[i][j].PieceColor = WHITE;
                    //cout<<Game.GameState.Board[i][j].PieceColor<<" ";
                    break;
                }
            }
            load >> m;
            //cout<<m<<" ";
            switch(m)
            {
                case 0:
                {
                    Game.GameState.Board[i][j].Code = NONE;
                    break;
                }
                case 1:
                {
                    Game.GameState.Board[i][j].Code = PAWN;
                    break;
                }
                case 2:
                {
                    Game.GameState.Board[i][j].Code = ROOK;
                    break;
                }
                case 3:
                {
                    Game.GameState.Board[i][j].Code = BISHOP;
                    break;
                }
                case 4:
                {
                    Game.GameState.Board[i][j].Code = KNIGHT;
                    break;
                }
                case 5:
                {
                    Game.GameState.Board[i][j].Code = QUEEN;
                    break;
                }
                case 6:
                {
                    Game.GameState.Board[i][j].Code = KING;
                    break;
                }
            }
        }
    }

    load.close();
    return 0;
}

void ShowGame(){

    cout<< Game.PlayerNames[1]<<"\tvs\t"<<Game.PlayerNames[0]<<endl;

    for(int r = 0; r < 8; r++ ){
        cout<<endl<<r;
        for(int c = 0; c < 8; c++){
            switch(Game.GameState.Board[r][c].Code){
                case NONE:
                    cout<<"\t..";
                break;
                default:
                    cout<<"\t";
                    if(Game.GameState.Board[r][c].PieceColor == BLACK)
                        cout<<"B";
                    else
                        cout<<"W";

                    switch(Game.GameState.Board[r][c].Code){
                    case PAWN:
                        cout<<"P";
                    break;

                    case ROOK:
                        cout<<"R";
                    break;

                    case KNIGHT:
                        cout<<"kN";
                    break;

                    case BISHOP:
                        cout<<"B";
                    break;

                    case QUEEN:
                        cout<<"Q";
                    break;

                    case KING:
                        cout<<"K";
                    break;
                    }
                break;
            }
        }
        cout<<endl<<endl;
    }
    cout<<endl;
    for(int c = 0; c< 8; c++)
        cout<<"\t"<<c;
    cout<<"\n";
}

void initNewGame(){
    cout<<"Enter First(WHITE) Player's Info"<<endl;
    Game.PlayerNames[1] = getPlayerinfo();
    cout<<"\n\nEnter Second(BLACK) Player's Info"<<endl;
    Game.PlayerNames[0] = getPlayerinfo();
    initGame(Game.GameState);
}

int PlayGame(){
    chessMove Move;
    ShowGame();

    while(!isCheckmate(Game.GameState, Game.GameState.TurningPlayer)){
        cout<<Game.PlayerNames[Game.GameState.TurningPlayer];
        if(Game.GameState.TurningPlayer == WHITE)
            cout<<" (WHITE) To Move";
        else
            cout<<" (BLACK) To Move";

        cout<<"\n\n"<<"Please enter your move  (use format FROM (Row# Column#) TO (Row# Column#) ) {Negative Value to move to the main menu}"<<endl;

        SaveGame();
        int u=0;
        while(isfacingCheck(Game.GameState, Game.GameState.TurningPlayer))
        {
            if(u==0)
            {
                cout<<"---------------------------Facing Check----------------------------------"<<endl;
            }
            else
            {
                cout<<"---------------------------Still Facing Check----------------------------------"<<endl;

            }
            u++;
            cin >> Move.FromRow>>Move.FromColumn;
            cin>>Move.ToRow>>Move.ToColumn;
            if(Move.FromRow < 0 || Move.FromColumn < 0 || Move.ToColumn < 0 || Move.ToRow < 0){
                cout<< "Moving to main menu \n";
                return 0;
            }


            if(!MakeMove(Game.GameState, Move))
            {
                if(Game.GameState.TurningPlayer == BLACK)
                    Game.GameState.TurningPlayer = WHITE;
                else
                    Game.GameState.TurningPlayer = BLACK;
            }
        }
        if(u!=0)
        {
            LoadGame();
            MakeMove(Game.GameState, Move);
            ShowGame();
        }
        else
        {
            cin >> Move.FromRow>>Move.FromColumn;
            cin>>Move.ToRow>>Move.ToColumn;

            if(Move.FromRow < 0 || Move.FromColumn < 0 || Move.ToColumn < 0 || Move.ToRow < 0){
                cout<< "Moving to main menu \n";
                return 0;
            }


            if(Game.GameState.Board[Move.FromRow][Move.FromColumn].Code==PAWN && isValidMove(Game.GameState,Move)==true && Move.ToRow==0)
            {
                int n;
                MakeMove(Game.GameState, Move);
                cout<<"CONGRATULATION ON PROMOTION OF PAWN "<<endl;
                cout<<"1.QUEEN                "<<"2.KNIGHT "<<endl;
                cout<<"3.ROOK                 "<<"4.BISHOP "<<endl;
                cout<<"Choose which one you wanna take: ";
                cin>>n;
                switch(n){
                case 1:
                    Game.GameState.Board[Move.ToRow][Move.ToColumn].Code=QUEEN;
                    break;
                case 2:
                    Game.GameState.Board[Move.ToRow][Move.ToColumn].Code=KNIGHT;
                    break;
                case 3:
                    Game.GameState.Board[Move.ToRow][Move.ToColumn].Code=ROOK;
                    break;
                case 4:
                    Game.GameState.Board[Move.ToRow][Move.ToColumn].Code=BISHOP;
                    break;
                }

                ShowGame();
            }

            if(Game.GameState.Board[Move.FromRow][Move.FromColumn].Code==PAWN && isValidMove(Game.GameState,Move)==true && Move.ToRow==7)
            {
                int n;
                MakeMove(Game.GameState, Move);
                cout<<"CONGRATULATION ON PROMOTION OF PAWN "<<endl;
                cout<<"1.QUEEN                "<<"2.KNIGHT "<<endl;
                cout<<"3.ROOK                 "<<"4.BISHOP "<<endl;
                cout<<"Choose which one you wanna take: ";
                cin>>n;
                switch(n){
                case 1:
                    Game.GameState.Board[Move.ToRow][Move.ToColumn].Code=QUEEN;
                    break;
                case 2:
                    Game.GameState.Board[Move.ToRow][Move.ToColumn].Code=KNIGHT;
                    break;
                case 3:
                    Game.GameState.Board[Move.ToRow][Move.ToColumn].Code=ROOK;
                    break;
                case 4:
                    Game.GameState.Board[Move.ToRow][Move.ToColumn].Code=BISHOP;
                    break;
                }

                ShowGame();
            }
            else
            {
                MakeMove(Game.GameState, Move);
                ShowGame();
            }
        }
    }

    return 0;

}

int main(){
    int choice = 0;
    do{
        do{
            cout<<"1. New Game\n2. Restart Game\n3. Save Game\n4. Load Game\n5. Exit\n\n Enter Your Choice(1-5) ";
            cin>>choice;
        }while(choice< 1 || choice > 5);

        switch(choice){
        case 1:
            initNewGame();
            PlayGame();
        break;
        case 2:
            PlayGame();
        break;
        case 3:
            SaveGame();
        break;
        case 4:
            LoadGame();
            PlayGame();
        break;
        case 5:
            return 0;
        break;
        }
    }while(1);

    return 0;
}
