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

box::box(int width, int height, float speed) {
    w=width;
    h=height;
    s=speed;
}
void box::setPosition(float init_x, float init_y){
    x=init_x;
    y=init_y;
    sprite.setPosition(x,y);
    hitbox=sf::Rect<float> (x,y,w,h);
}
void box::loadSprite(const char* texture, int pos_x, int pos_y){
    if(tex.loadFromFile(texture)==false){
        std::cerr <<"Error en al cargar el sprite";
        exit(0);
    }
    sprite=sf::Sprite(tex);
    sprite.setOrigin(0,0);
    sprite.setTextureRect(sf::IntRect(pos_x,pos_y,w,h));
}
void box::move(int dir_x,int dir_y){
    
}
box::~box() {
}

