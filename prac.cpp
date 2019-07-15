#include <iostream>
#include <vector>
using namespace std;

int main(){
	int ro = 2;
	int rp = 1;

	int n = 2;
	int m = 1;

	
	for(int i = 0; i < 10; i++){
		int rtot = (n*ro) + (m*rp);
		cout << "The rtot is: " << rtot << endl;

		int check_equal_to_one = (n*ro)/rtot + (m*rp/rtot); 
		int rate =  (n*rp)/rtot;

		cout << "This should be one --> " << check_equal_to_one << endl;
		cout << "The rate of this instance: " << rate << endl;

	    srand((unsigned int)time(NULL));    
	    int temp = (drand48()*2);  //get a random integer from 0 to (FACTOR NUMBER - 1)
	    cout << "Randomization: " << temp << endl;
	    if(rate > temp){
	    	//choose population n
	    	return 0;
	    } else {
	    	//choose population m
	    	return 1;
	    }

	    if(rate == 0){
	    	//rate is subpopulation 0.
	    	//Randomly pick a cell in this subpopulation.
			for(int i = 0; i < frontier.size(); i++){	//Entire Frontier look for the desired population.
				vector<int> temporary_use2 = frontier[i]; 
				site searching = lattice[temporary_use2[0]][temporary_use2[1]];	

				if(searching.label == 0){	//append the xy value to mother for m
					vector<int> mother_xy = frontier[i];
					site mother = lattice[mother_xy[0]][mother_xy[1]];
				} else {
					continue;
				}
			}
		} else if (rate == 1){
			for(int i = 0; i < frontier.size(); i++){	//Entire Frontier look for the desired population.
				vector<int> temporary_use2 = frontier[i]; 
				site searching = lattice[temporary_use2[0]][temporary_use2[1]];	

				if(searching.label == 1){	//append the xy value to mother for m
					vector<int> mother_xy = frontier[i];
					site mother = lattice[mother_xy[0]][mother_xy[1]];
				} else {
					continue;
				}
			}
		}
	}
}

/* To choose the subpopulation we iterate through frontier until label is what we want and 
* in a similar fashion as before we will choose the subpopulation and add it as a mother.

		for(int i = 0; i < frontier.size(); i++){	//Entire Frontier
			vector<int> temporary_use = frontier[i]; 
			site my_site = lattice[temporary_use[0]][temporary_use[1]];	
	 		if(my_site.label == 0){
			counter++;
			} else if (my_site.label == 1){
				counter2++;
			}

		}
			vector<int> temporary_use = frontier[i]; 
			site my_site = lattice[temporary_use[0]][temporary_use[1]];	


		vector<int> mother_xy = frontier[random_frontier_index]; // choose a random (x,y) pair in frontier 	//Does not save an index. frontier[] calls it save an x and y value.i

 		site mother = lattice[mother_xy[0]][mother_xy[1]]; // find the site at that randomly chosen frontier (x,y)







