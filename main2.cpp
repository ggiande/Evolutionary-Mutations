//
// stepstone.cpp
//
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <vector>
	
using namespace std;

/* global variables */
int LX = 640;
int LY = 480;
string outfilename = "test.csv";
string numerics = "make.csv";

int tmax = LX * LY;  //Catches the program.
vector<vector<int > > neighbor_sep = {{-1,0}, {1,0}, {0,-1}, {0,1}};

class site{
	public:
		int label = -1; // label for "gene". negative default value indicates "not filled"
		int timefilled = -1;
		vector<int > mother = vector<int>(2,-1); // two-element vector "mother" will contain (x,y) of mother.
												//fill both elements with -1 by default so we will know those are meaningless
												// until the site is filled
		void fill(int fillLabel, int fillTime, vector<int> fillMother){
			label = fillLabel;
			timefilled = fillTime;
			mother = fillMother;
		}
};

int modulo(int a, int b){ // shift a into the range [0, b-1] by adding multiples of b
	while (a < 0){
		a += b;
	}
	while (a >= b){
		a -= b;
	}
	return a;
}


/* Create a section where the user can change the amount of populations that will be present.*/

int num_ancestors = 2;
int shift = LY / num_ancestors;

/* Global variables end */

int main(void) {
	cout << "Printing out the number of ancestors, LX and LY into " << numerics << endl;
	ofstream g(numerics.c_str()); // declare an output stream to print to "numerics"	
	g << num_ancestors << " " << LX << " " << LY << endl;



	srand48(time(0));  // seed random number generator using time. Srand needs to run once before drand48 is called to ensure randomness.
	cout << "Size of the shift: " << shift << endl;
	vector<vector<site > > lattice = vector<vector<site > >(LX, vector<site>(LY)); // this is one of the many clumsy C++ ways to declare a vector of sites, called "lattice", of dimensions LX by LY.

	// initialization
    vector<vector<int > > ancestors_xy = vector<vector<int > >(0, vector<int>(2)); // initially occupied sites
	for(int i = 1; i <= num_ancestors; i++){
		ancestors_xy.push_back({0, i*10});
	}


	/* This section prints out the contents of the ancestors_xy vector.
	cout << "Contents of the vector: " << endl;	
	for (int i = 0; i < ancestors_xy.size(); i++) {
		for (int j = 0; j < ancestors_xy.size(); j++) {
			std::cout << ancestors_xy[i][j] << ", ";
		}
	}
	cout << "End of the coentents of ancestors_xy vector." << endl;
	cout << "" << endl;
	*/

	for (int i = 0; i < ancestors_xy.size(); i++) {
		lattice[ancestors_xy[i][0]][ancestors_xy[i][1]].fill(i,0,ancestors_xy[i]); // give each initially occupied site a unique label - Element of type site.
	}

	vector<vector<int > > frontier = ancestors_xy ; // declare "frontier" as a vector of 2-element vectors of integers (x,y), initialized with the ancestors
    // > > is closing the vector declaration statement. Needs the spacing. NOT STREAM.
	//cout << "Running... " << endl;

    for (int t = 0; t < tmax ; t++) { // quit when t hits tmax 		// the update step:
		cout << "Running..." << t << " out of ~" << LX*LY <<endl; 
		int random_frontier_index = int(drand48()*frontier.size()); // get A random integer from 0 to (length of frontier - 1)
		/* I need to save my new coordinate in terms of vector<int> mother_xy. (x,y)? I can completely replace the random frontier mechanism for duplication.			*/

		//cout << "Time at: " << t << ", and the random_frontier_index is: " << random_frontier_index << endl;
		vector<int> mother_xy = frontier[random_frontier_index]; // choose a random (x,y) pair in frontier 	//Does not save an index. frontier[] calls it save an x and y value.i

 		site mother = lattice[mother_xy[0]][mother_xy[1]]; // find the site at that randomly chosen frontier (x,y)

 		 //The random_frontier_index picks out one number from the index of the frontier and then site mother simply saves 2 values from the function call of random_frontier_index.
		//cout << "Site mother _xy[0]: " << mother_xy[0] << " " << "and Site mother_xy[1]: " << mother_xy[1] << endl;
		
		//cout << " " << endl; //Just spacing
		// find the possible daughter sites for this mother, i.e. the nearest neighbors that are not filled
		
		vector<vector<int > > possible_daughter_xyvals = vector<vector<int > >(0,vector<int >(2)); // vector of (x,y) pairs with zero elements to start with

		
        //module leaves only positive remainders.
        for (int i = 0; i < neighbor_sep.size(); i++) {
			vector<int> neighbor_xy = { modulo(mother_xy[0] + neighbor_sep[i][0], LX), modulo(mother_xy[1] + neighbor_sep[i][1], LY)}; // find xy values of neigbhors by shifting incrementally from random frontier site. Use modulo operation to impose periodic boundary conditions.    Periodic boundaries
            // Modulo is used to make sure that the the index is not out of the boundary. So it remains positive.
			if (lattice[neighbor_xy[0]][neighbor_xy[1]].label == -1) {  // the neighboring site has a -1 label, indicating not filled
				possible_daughter_xyvals.push_back(neighbor_xy); // append neighbor_xy to possible_daughter_xyvals      push_back is an append funciton.
			}
		}
        
        // Mother cell is chosen, the for loop is searching to see which neighbors are empty and are available. If empty, neighbor is appended to possible daughter.
		int num_possible_daughters = possible_daughter_xyvals.size();
		/* Gillespie Algorithm
		* Observe a random cell in a population that is at the frontier.
		* Choose a population at random and then choose a cell at random that is at the frontier.
		* Find the probability of that cell suceeding at that tick.
		*/

			if (num_possible_daughters > 0){
			int random_daughter_index = int(drand48()*num_possible_daughters); // get a random integer from 0 to (length of possible_daughter_xyvals - 1)
			vector<int> daughter_xy = possible_daughter_xyvals[random_daughter_index];  //Will hold an x and a y.
			lattice[daughter_xy[0]][daughter_xy[1]].fill(mother.label, t, mother_xy); // copy mother's label into daughter, and record the time and mother's xy values
            
            /* Time is a parameter that's being modified by the fill command."
             
             void fill(int fillLabel, int fillTime, vector<int> fillMother){
             label = fillLabel;
             timefilled = fillTime;
             mother = fillMother;
             }
             */
            
			frontier.push_back(daughter_xy); // append daughter's (x,y) values to the frontier. It's possible that daughter has no empty neighbors and doesn't belong in frontier, but that's ok, we will catch that with the else statement below if the daughter is chosen as a mother

            if (num_possible_daughters == 1){ // we just took away the last empty neighbor of the mother, so delete her from the frontier
				frontier.erase(frontier.begin()+random_frontier_index); // remember, random_frontier_index is mother's index in frontier
				if (frontier.size() == 0) {
					cout << "Size of frontier has reached zero." << endl;
					break; // terminate the loop
				}
			}
		} else { // no empty neighbors were found, so this site does not belong in the frontier
			frontier.erase(frontier.begin()+random_frontier_index); // remove that element from the frontier
			t--; // to avoid incrementing t, we decrement t here to counteract the t++ in the for loop

			if (frontier.size() == 0) {
				cout << "Size of frontier has reached zero." << endl;
				break; // terminate the loop
			}
		}
	}

	/* This part of the program begins to save all the contents compiled onto an outfile.
	* Note that this runs once timfilled = tmax. */

	cout << "Done." << endl;

	cout << "Printing results to " << outfilename << endl;

	ofstream f(outfilename.c_str()); // declare an output stream to print to "outfilename"

	//name of the class is site. class name  = lattice[i][j] -> What is being accessed.
	for (int i = 0; i < lattice.size(); i++){
		for (int j = 0; j<lattice[i].size(); j++){
			site thisSite = lattice[i][j];
			f << i << " " << j << " " << thisSite.label << " " << thisSite.timefilled << " " << thisSite.mother[0] << " " << thisSite.mother[1] << endl;

		}
	}
	cout << "Size of the frontier: " << frontier.size() << endl;

/* IGNORE —— This section was created to print out the contents of the frontier at tmax. 

	int counter = 0;
	cout << "Conents of frontier: " << endl;
 	for (int i = 0; i < frontier.size(); i++) {
 		cout << endl;
	    for (int j = 0; j < frontier[i].size(); j++) {
			std::cout << frontier[i][j] << ", ";

			
			if(frontier[i][j] == 0){	//searches for 0's in the entire 2dvector
				counter++;
			}
			

		}
	}

	cout << " " << endl;
	cout << "Counter of 0's: " << counter << endl;
	*/

	f.close();

	return 0;
}
/*

Avoiding the two populations from crashing.

tmax * .9 = 276480 
Only this number of timesteps will occur. 
We want to take measurements at 10 different points throughout this.
div = (tmax * .9)/10  //=27648
So every 27648 timesteps, we will take a survey of the rates of the number of subpopulations. 

Next step is to design an algorithm that will count the number of rates at the frontier of each subpopulation.

*/







