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
	 int i;
	 int j;
	 bool visited;
	 node* neighbors;
 };
//constants
const double BLOCKAGE_PERCENT = 0.4;
const char BLOCKED_PIN = 219;
const char EMPTY_PIN = ' ';
const char VISITED_PIN = 176;	//marks target pin
const char CALCULATED_PIN = 178;	//marks a pin that has 
const char NEIGHBOR_PIN = 145;
//global vars
double Lx, Ly, Lxy;				//dimension lengths in the grid
int ptr_lst=8;					//Detailed Output first item in the list to print
