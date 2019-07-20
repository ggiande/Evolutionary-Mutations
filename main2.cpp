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
int LX = 120;
int LY = 50;
string outfilename = "test.csv";
string numerics = "make.csv";
string data = "figures.csv";

int tmax = LX * LY;  //Catches the program.
vector<vector<int > > neighbor_sep = {{-1,0}, {1,0}, {0,-1}, {0,1}};

class site{
	public:
		int label = -1; // label for "gene". negative default value indicates "not filled"
		int timefilled = -1;
		vector<int > mother = vector<int>(2,-1); 
		/* two-element vector "mother" will contain (x,y) of mother. Fill both elements with
		-1 by default so we will know those are meaningless until the site is filled.  */
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
int shift = LY / num_ancestors; //use div for scaling

/* Global variables end */

int main(void) {
	//cout << "Printing out the number of ancestors, LX and LY into " << numerics << endl;
	ofstream g(numerics.c_str()); // declare an output stream to print to "numerics"	
	g << num_ancestors << " " << LX << " " << LY << endl;

	ofstream l(data.c_str());
	l << "time" << "," << "population1" << "population2" << endl;


	srand48(time(0));  // seed random number generator using time. Srand needs to run once before drand48 is called to ensure randomness.
	vector<vector<site > > lattice = vector<vector<site > >(LX, vector<site>(LY)); // this is one of the many clumsy C++ ways to declare a vector of sites, called "lattice", of dimensions LX by LY.

    vector<vector<int > > ancestors_xy = vector<vector<int > >(0, vector<int>(2)); // initially occupied sites
	for(int i = 0; i < num_ancestors; i++){
		ancestors_xy.push_back({0, (LY/(num_ancestors)*i+1)});
		cout << "i " << i << endl;
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
   
    for (int t = 0; t < tmax; t++) { // quit when t hits tmax-the update step:
		cout << "Running..." << t << " out of ~" << LX*LY << endl; 
		int counter = 0;
		int counter2 = 0;

		for(int i = 0; i < frontier.size(); i++){	//Entire Frontier
			vector<int> temporary_use = frontier[i];
			site my_site = lattice[temporary_use[0]][temporary_use[1]];	
	 		if(my_site.label == 0){
				counter++;
			} else if (my_site.label == 1){
				counter2++;
			}

		}
		/*Begging taking data points at every 100 time steps.*/
		if(t % 100 == 0){ //if divisible by 100, take data, else skip over this iteration.
		l << t << "," << counter << "," << counter2 << endl; //Saving time, and rates
		} else {
			continue;
		}



		/* Declaration of global variables for gillespie.
		*/
		float ro = 2;	//Setting the bias in each population.
		float rp = 1;
		float n = counter;
		float m = counter2;
		float rtot = (n*ro) + (m*rp);
		//cout << "The rtot is: " << rtot << endl;
		//cout << "The numer of 0 populations is: " << n << endl;
		//cout << "The number of 1 populations is: " << m << endl;
		float check_equal_to_one = (n*ro/rtot) + (m*rp/rtot); 
		float rate =  (n*ro)/rtot;
		//cout << rate << endl;

		//cout << "This should be one --> " << check_equal_to_one << endl;
		//cout << "The rate of this instance: " << float(rate) << endl;

	    srand((unsigned int)time(NULL));    
	    int temp = (drand48()*2);  //get a random integer from 0 to (FACTOR NUMBER - 1)
	    //cout << "Randomization: " << temp << endl;
	   	//cout << "Rate: " << rate << endl;	//Rate is always 0.
	   	//cout << " " << endl;
	    if(rate > temp){
	    	//choose population n
	    	//cout << "Choose population n or 0." << endl;
	    	rate = 0;
	    } else {
	    	//cout << "Choose population m or 1." << endl;
	    	//choose population m
	    	rate = 1;
	    }
		//cout << "Checkpoint 2" << endl;
	    int frontier_index = 0;
	    for(int a = 0; a < frontier.size(); a++){	//Entire Frontier look for the desired population.
			vector<int> temporary_use2 = frontier[a]; 
			site searching = lattice[temporary_use2[0]][temporary_use2[1]];	
			//cout << "Inside for loop" << endl;
			if(searching.label == rate){	//append the xy value to mother for m
				frontier_index = a;
				//cout << "If statement successul. " << frontier_index << endl;
			} else {
				//cout << "Not successul " << i << endl;
				a++;
			}
		}

		vector<int> mother_xy = frontier[frontier_index];
		site mother = lattice[mother_xy[0]][mother_xy[1]];
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
				frontier.erase(frontier.begin()+frontier_index); // remember, random_frontier_index is mother's index in frontier
				if (frontier.size() == 0) {
					cout << "Size of frontier has reached zero." << endl;
					break; // terminate the loop
				}
			}
		} else { // no empty neighbors were found, so this site does not belong in the frontier
			frontier.erase(frontier.begin()+frontier_index); // remove that element from the frontier
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







