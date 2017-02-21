/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   box.cpp
 * Author: pablo
 * 
 * Created on 12 de febrero de 2017, 20:38
 */
#include "box.h"
#include <iostream>

box::box(int width, int height, float sp) {
    w=width;
    h=height;
    speed=sp;
}
void box::setPosition(float init_x, float init_y){
    x=init_x;
    y=init_y;
    sprite.setPosition(x,y);
    hitbox=sf::Rect<float> (x,y,w,h);
}
void box::loadSprite(sf::Texture texture, int pos_x, int pos_y){
    tex = texture;
    sprite=sf::Sprite(tex);
    sprite.setOrigin(0,0);
    sprite.setTextureRect(sf::IntRect(pos_x,pos_y,w,h));
}
void box::move(int dir_x,int dir_y){
    float mX = dir_x*speed;
    float mY = dir_y*speed;
    
    x=hitbox.left=hitbox.left+mX;
    y=hitbox.top=hitbox.top+mY;
    
    sprite.move(mX,mY);
}
void box::setSpeed(float sp){
    speed=sp;
}
bool box::collision(sf::Rect<float> hit){
    return hitbox.intersects(hit);
}
box::~box() {
}

