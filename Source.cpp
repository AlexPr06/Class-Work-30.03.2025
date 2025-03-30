#include <iostream>
#include <vector>
#include <ctime>

#define INDENT cout << endl;


using namespace std;


class Animal
{
public:
	virtual void makeSound() {
		cout << "Some sound" << endl;
	}
	
};

class Dog : public Animal
{
public:
	void makeSound() override {
		cout << "Woof" << endl;
	}
};
class Cat : public Animal
{
public:
	void makeSound() override {
		cout << "Meow" << endl;
	}
};

class Bird : public Animal
{
public:
	void makeSound() override {
		cout << "Chirp" << endl;
	}
};




// Task 1


//class Payment
//{
//public:
//	virtual void pay()
//	{
//
//		cout << "Type of payment" << endl;
//	}
//};
//
//
//
//class CreditCard : public Payment
//{
//public:
//	static int number;
//
//
//	void pay() override
//	{
//		cout << "Credit Card" << endl;
//	}
//};
//
//int CreditCard::number = 10;
//
//class Cash : public Payment
//{
//	void pay() override
//	{
//		cout << "Cash" << endl;
//	}
//};
//
//class Cryptocurrency : public Payment
//{
//	void pay() override
//	{
//		cout << "Cryptocurrency" << endl;
//	}
//};
//
//class PayPal : public Payment
//{
//	void pay() override
//	{
//		cout << "PayPal" << endl;
//	}
//};
//
//class ApplePay : public Payment
//{
//	void pay() override
//	{
//		cout << "ApplePay" << endl;
//	}
//};


//Task 2

//class MethodOfConstruction
//{
//public:
//	virtual void build()
//	{
//		cout << "Type of construction" << endl;
//	}
//};
//
//class BrickMasonry : public MethodOfConstruction
//{
//	public:
//	void build() override
//	{
//		cout << "Brick Masonry method of construction" << endl;
//	}
//};
//
//class  MonolithicConstruction : public MethodOfConstruction
//{
//public:
//	void build() override
//	{
//		cout << "Monolithic Construction method of construction" << endl;
//	}
//};
//
//class  FrameConstruction : public MethodOfConstruction
//{
//public:
//	void build() override
//	{
//		cout << "Frame Construction method of construction" << endl;
//	}
//};
//
//class  PanelConstruction : public MethodOfConstruction
//{
//public:
//	void build() override
//	{
//		cout << "Panel Construction method of construction" << endl;
//	}
//};
//
//class  CastInPlaceConstruction : public MethodOfConstruction
//{
//public:
//	void build() override
//	{
//		cout << "Cast In Place Construction method of construction" << endl;
//	}
//};


// Task 3

class TicTacToeField
{

public:

	vector<vector<char>> field;
	TicTacToeField() {
		field = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
	}

	void resetField() {
		field = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
	}

	virtual void drawField()
	{
		for (int i = 0; i < field.size(); i++)
		{
			for (int j = 0; j < field[i].size(); j++)
			{
				cout << field[i][j] << "  ";
			}
			cout << endl;
		}
	}

	bool getWinner() {
		// Перевірка рядків та стовпців
		for (int i = 0; i < 3; i++) {
			if (field[i][0] == field[i][1] && field[i][1] == field[i][2]) return field[i][0]; // Рядок
			if (field[0][i] == field[1][i] && field[1][i] == field[2][i]) return field[0][i]; // Стовпець
		}

		// Перевірка діагоналей
		if (field[0][0] == field[1][1] && field[1][1] == field[2][2]) return field[0][0]; // Головна діагональ
		if (field[0][2] == field[1][1] && field[1][1] == field[2][0]) return field[0][2]; // Побічна діагональ

		// Перевірка нічиєї (немає вільних клітинок)
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (field[i][j] != 'X' && field[i][j] != 'O') {
					return '\0'; // Гра триває
				}
			}
		}

		return 'D'; // Нічия
	}

	// Getters
	char getFieldPosition(int i, int j)
	{
		char position = field[i][j];
		return position;
	}

	// Setters

	void setFieldPosition(int i, int j, char value)
	{
		field[i][j] = value;
	}
};


class Move
{
public:
	virtual void move()
	{
		return;
	}
};



class UserMove : public Move, public TicTacToeField
{
private:
	char userSymbol;
	TicTacToeField& customField;

public:
	UserMove(TicTacToeField& field, char userS) : customField(field), userSymbol(userS) {} // Constructor


	void move() override
	{
		int userPosition;

		while (true)
		{
			cout << "\033[032mUser move\033[0m" << endl;
			INDENT
			cout << "\033[033mEnter the position: \033[0m";
			cin >> userPosition;

			if (cin.fail()) {
				cout << "\033[031m Error! Please, enter a number.\033[0m\n" << endl;
				cin.clear(); 
				cin.ignore(1000, '\n');
				continue;
			}

			if (userPosition < 1 || userPosition > 9)
			{
				cout << "\033[031mInvalid position. Please enter a valid position: \033[0m" << endl;
				continue;
			}




			int I = (userPosition - 1) / 3;
			int J = (userPosition - 1) % 3;


			bool isPositionTaken = (customField.getFieldPosition(I, J) != static_cast<char>(userPosition + '0'));

			if (isPositionTaken) {
				cout << "\033[31mPosition is already taken. Please enter a valid position.\033[0m" << endl;
				continue;
			}


			customField.setFieldPosition(I, J, userSymbol);


			break;

		}
	}
};

class ComputerMove : public Move, public TicTacToeField
{
private:
	char computerSymbol;
	TicTacToeField& customField;
public:
	ComputerMove(TicTacToeField& field, char computerS) : customField(field), computerSymbol(computerS) {} // Constructor

	void move() override
	{
		INDENT
		cout << "\033[032mComputer move\033[0m" << endl;

		while (true)
		{
			int randomPosition = rand() % 9 + 1;
			int I = (randomPosition - 1) / 3;
			int J = (randomPosition - 1) % 3;

			bool isPositionTaken = (customField.getFieldPosition(I, J) != static_cast<char>(randomPosition + '0'));

			if (isPositionTaken) {
				continue;
			}

			customField.setFieldPosition(I, J, computerSymbol);
			break;
		}
	}
};




int main()
{
	/*Animal* myDog = new Dog();
	myDog->makeSound();

	Animal* myCat = new Cat();
	myCat->makeSound();

	Animal* myBird = new Bird();
	myBird->makeSound();

	delete[] myDog;
	delete[] myCat;
	delete[] myBird;*/



	// TASK 1
	/*Payment* myCreditCard = new CreditCard();
	myCreditCard->pay();

	cout << CreditCard::number << endl;

	Payment* myCash = new Cash();
	myCash->pay();

	Payment* myCryptocurrency = new Cryptocurrency();
	myCryptocurrency->pay();

	Payment* myPayPal = new PayPal();
	myPayPal->pay();

	Payment* myApplePay = new ApplePay();
	myApplePay->pay();

	delete[] myCreditCard;
	delete[] myCash;
	delete[] myCryptocurrency;
	delete[] myPayPal;
	delete[] myApplePay;*/

	// Task 2
	/*MethodOfConstruction* myBrickMasonry = new BrickMasonry();
	myBrickMasonry->build();
	INDENT

	MethodOfConstruction* myMonolithicConstruction = new MonolithicConstruction();
	myMonolithicConstruction->build();
	INDENT

	MethodOfConstruction* myFrameConstruction = new FrameConstruction();
	myFrameConstruction->build();
	INDENT

	MethodOfConstruction* myPanelConstruction = new PanelConstruction();
	myPanelConstruction->build();
	INDENT

	MethodOfConstruction* myCastInPlaceConstruction = new CastInPlaceConstruction();
	myCastInPlaceConstruction->build();
	INDENT




	delete[] myBrickMasonry;
	delete[] myMonolithicConstruction;
	delete[] myFrameConstruction;
	delete[] myPanelConstruction;
	delete[] myCastInPlaceConstruction;*/



	srand(time(0));


	TicTacToeField* myField = new TicTacToeField();
	UserMove* userMove = new UserMove(*myField, 'X');
	ComputerMove* computerMove = new ComputerMove(*myField, 'O');
	myField->drawField();
	INDENT

	int randNum = rand() % 2;
	bool userPlaysFirst;
	if (randNum == 0)
	{
		userPlaysFirst = false;
		cout << "\033[034mComputer plays first\033[0m" << endl;
	}
	else
	{
		userPlaysFirst = true;
		cout << "\033[034mUser plays first\033[0m" << endl;
	}
	INDENT INDENT
	

	while (true)
	{
		if (userPlaysFirst)
		{
			userMove->move();
			myField->drawField();
			INDENT

			userPlaysFirst = false;


			char winner = myField->getWinner();
			if (winner != '\0') {
				if (winner == 'X') cout << "\033[032mUser wins!\033[0m" << endl;
				else if (winner == 'O') cout << "\033[031mComputer wins!\033[0m" << endl;
				else cout << "\033[033mIt's a draw!\033[0m" << endl;
				break;
			}

		}
		else
		{
			computerMove->move();
			myField->drawField();
			INDENT

			userPlaysFirst = true;


			char winner = myField->getWinner();
			if (winner != '\0') {
				if (winner == 'X') cout << "\033[032mUser wins!\033[0m" << endl;
				else if (winner == 'O') cout << "\033[031mComputer wins!\033[0m" << endl;
				else cout << "\033[033mIt's a draw!\033[0m" << endl;
				break;
			}
		}

	}


	return 0;
}