/*
 * TerminalControl.hh
 *
 *  Created on: Sep 8, 2012
 *      Author: yuasa
 */

#ifndef TERMINALCONTROL_HH_
#define TERMINALCONTROL_HH_

#include "CxxUtilities/CommonHeader.hh"

namespace CxxUtilities {

class TerminalControl {
public:
	static void clearScreen(){
		printf("\033[2J");
	}

public:
	static void moveCursorToXY(uint32_t x,uint32_t y){
		printf("\033[%d;%dH" ,y,x);
	}

public:

};

}


#endif /* TERMINALCONTROL_HH_ */