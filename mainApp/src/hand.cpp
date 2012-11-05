//
//  hand.cpp
//  danceApp_V20
//
//  Created by Julia Eichler on 25.08.12.
//
//

#include "hand.h"


Hand::Hand(float _xpos, float _ypos, char _side, char _gender, int _size){
    position.x = _xpos;
    position.y = _ypos;
    
    side = _side;
    gender = _gender;
    size = _size;
    
    if(gender == 'f')
    {
        if(side == 'l')
        {
            handShape.loadImage("img/Icons/follower_hand_left.png");
        }
        else if(side == 'r')
        {
            handShape.loadImage("img/Icons/follower_hand_right.png");
        }
    }
    else if(gender == 'm')
    {
        if(side == 'r')
        {
            handShape.loadImage("img/Icons/leader_hand_right.png");
        }
        else if(side == 'l')
        {
            handShape.loadImage("img/Icons/leader_hand_left.png");
        }
    }
    
    int width = handShape.width*size/100;
    int height = handShape.height*size/100;
    handShape.draw(position.x - width/2, position.y - height/2, width, height);
}
