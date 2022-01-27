#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <cassert>


using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_DOCUMENT_LENGTH = 250;

//nPatterns - 1 

int makeProper(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int nPatterns);
int validateword(char a[][MAX_WORD_LENGTH + 1], int i);
int rate(const char document[], const char word1[][MAX_WORD_LENGTH + 1], const char word2[][MAX_WORD_LENGTH + 1],
	const int separation[], int nPatterns);

int main()
{
	const int TEST1_NRULES = 4;
	char test1w1[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"mad",       "deranged", "nefarious", "have"
	};
	char test1w2[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"scientist", "robot",    "plot",      "mad"
	};
	int test1dist[TEST1_NRULES] = {
		1,           3,          0,           12
	};

	int m = makeProper(test1w1, test1w2, test1dist, TEST1_NRULES);
	cout << "there are " << m << " proper patterns." << endl << endl;

	for (int i = 0; i < m; i++)
		cout << test1w1[i] << " " << test1w2[i] << " " << test1dist[i] << endl;
	cout << endl << endl;

	int n = rate("The nomad UCLA scientist unleashedaderanged evil giant robot.", test1w1, test1w2, test1dist, TEST1_NRULES);
	cout << endl << endl;
	cout <<	"The document's rating is: " << n << endl;


	assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 2);

	assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
	assert(rate("**** 2018 ****",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	assert(rate("  That plot: NEFARIOUS!",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	assert(rate("deranged deranged robot deranged robot robot",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	cout << "All tests succeeded" << endl;
	
}

int makeProper(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int nPatterns)
{
	int nProperPatterns = 0;
	bool newPattern = true;

	for (int i = 0; i < nPatterns; i++)
	{
		if (!strcmp(word1[i], "") || !strcmp(word2[i], ""))
			continue;

		//contains no characters or non-alpha characters
		if ((validateword(word1, i) == 1) && (validateword(word2, i) == 1) && (separation[i] >= 0))
		{
			//check for duplicate pattern
			newPattern = true;
			for (int k = 0; k < nProperPatterns; k++)
			{
				if (((!strcmp(word1[i], word1[k])) && (!strcmp(word2[i], word2[k]))) ||
					((!strcmp(word1[i], word2[k])) && (!strcmp(word2[i], word1[k]))))
				{
					//if the pattern is already there, don't copy it, but copy the separation value if it's larger than the current one.
					newPattern = false;
					if (separation[i] > separation[k])
						separation[k] = separation[i];
				}
			}
			//if it's not a dupe, put the pattern in valid patterns and sequence it
			if (newPattern)
			{
				//can't use strcpy, because strcpy does not handle memory overlaps well. memmove is functionally the same
				memmove(word1[nProperPatterns], word1[i], MAX_WORD_LENGTH);
				memmove(word2[nProperPatterns], word2[i], MAX_WORD_LENGTH);
				separation[nProperPatterns] = separation[i];
				nProperPatterns++;
			}
		}		
	}
	return nProperPatterns;
}

int validateword(char a[][MAX_WORD_LENGTH + 1], int i)
{
	for (int j = 0; a[i][j] != '\0'; j++)
	{
		if (!isalpha(a[i][j]))
		{
			return 0;
		}
		else
		{
			a[i][j] = tolower(a[i][j]);
		}
	}
	return 1;
}

int rate(const char document[], const char word1[][MAX_WORD_LENGTH + 1], const char word2[][MAX_WORD_LENGTH + 1],
	const int separation[], int nPatterns)
{
	if (nPatterns <= 0)
		return 0;

	//run through document, remove all nonalpha/space chars and make it lowercase
	//	store each word in a seperate array: max amt of words is 250 bc 250 chars

	char properDocument[MAX_DOCUMENT_LENGTH][MAX_DOCUMENT_LENGTH] = { "" };
	bool alreadyFound[MAX_DOCUMENT_LENGTH] = { false };
	int wordNum = 0;
	int letterNum = 0;

	int rating = 0;

//putting the document in a proper format
	for (int i = 0; i < MAX_DOCUMENT_LENGTH; i++)
	{
		if (isalpha(document[i]))
		{
			properDocument[wordNum][letterNum] = tolower(document[i]);
			letterNum++;
		}
		else if (document[i] == ' ')
		{
			letterNum = 0;
			wordNum++;
		}
		else if (document[i] == '\0')
		{
			wordNum++;
			break;
		}
	}

//finding the patterns
	for (int j = 0; j < wordNum; j++)
	{
		for (int k = 0; k < nPatterns; k++)
		{
			if (strcmp(properDocument[j], word1[k]) == 0)
			{
				for (int dist = 1; dist < separation[k] + 2; dist++)
				{
//make sure we're still looking within the bounds of the array: < wordNum and > 0
					if ((j + dist) < wordNum)
					{
						if (!strcmp(properDocument[j + dist], word2[k]))
						{
							if (!alreadyFound[k])
							{
								rating++;
								alreadyFound[k] = true;
							}
						}
					}
					else if ((j - dist) >= 0)
					{
						if (!strcmp(properDocument[j - dist], word2[k]))
						{
							if (!alreadyFound[k])
							{
								rating++;
								alreadyFound[k] = true;
							}
						}
					}
				}
			}
		}
	}
	return rating;
}