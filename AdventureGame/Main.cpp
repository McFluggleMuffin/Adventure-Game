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
		Player(int S, int A, int I, string N) : Name(N), Strength(S), Agility(A), Intelect(I){}
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
		Wallet wallet;
	private:
		string Name;
		int Strength;
		int Agility;
		int Intelect;
};
class Warrior : public Player
{
	public:
		Warrior(string N) : Player(10,5,0,N) {}
		void Shout(void);
};
class Mage : public Player
{
	public:
		Mage(string N) : Player(0,5,10,N) {}
		void Shout(void);
};

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

void Entry(void)
{
	cout << "Hi, welcome, what name" << endl;
	string name;
	cin >> name;
}

int main(void)
{
	
	string UnserializedJSON;	
	json Branches;

	ifstream Infile;
	Infile.open("dialogue_EN.json");
	cout << "Loading" << endl;
	Infile >> Branches;
	Infile.close();	

	cout << Branches.dump() << endl;
	Entry();
	return 0;
}
