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
//#include <vector>


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
const int rows = 3, cols =3;
node grid[rows][cols];

//int find_block_size(node[][cols], int starti, int startj);


//int findBlock_size(vector<vector<char> >& grid, int srci, int srcj)
int find_block_size(int starti, int startj)
{
	node start_node = grid[starti][startj];
	//make sure the starting point is blocked, if not return 0 (i.e. size of this block is 0)
	if(!start_node.blocked) return 0;
	
	int size = 1;
	grid[starti][startj].visited = true; //mark this node as expanded(counted in the block size), so we don't count it again in the future
	
	node neighbors_list [rows*cols] ;
	int neighbors_index = 0; // keeps track of how many (blocked)neighboring nodes detected so far
	
	//Add all neighboring nodes to the neighbors list
	if(startj > 0) {
		if(grid[starti][startj-1].blocked && !(grid[starti][startj-1].visited))//not likely to be true, since the nodes get expanded in spatial order.
		{																			//the node right before this one at grid[starti][startj-1] will be already visited
			neighbors_list[neighbors_index] = grid[starti][startj-1];
			neighbors_index++;
		}
		
		if(starti < cols-1)	
			if(grid[starti+1][startj-1].blocked && !(grid[starti+1][startj-1].visited))
			{
				neighbors_list[neighbors_index] = grid[starti][startj-1];
				neighbors_index++;
			}
	}
	
	if(starti < cols-1)	
	{
		if(grid[starti+1][startj].blocked && !(grid[starti+1][startj].visited))
		{
			neighbors_list[neighbors_index] = grid[starti][startj];
			neighbors_index++;
		}
		if(startj < cols-1)
			if(grid[starti+1][startj+1].blocked && !(grid[starti+1][startj+1].visited))
			{
				neighbors_list[neighbors_index] = grid[starti+1][startj+1];
				neighbors_index++;
			}
	}
	if(startj < cols-1)
		if(grid[starti][startj+1].blocked && !(grid[starti][startj+1].visited))
		{
			neighbors_list[neighbors_index] = grid[starti][startj+1];
			neighbors_index++;
		}		
	
		
	return neighbors_index;
}

int get_next_block(int starti, int startj, int& nexti, int& nextj) //returns 1 if a next block was found, returns 0 if the grid ended without finding another unvisited block
{
	for(int i=starti;i<rows;i++)
		for(int j=startj;j<cols;j++)
		{
			if(!(grid[i][j].visited) && grid[i][j].blocked)
			{
				nexti = i;
				nextj = j;
				return 1; //return 1 to indicate another block was found
			}
		}
		
	return 0; //did not find another block in the grid
}



int main()
{
	//Initialize the grid
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
		{
			grid[i][j].visited = false;
			grid[i][j].blocked = (i-j)%2;
		}
		
	//get the- next block and find its size
	int i=0, j=0, starti, startj, block_size = 0, biggest_block_size = 0, biggest_blocki, biggest_blockj;
	while(get_next_block(i,j,starti,startj))
	{
		block_size = find_block_size(starti,startj);
		if(block_size > biggest_block_size)
		{
			biggest_block_size = block_size;
			biggest_blocki = starti;
			biggest_blockj = startj;
		}
	}
	
	cout << "The largest block is of size: " << biggest_block_size << "\n and it was found at position [" << biggest_blocki << "][" << biggest_blockj << "]\n";
}
