/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bar.h
 * Author: pablo
 *
 * Created on 14 de febrero de 2017, 22:38
 */

#ifndef BAR_H
#define BAR_H

class bar : public box{
public:
    bar(int width, int height, int speed);
    void setPosition(int x, int y);
    void move(int dX,int dY);
    int collision(sf::Rect<float> hit);
    virtual ~bar();
private:
    sf::Rect<float> secondLeftHitbox;
    sf::Rect<float> leftHitbox;
    sf::Rect<float> centerHitbox;
    sf::Rect<float> secondRightHitbox;
    sf::Rect<float> rightHitbox;
};

#endif /* BAR_H */

