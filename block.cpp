/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   block.cpp
 * Author: pablo
 * 
 * Created on 14 de febrero de 2017, 22:31
 */
#include "box.h"
#include "block.h"
#include <iostream>

block::block(int width, int height) : box(width,height,0.0f) {
    visible = true;
}

block::~block() {
}

