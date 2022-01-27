#include <iostream>
#include <string>
using namespace std;

int main() {

	int initialOd;
	int finalOd;
	int days;
	string personsName;
	char yn;
	bool lux;
	int month;
	int error = 0;

	cout << "Odometer at start: ";
	cin >> initialOd;
	if (initialOd < 0)
	{
		error = 1;
	}

	cout << "Odometer at end: ";
	cin >> finalOd;
	if (finalOd < initialOd)
	{
		error = 2;
	}

	cout << "Rental days: ";
	cin >> days;
	cin.ignore(100000, '\n');
	if (days <= 0)
	{
		error = 3;
	}

	cout << "Customer name: ";
	getline(cin, personsName);
	if (personsName.empty())
	{
		error = 4;
	}

	cout << "Luxury car? (y/n): ";
	cin >> yn;
	if (yn == 'y') 
	{
		lux = true;
	}
	else if (yn == 'n')
	{
		lux = false;
	}
	else {
		error = 5;
	}

	cout << "Month (1=Jan, 2=Feb, etc.): ";
	cin >> month;
	if ((month > 12) || (month < 1)) 
	{
		error = 6;
	}

	cout << "---" << endl;
	if (error == 0)
	{
		//program got all the inputs properly! it will compute and output the correct answer
		int distance = finalOd - initialOd;
		double amount;
		double initialamount;
		double amountp1 = 0;
		double amountp2 = 0;
		double amountp3 = 0;
		//calculating the base charge
		if (lux)
		{
			initialamount = 61 * days;
		}
		else
		{
			initialamount = 33 * days;
		}
		//setting amountp1
		if (distance < 100)
		{
			amountp1 = distance * 0.27;
		}
		else
		{
			amountp1 = 27;
		}
		//setting amountp2
		if (distance > 100)
		{
			if (month < 4 || month == 12) 
			{
				if (distance < 400)
				{
					amountp2 = (distance - 100) * 0.27;
				}
				else 
				{
					amountp2 = 81;
				}
			}
			else 
			{
				if (distance < 400)
				{
					amountp2 = (distance - 100) * 0.21;
				}
				else
				{
					amountp2 = 63;
				}
			}
		}
		//setting amountp3
		if (distance > 400)
		{
			amountp3 = (distance - 400) * 0.19;
		}

		//adding all of the expenses together to get the total charge
		amount = initialamount + amountp1 + amountp2 + amountp3;
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << "The rental charge for " << personsName << " is $" << amount << endl;
		/*
		cout << "initialOd:" << initialOd << endl;
		cout << "finalOd: " << finalOd << endl;
		cout << "days: " << days << endl;
		cout << "personsName: " << personsName << endl;
		cout << "lux: " << lux << endl;
		cout << "month: " << month << endl;
		*/
		/*
		cout << initialamount << endl;
		cout << amountp1 << endl;
		cout << amountp2 << endl;
		cout << amountp3 << endl;
		*/
	}

	//somewhere along the line, an input was inputted incorrectly. this runs different error messages depending on the code.
	else if (error == 1)
	{
		//initialOd error
		cout << "The starting odometer reading must be nonnegative." << endl;
	}
	else if (error == 2)
	{
		//finalOd error
		cout << "The final odometer reading must be at least as large as the starting reading." << endl;
	}
	else if (error == 3)
	{
		//date error
		cout << "The number of rental days must be positive." << endl;
	}
	else if (error == 4)
	{
		//name error
		cout << "You must enter a customer name." << endl;
	}
	else if (error == 5)
	{
		//lux error
		cout << "You must enter y or n." << endl;
	}
	else if (error == 6)
	{
		//month error
		cout << "The month number must be in the range 1 through 12." << endl;
	}
	else
	{
		cout << "How did this happen? We're smarter than this." << endl;
	}
}