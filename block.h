/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   block.h
 * Author: pablo
 *
 * Created on 14 de febrero de 2017, 22:31
 */

#ifndef BLOCK_H
#define BLOCK_H

class block : public box{
public:
    block(int width,int height);
    void invisible(){visible=false;}
    virtual ~block();
    
    bool getVisible(){return visible;}
    
private:
    bool visible;
};

#endif /* BLOCK_H */

