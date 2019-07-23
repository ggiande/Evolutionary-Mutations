//
//	./for.out
//

#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <vector>
	
using namespace std;
int main(){
	/* Given */
	float ro = 2;
	float rp = 1;
	/* Design for Gillespie's Algorithm 2. */
	float Dec_By_Factor = 4;
	float newRO = (ro/Dec_By_Factor);
	float newRP = (rp/Dec_By_Factor);


	/* Design for the virtual frontier. Remains constant once initialized. */
	vector<vector<int > > virtual_frontier = {{2,17},{3,15}};

	int median;
	if(LX % 2 == 0){
		median = LX/2;
	} else {
		median = (LX + 1)/2
	}

	/* Iterator to find all the x,y coordinates at the median to create the virtual frontier. */
	for(int i = 0; i < LY; i++){	//Can now use median.
		virtual_frontier.push_back({median, i});
	}

	//Input from Gillespie's Algorithm 1.
	//vector<int> mother_xy = frontier[frontier_index];

	/* Iterator to find if x,y coordinates are in the virtual array. */
	for (int i = 0; i < virtual_frontier.size(); i++){
		for(int j = 0; j < virtual_frontier.size(); j++){
			if(mother_xy[0] == virtual_frontier[i][0] && mother_xy[1] == virtual_frontier[i][1]){ //if {2,17} == {{3,14}, {5,12}}
				//We know that the coordinates selected by the Gillespie Algorithm is inside of the virtual frontier.





			}
		}
	}
	cout << "Did not use the Second Gillespie Algorithm at time step: " << t << endl; 
	
}

				//cout << "Found: " << mother_xy[0] << "," mother_xy[1] << "==" << virtual_frontier[i][j] << endl
				float Dec_By_Factor = 4;
				float newRP = (ro/Dec_By_Factor);	//flip the red and blue factors.
				float newRO = (rp/Dec_By_Factor);
