#include<iostream>
#include<string>
#include<vector>
#include<fstream>

#include "nlohmann/json.hpp"

using namespace std;

using json = nlohmann::json;
void LeaveSpace(void)
{
	cout << string(50, '\n');
}

class Wallet
{
	public:
		int Gold;
		int Silver;
		int Bronze;	
		Wallet(void) : Gold(10), Silver(50), Bronze(250) {}	
};

class Player 
{
	public:
		Player(int S, int A, int I, string N) : Name(N), Strength(S), Agility(A), Intelect(I), Health(S * 2), Stamina(A * 2), Magika(I * 2) {}
		static Player* make_player(int Choice, string N);
		virtual void Shout(void) = 0;
		bool StrengthTest(int Pass){return Pass <= Strength;}
		bool AgilityTest(int Pass){return Pass <= Agility;}
		bool IntelectTest(int Pass){return Pass <= Intelect;}
		void Pay(int G, int S, int B)
		{
			wallet.Gold -= G;
			wallet.Silver -= S;
			wallet.Bronze -= B;
		}
		void Regen(int HealthGain)
		{
			Health = Health + HealthGain;
			if (Health > Strength * 2){Health = Strength * 2;}
		}
		Wallet wallet;
	private:
		string Name;
		int Strength;
		int Agility;
		int Intelect;
		int Health;
		int Stamina;
		int Magika;
};

class Warrior : public Player
{
	public:
		Warrior(string N) : Player(10,5,0,N) {}
		void Shout(void);
};
void Warrior::Shout(void)
{
	cout << "I am a mighty warrior" << endl;
}

class Mage : public Player
{
	public:
		Mage(string N) : Player(0,5,10,N) {}
		void Shout(void);
};
void Mage::Shout(void)
{
	cout << "I am a wizard" << endl;
}

Player* Player::make_player(int Choice, string N)
{
	switch (Choice)
	{
	case 1:
		return new Warrior(N);
		break;
	case 2: 	
		return new Mage(N);
		break;
	}
	return NULL;
}

Player* QuestOne_EnterDetails(void)
{
	vector<string> AllClasses = {"1. Warrior", "2. Mage"};
	LeaveSpace();	
	cout << "Hello, welcome to the Bearded Woman, the best tavern in the land!" << endl;
	cout << "Mind introducing yourself stranger? What's your name?" << endl;
	string Name;
	cin >> Name;	
	LeaveSpace();
	cout << "Well then " <<  Name   <<"  what are you known to be?" << endl;
	for (string C : AllClasses)
	{
		cout << C << endl;
	}
	int Choice;
	cin >> Choice;
	LeaveSpace();
	do
	{
		if (Choice <= static_cast<int>(AllClasses.size()) && Choice >= 1)
		{
			return Player::make_player(Choice, Name);
		}
		else 

		{
			cout << "Please enter a valid response" << endl;
		}
	}
	while(true);
}

class Branch
{
	public:
		vector<string> dialogue;
		vector<Branch*> branches;
		virtual void Action(void);
	private:
};
void StoryBranch(Branch* _branch)
{
	for(string &text:_branch->dialogue)
	{
		cout << text << endl;
	}
	int Choice;
	cin >> Choice;
	StoryBranch(_branch->branches[Choice - 1]);
}
int QuestOneIntro_One(bool discount, Player* _player)

{
	if (discount)
	{
		cout << "A room's gunna cost you 75 bronze pieces a night, or 8 silver for the nicer rooms at the top" << endl;		
		cout << "1. Hand over the 75 bronze for a room" << endl;
		cout << "2. Pay the 8 silver, it's been a long day on the road, you want the nicer bed" << endl;
	}
	else
	{
		cout << "A room is 2 silver pieces a night, or 10 for the nicer rooms at the top" << endl;
		cout << "1. Hand over 2 silver for a room" << endl;
		cout << "2. Pay the 10, it's been a long day on the road, you want the nicer bed" << endl;
	}
	cout << "3. You don't need the room, you're just here for a drink" << endl;  
	int Choice;
	int comfort = 0;
	cin >> Choice;
	LeaveSpace();
	switch (Choice)
	{
		case 1:
			if (discount){_player->Pay(0, 0, 75);}
			else {_player->Pay(0, 2, 0);}
			cout << "Thanks, here's your key, you'll be in room 4" << endl;
			comfort = 1;
			break;
		case 2:
			if (discount){_player->Pay(0, 8, 0);}
			else {_player->Pay(0, 10, 0);}
			cout << "Thanks, here's your key, you'll be in room 12" << endl;
			comfort = 2;
			break;
		case 3:
			cout << "I see, well the bar is just around the corner, come back if you want to stay the night" << endl;
			break;
	}
	return comfort;	
}
int ProcessTime(string time)
{
	if (time == "Morning") {return 1;}
	if (time == "Noon") {return 2;}
	if (time == "Evening") {return 3;}
	return 4;
}
void Sleep(string* Time, int Comfort)
{
	//Morning >> Noon >> Evening >> Midnight >> Morning
	cout << "It is currently " << *Time << ", when would you like to sleep until?" << endl;
	cout << "1. Midnight" << endl;
	cout << "2. Morning" << endl;
	int Choice;
	cin >> Choice;
	LeaveSpace();
	switch (Choice)
	{
		case 1:
			*Time = "Midnight";
			break;
		case 2:
			
			*Time = "Morning";
			break;
	}
}
void QuestOneIntro_Bar(void)
{
	cout << "You walk through the door to discover the bar is full of people." << endl;
	cout << "They're very joyful enjoying their mead, however one fellow in the corner seems to be sad." << endl;
	cout << "1. Approach the fellow" << endl;
	cout << "2. Get some mead (costs 10 bronze)" << endl;
	cout << "3. Leave the bar and speak the inn-keeper" << endl;
	int Choice;
	cin >> Choice;
	LeaveSpace();
	switch (Choice)
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
void QuestOneIntro_Two(string* Time, int comfort)
{
	cout << "If you're looking for a drink, the bar is just around the corner there" << endl;
	cout << "1. Head up to your room, you need the sleep" << endl;
	cout << "2. A drink at the bar sounds good" << endl;
	int Choice;
	cin >> Choice;
	LeaveSpace();
	switch (Choice)	
	{
		case 1:
			Sleep(Time, comfort);
			break;
		case 2:
			QuestOneIntro_Bar();
			break;
	}	
}
bool QuestOneIntro(Player* _player, string* Time)
{
	bool Accepted = false;
	cout << "Nice to meet you, I'm Gregor Karlsson, innkeeper here at the Bearded Woman." << endl;
	cout << "Say, an adventurer like yourself wouldn't be looking for a job would you, put a little cash in your pocket?" << endl;
	cout << "1. Politely decline, you don't need the money anyway" << endl;
	cout << "2. Ask for more details, you can't agree without them" << endl;
	cout << "3. You had me at money!" << endl;
	int Choice_1;
	cin >> Choice_1;
	LeaveSpace();
	int Choice_2;
	bool discount = false;
	switch (Choice_1)
	{
		
		case 1:
			cout << "Aww well" << endl;
			Accepted = false;
			break;
		case 2:
			cout << "A smart one you are, well, I'll tell you more then" << endl;
			cout << "About a week ago, Betty, my eldest daugther, went down to the basement and she saw something big" << endl;
			cout << "Being the man of this place, I went down to chase it out" << endl;
			cout << "As it turned out, it was a giant spider, about two feet off the ground" << endl;
			cout << "Anyway, I gave it a good wack, and it ran off into the forest, just east of here" << endl;
			cout << "I think it's got a nest down by the river, and the spiders have been giving me trouble ever since it happened" << endl;
			cout << "I can't leave here, but I recon a person of your strengths should be able to handle it, how does it sound?" << endl;	
			cout << "1. And the reward?" << endl;
			cout << "2. Of course, anything for a fellow citizen of the realm" << endl;
			cin >> Choice_2;
			LeaveSpace();
			switch (Choice_2)
			{
				case 1:
					cout << "Clear out the cave, and I'll give you 20 gold pieces" << endl;
					cout << "You up for that?" << endl;
					cout << "1. Agree to clear out the cave" << endl;
					cout << "2. Give it a pass, it's not worth the gold" << endl;
					int Choice_3;
					cin >> Choice_3;
					LeaveSpace();
					switch (Choice_3)
					{
						case 1:
							Accepted = true;
						case 2:
							Accepted = false;
					}
					break;
				case 2:
					cout << "I knew you'd say that! Seeing as you're so nice, I'll give you a little discount on your stay" << endl;
					Accepted = true;
					discount = true;
					break;		
			}
			break;
		case 3:
			cout << "Ok, well there is a cave full of spiders in the woods to the east, get rid of them and I'll pay you a king's randsom" << endl;
			Accepted = true;
			break;
	}	
	int comfort = QuestOneIntro_One(discount, _player);
	QuestOneIntro_Two(Time, comfort);
	return Accepted;

}

int main(void)
{
	string Time = "evening";
	string* pTime = &Time;

	Player* _player;
	string UnserializedJSON;	
	json Branches;

	ifstream Infile;
	Infile.open("dialogue_EN.json");
	cout << "Loading" << endl;
	Infile >> Branches;
	Infile.close();	

	cout << Branches.dump() << endl;

	_player = QuestOne_EnterDetails();
	bool QuestOneAccepted = QuestOneIntro(_player, pTime );

	return 0;
}
