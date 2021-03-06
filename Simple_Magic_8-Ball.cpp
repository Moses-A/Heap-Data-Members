//Game EightBall
//Simulates a game EightBall where players wait
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
#include <fstream>
#include <sstream>

using namespace std;

int PlayerCount;
int TotalPlayerCount;

WORD GetConsoleTextAttribute (HANDLE hCon)
{
  CONSOLE_SCREEN_BUFFER_INFO con_info;
  GetConsoleScreenBufferInfo(hCon, &con_info);
  return con_info.wAttributes;
}

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int saved_colors = GetConsoleTextAttribute(hConsole);
// there are two classes within this code, maintain them.

class Player
{
    public: 
        friend void Peek(const Player& aPlayer);
        Player(const string& name = "");
        string GetName() const;
        Player* GetNext() const;
        void SetNext(Player* next);
    
    private:
    	string m_Name;// holds the name of the Player
    	Player* m_pNext;  //Pointer to next Player in list; pointer to Player object
	// means that each Player object can hold a name and point to another Player object
};

Player::Player(const string& name)://initializes m_Name to a string object based on what's passed
    m_Name(name), 
    m_pNext(0)  // sets this to zero, meaning its a null pointer
{}

string Player::GetName() const
{
    return m_Name;
}

Player* Player::GetNext() const
{
    return m_pNext; // m_pNext links through this 
}

void Player::SetNext(Player* next)
{
    m_pNext = next;
}


// The creation of a NEW CLASS
class EightBall
{
    friend ostream& operator<<(ostream& os, const EightBall& aEightBall);
    // called a friend of EightBall so that it is able to send an object to the cout

    public:
        EightBall();
        ~EightBall();
	void AddPlayer();
	void RemovePlayer();
	void PlayGame();
	void Start();
	void Clear();
    
    private:
	Player* m_pHead;  // pointer that points to a Player object. THIS IS EightBall CLASS. represents the head of the line
	Player* m_pTail;
};

EightBall::EightBall():
    m_pHead(0), // makes it NULL (0)
    m_pTail(0)
{}

EightBall::~EightBall()
{
    Clear();// simply calls the clear function, removing all Player objects from the list, freeing the dynamic memory
	 // This delete, calls clear function, which calls remove function
}

void Peek(const Player& aPlayer);
void Peek(const Player& aPlayer)
{
    cout << aPlayer.m_Name;
}

void EightBall::Clear() // removes all the players from the EightBall
{
    while (m_pHead != 0) // if the list isn't empty it doesn't enter and skips over
	{	
	    RemovePlayer(); //calls the remove function
	}
}

void EightBall::RemovePlayer()//removes the Player's object, FREES THE MEMORY
{
	// if M_PHEAD IS 0, THE EightBall IS EMPTY AND THE FUNCTION STATES IT IS EMPTY.
	// removes the Player at the head of the line
    if (m_pHead == 0) // this function tests m_pHead value
	{
	    SetConsoleTextAttribute(hConsole, 0x0D); // the color magenta is used
	    cout << " This Place Is Empty. Who Am I Going To Kick Out?!\n";
	    SetConsoleTextAttribute(hConsole, 0x08); // Sets The Color To Gray
	}

    else
	{// the function creates a pointer pTemp, then points it to the first object in the list
	    Player* pTemp = m_pHead; // if there is a place, it deletes the first place on the list
	    m_pHead = m_pHead->GetNext(); // then sets m_pHead to the next thing on the list, either Player of 0
	 //delete pTemp; // this deletes the Player object pointed by pTemp
	    --TotalPlayerCount;
	}
}

void EightBall::AddPlayer()// creates a new Player, but ADDS TO END OF LIST
{
    //create a new Player node, and asks for the users input, and instantiates a new Player object on the Heap
    SetConsoleTextAttribute(hConsole, 0x0D); // the color magenta is used

        string suffix;

	if ( PlayerCount == 1 || PlayerCount == 21 || PlayerCount == 31 )
	{
	    suffix = "st";
	}	
	else if ( PlayerCount == 2 || PlayerCount == 22 || PlayerCount == 32)
	{
	    suffix = "nd";
	}
	else
	{
	    suffix = "rd";
	}

    cout << "\n  What Is The Name Of The " << PlayerCount << suffix << " Player? : ";
    string name;
    getline(cin, name);
    
    Player* pNewPlayer = new Player(name); // sets the objects pointer datat to the null pointer
    SetConsoleTextAttribute(hConsole, 0x08); // Sets The Color To Gray

    //if list is empty, make head of list this new Player
    if (m_pHead == 0)
	{
	    m_pHead = pNewPlayer;
	    m_pTail = (m_pHead + 1);
	}
    //otherwise find the end of the list and add the Player there
    else
	{
	    m_pTail = m_pTail->GetNext();
	    m_pTail ->SetNext(pNewPlayer);
	}
	m_pTail->SetNext(pNewPlayer);
}

void EightBall::Start()
{
	if (TotalPlayerCount < 4)
	{
	    cout << " \n\t Four Players Must Play. Insert Four Names Please. \n";
	    TotalPlayerCount = 4;
	}

	
}

void EightBall::PlayGame()
{
	int PassEightBall = 1;
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


	while (ContinuePlay == "y" || ContinuePlay == "Y")
	{
	    randomNumber = rand() % 19 + 0;         // random number between 0 and 20
	    SetConsoleTextAttribute(hConsole, 0x0E);
	    cout << "\n Please Pass The Magic EightBall To Player " << PassEightBall << ".....\n";
	    Sleep(2000);

	    cout << "\n Sounds Great. Player " << PassEightBall << " What Is Your Question? ";
	    getline(cin, Question);
	    cin.ignore();
	    ++PassEightBall;

	    cout << "\n\n Response: ";
	    SetConsoleTextAttribute(hConsole, 0x07);
	    cout << Answers[randomNumber];

		if (PassEightBall == TotalPlayerCount+1)
		{
		    SetConsoleTextAttribute(hConsole, 0x0C); // Sets The Color To Gray
		    break;
		}
	}
}

ostream& operator<<(ostream& os, const EightBall& aEightBall)
{
	/* if the EightBall is empty it shows the message, "The EightBall is Empty." If Not,
	   then the function goles through all of the players on the list, sending their
	   names to the output, it is able to do this because it overloads it through cout 
	   it uses pIter to move through this list*/

    Player* pIter = aEightBall.m_pHead; // moves using pIter

    os << "\n\n This Is The List Of Everyone Playing: \n";
    if (pIter == 0)
    {
        SetConsoleTextAttribute(hConsole, 0x0D); // the color magenta is used
	os << "\n Uh-oh. I Have Encountered An Issue. No One Is Playing. \n";
	SetConsoleTextAttribute(hConsole, 0x08); // Sets The Color To Gray
    }
    else
    {
	while (pIter != 0)
	{   
	    SetConsoleTextAttribute(hConsole, 0x0A); // the color green is used
	    Peek(*pIter); // this presents the name
	    cout << endl;
	    //os << pIter->GetName() << endl; // this is the display of the names, why it returns os
	    pIter = pIter->GetNext(); // the function makes the node point to the new Player object on the heap, which then addes the new object to the list   
	    SetConsoleTextAttribute(hConsole, 0x08); // Sets The Color To Gray
	}
    }

    return os;
}

int main()
{
    EightBall myEightBall; // creates a new EightBall object
    int SlotChosen;
    
	SetConsoleTextAttribute(hConsole, 0x0C); // Sets The Color To Gray
	cout << "\t Welcome To The Magic EightBall! Where We Tell You Your Future! \n\n";
	SetConsoleTextAttribute(hConsole, 0x0A); // the color green is used
	cout << " Hello,\n\n My Name Is Moses. I Will Assist You, By Telling Your Fortune. \n"
	     << " The Rules Are Simple: A Mininum Of 4 Players Can Play.\n\t However, You Can Choose However Many You Want To Play. \n\n So, Below Please Enter The ";
	SetConsoleTextAttribute(hConsole, 0x0D); // the color magenta is used
	cout << "Number";
	SetConsoleTextAttribute(hConsole, 0x0A); // the color green is used
	cout << " Of Everyone Playing: ";

	while(!(cin >> TotalPlayerCount))
	{
	    cin.clear();
 	    cin.ignore(numeric_limits<streamsize>::max_digits10, '\n');
	    cout << " This Is Incorrect, Try AGAIN! : ";
	}
	cin.ignore();

	myEightBall.Start();

	for ( int i = 0; i < TotalPlayerCount; ++i)
	{
	    PlayerCount++;
	    myEightBall.AddPlayer();
	}
	
	cout << "\n Please Wait As The Game Loads...." << endl;
	Sleep(1000);
	SetConsoleTextAttribute(hConsole, 0x0B); // the color dark cyan is used
	cout << "\n\t\t Alright, The Rules Of This Game Are Simple. \n Press Number 3, Ask A Question,"
	     << " Pass It To The Next Person, Then Continue. \n";
	     
    do 
    {
		
	SetConsoleTextAttribute(hConsole, 0x08); // Sets The Color To Gray

	cout << myEightBall;
        cout << "\n\n The Magic EightBall \n\n";
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
	    cin.ignore(numeric_limits<streamsize>::max_digits10, '\n');
	    cout << " This Be Incorrect, Try AGAIN! : ";
	}

	SetConsoleTextAttribute(hConsole, 0x08); // Sets The Color To Gray

        switch (SlotChosen)
        {
            case 0: cout << "\n\t The Game Will Pause... \n\n"; break;
	    case 1: myEightBall.AddPlayer(); ++TotalPlayerCount; break;  
            case 2: myEightBall.RemovePlayer(); break;
	    case 3: myEightBall.PlayGame(); break;
            case 4: myEightBall.Clear(); break;
            default: cout << " Fool, What? You Can't Type! \n";
        }
        
    } while (SlotChosen != 0);
    
    return 0;
}
