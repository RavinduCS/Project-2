/*
 * File:   Yahtzee_v2.cpp
 * Author: Ravindu Gangodawilage
 * Purpose: Project 2 Version 2
 *          Yahtzee using arrays and functions.
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
void menu();
void play();

void rollDie(int dice[],int size=5);
void rerol(int dice[],int roll[][5],int size=5);

void cntDie(int dice[],int cnt[],int size=5);

int score(int dice[],
          int cnt[],
          int catg);

void showDie(int dice[],int size=5);

void showRol(int roll[][5],
             int rows=3,
             int cols=5);

void show(string name,
          int dice[],
          int catg,
          int scr);

void save(string name,
          int dice[],
          int catg,
          int scr);

//Execution Begins Here
int main(){

    srand(static_cast<unsigned int>(time(0)));

    menu();

    return 0;
}

//Display Menu
void menu(){

    char ch;

    do{

        cout<<"=============================="<<endl;
        cout<<"         YAHTZEE"<<endl;
        cout<<"=============================="<<endl;
        cout<<"1. Play Game"<<endl;
        cout<<"2. Rules"<<endl;
        cout<<"0. Exit"<<endl;
        cout<<"Choice: ";
        cin>>ch;

        switch(ch){

            case '1':
                play();
                break;

            case '2':
                cout<<endl;
                cout<<"Roll five dice."<<endl;
                cout<<"You may reroll twice."<<endl;
                cout<<"Choose one scoring category."<<endl;
                cout<<endl;
                break;

            case '0':
                cout<<"Goodbye!"<<endl;
                break;

            default:
                cout<<"Invalid choice."<<endl;
        }

    }while(ch!='0');

}
void play(){

    string name;

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

}
//Roll Dice
void rollDie(int dice[],int size){

    for(int i=0;i<size;i++)
        dice[i]=rand()%6+1;

}

//Display Dice
void showDie(int dice[],int size){

    for(int i=0;i<size;i++)
        cout<<dice[i]<<" ";

    cout<<endl;

}

//Reroll Dice
void rerol(int dice[],int roll[][5],int size){

    bool rerol;

    int rNum;

    int dieNo;

    rNum=1;

    do{

        cout<<endl;
        cout<<"Reroll any dice? (1=yes 0=no): ";
        cin>>rerol;

        if(rerol){

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

            //Store Roll
            for(int i=0;i<size;i++)
                roll[rNum][i]=dice[i];

            cout<<endl;
            cout<<"Roll "<<rNum+1<<endl;

            showDie(dice);

        }

        rNum++;

    }while(rerol&&rNum<3);

}
//Count Dice Faces
void cntDie(int dice[],int cnt[],int size){

    //Reset Counts
    for(int i=0;i<7;i++)
        cnt[i]=0;

    //Count Each Face
    for(int i=0;i<size;i++)
        cnt[dice[i]]++;

}

//Calculate Score
int score(int dice[],
          int cnt[],
          int catg){

    int sum;
    int maxCt;
    bool is3;
    bool is2;

    sum=0;

    for(int i=0;i<5;i++)
        sum+=dice[i];

    maxCt=cnt[1];

    for(int i=2;i<=6;i++){

        if(cnt[i]>maxCt)
            maxCt=cnt[i];

    }

    is3=false;
    is2=false;

    for(int i=1;i<=6;i++){

        if(cnt[i]==3)
            is3=true;

        if(cnt[i]==2)
            is2=true;

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

    cout<<left<<setw(12)<<"Player:"<<name<<endl;

    cout<<left<<setw(12)<<"Dice:";
    showDie(dice);

    cout<<left<<setw(12)<<"Category:"<<catg<<endl;

    cout<<left<<setw(12)<<"Score:"<<scr<<endl;

    cout<<"-----------------------------"<<endl;

}

//Display All Rolls
void showRol(int roll[][5],
             int rows,
             int cols){

    cout<<endl;
    cout<<"Roll History"<<endl;

    for(int i=0;i<rows;i++){

        cout<<"Roll "<<i+1<<": ";

        for(int j=0;j<cols;j++)
            cout<<roll[i][j]<<" ";

        cout<<endl;
    }

}

//Save Game
void save(string name,
          int dice[],
          int catg,
          int scr){

    ofstream outFil;

    outFil.open("yahtzee_log.txt",ios::app);

    outFil<<name<<",";

    for(int i=0;i<5;i++)
        outFil<<dice[i]<<" ";

    outFil<<",";

    outFil<<catg<<",";

    outFil<<scr<<endl;

    outFil.close();

}