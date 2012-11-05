//
//  foot.cpp
//  danceApp_V14
//
//  Created by Julia Eichler on 24.08.12.
//
//

#include "foot.h"


Foot::Foot(float _xpos, float _ypos, char _side, char _gender, int _size){
    position.x = _xpos;
    position.y = _ypos;
    
    side = _side;
    gender = _gender;
    size = _size;
    
    if(gender == 'f')
    {
        if(side == 'l')
        {
            footShape.loadImage("img/Icons/follower_left.png");
        }
        else if(side == 'r')
        {
            footShape.loadImage("img/Icons/follower_right.png");
        }
    }
    else if(gender == 'm')
    {
        if(side == 'l')
        {
            footShape.loadImage("img/Icons/leader_right.png");
        }
        else if(side == 'r')
        {
            footShape.loadImage("img/Icons/leader_left.png");
        }
    }
    
    int width = footShape.width*size/100;
    int height = footShape.height*size/100;
    footShape.draw(position.x - width/2, position.y - height/2, width, height);
}
