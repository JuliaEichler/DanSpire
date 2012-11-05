//
//  choreography.cpp
//  danceApp_V14
//
//  Created by Julia Eichler on 24.08.12.
//
//

#include "choreography.h"

Choreography::Choreography(){}

vector< vector<int> > Choreography::init(int x, int y, int width, int height, string type){
    
    int boxX1, boxX2, boxX3, boxX4, boxX5, boxX6, boxY1, boxY2, boxY3;
    
    if(type == "Waltz")
    {
        vector< vector<int> > choreo(6, vector<int>(4));
        
        boxX1 = x;
        boxY1 = y;
        boxX2 = boxX1+width;
        boxY2 = boxY1+height;
        
        // x-pos ------------------ y-pos --------------------- 0 - left, 1 -right ---- icon ------------
        choreo[0][0] = boxX2;       choreo[0][1] = boxY2;       choreo[0][2] = 1;       choreo[0][3] = 1;
        choreo[1][0] = boxX1;       choreo[1][1] = boxY2;       choreo[1][2] = 0;       choreo[1][3] = 7;
        choreo[2][0] = boxX1;       choreo[2][1] = boxY2;       choreo[2][2] = 1;       choreo[2][3] = 4;
        choreo[3][0] = boxX1;       choreo[3][1] = boxY1;       choreo[3][2] = 0;       choreo[3][3] = 2;
        choreo[4][0] = boxX2;       choreo[4][1] = boxY1;       choreo[4][2] = 1;       choreo[4][3] = 6;
        choreo[5][0] = boxX2;       choreo[5][1] = boxY1;       choreo[5][2] = 0;       choreo[5][3] = 3;
        
        return choreo;
    }
    
    else if(type == "Salsa")
    {
        vector< vector<int> > choreo(6, vector<int>(4));
        
        boxX1 = x;
        boxX2 = boxX1+width;
        boxY1 = y;
        boxY2 = (boxY1+height)/2;
        boxY3 = boxY1+height;
        
        // x-pos ------------------ y-pos --------------------- 0 - left, 1 -right ---- icon ------------
        choreo[0][0] = boxX2;       choreo[0][1] = boxY3;       choreo[0][2] = 1;       choreo[0][3] = 1;
        choreo[1][0] = boxX1;       choreo[1][1] = boxY2;       choreo[1][2] = 0;       choreo[1][3] = 5;
        choreo[2][0] = boxX2;       choreo[2][1] = boxY2;       choreo[2][2] = 1;       choreo[2][3] = 2;
        choreo[3][0] = boxX1;       choreo[3][1] = boxY1;       choreo[3][2] = 0;       choreo[3][3] = 2;
        choreo[4][0] = boxX2;       choreo[4][1] = boxY2;       choreo[4][2] = 1;       choreo[4][3] = 5;
        choreo[5][0] = boxX1;       choreo[5][1] = boxY2;       choreo[5][2] = 0;       choreo[5][3] = 1;
        
        return choreo;
    }
    
    else if(type == "Jive")
    {
        vector< vector<int> > choreo(8, vector<int>(5));
        /*
        boxX1 = x;
        boxX2 = (boxX1+width)*1/5;
        boxX3 = (boxX1+width)*2/5;
        boxX4 = (boxX1+width)*3/5;
        boxX5 = boxX1+width;
        boxY1 = y;
        boxY2 = boxY1+height;
        
        // x-pos ------------------ y-pos --------------------- 0 - left, 1 -right ---- icon ------------------ half-step -------
        choreo[0][0] = boxX2;       choreo[0][1] = boxY2;       choreo[0][2] = 1;       choreo[0][3] = 1;       choreo[0][4] = 0;
        choreo[1][0] = boxX1;       choreo[1][1] = boxY1;       choreo[1][2] = 0;       choreo[1][3] = 5;       choreo[1][4] = 0;
        choreo[2][0] = boxX4;       choreo[2][1] = boxY1;       choreo[2][2] = 1;       choreo[2][3] = 6;       choreo[2][4] = 1;
        choreo[3][0] = boxX3;       choreo[3][1] = boxY1;       choreo[3][2] = 0;       choreo[3][3] = 3;       choreo[3][4] = 1;
        choreo[4][0] = boxX5;       choreo[4][1] = boxY1;       choreo[4][2] = 1;       choreo[4][3] = 3;       choreo[4][4] = 0;
        choreo[5][0] = boxX3;       choreo[5][1] = boxY1;       choreo[5][2] = 0;       choreo[5][3] = 5;       choreo[5][4] = 1;
        choreo[6][0] = boxX4;       choreo[6][1] = boxY1;       choreo[6][2] = 1;       choreo[6][3] = 4;       choreo[6][4] = 1;
        choreo[7][0] = boxX1;       choreo[7][1] = boxY1;       choreo[7][2] = 0;       choreo[7][3] = 4;       choreo[7][4] = 0;
        */
        
        boxX1 = x;
        boxX2 = (boxX1+width)*1/7;
        boxX3 = (boxX1+width)*2/7;
        boxX4 = (boxX1+width)*5/7;
        boxX5 = (boxX1+width)*6/7;
        boxX6 = boxX1+width;
        boxY1 = y;
        boxY2 = boxY1+height;
        
        // x-pos ------------------ y-pos --------------------- 0 - left, 1 -right ---- icon ------------------ half-step -------
        choreo[0][0] = boxX1;       choreo[0][1] = boxY2;       choreo[0][2] = 1;       choreo[0][3] = 1;       choreo[0][4] = 0;
        choreo[1][0] = boxX1;       choreo[1][1] = boxY1;       choreo[1][2] = 0;       choreo[1][3] = 5;       choreo[1][4] = 0;
        choreo[2][0] = boxX5;       choreo[2][1] = boxY1;       choreo[2][2] = 1;       choreo[2][3] = 6;       choreo[2][4] = 1;
        choreo[3][0] = boxX4;       choreo[3][1] = boxY1;       choreo[3][2] = 0;       choreo[3][3] = 3;       choreo[3][4] = 1;
        choreo[4][0] = boxX6;       choreo[4][1] = boxY1;       choreo[4][2] = 1;       choreo[4][3] = 3;       choreo[4][4] = 0;
        choreo[5][0] = boxX2;       choreo[5][1] = boxY1;       choreo[5][2] = 0;       choreo[5][3] = 5;       choreo[5][4] = 1;
        choreo[6][0] = boxX3;       choreo[6][1] = boxY1;       choreo[6][2] = 1;       choreo[6][3] = 4;       choreo[6][4] = 1;
        choreo[7][0] = boxX1;       choreo[7][1] = boxY1;       choreo[7][2] = 0;       choreo[7][3] = 4;       choreo[7][4] = 0;
        
        return choreo;
    }
}