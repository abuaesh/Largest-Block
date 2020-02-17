/*****************************
LARGEST BLOCK IN A GRID
******************************
This program finds the largest block in a grid. Inspired from: https://medium.com/free-code-camp/bet-you-cant-solve-this-google-interview-question-4a6e5a4dc8ee
******************************
By:
	Noha Abuaesh 	noha.abuaesh@gmail.com
*/
#include  <iostream>
#include <vector>
using namespace std;

//node data structure
struct node
{
	 bool blocked;
	 bool visited;
 };

//Grid data
const int rows = 5, cols = 5; //Grid dimensions
node grid[rows][cols]; // The grid is a 2D array

//==============================================================================================================================================================================
//==============================================================================================================================================================================//int findBlock_size(vector<vector<char> >& grid, int srci, int srcj)
int find_block_size(int starti, int startj, int block_number)
{
	node start_node = grid[starti][startj];
	//make sure the starting point is blocked, if not return 0 (i.e. size of this block is 0)
	if(!start_node.blocked) return 0;
	
	static int blocks_sizes[rows*cols] = {0}; //the maximum number of blocks that can be in the grid is much less than rows*cols; I am too lazy to calculate it, so just use a vector :)
	blocks_sizes[block_number]++;
	grid[starti][startj].visited = true; //mark this node as expanded(counted in the block size), so we don't count it again in the future
	
	//node neighbors_list [rows*cols] ;
	//vector<node> neighbors_list; //we do not know the size of the neighbors_list in advance, plus, we need to dynamically erase and add elements to it.
	//int neighbors_index = 0; // keeps track of how many (blocked)neighboring nodes detected so far
	
	//Explore all neighboring nodes (and their neighbors by recursion)
	/*
	Each node has 8 neighbors, or less, depending on it's location on the grid
	
	Note: Some of the following checks are not likely to be true for the starting node in the block, 
		since the nodes get expanded in spatial order: Left to Right, Top to Bottom. 
		Since the nodes before this current one (e.g. at grid[starti][startj-1]) will have been already visited
		But this check is needed for subsequent nodes in the block, to accomodate for all neighbors.
	*/
	if(startj > 0) //There is a left column
	{
		if(grid[starti][startj-1].blocked && !(grid[starti][startj-1].visited)) //1. Checking the Left Neighbor
		{							
			grid[starti][startj-1].visited = true; //mark this node as visited
			blocks_sizes[block_number]++; //increment current block size by one
			find_block_size(starti, startj-1, block_number); //find the neighboring nodes to the current node that are part of the same block and have not been visited
		}
		
		if(starti < rows-1)	//There is a bottom row
			if(grid[starti+1][startj-1].blocked && !(grid[starti+1][startj-1].visited)) //2. Checking the Bottom-Left Neighbor
			{
				grid[starti+1][startj-1].visited = true; //mark this node as visited
				blocks_sizes[block_number]++; //increment current block size by one
				find_block_size(starti+1, startj-1, block_number); //find the neighboring nodes to the current node that are part of the same block and have not been visited
			}
			
		if(starti > 0)	//There is a top row
			if(grid[starti-1][startj-1].blocked && !(grid[starti-1][startj-1].visited)) //3. Checking the Top-Left Neighbor
			{
				grid[starti-1][startj-1].visited = true; //mark this node as visited
				blocks_sizes[block_number]++; //increment current block size by one
				find_block_size(starti-1, startj-1, block_number); //find the neighboring nodes to the current node that are part of the same block and have not been visited
			}
	}
	
	if(starti > 0)	//There is a top row
	{
		if(grid[starti-1][startj].blocked && !(grid[starti-1][startj].visited)) //4. Checking the Top neighbor
		{
			grid[starti-1][startj].visited = true; //mark this node as visited
			blocks_sizes[block_number]++; //increment current block size by one
			find_block_size(starti-1, startj, block_number); //find the neighboring nodes to the current node that are part of the same block and have not been visited
		}
		
		if(startj < cols-1) //There is a right column
			if(grid[starti-1][startj+1].blocked && !(grid[starti-1][startj+1].visited)) //5. Checking the Top-Right neighbor
			{
				grid[starti-1][startj+1].visited = true; //mark this node as visited
				blocks_sizes[block_number]++; //increment current block size by one
				find_block_size(starti-1, startj+1, block_number); //find the neighboring nodes to the current node that are part of the same block and have not been visited
			}
	}
		
	
	if(starti < rows-1)	//There is a bottom row
	{
		if(grid[starti+1][startj].blocked && !(grid[starti+1][startj].visited)) //6. Checking the Bottom neighbor
		{
			grid[starti+1][startj].visited = true; //mark this node as visited
			blocks_sizes[block_number]++; //increment current block size by one
			find_block_size(starti+1, startj, block_number); //find the neighboring nodes to the current node that are part of the same block and have not been visited
		}
		if(startj < cols-1) //There is a right column
			if(grid[starti+1][startj+1].blocked && !(grid[starti+1][startj+1].visited)) //7. Checking the Bottom-Right Neighbor
			{
				grid[starti+1][startj+1].visited = true; //mark this node as visited
				blocks_sizes[block_number]++; //increment current block size by one
				find_block_size(starti+1, startj+1, block_number); //find the neighboring nodes to the current node that are part of the same block and have not been visited
			}
	}
	if(startj < cols-1) // There is a right column
		if(grid[starti][startj+1].blocked && !(grid[starti][startj+1].visited)) //8. Checking the Right Neighbor
		{
			grid[starti][startj+1].visited = true; //mark this node as visited
			blocks_sizes[block_number]++; //increment current block size by one
			find_block_size(starti, startj+1, block_number); //find the neighboring nodes to the current node that are part of the same block and have not been visited
		}		
	
		
	return blocks_sizes[block_number]; //return neighbors_index;
}
//==============================================================================================================================================================================
//==============================================================================================================================================================================
bool get_next_block(int starti, int startj, int& nexti, int& nextj) //returns 1 if a next block was found, returns 0 if the grid ended without finding another unvisited block
{
	for(int i = starti; i < rows; i++)
		for(int j = startj; j < cols; j++)
		{
			if(!(grid[i][j].visited) && grid[i][j].blocked)
			{
				//Pass by reference to your caller the position of new found block 
				nexti = i;
				nextj = j;
				return true; //return 1 to indicate another block was found
			}
		}
		
	return false; //did not find another block in the grid
}
//==============================================================================================================================================================================
//==============================================================================================================================================================================
int main()
{
	//Initialize the grid
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
		{
			grid[i][j].visited = false;
			grid[i][j].blocked = ((i)%2);
		}
		
	//Display the grid
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			if(grid[i][j].blocked)	cout << "#";
			else  cout << "_";
		}
		cout << endl;
	}
		
	//get the next block and find its size
	//int i=0, j=0; //search indices
	int starti = -1, startj = -1; //the indices where the next block starts--set by get_next_block
	int block_size = 0; //the size of the block--returned by find_block_size
	int biggest_block_size = 0, biggest_blocki, biggest_blockj; //index and size of the biggest block found so far
	int block_number = 0; //index of block currently being processed; used by find_block_size to keep track of the current block index. Also serves as block count in main
	
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
		{
			cout << "Exploring node[" << i << "][" << j << "]:\t";
			if(grid[i][j].visited){
				cout << "Already visited.\n";
				continue;
			}
			
			if(get_next_block(i,j,starti,startj))
			{
				cout << "Found a new block.";
				block_size = find_block_size(starti,startj, block_number); 
				cout << "It is of size: " << block_size << endl;
				/*if(block_size > biggest_block_size)
				{
					biggest_block_size = block_size;
					biggest_blocki = starti;
					biggest_blockj = startj;
				}*/
				block_number++; // block count
			}
			else
				cout << "No block found.\n";
		}
	
	if(block_number == 0)
		cout << "There are no blocks in the grid";
	else
	{
		cout << "There are " << block_number << " blocks in the grid.\n";
		cout << "The largest block is of size: " << biggest_block_size << "\n";
		cout << " The largest block was found at position: [" << biggest_blocki << "][" << biggest_blockj << "]\n";
	}

}
