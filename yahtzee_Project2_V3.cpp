/*
 * File:   Yahtzee_v3.cpp
 * Author: Ravindu Gangodawilage
 * Purpose: Project 2 Version 3
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

void menu();

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

void rollDie(int dice[],int size=5);

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
        cout<<"========================"<<endl;
        cout<<"      YAHTZEE"<<endl;
        cout<<"========================"<<endl;
        cout<<"1 Play Game"<<endl;
        cout<<"2 Leaderboard"<<endl;
        cout<<"3 Statistics"<<endl;
        cout<<"4 Save Tournament"<<endl;
        cout<<"5 Load Tournament"<<endl;
        cout<<"6 Rules"<<endl;
        cout<<"0 Exit"<<endl;
        cout<<"Choice: ";
        cin>>ch;

        switch(ch){

            case '1':{

                string pName;

                name[game]="";

                scr[game]=play(pName);

                name[game]=pName;

                game++;

                break;
            }

            case '2':

                leadBd(name,scr,game);

                break;

            case '3':

                stats(scr,game);

                break;

            case '4':

                saveTm(name,scr,game);

                break;

            case '5':

                loadTm(name,scr,game);

                break;

            case '6':

                cout<<endl;
                cout<<"Roll five dice."<<endl;
                cout<<"You may reroll twice."<<endl;
                cout<<"Choose a scoring category."<<endl;

                break;

            case '0':

                saveTm(name,scr,game);

                cout<<"Tournament Saved."<<endl;

                break;

            default:

                cout<<"Invalid Choice"<<endl;

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
    cout<<"=========================="<<endl;
    cout<<"      LEADERBOARD"<<endl;
    cout<<"=========================="<<endl;

    cout<<left<<setw(5)<<"#"
        <<setw(15)<<"Player"
        <<setw(8)<<"Score"<<endl;

    cout<<"--------------------------"<<endl;

    for(int i=0;i<game;i++){

        cout<<left
            <<setw(5)<<i+1
            <<setw(15)<<name[i]
            <<setw(8)<<scr[i]
            <<endl;

    }

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