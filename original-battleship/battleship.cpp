#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <random>


using namespace std;

/*
classes:

arena - has the grid of the array, the characters
game - initializes and runs the game	


have a character that shows for a hit - *
miss character: ~
when you sink a ship, the type of ship is revealed, and the hits change to a letter

*/
//game parameters
const int MAX_SHIPS = 5;
const int MAX_ROWS = 9;
const int MAX_COLS = 9;

//translations for stuff
const int UP = 1;
const int DOWN = 2;
const int LEFT = 3;
const int RIGHT = 4;

const int MISS = 0;
const int HIT = 1;
//types of ship
const int BATTLESHIP = 1;
const int DESTROYER = 2;
const int CARRIER = 3;
const int SUB = 4;
const int PATROL = 5;


int arenaGrid[MAX_ROWS][MAX_COLS]; //grid for tracking location of battleships. 0 is no ship, 1+ is ship present (//1 is battleship, 2 is destroyer, etc)
	
bool shotAt[MAX_ROWS][MAX_COLS]; //grid for tracking which locations have been shot at by the player. true if targed, false if not

char grid[MAX_ROWS][MAX_COLS]; //grid that is displayed on screen

//function declarations
class Arena;
void clearScreen();
int randInt(int min, int max);
int aliveShips = MAX_SHIPS;

class Ship
{
public:
	Ship(Arena* ap, int r, int c, int type);
	//accessors
	int row();
	int col();
	int type();

	//mutators
	bool determineNewPosition(int& r, int& c, int dir, int spec);
	bool isDead();
	bool setDead();

private:
	Arena* m_arena;
	int m_row;
	int m_col;
	int m_direction;
	int m_length;
	int m_type;
	bool m_sunk;
};

class Arena
{
public:
	Arena(int nRows, int nCols);
	~Arena();
	void Display();
	
	//accessors
	bool shipPresent(int r, int c);
	int rows();
	int cols();
	void checkSunk();

	//mutators
	void makeShips(int num);

private:
	int m_rows; //indexed at 0. STARTS COUNTING AT 0
	int m_cols; //me too thanks
	int m_nShips;
	Ship* m_Ships[MAX_SHIPS]; //why is it a pointer
};

class Game
{
public:
	Game(int rows, int cols, int numShips);
	~Game();
	void play();
private:
	Arena* m_arena;
};



///////////////////Ship Fcn Definitions

Ship::Ship(Arena* ap, int r, int c, int type)
{
	m_row = r;
	m_col = c;
	m_arena = ap;
	m_sunk = false;
	m_type = type;
	m_length = 0;
	m_direction = randInt(1, 4);

	//vars used to create the ship
	int ideallength = randInt(3, 5);
	int temprow = m_row;
	int tempcol = m_col;

	arenaGrid[temprow][tempcol] = type;
	for (int i = ideallength; i > 0; i--)
	{
		if (determineNewPosition(temprow, tempcol, m_direction, 0))
		{
			arenaGrid[temprow][tempcol] = m_type;
			m_length++;
		}
		else
		{
			break;
		}
	}
}

bool Ship::determineNewPosition(int& r, int& c, int dir, int spec) //used in the placement of ships. Checks if the next part of the ship can be placed, and moves it forward 1
{
	//switch for each direction. if the purported row/column is out of the bounds of the array, or there's already a ship or part of ship there, return false
	switch (dir)
	{
	case UP:
		if ((r <= 0) || arenaGrid[r - 1][c] != spec) //won't work for setting sunk ships, change the 0 to 0 or the ship type
			return false;
		r--;
		break;
	case DOWN:
		if ((r >= m_arena->rows()) || arenaGrid[r + 1][c] != spec)
			return false;
		r++;
		break;
	case LEFT:
		if ((c <= 0) || arenaGrid[r][c - 1] != spec)
			return false;
		c--;
		break;
	case RIGHT:
		if ((c >= m_arena->cols()) || arenaGrid[r][c + 1] != spec)
			return false;
		c++;
		break;
	default:
		return false;
	}
	return true;
}

bool Ship::isDead()
{
	int r = m_row;
	int c = m_col;
	int checker = 0;
	for (int i = m_length; i > 0; i--)
	{
		if (determineNewPosition(r, c, m_direction, m_type))
		{
			if (shotAt[r][c])
			{
				checker++;
			}
		}
		else
		{
			break;
		}
	}
	if (checker == m_length)
	{
		if (!m_sunk)
			setDead();
		return true;
	}
	return false;
}

bool Ship::setDead()
{
	m_sunk = true;
	int r = m_row;
	int c = m_col;
	aliveShips--;
	arenaGrid[r][c] *= 10;

	for (int i = m_length; i > 0; i--)
	{
		if (determineNewPosition(r, c, m_direction, m_type))
		{
			arenaGrid[r][c] *= 10;
		}
		else
		{
			break;
		}
	}
	return true;
}

int Ship::row()
{
	return m_row;
}

int Ship::col()
{
	return m_col;
}

int Ship::type()
{
	return m_type;
}

///////////////////Arena Fcn Definitions (most of the game)

Arena::Arena(int nRows, int nCols)
{
	m_rows = (nRows - 1);
	m_cols = (nCols - 1);
	m_nShips = 0;
	for (int r = 0; r <= m_rows; r++)
	{
		for (int c = 0; c <= m_cols; c++)
		{
			arenaGrid[r][c] = 0;
			shotAt[r][c] = true;
		}
	}
}

Arena::~Arena()
{
	for (int i = 0; i < m_nShips; i++)
		delete m_Ships[i];
}

//access functions

int Arena::rows()
{
	return m_rows;
}

int Arena::cols()
{
	return m_cols;
}

void Arena::checkSunk()
{
	for (int i = 0; i < m_nShips; i++)
	{
		m_Ships[i]->isDead();
	}

}

void Arena::makeShips(int num)
{
	int ship_type = BATTLESHIP; //give each ship a unique tag so we can tell them apart. DIFFERENT FROM THE SUNKEN TAG
	while (m_nShips != num)
	{
		int row = randInt(0, m_rows);
		int col = randInt(0, m_cols);
		//don't make a ship if one already exists there
		if (!shipPresent(row, col))
		{
			m_Ships[m_nShips] = new Ship(this, row, col, ship_type);
			m_nShips++;
			ship_type++;
		}
	}
}

bool Arena::shipPresent(int r, int c)
{
	for (int j = 0; j < m_nShips; j++)
	{
		if ((r == m_Ships[j]->row()) && (c == m_Ships[j]->col()))
			return true;
	}
	return false;
}

void Arena::Display()
{
	char grid[MAX_ROWS][MAX_COLS];

	int r, c;
	//setting values of the grid
	for (r = 0; r <= m_rows; r++)
	{
		for (c = 0; c <= m_cols; c++)
		{
			if (shotAt[r][c])
			{
				switch (arenaGrid[r][c])
				{
				case MISS:
					grid[r][c] = '~';
					break;
					//10 * the types signifies sunk ships
				case 10 * BATTLESHIP:
					grid[r][c] = '@';
					break;
				case 10 * DESTROYER:
					grid[r][c] = '%';
					break;
				case 10 * CARRIER:
					grid[r][c] = '#';
					break;
				case 10 * SUB:
					grid[r][c] = '$';
					break;
				case 10 * PATROL:
					grid[r][c] = '&';
					break;
				default:
					grid[r][c] = '*';
					break;
				}			
			}
			else
			{
				grid[r][c] = '.';
			}

		}
	}
	//displaying the grid
	clearScreen();
	//letters at the top
	cout << "  ";
	for (c = 0; c <= m_rows; c++)
		cout << (char)('A' + c) << ' ';
	cout << endl;
	//main grid
	for (r = 0; r <= m_rows; r++)
	{
		//numbers on the side
		cout << (r + 1) << ' ';
		//grid proper
		for (c = 0; c <= m_cols; c++)
			cout << grid[r][c] << ' ';
		cout << endl;
	}
	cout << endl << "There are " << aliveShips << " ships unsunk and " << m_nShips << " total ships." << endl;

	/*
	//Debug \ Cheat Mode
	cout << "Ship Locations: " << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << m_Ships[i]->row() << ", " << m_Ships[i]->col() << " type: " << m_Ships[i]->type() << endl;
	}
	*/	
}

Game::Game(int rows, int cols, int numShips)
{
	m_arena = new Arena(rows, cols);
	m_arena->makeShips(numShips);
}

Game::~Game()
{
	delete m_arena;
}

void Game::play()
{
	m_arena->Display();

	//start loop here
	while (aliveShips > 0)
	{
		cout << endl;

		cout << "Pick a column (A-I): ";
		char inputColumn;
		cin >> inputColumn;
		cin.ignore(10000, '\n');
		if (inputColumn == 'q')
			exit(1);
		if (!((inputColumn >= 'A') && (inputColumn <= 'I')))
		{
			cout << "Invalid Input. Please enter a Capital Letter between A and I " << '\a';
			continue;
		}
		int targetColumn = inputColumn - 'A';

		cout << "Pick a row (1-9): ";
		char inputRow;
		cin >> inputRow;
		cin.ignore(10000, '\n');

		if ((inputRow < 1) || (!isdigit(inputRow)))
		{
			cout << "Invalid Input. Please enter a number between 1 and " << MAX_ROWS << '\a';
			continue;
		}
		int targetRow = (inputRow - '0') - 1;



		shotAt[targetRow][targetColumn] = true;
		
		m_arena->checkSunk();

		m_arena->Display();
	}
	cout << "You sunk all their ships! You win!" << endl;
}

int randInt(int min, int max)
{
	if (max < min)
		swap(max, min);
	static random_device rd;
	static default_random_engine generator(rd());
	uniform_int_distribution<> distro(min, max);
	return distro(generator);
}

void clearScreen()  // will just write a newline in an Xcode output window
{
	static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
	cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
}

int main()
{
	//create a 9 by 9 arena
	Game g(9, 9, 5);

	g.play();
}