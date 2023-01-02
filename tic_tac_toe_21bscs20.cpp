#include<iostream>
#include<ctime>
#include<fstream>
using namespace std;

// For Reading and writing in Files
ifstream read;
ofstream write;

// Declearing Global Variables o It can be Accessed by All Functions
char board[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
char CurrentMark;
int CurrentPlayer;
int Human=1,Pc=2;

inline void starline(){
    for(int i=0; i<40; i++){
        cout<<'*';
    }
}

bool placeMarker(int slot) // This Will Place Marker on Given Slot
{
    int row = slot / 3;
    int col;
    
    // This will Finds Row Number
    if(slot % 3 == 0){
        row = row - 1;
        col = 2;
    }
    //  This will Find Column Number
    else {
        col = (slot % 3) - 1;
    }
    // This will check whether slot is Empty or Not then Print Marker on Given Slot
    if(board[row][col] != 'X' && board[row][col] != 'x' && board[row][col] != 'O' && board[row][col] != 'o') {
        board[row][col] = CurrentMark;
        return true;
    }else {
        return false;
    }
}

void drawBoard() // Function to Draw Tik Tac Toe Game Board
{
    cout<<endl;
    cout<<"      |       |      "<<"\n";
    cout<<"   "<<board[0][0]<<"  |   "<<board[0][1]<<"   |   "<<board[0][2]<<"\n";
    cout<<"______|_______|______"<<"\n";
    cout<<"      |       |      "<<"\n";
    cout<<"   "<<board[1][0]<<"  |   "<<board[1][1]<<"   |   "<<board[1][2]<<"\n";
    cout<<"______|_______|______"<<"\n";
    cout<<"      |       |      "<<"\n";
    cout<<"   "<<board[2][0]<<"  |   "<<board[2][1]<<"   |   "<<board[2][2]<<"\n";
    cout<<"      |       |      "<<"\n";

}

void reset_Board(){

    if(board[0][0] != '1'){
        board[0][0] = '1';
    }
    if(board[0][1] != '2'){
        board[0][1] = '2';
    }
    if(board[0][2] != '3'){
        board[0][2] = '3';
    }
    if(board[1][0] != '4'){
        board[1][0] = '4';
    }
    if(board[1][1] != '5'){
        board[1][1] = '5';
    }
    if(board[1][2] != '6'){
        board[1][2] = '6';
    }
    if(board[2][0] != '7'){
        board[2][0] = '7';
    }
    if(board[2][1] != '8'){
        board[2][1] = '8';
    }
    if(board[2][2] != '9'){
        board[2][2] = '9';
    }
}

int theWinner() // This will Declare the Winner
{
    for(int i=0; i<3; i++){
        // Rows
        if(board[i][0]==board[i][1]&&board[i][1]==board[i][2]) {
            return CurrentPlayer;
        }
        // Columns
        if(board[0][i]==board[1][i]&&board[1][i]==board[2][i]) {
            return CurrentPlayer;
        }
    }
    
    if(board[0][0]==board[1][1]&&board[1][1]==board[2][2]) {
        return CurrentPlayer;
    }
    if(board[0][2]==board[1][1]&&board[1][1]==board[2][0]) {
        return CurrentPlayer;
    }
    
    return 0;
}

void swaping() // This will Exchange Player and Markers
{
    // Swaping Markers
    if(CurrentMark == 'X'){
        CurrentMark = 'O';
    }
    else if(CurrentMark == 'O'){
        CurrentMark = 'X';
    }
    if(CurrentMark == 'x') {
        CurrentMark = 'o';
    }
    else if(CurrentMark == 'o') {
        CurrentMark = 'x';
    }

    // Swaping Players
    if(CurrentPlayer == 1) {
        CurrentPlayer = 2;
    }
    else {
        CurrentPlayer = 1;
    }

}

void Human_vs_Human() // Main Function to Execute Game
{
    write.open("winner.txt",ios::app);
    int slot,winner;
    char marker;
    string p1,p2;

    do{
    cin.ignore();
    cout<<"\nPlayer 1 Please Enter Your Name : ";
    getline(cin,p1);
    starline();
    cout<<"\nPlayer 2 Please Enter Your Name : ";
    getline(cin,p2);
    starline();
    cout<<endl<<p1<<", Please Choose Your Marker!\n";
    starline();
    cout<<"\nSelect (X or O): "; 
    cin>>marker;
    starline();
    }while(marker!='O' && marker!='o' && marker!='x'&& marker!='X');
    
    CurrentPlayer = 1;
    CurrentMark = marker;
    drawBoard();
    for(int i=0; i<9; i++){
        if(CurrentPlayer == 1){
            cout<<endl<<p1<<"'s Turn"<<endl<<"Please Enter Your Slot : ";
            cin>>slot;
        
            if(slot<1 || slot>9){
                drawBoard();
                cout<<"\nInvalid Slot!\nPlease Re-Enter Slot.";
                --i;
                continue;
            }

            if(!placeMarker(slot)){
                drawBoard();
                cout<<"\nThat Slot is Occupied!\nPlease Choose another Slot.\n";
                --i;
                continue;
            }
        }

        if(CurrentPlayer == 2){
            cout<<endl<<p2<<"'s Turn"<<endl<<"Please Enter Your Slot : ";
            cin>>slot;
        
            if(slot<1 || slot>9){
                drawBoard();
                cout<<"\nInvalid Slot!\nPlease Re-Enter Slot.";
                --i;
                continue;
            }

            if(!placeMarker(slot)){
                drawBoard();
                cout<<"\nThat Slot is Occupied!\nPlease Choose another Slot.\n";
                --i;
                continue;
            }
        }

        
        winner = theWinner(); // Assigning Full Function to a Variable
        if(winner==1){
            drawBoard();
            starline();
            write<<"=> Human vs Human"<<endl<<p1<<" Won the Game <3\n"<<p2<<" Loss the Game :(\n"<<endl;
            cout<<"\nCongratulations "<<p1<<", You are the Winner <3"<<endl;
            starline();
            break;
        }
        if (winner==2){
            drawBoard();
            starline();
            write<<"=> Human vs Human"<<endl<<p2<<" Won the Game <3\n"<<p1<<" Loss the Game :(\n"<<endl;
            cout<<"\nCongratulations "<<p2<<", You are the Winner <3"<<endl;
            starline();
            break;
        }
        swaping();
        drawBoard();
        }

    if(winner == 0){
        starline();
        write<<"=> Human vs Human\n   Game Tied!\n"<<endl;
        cout<<"\nGame Tied!\n";
        starline();
    }

    reset_Board();
    write.close();
}

void Human_vs_Pc(){
    write.open("winner.txt",ios::app);
    srand(time(0)); //Initializing Random Number Generator
    int slot,winner;
    string Name;
    char marker;

    do{
    cin.ignore();
    cout<<"\nPlease Enter Your Name : ";
    getline(cin,Name);
    starline();
    cout<<"\nPlease Choose Your Marker!\n";
    starline();
    cout<<"\nSelect (X or O): "; 
    cin>>marker;
    starline();
    }while(marker!='O' && marker!='o' && marker!='x'&& marker!='X');
    CurrentPlayer = Human;
    CurrentMark = marker;

    drawBoard();

    for(int i=0; i<9; i++){
        if(CurrentPlayer == Human){
            cout<<endl<<Name<<"'s Turn\nPlease Enter Your Slot : ";
            cin>>slot;
            if(slot<1 || slot>9){
                drawBoard();
                cout<<"\nInvalid Slot!\nPlease Re-Enter Slot.";
                --i;
                continue;
        }

            if(!placeMarker(slot)){
                drawBoard();
                cout<<"\nThat Slot is Occupied!\nPlease Choose another Slot.\n";
                --i;
                continue;
        }
        }

        else if(CurrentPlayer == Pc){
            slot = ((rand()%9)+1);
            if(slot<1 || slot>9){
            --i;
            continue;
        }

            if(!placeMarker(slot)){
            --i;
            continue;
        }
        cout<<"\nPc's Turn";
        cout<<"\nPc Choosed Slot No : "<<slot<<endl;
        }

        winner = theWinner(); // Assigning Full Function to a Variable
        if(winner == Human){
            drawBoard();
            starline();
            write<<"=> Human vs Pc\n"<<Name<<" Won The Game <3\nPc Loss the Game :(\n"<<endl;
            cout<<"\nCongratulations "<<Name<<", You are the Winner <3"<<endl;
            starline();
            break;
        }
        if (winner == Pc){
            drawBoard();
            starline();
            write<<"=> Human vs Pc\nPc Won the Game <3\n"<<Name<<" Loss the Game :(\n"<<endl;
            cout<<"\nPc is the Winner <3\n"<<Name<<", Better Luck Next Time!"<<endl;
            starline();
            break;
        }
        swaping();
        drawBoard();
    }

     if(winner == 0){
        starline();
        write<<"=> Human vs Pc\n   Game Tied!\n"<<endl;
        cout<<"\nGame Tied!\n";
        starline();
    }
    
    reset_Board();
    write.close();
}

void showGameHistory(){
    read.open("winner.txt");
    string str;
    getline(read,str);
    bool empty = str.empty() != 0;
    if(empty){
        cout<<"No Game History Found!"<<endl;
    }
    else{
        cout<<str<<endl;
        while(read.eof()==0){
        getline(read,str);
        cout<<str<<endl;
    }
    }
    starline();
    read.close();
}

void deleteGameHistory(){
    write.open("winner.txt");
    write<<"";
    cout<<"\nHistory Deleted"<<endl;
}

int main(){
    char ans;
    int choice;

    do{
    system("clear");
    cout<<"\t*****TIC TAC TOE*****\n";
    starline();
    cout<<"\n1 : Human vs Human\n2 : Human vs PC\n3 : Game History\n4 : Delete History\n5 : Quit"<<endl;
    starline();
    cout<<"\nEnter Your Choice : ";
    cin>>choice;
    starline();
    switch(choice){
        case 1:
            cout<<"\nYou Choosed (Human vs Human)"<<endl;
            starline();
            Human_vs_Human();
            break;
        case 2:
            cout<<"\nYou Choosed (Human vs PC)"<<endl;
            starline();
            Human_vs_Pc();
            break;
        case 3:
            cout<<"\nGame History"<<endl;
            starline();
            cout<<endl;
            showGameHistory();
            break;
        case 4:
            deleteGameHistory();
            starline();
            break;
        case 5:
            cout<<"\nThanks for Playing!\nMade by Abrar Ahmed Shahok"<<endl;
            starline();
            cout<<endl;
            return 0;
        default:
            cout<<"\nInvalid Choice!"<<endl;
            starline();
    }

    cout<<"\nDo You Want to Play Game Again? (Y/N) : ";
    cin>>ans;
    }while(ans == 'Y' || ans == 'y');

    if(ans=='N' || ans=='n'){
        starline();
        cout<<"\nThanks for Playing!\nMade by Abrar Ahmed Shahok"<<endl;
        starline();
        cout<<endl;
    }
}