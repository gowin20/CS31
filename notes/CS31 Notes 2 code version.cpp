CS31 Notes Pt 2

Week 5+


c strings have '\o' at the end to delineate the end of a string

vector<int> k, 				//a dynamic array, that can change size and stuff

std::array<double 5> b;

^ c++ array. 
b[1]
possible to do b.size()





start
get string

run through string
//	check for valid state codes
//	check for valid party inputs
	
	/*
	string data = "CT5D,NY9R17D1I,VT,ne3r00D";
	char part;
	int seatTally = 0;
	bool ret = hasProperSyntax(data);
	if (ret)
		cout << data << " has PROPER SYNTAX" << endl;
	else
		cout << data << " DOESNT HAVE PROPER SYNTAX" << endl;
	cout << "enter the party for which you wish to tally seats: ";
	cin >> part;
	tallySeats(data, part, seatTally);
	cout << "The " << part << " party is projected to get " << seatTally << " seats." << endl;
*/

string is a vector of characters.

tosum problem

VERY common interview question
use a hash table

bool isPair(int foo[], int size, int k);



dynamic memory allocation:

the stack and the heap
stack:


int foo(int n)
{
	int k = 5
	chat c[] = "Hello";
}
the value of k will go on the stack, if it doesn't go in the register
when a function is called you have to allocate more memory for it, so the stack grows
the characters of c[] go on the stack too. However, the stack is limited (see stackoverflow). If you go over the stack limit, the program will crash RIP. 

In c++, use:
operator new

in c, use:

malloc
and 
dealloc

only use it if you know what you're doing, though, because you have to manually manage memory
when you're done with new, call delete. Otherwise you could cause a memory leak
Other languages have something called garbage collection that prevents it. The problem is that it can cause delays and stuff at inopportune times, so C/C++ is a lot more efficient in those regards.

hash tables:












template<class _T>
void swap(_T& a, _T& b)
{
	_T tempt = a;
	a = b;
	b = temp;
}







void diagonal(int a[][], int n)
{
	for (int i = 0; i != size(a), i++)
	{
		cout << a[i][i];
	}
}






Discussion W5

Array

<type> <name>[size]

int a[4] =
{1, 2, 3, 4}
 (0  1  2  3) <- location in array

a[i] is the i-th variable, i is a positive integer const

const int N = 10;
ant a[N];

each element of the array is a variable duh

cannot set the size of the array to anything less than the number of elements in the initialization statement. More than that is ok tho


Multidimensional arrays

int i[ROWS][COLUMNS];

int i[ROWS][COLUMNS] = {
{row_00, row_01, ...}
{row_10, row_11, ...}
...,
{row_i0, row_i1, ...}
}

void fibo10(int fib[]);
can pass the size of the array as an int n
void fibo10(int fib[], int n);

void fibo10(int fib[][], int n);




bool isValidDate(int y, int m, int d)
{
	const int daysInMonth[12] = 
	{
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	};
	
	...
	
	if (m < 1 || m > 12 || d < 1)
		return false
	if (m != 2)
		return d <= daysInMonth[
	
	
}


const int MAX_NUMBER_OF_SCORES = 10000;
int scores[MAX_NUMBER_OF_SCORES];
int nScores = 0;
int total = 0;
cout << "Enter the scores (negative when done): ";
for (;;)
{
	int s;
	cin >> s;
	if (s < 0)
		break;
	if (nScores == MAX_NUMBER_OF_SCORES)
	{
		cout << "This program is only equipped to handle " << MAX_NUMBER_OF_SCORES << " scores." << endl;
		cout << "Continuing with just the first " << MAX_NUMBER_OF_SCORES << " values." << endl; 				
							//if your program is gonna take some sort of recovery action, inform the user as to what it is you're doing
		break;
	}
	total += s;
	scores[nScores] = s;
	nScores++;
}
if (nScores == 0)
	cout << "There were no scores, so no statistics" << endl;
else
{
	double mean = static.cast<double>(total)/nScores;
	cout << "The average of all the scores is " << mean << endl;
	double sumOfSquares = 0;
	for (int k = 0; k < nScores; k++)
	{
		double diff = scores[k] - mean;
		sumOfSquares += diff * diff;
	}
	cout << "The std. deviation is " << sqrt(sumOfSquares/nScores) << endl;

}




int main()
{
	const int MAX_NUMBER_OF_SCORES = 10000;
	int scores[MAX_NUMBER_OF_SCORES];
	int nScores = 0;
			... //fill up the array
	double m = computeMean(scores, nScores)
	
	..
	int stuff[100];
		... //fill up the array
	double m2 = computeMean(stuff, 100);
}


//no way you can ask for how many elements are in an array, just by using the array name.
//in a function from an array parameter itself, you know nothing about how many elements are in an array. 
double computeMean(const int a[], int n) //const int a[] is an array of integers that the program promises not to modify.
{
	if (n == 0)
		return 0;
	int total = 0;
	for (int k = 0; k < n; k++)
	{
		total += a[k];
	}
	return static.cast<double>(total) / n; 
						//creating a temporary double named total and dividing it by n, returns the result of that. this is how you convert ints into doubles for computations
}

void setFirst(int a[], int n, int value)
{
	if (n >= 1)
		a[0] = value;
	... computeMean(a, n) ...
	
}



===================================================================================================
				C++ Strings
===================================================================================================

#include <string>
using namespace std;

string t = "Ghost"
string s; //empty string

for (int k = 0; k != t.size; k++)
	cout << t[k] << endl;
	
cout << t;
getline(cin, s);

s = t; //sets s to Ghost
s += "!!!"; // sets s to Ghost!!!

if (t < s)
	...

===================================================================================================
								C Strings
===================================================================================================

Comparing Strings:
	If both strings are the same length and have the same characters at the same point, they're equal. It compares letters based on their encoded values
	Ghostwriter
	Ghoul
	Ghostwriter < Ghoul
	The lengths don't matter, it's the encoded values of the characters at each location in the string.
	Creates the same order that a dictionary would.
	
	Ghostwriter > Ghost


find the first character that's a zero byte ---> count how many interesting characters there are in a string.

C Strings are just arrays of chars

#include <cstring>

char t[10] = { 'G', 'h', 'o', 's', 't');
char t[10] = "Ghost";
char s[100] = "";

	/*
	for (int k = 0; k != strlen(t); k++) //don't do this
		cout << t[k] << endl;
	*/
for (int k = 0; t[k] != '\0'; k++)
	cout << t[k] << endl;
	
cout << t;
cin.getline(s, 100);

//s = t; // gives you an error: can't assign arrays
	strcpy(s, t); //strcpy(destination, source)
			//strcpy(t, "abcdefghij");

strcat(s, "!!!");	//now s is "Ghost!!!"
	
//if (t < s) //this will compile properly but not function properly

	... strcmp(a, b) ...
			returns
				negative if a comes before b
				0 if a equals b
				positive if a comes after b

C++ strings: a OP b
C strings: strcomp(a, b) OP 0


Is a equal to b?
	WRONG: if (strcmp(a, b)) //this yields the opposite result?
	
	RIGHT: if (strcmp(a, b) == 0)
	
Does a come before b?
	WRONG: if (a < b) // will compile for C strings, but it doesn't do what you want
	
	RIGHT: if (strcmp(a, b) < 0)
	
void f(const char cs[])
{
	...
}

int main()
{
	string s = "Hello";
	f(s); //won't compile, because this is a C++ string not a c string
	f(s.c.str()); //works ok
	
	chat t[10] = "Ghost";
	s = t; //s is now Ghost
	s = "Wow"
	t = s; //won't compile
	t = s.c.str(); //also won't compile
	strcpy(t, s.c.str()); //t is now Wow
}

const int x = 10;
int y = 10;
int z = x;





Lil program action

						const int NWEEKS = 5;
						const int NDAYS = 7;

						int attendance[NWEEKS][NDAYS];

						cout << attendance[2][5];

						for (int w = 0; w < NWEEKS; w++)
						{
							int t = 0;
							for (int d = 0; d < NDAYS; d++)
								t += attendance[w][d];
							cout << "The total for week " << w << " is " << t << endl;
						}

						const string dayNames[NDAYS] =
						{
							"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
						};

						int grandTotal = 0;
						for (int d = 4 /* Friday */; d < NDAYS; d++)
						{
							int t = 0;
							for (int w = 0; w < NWEEKS; w++)
								t += attendance[w][d];
							cout << "The total for week " << w << " is " << t << endl;
							grandTotal += t;
						}
						cout << "Over the course of " << NWEEKS << " weeks, weekend attendance was " << grandTotal << endl;


						double computeMean(const int a[], int n);

						double meanForADay(const int a[][NDAYS], int nRows, int dayNumber)
						{
							if (nRows <= 0)
								return 0;
							int total = 0;
							for (int r = 0; r < ; r++)
								total += a[r][dayNumber];
							return static.cast.double(total) / nRows;
						}

						int main()
						{
							int attendance[NWEEKS][NDAYS];
							...
							double meanFri = meanForADay(attendance, NWEEKS, 4 /* Friday */);
							...
						}


void makeUpperCase(string& s)
{
	for (int k = 0; k != s.size(); k++)
		s[k] = toupper(s[k]);
}

void makeUpperCase(char s[])
{
	for (int k = 0; s[k] != '\0'; k++)
		s[k] = toupper(s[k]);
}



const int MAX_WORD_LENGTH = 6;

int main()
{
	const int MAX_PETS = 5;
	char pets[MAX_PETS][MAX_WORD_LENGTH + 1] = { //equivalent to string pets[MAX_PETS];
	"cat", "mouse", "eel", "ferret", "horse"
	};
	
	cout << countLength(pets, MAX_PETS, 5); //how many 5-character strings are there?
}


// C STRING VERSION
int countLength(const char a[][MAX_WORD_LENGTH + 1], int n, int targetLength)
{
	int total = 0;
	for (int k = 0; k < n; k++)
	{
		if (strlen(a[k] == targetLength)
			total++;
	}
	return total;
}

// C++ STRING VERSION
int countLength(const string a[], int n, int targetLength)
{
	int total = 0;
	for (int k = 0; k < n; k++)
	{
		if (a[k].size() == targetLength)
			total++;
	}
	return total;
}


====================================================================================================================================
												POINTERS
====================================================================================================================================
/*
Four major uses of pointers:

	Another way to implement passing by reference
		
	Transverse arrays
		usually done through integer subscripts (k = 0; k < n; k++)
		possible to do with pointers instead
	Manipulate dynamic storage/memory
	Represent relationships in data structures

*/


#include <cmath>
using namespace std;


void polarToCartesian(double rho, double theta, double* xx, double* yy);

int main()
{
	double r;
	double angle;
	//get values for r and angle
	double x;
	double y;
	polarToCartesian(r, angle, x, y);
	...
	double y2;
	polarToCartesian(2*r, angle, x, y2);
}

void polarToCartesian(double rho, double theta, double* xx, double* yy);
{
		xx = rho * cos(theta);
		yy = rho * cos(theta);
}



/*
//a double is 8 bytes long. a pointer for a double is only 4 bytes long, and is basically an arrow pointing to a specific memory address
//we're not passing xx, we're passing a pointer to x. The operator for that is &

double& means reference-to-double or another-name-for-some-double
double* means pointer-to-double or the-address-of-some-double

&x means "generate a pointer to x"		"the address of x"

*p means "follow the pointer p"	       "the object that p points to"
//reference: another name for the object
//pointer: value of the memory of the object
usually we're gonna use reference variables instead of pointers to reference things, but there are applications for both
pointers are the only way to pass by reference in C
*/


	polarToCartesian		main
	rho[5]					[5]r
	theta[0]				[0]angle
	xx[]		<----		[???]x
	yy[]		<----		[???]y

//	don't put the thing in xx, look at xx to see where we're talking about, and then put the value there (in this case, in x)
										//DONT DO THESE
double a = 3.;
double b = 5.1;
double* p = &a;
										//double* q = 7.6
double c = a;

double d = *p;							//double d = p
double& dd = d; //reference, not pointer

p = b; //won't compile. P is a pointer to a double, b is a double.
p = &b; //works, assigns one pointer to another

*p += 4; // *p = *p + 4
										//p = &k; no
int k = 7;

int* z = &k;

cout << (k * b);						//cout << (k b);

cout << (k * *p);		cout << (k**p);
cout << (*z**p);		cout << (*z * *p);

double* q;
										// *q = 4.7; --> causes undefined behavior: q is uninitialized

q = p;
double* r = &a;
*r = b;
if (p == r) //falce -> comparing 2 pointers

if (p == q) //true -> comparing 2 pointers

if (*p == *r) //true -> comparing 2 doubles

//There's a difference between the pointer and the thing pointed to

//Sample Program
const int MAXSIZE = 5;
double da[MAXSIZE];
int k;
double* dp;

//using integer subscripts to visit each element
for (k = 0; k < MAXSIZE; k++)
	da[k] = 3.6;

//using pointers to visit each element	
for (dp = &da[0]; dp < &da[MAXSIZE]; dp++) // dp++ -> dp += 1 -> dp = dp + 1
	*dp = 3.6;
	//assigning elements in the array values
	//*dp = 3.6;
	//*(&da[0]) = 3.6;
	//da[0] = 3.6;

//pointer to element i of a, plus an integer j, is a pointer to element i+j of the array. Legal to go up to the size of the array but not past!
dp = dp + 1;
dp = &da[0] + 1;
dp = &da[0 + 1];
dp = &da[1];


//all 4 of these lines mean the same thing
&da[5]
&da[0 + 5]
&da[0] + 5
da + 5

//pointer arithemetic in C++ is always in the unit of the thing being pointed to - e.g. doubles, ints, etc. ex. if you add 1 to a double location you go forward "1 double"

*&x ==> x;
&a[i] + j ==> &a[i + j] //same with subtraction
&a[i] < &a[j] ==> i < j //also works with all other logic symbols
a <===> &a[0]

//by definition, if you define a parameter to a function and declare it in array form, what you're really declaring is a pointer. SHOCK AND ALARM
int lookup(const string* a /* equivalent to const string a[] */, int n, string target)
{
	a[k]
}

int main()
{
	string sa[5] = { "cat", "mouse", "eel", "snake", "worm" }
	
	int i = lookup(sa, 5, "eel");
	int j = lookup(&sa[0], 5, "eel");
	int m = lookup(sa + 1, 3, "booty");
					//^ is &sa[1]
	
}









W6 Discussion:

//seperation: 1
The mad scientist // good
The mad crazy scientist //good
The mad crazy annoying scientist //nope

d: deranged
r: robot

		d r d d r r		seperation: 3
index:  0 1 2 3 4 5

remove, makeproper

make some remove helper functions
-> move pattern from pos ^H to the end of the array
	one place to the left
	
//Visual studio

#define _CRT_SECURE_NO_WARNINGS
	
#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype> // ==> isalpha()


makeProper:
1. npattern >= 0
	while (i < npatterns)
	{
		seperation[i] > 0
		words[i][0] == '\0' // words [i][0] = '\0' => remove
		convert letter to lowercase 'a' -> 'z' // delete if not in (a-z) or (A-Z)
		check duplicate pattern ==> // mad scientist | mad scientist | scientist mad
		
	}
rate
remove non-alpha, non-space characters

C strings: used because not everything is written in c++

strlen(s) //returns length of s not including \0
strcpy(t,s) //copies the string s to t
strncpy(t,s,n) //copies the first n characters of s to t
strcat(t,s) //appends s to the end of t
strcmp(t,s) //compares t and s, returns 0 if they're equal, > 0 if t > s, and < 0 if t < s


	if (strlen(str) + 2 > max) <- inserting 1 extra character. also the end \0 which is why it's +2
	
	//don't use strlen in for loops, because it runs in n time, causing the loop to run in n^2 time. store it in a seperate variable and reference that instead.
	
	
	
	except that you may bring one 8½"×11" sheet of notes (you may use both sides, written or printed as small as you like)0
	
	
memcpy() //it's strcpy, but not. memcpy is the fastest way to copy to n locations	
ec()
	
	Data Structures:
	
	A stack is 
	
	FILO
	FIFO
	someething
	
	
	Memory is a really big array, like 2^64
	An array is a small subsection of the memory, which points to the first value stored there
	char* k = "Hello"; //function exactly the same, but the pointer to the array takes up more memory.
	char k2[] = "Hello";
	char* k3 = k2
	
	
	
	
	
	
	double* findFirstNegative(double a[], int n)
	{
		for (double* p = a; p < a + n; p++)
		{
			if (*p < 0)
				return 0;
		}
		return nullptr;
	}
	
	int main()
	{
		double da[5];
		...
		double* pfn = findFirstNegative(da, 5)/
		if (pfn == nullptr)
			cout << "There are no negatives" << endl;
		else
		{
			cout << "The first negative value is " << pfn << endl;
			cout << "At element number " << pfn - da << endl;
		}
	}
	
	
	

null pointer value:
C++ 11: nullptr
C++ 11 and earlier: NULL

double* p = nullptr;
p = nullptr;
if (p == nullptr) ...
if (p != nullptr) ...	
	

OTHER USE OF POINTERS: dynamic array usage



	
	
	//Project 5 Notes
	
	Input string
	
	parse string: remove non-alpha chars and do something with spaces
	
	when the first word is found, sequence begins:
	store first word in var? if var == word1?
	do some pointer magic alternatively
	
	use spaces to determine breaks in the thing - if space seperation++

	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	
