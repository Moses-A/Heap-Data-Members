//Game Magic 8 Ball
//Command Line Based Classic Magic 8 Ball Game
// Author is Moses Arocha


#include <iostream>
#include <windows.h>
#include <string>
#include <limits>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <fstream>
#include <sstream>

using namespace std;

vector<string> PlayerList;
vector<string>::iterator iter;


WORD GetConsoleTextAttribute (HANDLE hCon)
{
  CONSOLE_SCREEN_BUFFER_INFO con_info;
  GetConsoleScreenBufferInfo(hCon, &con_info);
  return con_info.wAttributes;
}

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int saved_colors = GetConsoleTextAttribute(hConsole);


void AddPlayer(vector<string>& PlayerList);
void AddPlayer(vector<string>& PlayerList)
{

   SetConsoleTextAttribute(hConsole, 0x0D); // the color magenta is used
    cout << "\n  What Is The Name Of A Player? : ";
    string name;
    getline(cin, name);
    PlayerList.push_back(name);
}

void Clear();
void Clear()
{
    system("cls");
    cout << "\n\n\n\t Self Destruction Mode Has Been Enabled...\n\n\n\n";
}


void Start(vector<string>& PlayerList, int& SlotChosen);
void Start(vector<string>& PlayerList, int& SlotChosen)
{
    int players = 1;
 
    while(!(cin >> SlotChosen))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::digits, '\n');
        cout << "\nInvalid input\nTry again: ";
    }
    
    while (SlotChosen < 4)
    {
        cout << "\nYou must have 4 players\n";
        cout << "\nHow many players are there? ";
        cin >> SlotChosen;
    }
    
    SlotChosen = SlotChosen + 1;
    cin.ignore();
    
    while ((players != 5) || (players != SlotChosen))
    {
        ++players;
        AddPlayer(PlayerList);
        
        if ((players == 5 && SlotChosen == 4) || (players == SlotChosen))
        {
            break;
        }
    }

}

void PlayGame(vector<string>& PlayerList);
void PlayGame(vector<string>& PlayerList)
{
    int PassEightBall = 0;
    string Question;
    string ContinuePlay = "y";
    int randomNumber;

    srand(static_cast<unsigned int>(time(0)));  //seed random number generator
  

    const string Answers[20] = { " I do not have an answer.\n\n", " I advise you not do so.\n\n",
                                 " It seems the Timing is right.\n", " I would state yes! \n",
                                 " I see great things In your future. \n", " Let's ask another question, later. \n",
                                 " My fortunes tell me to tell you hurry up, it's a yes! \n", "You will leave a Legacy! \n",
                                 " I see good things, I think you will fine.\n", " It seems that you will be in Caleb's Basement soon. \n",
                                 " I do not see a future in this, please stop. \n", " I couldn't say yes anymore, let's do it! \n",
                                 " You will succeed, and will have a fortune. \n",  " It seems this is out of my reach.\n",
                                 " I do not know, ask later. I do not care.\n", " Hmm, who knows? Because I don't.\n",
                                 " Quit it, You are horrible. Stop!\n", " I hope you have a great day, it's a yes!\n",
                                 " Defintely, a yes, get too it soon!\n", " I would state the answer is up to you, I say most likely.\n" };


    while (PassEightBall != PlayerList.size())
    {
        randomNumber = rand() % 19 + 0;         // random number between 0 and 20
        SetConsoleTextAttribute(hConsole, 0x0E);
        cout << "\n Please Pass The Magic EightBall To Player ";
        SetConsoleTextAttribute(hConsole, 0x0D); // Sets The Color To purple
        cout << PlayerList[PassEightBall];
        SetConsoleTextAttribute(hConsole, 0x0E);
        cout << " .....\n";

          Sleep(2000);

        cout << "\n Sounds Great. Player ";

        SetConsoleTextAttribute(hConsole, 0x0D); // Sets The Color To purple
        cout << PlayerList[PassEightBall];
        SetConsoleTextAttribute(hConsole, 0x0E);
        cout << " What Is Your Question? ";

        getline(cin, Question);
        cin.ignore();
        ++PassEightBall;

        cout << "\n\n Response: ";
        SetConsoleTextAttribute(hConsole, 0x07);
        cout << Answers[randomNumber];

        if (PassEightBall == PlayerList.size())
        {
            SetConsoleTextAttribute(hConsole, 0x0C); // Sets The Color To Gray
            break;
        }

      Sleep(1500);

    }
}

void RemovePlayer(vector<string>& PlayerList);
void RemovePlayer(vector<string>& PlayerList)
{
    system("cls");

    int i = 1;
    int number;
    
    for (iter = PlayerList.begin(); iter != PlayerList.end(); ++iter)
    {
        cout << "\n Player " << i << ": " << *iter << endl;
        ++i;
    }

    cout << "\n\n Please Insert The Number Of The Person You Want To Delete: ";
    
    while(!(cin >> number))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::digits, '\n');
        cout << " This Is Incorrect, Try AGAIN! : ";
    }

    PlayerList.erase(PlayerList.begin()+number-1);
        
    if (PlayerList.size() < number -1 )
    {
        cout << "\n This Is An Incorrect Value.\n";
        cout << "\n\n Please Insert The Number Of The Person You Want To Delete: ";
        
        while(PlayerList.size() < number)
        {
            cin >> number;              
        }

    }

}

int main()
{
    int SlotChosen;
  
    SetConsoleTextAttribute(hConsole, 0x0C); // Sets The Color To Gray
    cout << "\t Welcome To The Magic EightBall! Where We Tell You Your Future! \n\n";
    SetConsoleTextAttribute(hConsole, 0x0A); // the color green is used
    cout << " Hello,\n\n My Name Is Moses. I Will Assist You, By Telling Your Fortune. \n"
         << " The Rules Are Simple: A Mininum Of 4 Players Can Play.\n\t However, You Can Choose However Many You Want To Play. \n\n So, Below Please Enter The ";        SetConsoleTextAttribute(hConsole, 0x0D); // the color magenta is used
    cout << "Number";
    SetConsoleTextAttribute(hConsole, 0x0A); // the color green is used
    cout << " Of Everyone Playing: ";

    Start(PlayerList, SlotChosen);

  
    cout << "\n Please Wait As The Game Loads...." << endl;
    Sleep(1000);
    SetConsoleTextAttribute(hConsole, 0x0B); // the color dark cyan is used
    cout << "\n\t\t Alright, The Rules Of This Game Are Simple. \n Press Number 3, Ask A Question,"
         << " Pass It To The Next Person, Then Continue. \n";
    do
    {    
        SetConsoleTextAttribute(hConsole, 0x0B); // Sets The Color To cyan
        int i = 1;
        
        for (iter = PlayerList.begin(); iter != PlayerList.end(); ++iter)
        {
            cout << "\n Player " << i << ": " << *iter << endl;
            ++i;
        }

        SetConsoleTextAttribute(hConsole, 0x08); // Sets The Color To Gray

        cout << "\n\n The Magic EightBall Game\n\n";
        cout << "\t 0 - Pause The Game. \n";
        cout << "\t 1 - Add A Player To The Game! \n";
        cout << "\t 2 - Remove A Player From The Game! \n";
        cout << "\t 3 - Play The Game. \n";
        cout << "\t 4 - Enable Self-Destruction Mode. \n";
        cout << endl << "\t\t Please Enter Your Choice: ";

        SetConsoleTextAttribute(hConsole, 0x0D); // the color magenta is used
        
        while(!(cin >> SlotChosen))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::digits, '\n');
            cout << " This Is Incorrect, Try AGAIN! : ";
        }

        SetConsoleTextAttribute(hConsole, 0x08); // Sets The Color To Gray

        switch (SlotChosen)
        {
            case 0: cout << "\n\t The Game Will Pause... \n\n"; break;
            case 1: AddPlayer(PlayerList); break;
            case 2: RemovePlayer(PlayerList); break;
            case 3: PlayGame(PlayerList); break;
            case 4: Clear(); SlotChosen = 0; break;
            default: cout << " This Is An Incorrect Entrance. \n";
        }
        
    } while (SlotChosen != 0);
  
    return 0;
}
