/*
 * File:   Yahtzee_v3.cpp
 * Author: Ravindu Gangodawilage
 * Purpose: Project 2 Version 4
 *          Yahtzee Tournament
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

//Function Prototypes
int play(string &);

void leadBd(string name[],
            int scr[],
            int game);

void stats(int scr[],
           int game);

void saveTm(string name[],
            int scr[],
            int game);

void loadTm(string name[],
            int scr[],
            int &game);

//Sorting Functions
void bubSor(string name[],
            int scr[],
            int game);

void selSor(string name[],
            int scr[],
            int game);

//Searching Functions
int linSrc(string name[],
           int game,
           string key);

int binSrc(string name[],
           int game,
           string key);

//Overloaded Swap Functions
void swapIt(int &,
            int &);

void swapIt(string &,
            string &);

//Yahtzee Functions
void rollDie(int dice[],
             int size=5);

void rerol(int dice[],
           int roll[][5],
           int size=5);

void cntDie(int dice[],
            int cnt[],
            int size=5);

int score(int dice[],
          int cnt[],
          int catg);

void showDie(int dice[],
             int size=5);

void showRol(int roll[][5],
             int rows=3,
             int cols=5);

void show(string,
          int[],
          int,
          int);

void save(string,
          int[],
          int,
          int);

//Execution Begins Here
int main(){

    srand(static_cast<unsigned int>(time(0)));

    string name[20];

    int scr[20];

    int game=0;

    char ch;

    loadTm(name,scr,game);

    do{

        cout<<endl;
        cout<<"============================"<<endl;
        cout<<"          YAHTZEE"<<endl;
        cout<<"============================"<<endl;
        cout<<"1 Play Game"<<endl;
        cout<<"2 Leaderboard"<<endl;
        cout<<"3 Statistics"<<endl;
        cout<<"4 Bubble Sort by Score"<<endl;
        cout<<"5 Selection Sort by Name"<<endl;
        cout<<"6 Linear Search"<<endl;
        cout<<"7 Binary Search"<<endl;
        cout<<"8 Save Tournament"<<endl;
        cout<<"9 Load Tournament"<<endl;
        cout<<"R Rules"<<endl;
        cout<<"0 Exit"<<endl;
        cout<<"Choice: ";
        cin>>ch;

        switch(ch){

            case '1':{

                if(game<20){

                    string pName;

                    scr[game]=play(pName);

                    name[game]=pName;

                    game++;

                }
                else{

                    cout<<endl;
                    cout<<"Tournament Full."<<endl;

                }

                break;
            }

            case '2':

                leadBd(name,scr,game);

                break;

            case '3':

                stats(scr,game);

                break;

            case '4':

                bubSor(name,scr,game);

                cout<<endl;
                cout<<"Players sorted by score."<<endl;

                leadBd(name,scr,game);

                break;

            case '5':

                selSor(name,scr,game);

                cout<<endl;
                cout<<"Players sorted by name."<<endl;

                leadBd(name,scr,game);

                break;

            case '6':{

                string key;

                int pos;

                if(game==0){

                    cout<<endl;
                    cout<<"No Games Played."<<endl;

                }
                else{

                    cout<<endl;
                    cout<<"Enter player name: ";
                    cin>>key;

                    pos=linSrc(name,game,key);

                    if(pos>=0){

                        cout<<"Player Found."<<endl;
                        cout<<"Name : "<<name[pos]<<endl;
                        cout<<"Score: "<<scr[pos]<<endl;

                    }
                    else{

                        cout<<"Player Not Found."<<endl;

                    }
                }

                break;
            }

            case '7':{

                string key;

                int pos;

                if(game==0){

                    cout<<endl;
                    cout<<"No Games Played."<<endl;

                }
                else{

                    //Binary search requires sorted names
                    selSor(name,scr,game);

                    cout<<endl;
                    cout<<"Enter player name: ";
                    cin>>key;

                    pos=binSrc(name,game,key);

                    if(pos>=0){

                        cout<<"Player Found."<<endl;
                        cout<<"Name : "<<name[pos]<<endl;
                        cout<<"Score: "<<scr[pos]<<endl;

                    }
                    else{

                        cout<<"Player Not Found."<<endl;

                    }
                }

                break;
            }

            case '8':

                saveTm(name,scr,game);

                break;

            case '9':

                loadTm(name,scr,game);

                cout<<endl;
                cout<<"Tournament Loaded."<<endl;

                break;

            case 'r':

            case 'R':

                cout<<endl;
                cout<<"Roll five dice."<<endl;
                cout<<"You may reroll twice."<<endl;
                cout<<"Choose one scoring category."<<endl;
                cout<<"The tournament stores up to 20 players."<<endl;

                break;

            case '0':

                saveTm(name,scr,game);

                cout<<"Tournament Saved."<<endl;
                cout<<"Goodbye!"<<endl;

                break;

            default:

                cout<<"Invalid Choice."<<endl;

        }

    }while(ch!='0');

    return 0;
}

//Play One Round
int play(string &name){

    int dice[5];

    int cnt[7]={0};

    int roll[3][5]={0};

    int catg;

    int scr;

    int high;

    bool found;

    ifstream inFil;

    cout<<endl;
    cout<<"Enter player name: ";
    cin>>name;

    //Load High Score
    inFil.open("highscore.txt");

    found=inFil?true:false;

    if(found)
        inFil>>high;
    else
        high=0;

    inFil.close();

    //First Roll
    rollDie(dice);

    for(int i=0;i<5;i++)
        roll[0][i]=dice[i];

    cout<<endl;
    cout<<"Roll 1"<<endl;

    showDie(dice);

    //Allow Rerolls
    rerol(dice,roll);

    //Count Dice
    cntDie(dice,cnt);

    cout<<endl;
    cout<<"Choose Category"<<endl;
    cout<<"1  Ones"<<endl;
    cout<<"2  Twos"<<endl;
    cout<<"3  Threes"<<endl;
    cout<<"4  Fours"<<endl;
    cout<<"5  Fives"<<endl;
    cout<<"6  Sixes"<<endl;
    cout<<"7  Three Kind"<<endl;
    cout<<"8  Four Kind"<<endl;
    cout<<"9  Full House"<<endl;
    cout<<"10 Yahtzee"<<endl;
    cout<<"11 Chance"<<endl;
    cout<<"Choice: ";
    cin>>catg;

    scr=score(dice,cnt,catg);

    show(name,dice,catg,scr);

    showRol(roll);

    save(name,dice,catg,scr);

    if(scr>high){

        ofstream outFil;

        outFil.open("highscore.txt");

        outFil<<scr<<endl;

        outFil.close();

        cout<<endl;
        cout<<"*** NEW HIGH SCORE ***"<<endl;

    }

    return scr;

}
//Display Leaderboard
void leadBd(string name[],
            int scr[],
            int game){

    if(game==0){

        cout<<endl;
        cout<<"No Games Played."<<endl;
        return;

    }

    cout<<endl;
    cout<<"=================================="<<endl;
    cout<<"          LEADERBOARD"<<endl;
    cout<<"=================================="<<endl;

    cout<<left
        <<setw(5)<<"#"
        <<setw(18)<<"Player"
        <<setw(8)<<"Score"<<endl;

    cout<<"----------------------------------"<<endl;

    for(int i=0;i<game;i++){

        cout<<left
            <<setw(5)<<i+1
            <<setw(18)<<name[i]
            <<setw(8)<<scr[i]
            <<endl;

    }

    cout<<"=================================="<<endl;
    cout<<endl;
}
//Tournament Statistics
void stats(int scr[],
           int game){

    if(game==0){

        cout<<endl;
        cout<<"No Games Played."<<endl;
        return;

    }

    int high=scr[0];
    int low=scr[0];
    int sum=0;

    float avg;

    for(int i=0;i<game;i++){

        if(scr[i]>high)
            high=scr[i];

        if(scr[i]<low)
            low=scr[i];

        sum+=scr[i];

    }

    avg=(float)sum/game;

    cout<<endl;
    cout<<"=========================="<<endl;
    cout<<"   TOURNAMENT STATS"<<endl;
    cout<<"=========================="<<endl;

    cout<<"Games Played : "<<game<<endl;
    cout<<"Highest Score: "<<high<<endl;
    cout<<"Lowest Score : "<<low<<endl;
    cout<<fixed<<setprecision(1);
    cout<<"Average Score: "<<avg<<endl;
    cout<<endl;

}
//Save Tournament
void saveTm(string name[],
            int scr[],
            int game){

    ofstream outFil;

    outFil.open("players.txt");

    outFil<<game<<endl;

    for(int i=0;i<game;i++){

        outFil<<name[i]<<" "
              <<scr[i]<<endl;

    }

    outFil.close();

    cout<<endl;
    cout<<"Tournament Saved."<<endl;
}
void loadTm(string name[],
            int scr[],
            int &game){

    ifstream inFil;

    inFil.open("players.txt");

    if(!inFil){

        game=0;

        inFil.close();

        return;
    }

    inFil>>game;

    if(game>20)
        game=20;

    for(int i=0;i<game;i++){

        inFil>>name[i]
             >>scr[i];

    }

    inFil.close();
}
//Swap Integer Values
void swapIt(int &a,int &b){

    int temp;

    temp=a;
    a=b;
    b=temp;

}

//Swap String Values
void swapIt(string &a,string &b){

    string temp;

    temp=a;
    a=b;
    b=temp;

}
//Bubble Sort by Score
void bubSor(string name[],
            int scr[],
            int game){

    bool swap;

    int last;

    last=game-1;

    do{

        swap=false;

        for(int i=0;i<last;i++){

            if(scr[i]<scr[i+1]){

                swapIt(scr[i],scr[i+1]);

                swapIt(name[i],name[i+1]);

                swap=true;

            }

        }

        last--;

    }while(swap);

}
//Selection Sort by Name
void selSor(string name[],
            int scr[],
            int game){

    int minPos;

    for(int i=0;i<game-1;i++){

        minPos=i;

        for(int j=i+1;j<game;j++){

            if(name[j]<name[minPos])
                minPos=j;

        }

        if(minPos!=i){

            swapIt(name[i],name[minPos]);

            swapIt(scr[i],scr[minPos]);

        }

    }

}
//Linear Search
int linSrc(string name[],
           int game,
           string key){

    for(int i=0;i<game;i++){

        if(name[i]==key)
            return i;

    }

    return -1;
}
//Binary Search
int binSrc(string name[],
           int game,
           string key){

    int first=0;
    int last=game-1;
    int mid;

    while(first<=last){

        mid=(first+last)/2;

        if(name[mid]==key){

            return mid;

        }
        else if(name[mid]<key){

            first=mid+1;

        }
        else{

            last=mid-1;

        }

    }

    return -1;
}
//Roll Dice
void rollDie(int dice[],int size){

    for(int i=0;i<size;i++){

        dice[i]=rand()%6+1;

    }
}

//Display Dice
void showDie(int dice[],int size){

    for(int i=0;i<size;i++){

        cout<<dice[i]<<" ";

    }

    cout<<endl;
}

//Reroll Dice
void rerol(int dice[],int roll[][5],int size){

    bool again;

    int rNum=1;

    int dieNo;

    do{

        cout<<endl;
        cout<<"Reroll any dice? (1=yes 0=no): ";
        cin>>again;

        if(again){

            dieNo=-1;

            do{

                cout<<"Enter die number (1-5)";
                cout<<" or 0 to stop: ";
                cin>>dieNo;

                if(dieNo>=1&&dieNo<=5){

                    dice[dieNo-1]=rand()%6+1;

                }
                else if(dieNo!=0){

                    cout<<"Invalid die number."<<endl;

                }

            }while(dieNo!=0);

            for(int i=0;i<size;i++){

                roll[rNum][i]=dice[i];

            }

            cout<<endl;
            cout<<"Roll "<<rNum+1<<endl;

            showDie(dice);

        }

        rNum++;

    }while(again&&rNum<3);
}

//Count Dice Faces
void cntDie(int dice[],int cnt[],int size){

    for(int i=0;i<7;i++){

        cnt[i]=0;

    }

    for(int i=0;i<size;i++){

        cnt[dice[i]]++;

    }
}

//Calculate Score
int score(int dice[],int cnt[],int catg){

    int sum=0;

    int maxCt=cnt[1];

    bool is2=false;

    bool is3=false;

    for(int i=0;i<5;i++){

        sum+=dice[i];

    }

    for(int i=2;i<=6;i++){

        if(cnt[i]>maxCt){

            maxCt=cnt[i];

        }
    }

    for(int i=1;i<=6;i++){

        if(cnt[i]==2){

            is2=true;

        }

        if(cnt[i]==3){

            is3=true;

        }
    }

    switch(catg){

        case 1:
            return cnt[1];

        case 2:
            return cnt[2]*2;

        case 3:
            return cnt[3]*3;

        case 4:
            return cnt[4]*4;

        case 5:
            return cnt[5]*5;

        case 6:
            return cnt[6]*6;

        case 7:

            if(maxCt>=3)
                return sum;
            else
                return 0;

        case 8:

            if(maxCt>=4)
                return sum;
            else
                return 0;

        case 9:

            if(is3&&is2)
                return 25;
            else
                return 0;

        case 10:

            if(maxCt==5)
                return 50;
            else
                return 0;

        case 11:
            return sum;

        default:
            return 0;
    }
}

//Display Results
void show(string name,
          int dice[],
          int catg,
          int scr){

    cout<<endl;
    cout<<"-----------------------------"<<endl;

    cout<<left<<setw(12)<<"Player:"
        <<name<<endl;

    cout<<left<<setw(12)<<"Dice:";

    showDie(dice);

    cout<<left<<setw(12)<<"Category:"
        <<catg<<endl;

    cout<<left<<setw(12)<<"Score:"
        <<scr<<endl;

    cout<<"-----------------------------"<<endl;
}

//Display Roll History
void showRol(int roll[][5],
             int rows,
             int cols){

    cout<<endl;
    cout<<"Roll History"<<endl;

    for(int i=0;i<rows;i++){

        cout<<"Roll "<<i+1<<": ";

        for(int j=0;j<cols;j++){

            cout<<roll[i][j]<<" ";

        }

        cout<<endl;
    }
}

//Save Individual Game
void save(string name,
          int dice[],
          int catg,
          int scr){

    ofstream outFil;

    outFil.open("yahtzee_log.txt",ios::app);

    outFil<<name<<",";

    for(int i=0;i<5;i++){

        outFil<<dice[i]<<" ";

    }

    outFil<<","<<catg<<","<<scr<<endl;

    outFil.close();
}