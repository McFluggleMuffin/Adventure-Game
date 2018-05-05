#include<iostream>
#include<string>
#include<vector>

using namespace std;

class PartyMember
{
	public:
		PartyMember(int S, int A, int I, string N) : Name(N), Strength(S), Agility(A), Intelect(I) {}
		static PartyMember* make_member(int Choice, string N);
		virtual void Shout(void) = 0;
		bool StrengthTest(int Pass){return Pass <= Strength;}
		bool AgilityTest(int Pass){return Pass <= Agility;}
		bool IntelectTest(int Pass){return Pass <= Intelect;}
	private:
		string Name;
		int Strength;
		int Agility;
		int Intelect;
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
	case 2: 	
		return new Mage(N);
	}
	return NULL;
}

PartyMember* Setup(void)
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

int main(void)
{
	vector<PartyMember*> Party;
	Party.push_back(Setup());
	Party[0]->Shout();
	cout << Party[0]->StrengthTest(8) << endl;
	return 0;
}
