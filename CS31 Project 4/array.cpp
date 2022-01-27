#include <iostream>
#include <string>
#include <array>
using namespace std;



bool hasProperSyntax(int n, int pos = -1) 
{
	if ((n < 0) || (pos >= n))
	{
		return false;
	}
	return true;
}


int appendToAll(string a[], int n, string value)
{
	if (!hasProperSyntax(n))
		return -1;
	for (int i = 0; i < n; i++)
	{
		a[i] += value;
	}
	return n;
}

int lookup(const string a[], int n, string target)
{
	if (!hasProperSyntax(n))
		return -1;
	for (int i = 0; i < n; i++)
	{
		if (a[i] == target)
		{
			return i;
		}
	}
	return -1;
}

int positionOfMax(const string a[], int n)
{
	if (!hasProperSyntax(n) || (n == 0))
		return -1;

	int biggestBoi = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] > a[biggestBoi])
		{
			biggestBoi = i;
		}
	}
	return biggestBoi;
}

int rotateLeft(string a[], int n, int pos)
{
	if (!hasProperSyntax(n, pos) || (pos < 0))
		return -1;
	string moveToLast = a[pos];
	for (int i = pos; i < (n - 1); i++)
		a[i] = a[i + 1];
	a[n - 1] = moveToLast;
	return pos;
}

int countRuns(const string a[], int n)
{
	if (!hasProperSyntax(n))
		return -1;
	bool sequence = false;
	int numberOfRuns = 0;
	for (int i = 0; i < (n - 1); i++)
	{
		if (a[i] == a[i + 1])
		{
			if (sequence == false)
			{
				numberOfRuns++;
				sequence = true;
			}
		}
		else
			sequence = false;
	}
	return numberOfRuns;
}

int flip(string a[], int n)
{
	if (!hasProperSyntax(n))
		return -1;
	string dummy;
	int j = (n - 1);
	for (int i = 0; i <= j; i++)
	{
		//swap(a[i], a[j]);
		dummy = a[i];
		a[i] = a[j];
		a[j] = dummy;
		j--;
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
	if ((!hasProperSyntax(n1)) || (!hasProperSyntax(n2)))
		return -1;
	int lesser = min(n1, n2);
	for (int i = 0; i < lesser; i++)
	{
		if (a1[i] != a2[i])
			return i;
	}
	return lesser;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	if (!hasProperSyntax(n1) || !hasProperSyntax(n2))
		return -1;
	int location = -1;
	if (n2 == 0)
		location = 0;
	int streak = 0;
	for (int i = 0; i < n1; i++)
	{
		if (a1[i] == a2[streak])
		{
			streak++;
			if (streak == n2)
				location = (i - (streak - 1));
		}
		else
			streak = 0;
	}
	return location;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	if (!hasProperSyntax(n1) || !hasProperSyntax(n2))
		return -1;
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			if (a1[i] == a2[j])
				return i;
		}
	}
	return -1;
}

int divide(string a[], int n, string divider)
{
	if (!hasProperSyntax(n))
		return -1;
//rearranging the array
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < (n - i); j++)
		{
			if (a[j] >= divider)
				rotateLeft(a, n, j);
		}
	}
//array is sorted, finding the proper value to return
	for (int i = 0; i < n; i++)
		if (a[i] >= divider)
			return i;
	return n;

}

int main()
{
	string data[10] = { "bro", "b", "EFG", "d", "EFG", "", "78", "eight", "NINE", "tenth" };
	string candidate[6] = { "etho", "rembrandt", "zisteau", "michaelangelo", "teetho", "norman" };
	string folks[10] = { "x", "z", "c", "h", "a", "y", "d", "e", "g", "b" };
	string folks2[4] = { "b", "a", "z", "c" };
/*
	//APPENDTOALL TEST
	size_t dsize = sizeof(data) / sizeof(data[0]);
	appendToAll(data, dsize, "!!!");
	for (int i = 0; i != dsize; i++)
		cout << data[i] << endl;
*/
/*
	//LOOKUP TEST
	int location1 = lookup(data, 2, "EFG!!!");
	cout << location1 << endl;
*/
/*
	//POSITIONOFMAX TEST
	cout << positionOfMax(candidate, 6) << endl;
	cout << positionOfMax(data, 10) << endl;
*/
/*
	//ROTATELEFT TEST
	int m = rotateLeft(candidate, 0, -1);
	cout << m << endl;
	for (int i = 0; i != 6; i++)
	cout << candidate[i] << endl;

*/

/*
	//COUNTRUNS TEST
	int m = countRuns(candidate, 6);
	cout << m << endl;
*/
/*
	//FLIP TEST
	int m = flip(candidate, 6);
	int n = flip(data, 10);
	for (int i = 0; i != 6; i++)
		cout << candidate[i] << endl;
	for (int j = 0; j != 10; j++)
		cout << data[j] << endl;
*/

/*
	//DIFFER TEST
	int r = differ(folks, 6, group, 5);
	int s = differ(folks, 3, group, 5);
	cout << r << ' ' << s << endl;
*/
/*
	//SUBSEQUENCE TEST
	string group[5] = { "john", "daanne", "xavier", "kevin" };
	string group2[3] = { "" };
	int m = subsequence(folks, 6, group2, 0);
	cout << "subsequence starts at: " << m << endl;
*/


/*
	//DIVIDE TEST
	int m = divide(folks, 10, "");
	for (int i = 0; i < 10; i++)
		cout << folks[i] << endl;;
	cout << "divide returns " << m << endl;
*/

	


}

