#include<iostream>
#include<string>
#include<vector>

using namespace std;

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

class PartyMember
{
	public:
		PartyMember(int S, int A, int I, string N) : Name(N), Strength(S), Agility(A), Intelect(I), Health(S * 2), Stamina(A * 2), Magika(I * 2) {}
		static PartyMember* make_member(int Choice, string N);
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

class Warrior : public PartyMember
{
	public:
		Warrior(string N) : PartyMember(10,5,0,N) {}
		void Shout(void);
};
void Warrior::Shout(void)
{
	cout << "I am a mighty warrior" << endl;
}

class Mage : public PartyMember
{
	public:
		Mage(string N) : PartyMember(0,5,10,N) {}
		void Shout(void);
};
void Mage::Shout(void)
{
	cout << "I am a wizard" << endl;
}

PartyMember* PartyMember::make_member(int Choice, string N)
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

PartyMember* InitialEncounter(void)
{
	
	vector<string> AllClasses = {"1. Warrior", "2. Mage"};
	
	cout << "Hello, welcome to the Bearded Woman, the best tavern in the land!" << endl;
	cout << "Mind introducing yourself stranger? What's your name?" << endl;
	string Name;
	cin >> Name;	
	cout << "Well then " + Name + ", what are you known to be?" << endl;
	for (string C : AllClasses)
	{
		cout << C << endl;
	}
	int Choice;
	cin >> Choice;
	do
	{
		if (Choice <= static_cast<int>(AllClasses.size()) && Choice >= 1)
		{
			return PartyMember::make_member(Choice, Name);
		}
		else 
		{
			cout << "Please enter a valid response" << endl;
		}
	}
	while(true);
}

void QuestOneIntro_One(bool discount, PartyMember* Adventurer)
{
	string LowPrice;
	string HighPrice;
	vector<int> LowPricev;
	vector<int> HighPricev;
	if (discount)
	{
		LowPrice = "75 bronze";
		HighPrice = "8 silver";		
		LowPricev = {0, 0, 75};
		HighPricev = {0, 8, 0};
	}	
	else
	{
		LowPrice = "2 silver";
		HighPrice = "10";
		LowPricev = {0, 2, 0};
		HighPricev = {0, 10, 0};
	}
	LeaveSpace();
	cout << "A room is " + LowPrice + " pieces a night, or " + HighPrice + " for the nicer rooms at the top" << endl;
	cout << "1. Hand over " + LowPrice + " for a room" << endl;
	cout << "2. Pay the " + HighPrice + ", it's been a long day on the road, you want the nicer bed" << endl;
	cout << "3. You don't need the room, you're just here for a drink" << endl;  
	int Choice;
	cin >> Choice;
	bool BarOrBed;
	switch (Choice)
	{
		case 1:
			Adventurer->Pay(LowPrice[0], LowPrice[1], LowPrice[2]);
			cout << "Thanks, here's your key, you'll be in room 4" << endl;
			break;
		case 2:
			Adventurer->Pay(HighPrice[0], HighPrice[1], HighPrice[2]);
			cout << "Thanks, here's your key, you'll be in room 12" << endl;
			break;
		case 3:
			cout << "I see, well the bar is just around the corner, come back if you want to stay the night" << endl;
			break;
	}
}
bool QuestOneIntro_Two(void)
{
	LeaveSpace();
	cout << "If you're looking for a drink, the bar is just around the corner there" << endl;
	cout << "1. Head up to your room, you need the sleep" << endl;
	cout << "2. A drink at the bar sounds good" << endl;
	int Choice;
	cin >> Choice;
	switch (Choice)	
	{
		case 1:
			return true;	
			break;
		case 2:
			return false;	
			break;
	}	
}
bool QuestOneIntro(vector<PartyMember*> Party)
{
	bool Accepted = false;
	LeaveSpace();
	cout << "Nice to meet you, I'm Gregor Karlsson, innkeeper here at the Bearded Woman." << endl;
	cout << "Say, an adventurer like yourself wouldn't be looking for a job would you, put a little cash in your pocket?" << endl;
	cout << "1. Politely decline, you don't need the money anyway" << endl;
	cout << "2. Ask for more details, you can't agree without them" << endl;
	cout << "3. You had me at money!" << endl;
	int Choice_1;
	cin >> Choice_1;
	int Choice_2;
	bool discount = false;
	switch (Choice_1)
	{
		
		case 1:
			cout << "Aww well" << endl;
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
			int Choice_3;
			cin >> Choice_3;
			switch (Choice_3)
			{
				case 1:
					cout << "Clear out the cave, and I'll give you 20 gold pieces" << endl;
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
			break;
	}
	QuestOneIntro_One(discount, Party[0]);
	return Accepted;
}
	

int main(void)
{
	vector<PartyMember*> Party;
	Party.push_back(InitialEncounter());
	bool QuestOneAccepted = QuestOneIntro(Party);
	return 0;
}
