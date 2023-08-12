/*
  Compiler     :	Visual Studio 2022
  Group No.    :	22
  Group Members:	Kevin Chew Ken Yi, 1806611, MH
					Ong Yi Zhe, 2101135, MH
					Nafiz Azhar, 1900856, CL
					Tan Ke Keng, 2100647, MH
					Hemaganesh A/L Manoharan, 1905008, MH
					Peter Young Kwok Hua, 2100465, MH

*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cctype>
#include <string>
#include <Windows.h>
using namespace std;

//function prototypes
void summary();
void ordered_dish();
void bill_log();
void end_program();
void table_info();
void add_order();
void cancel_order();
void pay_and_clear_table();
void welcome_page();
void blinking(void);
void clearScreen(int characterLength);
void changeColour(int colour);

//global variables
int quantity[21][10] = { 0 };
string dishname[20] = { "0" };
double price[20] = { 0 };
int dishcode, tablenumber, dishquantity;
bool firstlog = 0;

//constant integers for welcome page animation
const int BLUE = 1;
const int GREEN = 2;
const int THREE = 3;
const int RED = 4;
const int FIVE = 5;
const int SIX = 6;
const int SEVEN = 7;
const int EIGHT = 8;
const int NINE = 9;
const int TEN = 10;
const int ELEVEN = 11;
const int TWELVE = 12;
const int WHITE = 15;

int main()
{
	//Retrieve data from configuration.txt into variables
	ifstream file("G22_MHCL_B_configuration.txt");

	if (!file)
	{
		cout << "Error opening G22_MHCL_B_configuration.txt file" << endl;
		exit(0);
	}

	if (file.is_open())
	{
		string temp;
		for (int i = 0; i < 20; i++)
		{
			getline(file, temp, '\t');
			dishname[i] = temp;
			getline(file, temp);
			price[i] = stod(temp);
		}
	}

	welcome_page();
	summary();
}

void summary()
{
	//show all ordered food for all table
	for (tablenumber = 1; tablenumber < 9; tablenumber++)
	{
		int count = 1;
		cout << "Table number: " << tablenumber << endl;
		cout << "No.\t" << "Dish\t\t" << "Quantity\t" << "Price" << endl;
		for (dishcode = 1; dishcode < 21; dishcode++)
		{

			if (quantity[dishcode][tablenumber] != 0)
			{

				cout << left << setw(3) << count << "\t" << setw(11) << dishname[dishcode - 1] << "\t" << setw(8) << quantity[dishcode][tablenumber] << "\t" << fixed << setprecision(2) << quantity[dishcode][tablenumber] * price[dishcode - 1] << endl;
				count = count + 1;
			}
		}
		cout << "-------------------------------------------------------------------------------------------------" << endl;
	}

	//give selection for user
	char selection_1;
	cout << "Press (o) for Ordered dish, (b) for Bill log, (t) to check for a table info, (e) for End, " << endl;
	cout << "Your selection: ";
	cin >> selection_1;
	selection_1 = tolower(selection_1);
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	while (selection_1 != 'e')
	{
		switch (selection_1)
		{
		case 'o':
			ordered_dish();
			break;
		case 'b':
			bill_log();
			break;
		case 't':
			cout << "Please enter table number: ";
			cin >> tablenumber;

			//confirm table number valid
			while (tablenumber <= 0 || tablenumber > 8)
			{
				cout << "Please enter table number: ";
				cin >> tablenumber;
			}

			table_info();
			break;
		}
		cout << "Press (o) for Ordered dish, (b) for Bill log, (t) to check for a table info, (e) for End," << endl;
		cout << "Your selection: ";
		cin >> selection_1;
		selection_1 = tolower(selection_1);
		cout << "-------------------------------------------------------------------------------------------------" << endl;
	}

	end_program();

	return;
}

//Displays list of all ordered dishes
void ordered_dish()
{
	int count = 1;
	//9 is the total
	cout << "No.\t" << "Dish\t\t" << "Quantity\t" << endl;
	for (dishcode = 1; dishcode < 21; dishcode++)
	{
		if (quantity[dishcode][9] != 0)
		{
			cout << left << setw(3) << count << "\t" << setw(11) << dishname[dishcode - 1] << "\t" << setw(8) << quantity[dishcode][9] << endl;
			count = count + 1;
		}
	}
}

void bill_log()
{
	//prints bill log
	ifstream bill_log("G22_MHCL_B_bill_log.txt");
	if (!bill_log)
		cout << "Error opening log file\n";
	else
	{
		char words[50];
		bill_log.getline(words, 50);
		while (bill_log)
		{
			cout << words << endl;
			bill_log.getline(words, 50);
		}
	}
	bill_log.close();
}

//Exit program
void end_program()
{
	char confirm;
	cout << "Confirm to end the program? (y/n) ";
	cin >> confirm;
	confirm = tolower(confirm);
	if (confirm == 'y')
		exit(0);
	else
		summary();
}

void table_info()
{
	double sum = 0;
	//display food ordered
	cout << "Table number: " << tablenumber << endl;
	cout << "No." << "\t" << "Dish" << "\t\t" << "Quantity" << "\t" << "Price" << endl;
	int count = 1;
	for (int dishcode = 1; dishcode < 21; dishcode++)
	{
		if (quantity[dishcode][tablenumber] != 0)
		{
			cout << left << setw(3) << count << "\t" << setw(11) << dishname[dishcode - 1] << "\t" << setw(8) << quantity[dishcode][tablenumber] << "\t" << fixed << setprecision(2) << quantity[dishcode][tablenumber] * price[dishcode - 1] << "\t" << endl;
			count = count + 1;
			sum += quantity[dishcode][tablenumber] * price[dishcode - 1];
		}

	}
	cout << "\t\t" << right << setw(24) << " Total: " << sum << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;

	//give selection for user
	char selection_2;
	cout << "Press (a) to add order, (c) to cancel order, (p) to pay and clear table, (s) to summary" << endl;
	cout << "Your selection: ";
	cin >> selection_2;
	selection_2 = tolower(selection_2);
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	while (selection_2 != 'p')
	{
		switch (selection_2)
		{
		case 'c':
			cancel_order();
			break;
		case 's':
			summary();
			break;
		case 'a':
			add_order();
			break;
		}
		cout << "Press (a) to add order, (c) to cancel order, (p) to pay and clear table, (s) to summary" << endl;
		cout << "Your selection: ";
		cin >> selection_2;
		selection_2 = tolower(selection_2);
		cout << "-------------------------------------------------------------------------------------------------" << endl;
	}
	pay_and_clear_table();
}

//Add order to table
void add_order()
{
	//user enter dish code and quantity 
	cout << "Enter dish code: ";
	cin >> dishcode;
	cout << "Enter quantity: ";
	cin >> dishquantity;

	//verification of dish code
	while (dishcode < 1 || dishcode > 20)
	{
		cout << "Enter dish code: ";
		cin >> dishcode;
		cout << "Enter quantity: ";
		cin >> dishquantity;
	}

	quantity[dishcode][tablenumber] += dishquantity;
	quantity[dishcode][9] += dishquantity;

	table_info();
}

//Cancel selected order
void cancel_order()
{
	//user enter dish code and quantity
	cout << "Enter dish code: ";
	cin >> dishcode;
	cout << "Enter quantity: ";
	cin >> dishquantity;

	//verification of dish code
	while (dishcode < 1 || dishcode > 20)
	{
		cout << "Enter dish code: ";
		cin >> dishcode;
		cout << "Enter quantity: ";
		cin >> dishquantity;
	}

	//verification of food quantity
	while (dishquantity > quantity[dishcode][tablenumber])
	{
		cout << "Enter dish code: ";
		cin >> dishcode;
		cout << "Enter quantity: ";
		cin >> dishquantity;
	}

	quantity[dishcode][tablenumber] -= dishquantity;
	quantity[dishcode][9] -= dishquantity;

	table_info();
}

void pay_and_clear_table()
{
	int count = 1;
	double sum = 0;

	//add to bill log
	ofstream bill_log;

	//checks if the bill log was saved in the same session
	if (firstlog == 1)
		bill_log.open("G22_MHCL_B_bill_log.txt", std::ios_base::app);
	else
		bill_log.open("G22_MHCL_B_bill_log.txt");

	//checks if bill log was opened successfully
	if (!bill_log)
	{
		cout << "Error opening log file\n";
	}
	else
	{
		bill_log << right << setw(26) << "BILL LOG" << endl;
		bill_log << "==============================================" << endl;
		bill_log << "Table " << tablenumber << endl;
		bill_log << "No." << "\t" << "Dish" << "\t\t" << "Quantity" << "\t" << "Price" << endl;
	}
	for (int n = 1; n < 21; n++)
	{
		if (quantity[n][tablenumber] != 0)
		{
			bill_log << left << setw(3) << count << "\t" << setw(11) << dishname[n - 1] << "\t" << setw(8) << quantity[n][tablenumber] << "\t" << fixed << setprecision(2) << quantity[n][tablenumber] * price[n - 1] << endl;
			count++;
			sum += quantity[n][tablenumber] * price[n-1];
		}

	}
	bill_log << "\t\t" << right << setw(24) << " Total: " << fixed << setprecision(2) << sum << endl;
	bill_log << setfill('=') << setw(46) << '=' << endl;
	bill_log.close();
	firstlog = 1;

	//clears total
	for (dishcode = 1; dishcode < 21; dishcode++)
	{
		quantity[dishcode][9] -= quantity[dishcode][tablenumber];
	}

	//clear table
	for (dishcode = 1; dishcode < 21; dishcode++)
	{
		quantity[dishcode][tablenumber] = 0;
	}
	summary();
}

//Welcome page animation
void welcome_page()
{
	string hello;
	hello = "WELCOME";
	int x = 0;
	cout << "       ";
	while (hello[x] != '\0')
	{
		cout << hello[x];
		Sleep(200);
		x++;
	};

	cout << "\n\n";

	string line1, line2, line3, line4, line5;
	line1 = "   )( ,\n";
	line2 = " |  ))|     o8Oo./\n";
	line3 = "C|====| ._o8o8o8Oo_.\n";
	line4 = " |    |  \\========/\n";
	line5 = " `----'   `------'\n";

	int a, b, c, d, e;
	a = 0;
	b = 0;
	c = 0;
	d = 0;
	e = 0;

	while (line1[a] != '\0')
	{
		cout << line1[a];
		Sleep(20);
		a++;
	};

	while (line2[b] != '\0')
	{
		cout << line2[b];
		Sleep(20);
		b++;
	};

	while (line3[c] != '\0')
	{
		cout << line3[c];
		Sleep(20);
		c++;
	};

	while (line4[d] != '\0')
	{
		cout << line4[d];
		Sleep(20);
		d++;
	};

	while (line5[e] != '\0')
	{
		cout << line5[e];
		Sleep(20);
		e++;
	};

	blinking();
}

//Blinking lines for welcome animation
void blinking(void)
{
	int i;
	string closed = "- - - - - - - - - - -", open = "* * * * * * * * * * *";
	int colour[] = { RED, GREEN, THREE, BLUE, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ELEVEN, TWELVE };

	cout << closed;

	for (i = 0; i < 12; i++)
	{
		Sleep(200);

		clearScreen(21);
		changeColour(colour[i]);

		cout << open;

		Sleep(200);

		clearScreen(21);
		changeColour(WHITE);

		cout << closed;
	}

	clearScreen(5);
	changeColour(WHITE);
	cout << "\n" << "-------------------------------------------------------------------------------------------------" << endl;
}

//Clear screen for animation
void clearScreen(int characterLength)
{
	for (int i = 0; i < characterLength; i++)
	{
		cout << "\b";
	}
}

//Colour changing settings
void changeColour(int colour)
{
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);
}