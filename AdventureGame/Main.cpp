#include<iostream>
#include<string>
#include<vector>
#include<fstream>

#include "Main.hpp"
#include "nlohmann/json.hpp"
const std::string JsonStoryTag::narrative = "narrative";
const std::string JsonStoryTag::branches = "branches";
const std::string JsonStoryTag::options = "options";
const std::string JsonStoryTag::functions = "functions";

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

void StoryBranch(string _branch, json _j)
{
	vector<string> NARRATIVE = _j[_branch][JsonStoryTag::narrative].get<std::vector<string>>();
	for (auto child : NARRATIVE)
	{
		cout << child << endl;
	}
	vector<string> FUNCTIONS = _j[_branch][JsonStoryTag::functions].get<std::vector<string>>();
	for (auto child : FUNCTIONS)
	{
		//TODO run functions based on strings in FUNCTIONS
	}
	vector<string> OPTIONS = _j[_branch][JsonStoryTag::options].get<std::vector<string>>();
	if (OPTIONS.size() == 0)
	{
		for (auto child : OPTIONS)
		{
			cout << child << endl;
		}
		int Choice;
		cin >> Choice;
		LeaveSpace();
		//TODO move for loop for functions and run them all
		StoryBranch(_j[_branch][JsonStoryTag::branches][Choice - 1], _j);
	}
	else
	{
		//TODO run all functions in array
		StoryBranch(_j[_branch][JsonStoryTag::branches][0], _j);
	}
}

void Entry(void)
{
	cout << "Hi, welcome, what is your name" << endl;
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
	LeaveSpace();
	StoryBranch("entrypoint", Branches);
	return 0;
}
