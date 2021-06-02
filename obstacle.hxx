//
// Created by Nicole Fay on 29/05/21.
//
#pragma once
#include <ge211.hxx>
#include "game_config.hxx"
#include <iostream>
#include "trex.hxx"


using Position = ge211::geometry::Posn<int>;
using Velocity = ge211::geometry::Dims<int>;
using Dimensions = ge211::geometry::Dims<int>;

// there are 3 variants of an obstacle:
// 1) cactus that can be cleared with 1 jump
// 2) cactus that must be cleared with 2 jumps
// 3) the bird obstacle

struct Obstacle
{
    // CONSTRUCTOR
    Obstacle(Game_config const&, Velocity);

    // MEMBER FUNCTIONS
    Obstacle next(double dt) const;

    // MEMBER VARIABLES
    int obstacle_type;
    Velocity obstacle_velocity;
    Velocity storage_velocity;
    Position obstacle_position;
    Dimensions obstacle_size;

};