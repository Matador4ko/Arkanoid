/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   box.h
 * Author: pablo
 *
 * Created on 12 de febrero de 2017, 20:38
 */

#ifndef BOX_H
#define BOX_H
#include <SFML/Graphics.hpp>

class box {
public:
    box(int width, int height, float sp);
    void setPosition(float init_x, float init_y);
    void loadSprite(sf::Texture texture, int pos_x, int pos_y);
    void move(int dir_x,int dir_y);
    void setSpeed(float sp);
    bool collision(sf::Rect<float> hit);
    virtual ~box();
    
    float getS(){return speed;}
    float getX(){return x;}
    float getY(){return y;}
    int getW(){return w;}
    int getH(){return h;}
    sf::Sprite getSprite(){return sprite;}
    sf::Rect<float> getHit(){return hitbox;}
    
private:
    int w, h;
    float x, y;
    float speed;
    
    sf::Texture tex;
    sf::Sprite sprite;
    sf::Rect<float> hitbox;
};

#endif /* BOX_H */

