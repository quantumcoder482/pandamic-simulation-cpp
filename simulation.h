/**
Author: Hunter Schmidt
Date: 09/16/2022


Simulation Class define

- Entire group for simulation with Persons
- 3 member functions to simulation
  infect(): set first infected person
  spread(): spread virus in a day
  checkAllRecoverd(): check all person recoverd or not

*/

#include <cassert>
#include <iostream>
#include <vector>
#include "agent.h"

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

class Simulation {
	private:
		size_t _nRows, _nCols;
		vector<vector<Person>> group;
	public:
		Simulation(size_t nRows, size_t nCols) {
			// initialize row and col
			_nRows = nRows;
			_nCols = nCols; 
			
			// initialize group
			vector<Person> row(nCols, Person ('P'));
			vector<vector<Person>> g(nRows, row);
			group = g;
		}
		
		~Simulation() = default;
		Simulation(const Simulation&) = default;
		Simulation& operator=(const Simulation&) = default;
		
		vector<vector<Person>>& get() {
			return group;
		}
		
		void infect(size_t row, size_t col) { 
			group[row-1][col-1].status = 'I';
			group[row-1][col-1].prevStatus = 'I';
		}
		
		void spread() {
			for(size_t i = 0; i < _nRows; i++) {
				for(size_t j = 0; j < _nCols; j++) {
					switch(group[i][j].status) {
						case 'P': {// Check infected in neighbourhood
							bool infect = false;
							for (int iP = -1; !infect && iP <= 1; ++iP) {
					            for (int jP = -1; !infect && jP <= 1; ++jP) {
					            	if(i + iP < 0 || i + iP >= _nRows || j + jP < 0 || j + jP >= _nCols) continue;  // skip if overed group row and col range
					            	infect = group[i + iP][j + jP].prevStatus == 'I';
					            }
					        }
							group[i][j].status = infect ? 'I' : 'P';
							} break;
						case 'I': // Infected to Recoverd
							// skip this case to recover
						case 'R':
							group[i][j].status = 'R';
							break;
						default: assert(false); // Wrong status	
					}
				}
			}
			
			// reset group infected status - all person prev status set with current status
			for(size_t i = 0; i < _nRows; i++) {
				for(size_t j = 0; j < _nCols; j++) {
					group[i][j].prevStatus = group[i][j].status;
				}
			}
		}
		
		bool checkAllRecoverd() {
			for(size_t i = 0; i < _nRows; i++) {
				for(size_t j = 0; j < _nCols; j++) {
					if(group[i][j].status != 'R') return false;
				}
			}
			return true;
		}
		
		void showSimulationGroup() {
			for (size_t i = 0; i < _nRows; ++i) {
			    for (size_t j = 0; j < _nCols; ++j) {
			      switch(group[i][j].status) {
			      	case 'P':
			      		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE); 
			      		break;
			    	case 'R':
			    		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); 
			    		break;
					case 'I': 
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED); 
						break;
				  }
			      cout << ' ' << group[i][j].status;
			    }
			    cout << '\n';
			}
			cout << endl;
		}	
};