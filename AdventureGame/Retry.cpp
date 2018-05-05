#include<iostream>
#include<string>
#include<vector>

using namespace std;

class PartyMember
{
	public:
		PartyMember(int S, int A, int M, string N) : Strength(S), Agility(A), Magika(M), Name(N) {}
		static PartyMember* make_member(int Choice, string N);
		virtual void Shout(void) = 0;
	private:
		string Name;
		int Strength;
		int Agility;
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
	case 2: 	
		return new Mage(N);
	}
}

PartyMember* Setup(void)
{
	cout << "Hello, welcome to the Bearded Woman, the best tavern in the land!" << endl;
	cout << "Mind introducing yourself stranger? What's your name?" << endl;
	string Name;
	cin >> Name;	
	cout << "Well then " + Name + ", what are you known to be?" << endl;
	int Choice;
	cin >> Choice;
	do
	{
		if (Choice <= 2 && Choice >= 1)
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
	return 0;
}
