/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bar.cpp
 * Author: pablo
 * 
 * Created on 14 de febrero de 2017, 22:38
 */
#include "box.h"
#include "bar.h"
#include <iostream>

bar::bar(int width, int height, int speed) : box(width, height, speed) {
}

void bar::setPosition(int x, int y){
    box::setPosition(x,y);
    
    float w = box::getW();
    float h = box::getH();
    float size = w/5;
    
    secondLeftHitbox = sf::Rect<float>(x, y, size, h);
    leftHitbox = sf::Rect<float>(x+size, y, size, h);
    centerHitbox = sf::Rect<float>(x+(size*2), y, size, h);
    rightHitbox = sf::Rect<float>(x+(size*3), y, size, h);
    secondRightHitbox = sf::Rect<float>(x+(4*size), y, size, h);
    
}

void bar::move(int dX, int dY){
    box::move(dX,dY);
    float mX = dX*box::getS();
    
    secondLeftHitbox.left = secondLeftHitbox.left + mX;
    leftHitbox.left = leftHitbox.left + mX;
    centerHitbox.left = centerHitbox.left + mX;
    rightHitbox.left = rightHitbox.left + mX;
    secondRightHitbox.left = secondRightHitbox.left + mX;
}

int bar::collision(sf::Rect<float> hit){
    if(secondLeftHitbox.intersects(hit)) return 0;
    else if(leftHitbox.intersects(hit)) return 1;
    else if(centerHitbox.intersects(hit)) return 2;
    else if(rightHitbox.intersects(hit)) return 3;
    else if(secondRightHitbox.intersects(hit)) return 4;
    else return -1;
}

bar::~bar() {
}

