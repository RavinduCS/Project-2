/*
 * File:   Yahtzee_v1.cpp
 * Author: Ravindu Gangodawilage
 * Purpose: Project 2 Version 1
 *          Yahtzee using functions.
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
void rollDie(int &, int &, int &, int &, int &);
void rerol(int &, int &, int &, int &, int &, int size=5);
void cntDie(int,int,int,int,int,
            int&,int&,int&,int&,int&,int&);
int score(int,int,int,int,int,
          int,int,int,int,int,int,
          int);
void show(string,int,int,int,int,int,int,int);
void save(string,int,int,int,int,int,int,int);

//Execution Begins Here
int main() {
    srand(static_cast<unsigned int>(time(0)));

    menu();

    return 0;
}

//Display Menu
void menu() {
    char ch;

    do {
        cout << "==============================" << endl;
        cout << "        YAHTZEE" << endl;
        cout << "==============================" << endl;
        cout << "1. Play Game" << endl;
        cout << "2. Rules" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> ch;

        switch(ch) {
            case '1':
                play();
                break;

            case '2':
                cout << endl;
                cout << "Roll five dice." << endl;
                cout << "You may reroll up to two times." << endl;
                cout << "Choose a scoring category." << endl;
                cout << endl;
                break;

            case '0':
                cout << "Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice." << endl;
        }

    } while(ch!='0');
}

//Play One Round
void play() {

    string name;

    int die1,die2,die3,die4,die5;

    int cnt1,cnt2,cnt3,cnt4,cnt5,cnt6;

    int catg;

    int scr;

    int high;

    bool found;

    ifstream inFil;

    cout << endl;
    cout << "Enter player name: ";
    cin >> name;

    //Load High Score
    inFil.open("highscore.txt");

    found=inFil?true:false;

    if(found)
        inFil>>high;
    else
        high=0;

    inFil.close();

    //Initial Roll
    rollDie(die1,die2,die3,die4,die5);

    cout << endl;
    cout << "Roll 1 : "
         << die1 << " "
         << die2 << " "
         << die3 << " "
         << die4 << " "
         << die5 << endl;

    //Allow Rerolls
    rerol(die1,die2,die3,die4,die5);

    //Count Dice
    cntDie(die1,die2,die3,die4,die5,
           cnt1,cnt2,cnt3,cnt4,cnt5,cnt6);

    cout << endl;
    cout << "Choose Category" << endl;
    cout << "1 Ones" << endl;
    cout << "2 Twos" << endl;
    cout << "3 Threes" << endl;
    cout << "4 Fours" << endl;
    cout << "5 Fives" << endl;
    cout << "6 Sixes" << endl;
    cout << "7 Three Kind" << endl;
    cout << "8 Four Kind" << endl;
    cout << "9 Full House" << endl;
    cout << "10 Yahtzee" << endl;
    cout << "11 Chance" << endl;
    cout << "Choice: ";
    cin >> catg;

    //Calculate Score
    scr=score(die1,die2,die3,die4,die5,
              cnt1,cnt2,cnt3,cnt4,cnt5,cnt6,
              catg);

    //Display
    show(name,
         die1,die2,die3,die4,die5,
         catg,scr);

    //Save Results
    save(name,
         die1,die2,die3,die4,die5,
         catg,scr);

    //High Score
    if(scr>high){

        ofstream outFil;

        outFil.open("highscore.txt");

        outFil<<scr<<endl;

        outFil.close();

        cout << "*** NEW HIGH SCORE ***" << endl;
    }

    cout << endl;
}
//Roll Five Dice
void rollDie(int &die1,int &die2,int &die3,
             int &die4,int &die5){

    die1=rand()%6+1;
    die2=rand()%6+1;
    die3=rand()%6+1;
    die4=rand()%6+1;
    die5=rand()%6+1;
}

//Allow Player to Reroll
void rerol(int &die1,int &die2,int &die3,
           int &die4,int &die5,int size){

    bool rerol;
    int rNum;
    int dieNo;

    rNum=0;

    do{

        cout << endl;
        cout << "Reroll any dice? (1=yes 0=no): ";
        cin >> rerol;

        if(rerol){

            dieNo=-1;

            do{

                cout << "Enter die number (1-5)";
                cout << " or 0 to stop: ";
                cin >> dieNo;

                switch(dieNo){

                    case 1:
                        die1=rand()%6+1;
                        break;

                    case 2:
                        die2=rand()%6+1;
                        break;

                    case 3:
                        die3=rand()%6+1;
                        break;

                    case 4:
                        die4=rand()%6+1;
                        break;

                    case 5:
                        die5=rand()%6+1;
                        break;

                    case 0:
                        break;

                    default:
                        cout << "Invalid die number."
                             << endl;
                }

            }while(dieNo!=0);

            cout << endl;
            cout << "Current Dice: ";

            cout << die1 << " "
                 << die2 << " "
                 << die3 << " "
                 << die4 << " "
                 << die5 << endl;
        }

        rNum++;

    }while(rerol && rNum<2);
}
//Count Dice Faces
void cntDie(int die1,int die2,int die3,
            int die4,int die5,
            int &cnt1,int &cnt2,int &cnt3,
            int &cnt4,int &cnt5,int &cnt6){

    cnt1=(die1==1)+(die2==1)+(die3==1)+(die4==1)+(die5==1);

    cnt2=(die1==2)+(die2==2)+(die3==2)+(die4==2)+(die5==2);

    cnt3=(die1==3)+(die2==3)+(die3==3)+(die4==3)+(die5==3);

    cnt4=(die1==4)+(die2==4)+(die3==4)+(die4==4)+(die5==4);

    cnt5=(die1==5)+(die2==5)+(die3==5)+(die4==5)+(die5==5);

    cnt6=(die1==6)+(die2==6)+(die3==6)+(die4==6)+(die5==6);
}

//Calculate Score
int score(int die1,int die2,int die3,
          int die4,int die5,
          int cnt1,int cnt2,int cnt3,
          int cnt4,int cnt5,int cnt6,
          int catg){

    int sum;
    int maxCt;
    bool is3;
    bool is2;
    int scr;

    sum=die1+die2+die3+die4+die5;

    maxCt=cnt1;

    if(cnt2>maxCt) maxCt=cnt2;
    if(cnt3>maxCt) maxCt=cnt3;
    if(cnt4>maxCt) maxCt=cnt4;
    if(cnt5>maxCt) maxCt=cnt5;
    if(cnt6>maxCt) maxCt=cnt6;

    is3=(cnt1==3||cnt2==3||cnt3==3||
         cnt4==3||cnt5==3||cnt6==3);

    is2=(cnt1==2||cnt2==2||cnt3==2||
         cnt4==2||cnt5==2||cnt6==2);

    switch(catg){

        case 1:
            scr=cnt1;
            break;

        case 2:
            scr=cnt2*2;
            break;

        case 3:
            scr=cnt3*3;
            break;

        case 4:
            scr=cnt4*4;
            break;

        case 5:
            scr=cnt5*5;
            break;

        case 6:
            scr=cnt6*6;
            break;

        case 7:
            if(maxCt>=3)
                scr=sum;
            else
                scr=0;
            break;

        case 8:
            if(maxCt>=4)
                scr=sum;
            else
                scr=0;
            break;

        case 9:
            if(is3&&is2)
                scr=25;
            else
                scr=0;
            break;

        case 10:
            if(cnt1==5||cnt2==5||cnt3==5||
               cnt4==5||cnt5==5||cnt6==5)
                scr=50;
            else
                scr=0;
            break;

        case 11:
            scr=sum;
            break;

        default:
            scr=0;
    }

    return scr;
}
//Display Results
void show(string name,
          int die1,int die2,int die3,
          int die4,int die5,
          int catg,int scr){

    cout << endl;
    cout << "-----------------------------" << endl;
    cout << left << setw(12) << "Player:" << name << endl;

    cout << left << setw(12) << "Dice:";
    cout << die1 << " "
         << die2 << " "
         << die3 << " "
         << die4 << " "
         << die5 << endl;

    cout << left << setw(12) << "Category:"
         << catg << endl;

    cout << left << setw(12) << "Score:"
         << scr << endl;

    cout << "-----------------------------" << endl;
}

//Save Game
void save(string name,
          int die1,int die2,int die3,
          int die4,int die5,
          int catg,int scr){

    ofstream outFil;

    outFil.open("yahtzee_log.txt",ios::app);

    outFil << name << ",";

    outFil << die1 << " "
           << die2 << " "
           << die3 << " "
           << die4 << " "
           << die5 << ",";

    outFil << catg << ",";

    outFil << scr << endl;

    outFil.close();
}