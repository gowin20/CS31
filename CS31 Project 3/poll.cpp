#include <iostream>
#include <string>
#include <cassert>
using namespace std;

bool hasProperSyntax(string pollData);
int tallySeats(string pollData, char party, int& seatTally);
bool isValidUppercaseStateCode(string stateCode);

int main()
{
	assert(!hasProperSyntax("5"));
	assert(hasProperSyntax("MA9D,,KS4R") == hasProperSyntax("KS4R,,MA9D"));
	assert(hasProperSyntax("MA9D,KS4R") && hasProperSyntax("KS4R,MA9D"));
	assert(!hasProperSyntax("5DCT,9RNY17D1I,VT,ne3r00D"));
	int seats;
	seats = -999;    // so we can detect whether tallySeats sets seats
	assert(tallySeats("NY", 'd', seats) == 0 && seats == 0);
	seats = -999;    // so we can detect whether tallySeats sets seats
	assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", '%', seats) == 2 && seats == -999);
	assert(tallySeats("VTA5D,NY9R17D1I,VT,ne3r00D", 'i', seats) == 1 && seats == -999);
	assert(tallySeats("D00r3enCT5sdasdgDeaeY9asd171D1IVTne3r00D", 'd', seats) == 1 && seats == -999);
	
	assert(tallySeats("nm20r52d10i3g6g5d8f9p,tN3r50R2D,CA,VT", 'D', seats) == 0 && seats == 59);
	cout << "All tests succeeded" << endl;
}

bool hasProperSyntax(string pollData)
{
	bool inPartyResults = false;
	
	if (pollData.size() == 0)
		return true;
	//can't start or end with a comma
	if ((pollData[pollData.size() - 1] == ',') || (pollData[0] == ','))
		return false;
	for (int i = 0; i != pollData.size(); i++)
	{
		//can't have spaces anywhere
		
		//commas denote the end of a state forecast, and possibly the start of a new one
		if (pollData[i] == ',')
			inPartyResults = false;
		else if (isalpha(pollData[i]))
		{
			if (isalpha(pollData[i + 1]))
			{
				if (inPartyResults == false)
				{
					//checking the validity of the state codes
					string sCode;
					sCode += toupper(pollData[i]);
					sCode += toupper(pollData[i + 1]);
					if (!isValidUppercaseStateCode(sCode))
						return false;
					//everything that follows will be treated as part of the party results, until a comma is reached
					inPartyResults = true;
				}
				//if there are 2 letters in a row and there was already a state code, this returns false.
				else
					return false;
			}
			else
			{
				if (inPartyResults == false)
					return false;
			}
		}
		//checking to make sure the party results are valid
		else if (isdigit(pollData[i]))
		{
			if (inPartyResults == true)
			{
				//all digits are followed by either a number or a letter. If there are 3 or more digits in a row that's not allowed either.
				if (!(isdigit(pollData[i + 1]) || isalpha(pollData[i + 1])))
					return false;
				if (isdigit(pollData[i + 1]) && isdigit(pollData[i + 2]))
					return false;
			}
			//if there are digits before the state code, or some other place outside the party results, this returns false.
			else
				return false;
		}
		else
			return false;
	}
	//if it reaches the end, the string is valid
	return true;
}

bool isValidUppercaseStateCode(string stateCode)
{
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
		"LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
		"OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos  &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}

int tallySeats(string pollData, char party, int& seatTally)
{
	//checking to make sure the string is in the proper format, and that the party given is valid.
	if (!hasProperSyntax(pollData))
		return 1;
	if (!isalpha(party))
		return 2;
	seatTally = 0;
	//since the string has the proper syntax, the first 2 characters will always be a state code, so we don't need to check them. This prevents undefined behavior if the first character is the desired party.
	for (int i = 2; i <= pollData.size(); i++)
	{
		//if the proper party letter is found, and it's not in the state code (there is at least 1 number preceding it)
		if ((toupper(pollData[i]) == toupper(party)) && (isdigit(pollData[i - 1])))
		{
			//add the ones digit of the number to the total tally
			seatTally += (pollData[i - 1] - '0');
			if (isdigit(pollData[i - 2]))
				//add the tens digit to the tally, if it exists
				seatTally += (10 * (pollData[i - 2] - '0'));
		}
	}
	return 0;
}