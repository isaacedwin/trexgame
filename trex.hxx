//
// Created by Nicole Fay on 30/05/21.
//

#pragma once
#include <ge211.hxx>
#include "game_config.hxx"
#include "obstacle.hxx"
#include <iostream>




using Position = ge211::geometry::Posn<int>;
using Velocity = ge211::geometry::Dims<int>;
using Dimensions = ge211::geometry::Dims<int>;

struct Trex
{
    // CONSTRUCTOR

    Trex(Game_config const&);

    // MEMBER FUNCTIONS

    // Returns the state of the T-rex after `dt` seconds have passed
    Trex next(double dt) const;

    // has the T-rex hit the top? (for double jump)
    bool hits_top(Game_config const&);

    // has the T-rex hit the middle? (for single jump)
    bool hits_middle(Game_config const&);

    // has the T-rex landed again?
    bool hits_floor(Game_config const&);



    // MEMBER VARIABLES

    // Position of top left, jumping + neutral
    Position trex_pos;

    // Position of top left, slide
    Position trex_sliding_pos;

    // Velocity, especially pertaining to vertical. X-velocity stays at 0.
    Velocity velocity;

    // true when trex slides
    bool slide;

    // true when trex double jumps
    bool isdoublejump;

    // Dimensions
    Dimensions trex_size;
    Dimensions trex_slide_size;

    //point counter
    int pointtotal;

};

// for tests
bool operator==(Trex const&, Trex const&);
bool operator!=(Trex const&, Trex const&);


