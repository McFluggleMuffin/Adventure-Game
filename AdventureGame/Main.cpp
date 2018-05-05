#include<iostream>
#include<vector>
#include<string>
using namespace std;

class CharacterClass;
{
	public:
		int Strength;	
		int Agility;
		int Magika;
		CharacterClass(int S, int A, int M);
};
CharacterClass::CharacterClass(int S, int A, int M)
{
	Strength = S;
	Agility = A;
	Magika = M;
}	

class Warrior: public CharacterClass
{
	public:
		Warrior(void);
};
Warrior::Warrior(void)
{
	CharacterClass(10,5,0);
}

class PartyMember
{
	public: 
		string Name;
		CharacterClass* MemberClass
		PartyMember(string N);
};
PartyMember::PartyMember(string N)
{
	Name = N;
}

int main(void)
{

	cout << "Hello, please input the name of your first party member" << endl;
	string Name;
	cin >> Name;
	vector<string> Classes = {"1. Warrior", "2. Mage", "3. Archer"};
	cout << "What class do you want " + Name + " to be?" << endl;
	for(string i : Classes)
	{
		cout << i << endl;
	}
	int ClassChoice;
	cin >> ClassChoice;
	vector<PartyMember*> Party;
	PartyMember* pm1(Name);
	switch (ClassChoice) 
	{
	case 1 :
		pm1->MemberClass = new Warrior();
		break;
	default :
		cout << "Please select a valid class" << endl;
		break;
	}
	cout << Party[0]->Name << endl;
	return 0; 

};
