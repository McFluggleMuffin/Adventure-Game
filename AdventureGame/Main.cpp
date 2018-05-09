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
};
class Mage : public Player
{
	public:
		Mage(string N) : Player(0,5,10,N) {}
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
		Branch(vector<string> _dialogue) : dialogue(_dialogue) {}
	private:
};

void ParseDialogue(json _j, vector<string>* _dialogue)
{
	for (auto it = _j.begin(); it != _j.end(); ++it)
	{
    		std::cout << it.key() << " | " << it.value()["dialogue"] << "\n";
	}
}
void ParseBranches(json _j, vector<Branch*> _branches)
{


}
void StoryBranch(string _branch, json _j)
{
	cout << _j[_branch]["dialogue"][0].get<std::string>() << endl;
	int Choice;
	cin >> Choice;
	StoryBranch(_j[_branch]["branches"][Choice - 1], _j);
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
	vector<string> temp;	
	vector<string>* ptemp;
	ptemp = &temp;
	StoryBranch("entrypoint", Branches);
	Entry();
	return 0;
}
