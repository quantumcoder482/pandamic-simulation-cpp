/** 
Author: Hunter Schemidt
Date: 09/16/2022
Course Name:  
Title: Simulation Pandamic  

This project simulating the pandamic by the virus. 

## Test Cases
 
*/

#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>
#include <windows.h>
#include "simulation.h"

#define FOREGROUND_WHITE 15

int main()
{
  size_t nRows = 9, nCols = 9;
  
  std::cout << "Input Persons Group N X N " << std::endl;
  std::cout << "N Rows: "; std::cin >> nRows;
  std::cout << "N Cols: "; std::cin >> nCols;
  
  if(nRows <= 0 || nCols <= 0) {
  	std::cerr << "N must be more than 0"<< std::endl;
  	return -1;
  }
  
  // initialize Simulation Group
  std::cout << "Init.:\n";
  Simulation simulation(nRows, nCols);
  
  // displasy initial view;
  simulation.showSimulationGroup();
  
  // infect somebody
  size_t i = 1, j = 1;

  SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE); 
  std::cout << "Patient 0:\n";
  std::cout << "row: "; std::cin >> i;
  std::cout << "col: "; std::cin >> j;
  
  if(i <= 0 || j <= 0 || i >= nRows || j >= nCols) {
  	std::printf("Patient position overed %d, %d", nRows, nCols);
  	return -1;
  }
	
  simulation.infect(i, j);
	
  // simulation loop
  for (unsigned day = 0;;) {
  	
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE); 
    std::cout << "Day " << day << ":\n";
    simulation.showSimulationGroup();
    
    if (simulation.checkAllRecoverd()) {
      	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE); 
	  	std::cout << "No further progress detected on day "<< day << ".\n";
        
		break; // exit sim. loop
    }
    
    // simulate next day
    ++day;
    simulation.spread();
    
  }
  // done
  std::cout << "Done.\n";
  return 0;
}