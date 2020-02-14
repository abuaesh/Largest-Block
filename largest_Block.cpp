/*****************************
LARGEST BLOCK IN A GRID
******************************
This program finds the largest block in a grid. Inspired from: https://medium.com/free-code-camp/bet-you-cant-solve-this-google-interview-question-4a6e5a4dc8ee
******************************
By:
	Noha Abuaesh 	noha.abuaesh@gmail.com
*/
#include  <iostream>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <vector>


using namespace std;

enum Colors { blue=1, green, cyan, red, purple, yellow, grey, dgrey, hblue, hgreen, hred, hpurple, hyellow, hwhite };
//node data structure
struct node
{
	 //int i;
	 //int j;
	 bool blocked;
	 bool visited;
	 //node* next; //used when manipulating the list of neighbors in function findBlockSize
 };
/*//constants
const double BLOCKAGE_PERCENT = 0.4;
const char BLOCKED_PIN = 219;
const char EMPTY_PIN = ' ';
const char VISITED_PIN = 176;	//marks target pin
const char CALCULATED_PIN = 178;	//marks a pin that has 
const char NEIGHBOR_PIN = 145;
//global vars
double Lx, Ly, Lxy;				//dimension lengths in the grid
int ptr_lst=8;					//Detailed Output first item in the list to print

*/
int findBlockSize(node[][3], int starti, int startj);


//int findBlock_size(vector<vector<char> >& grid, int srci, int srcj)
int findBlockSize(node  mgrid [][3], int starti, int startj)
{
	node* start_node = &(mgrid[starti][startj]);
	//make sure the starting point is blocked, if not return 0 (i.e. size of this block is 0)
	if(!start_node->blocked) return 0;
	
	int size = 1;
//	node* neighbors;
	return size;
}

int main()
{
	node grid[3][3];
	grid[0][0].blocked = false;
	grid[0][0].visited = false;
	//grid[0][0].next = NULL;
	
	cout << findBlockSize(grid,0,0);
}
