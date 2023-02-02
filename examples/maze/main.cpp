#include "Pokitto.h"


// https://talk.pokitto.com/t/recursive-maze-generation/2126/7

// Globals for Maze
#define MAZEWIDTH 45    // Must be odd
#define MAZEHEIGHT 45   // Must be odd

// Wall and floor colours
#define WALL 1
#define FLOOR  0

// The maze
uint8_t theMaze[MAZEWIDTH][MAZEHEIGHT];

// read pixel from maze array
int getMaze(int x,int y){
    return theMaze[x][y];
}

// set pixel in maze and alto plot to screen
void putMaze(int x, int y, int pix){
    theMaze[x][y] = pix;
    Pokitto::Display::drawPixel(x, y, pix);
	Pokitto::Core::update();
}

// draw the full maze to screen
void drawMaze(){
	for(int y1 = 0; y1< MAZEHEIGHT; y1++){
    	for(int x1 = 0; x1<MAZEWIDTH; x1++){
            Pokitto::Display::drawPixel(x1, y1, getMaze(x1,y1));
        }
    }
}

// randomly plot a maze using pure luck to complete it.
void stacklessMaze(){
	for(int y = 0; y< MAZEHEIGHT; y++){
		for(int x = 0; x<MAZEWIDTH; x++){
            Pokitto::Display::drawPixel(x, y, WALL);
			putMaze(x,y,WALL);
	    }
    }

    int mX = 1+random(MAZEWIDTH/2)*2;
    int mY = 1+random(MAZEHEIGHT/2)*2;
	putMaze(mX,mY,FLOOR);

    bool mazeDone = false;
    while (mazeDone == false){
        for(int i=0; i<16; i++){
            int oldX = mX;
            int oldY = mY;
            switch(random(100)/25){
                case 0:
                    if(mX+2<MAZEWIDTH){mX+=2;}
                break;
                case 1:
                    if(mX-2>0){mX-=2;}
                break;
                case 2:
                    if(mY+2<MAZEHEIGHT){mY+=2;}
                break;
                case 3:
                    if(mY-2>0){mY-=2;}
                break;
            }
            if(getMaze(mX,mY)==WALL){
                putMaze(mX,mY,FLOOR);
                putMaze((oldX+mX)/2,(oldY+mY)/2,FLOOR);
            }

            mazeDone = true;
        	for(int y = 1; y< MAZEHEIGHT-1; y+=2){
        		for(int x = 1; x<MAZEWIDTH-1; x+=2){
        			if(getMaze(x,y)==WALL){mazeDone = false;}
        	    }
            }
        }
    }

}


int main(){
    using PC=Pokitto::Core;
    using PD=Pokitto::Display;
    PC::begin();
    PD::persistence = true;
    PD::invisiblecolor = -1;
    srand(time(0));

    stacklessMaze();
    Pokitto::Display::setColor(1);
    Pokitto::Display::print(0,MAZEHEIGHT+1, "Finished!");
	Pokitto::Core::update();

    while( PC::isRunning() ){
        if( !PC::update() )
            continue;

    }

    return 0;
}

