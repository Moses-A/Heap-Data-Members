//Game Dealership
//Simulates a game Dealership where players wait
// Author is Moses Arocha

#include <iostream>
#include <windows.h> // a windows only library, displays color in output
#include <string>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

WORD GetConsoleTextAttribute (HANDLE hCon)
{
  CONSOLE_SCREEN_BUFFER_INFO con_info;
  GetConsoleScreenBufferInfo(hCon, &con_info);
  return con_info.wAttributes;
}

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int saved_colors = GetConsoleTextAttribute(hConsole);

// there are two classes within this code, the goal is to maintain them.

class Car
{

public: 
    friend void Peek(const Car& aCar);
    Car(const string& name = "");
    string GetName() const;
    Car* GetNext() const;
    void SetNext(Car* next);
    
private:
    string m_Name;// holds the name of the Car
    Car* m_pNext;  //Pointer to next Car in list; pointer to Car object
	                 // means that each Car object can hold a name and point to another Car object
};

Car::Car(const string& name)://initializes m_Name to a string object based on what's passed
    m_Name(name), 
    m_pNext(0)  // sets this to zero, meaning its a null pointer
{}

string Car::GetName() const
{
    return m_Name;
}

Car* Car::GetNext() const
{
    return m_pNext; // m_pNext links through this 
}

void Car::SetNext(Car* next)
{
    m_pNext = next;
}


// The creation of a NEW CLASS
class Dealership
{
    friend ostream& operator<<(ostream& os, const Dealership& aDealership);
    // called a friend of Dealership so that it is able to send an object to the cout

public:
	
    Dealership();
    ~Dealership();
    void AddPlayer();
    void RemovePlayer();
    void Clear();
    
private:
    Car* m_pHead;  // pointer that points to a Car object. THIS IS Dealership CLASS. represents the head of the line
    Car* m_pTail;
};

Dealership::Dealership():
    m_pHead(0), // makes it NULL (0)
    m_pTail(0)
{}

Dealership::~Dealership()
{
    Clear();// simply calls the clear function, removing all Car objects from the list, freeing the dynamic memory
			 // This delete, calls clear function, which calls remove function
}

void Peek(const Car& aCar);
void Peek(const Car& aCar)
{
	cout << aCar.m_Name;
}

void Dealership::Clear() // removes all the players from the Dealership
{
    while (m_pHead != 0) // if the list isn't empty it doesn't enter and skips over
		{	
			RemovePlayer(); //calls the remove function
		}
}

void Dealership::RemovePlayer()//removes the Car's object, FREES THE MEMORY
{
	// if M_PHEAD IS 0, THE Dealership IS EMPTY AND THE FUNCTION STATES IT IS EMPTY.
	// removes the Car at the head of the line
    if (m_pHead == 0) // this function tests m_pHead value
		{
			SetConsoleTextAttribute(hConsole, 0x0D); // the color magenta is used
			cout << " This Place Be Empty. Who Am I Gonna Kick Out?!\n";
			SetConsoleTextAttribute(hConsole, 0x08); // Sets The Color To Gray
		}

    else
		{	// the function creates a pointer pTemp, then points it to the first object in the list
			Car* pTemp = m_pHead; // if there is a place, it deletes the first place on the list
			m_pHead = m_pHead->GetNext(); // then sets m_pHead to the next thing on the list, either Car of 0
			//delete pTemp; // this deletes the Car object pointed by pTemp
		}
}

void Dealership::AddPlayer()// creates a new Car, but ADDS TO END OF LIST
{
    //create a new Car node, and asks for the users input, and instantiates a new Car object on the Heap
    SetConsoleTextAttribute(hConsole, 0x0D); // the color magenta is used
	cout << " Give Me A Sec, I Got To Get A 40. I Mean The Papers." << endl;
	Sleep(5000);
    cout << "  Sign The Papers,  What You Wanna Name Her? : ";
    string name;
    getline(cin, name);
    Car* pNewCar = new Car(name); // sets the objects pointer datat to the null pointer
	SetConsoleTextAttribute(hConsole, 0x08); // Sets The Color To Gray

    //if list is empty, make head of list this new Car
    if (m_pHead == 0)
		{
			m_pHead = pNewCar;
			m_pTail = (m_pHead + 1);
		}
		
    //otherwise find the end of the list and add the Car there
    else
		{
		 m_pTail = m_pTail->GetNext();
		 m_pTail ->SetNext(pNewCar);
		}
		
	m_pTail->SetNext(pNewCar);
}

ostream& operator<<(ostream& os, const Dealership& aDealership)
{
	/* if the Dealership is empty it shows the message, "The Dealership is Empty." If Not,
	   then the function goles through all of the players on the list, sending their
	   names to the output, it is able to do this because it overloads it through cout 
	   it uses pIter to move through this list*/

    Car* pIter = aDealership.m_pHead; // moves using pIter

    os << "\n\n This Is Who Be Up In This Place: \n";
    if (pIter == 0)
		{
			SetConsoleTextAttribute(hConsole, 0x0D); // the color magenta is used
			os << "\n Yoo Fool! The Dealership Is Empty. Fill It Up My Dude! \n";
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
				pIter = pIter->GetNext(); // the function makes the node point to the new Car object on the heap, which then addes the new object to the list   
				SetConsoleTextAttribute(hConsole, 0x08); // Sets The Color To Gray
			}
		}

    return os;
}

int main()
{
    Dealership myDealership; // creates a new Dealership object
    int CarChosen;
    
	SetConsoleTextAttribute(hConsole, 0x08); // Sets The Color To Gray
	cout << "\t The Ghetto Car Dealership, The Chronicles. \n\n";
	SetConsoleTextAttribute(hConsole, 0x0A); // the color green is used
	cout << " Welcome, My Name Be Caleb. I Will Assist You, Or However You Spell It.\n"
             << " What You Want? Hurry Up And Choose! I Ain't Got All Day!\n";

    do
	{
		SetConsoleTextAttribute(hConsole, 0x08); // Sets The Color To Gray

	cout << myDealership;
        cout << "\n\n The Ghetto Car Dealership\n";
        cout << " 0 - Bounce From The Dealership.\n";
        cout << " 1 - Add A Porsche Up In This Place! \n";
        cout << " 2 - Sell A Porshce. Then Buy More. \n";
        cout << " 3 - Set The Place A Blaze. \n";
        cout << endl << " Please Enter Your Choice: ";

        SetConsoleTextAttribute(hConsole, 0x0D); // the color magenta is used

		while(!(cin >> CarChosen))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max_digits10, '\n');
			cout << " This Be Incorrect, Try AGAIN! : ";
		}

		SetConsoleTextAttribute(hConsole, 0x08); // Sets The Color To Gray

        switch (CarChosen)
        {
            case 0: cout << " Nahh My Dude, Disrespect. SMH.\n"; break;
	        case 1: myDealership.AddPlayer(); break;  
            case 2: myDealership.RemovePlayer(); break;
            case 3: myDealership.Clear(); break;
            default: cout << " Fool, What? You Can't Type! \n";
        }
    }
    while (CarChosen != 0);
    
    return 0;
}
