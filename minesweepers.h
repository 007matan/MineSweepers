/***enums***/
typedef enum{ZERO = 0, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN} MinesAround;//מוקשים בסביבתך
typedef enum{MINES=0, NOTMINES} Moolian;
typedef enum{DISCOVERD=0, NOTDISCOVERD} Show;
typedef enum{FALSE, TRUE} OnMine;
typedef char point;

/***struct***/
typedef struct MineSweeper
{
	Show dis;
	Moolian thereIs;
	union
	{
		MinesAround minesCount;
		point mine;
	}ItemNode;
	
}MineSweeperNode;


/*****FunctionPrototypes*****/
void Init(MineSweeperNode territory[][14]);
void InsertMines(MineSweeperNode field[][14]);
void InsertMinesAround(MineSweeperNode field[][14]);
OnMine Print(MineSweeperNode  field[][14]);
void ZeroMinesAround(MineSweeperNode  field[][14], int row, int col);
void DiscoverdAll (MineSweeperNode territory[][14]);