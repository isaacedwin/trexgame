//
//
// Created by Nicole Fay on 30/05/21.
//

#pragma once
#include <ge211.hxx>
#include <iostream>


struct Game_config
{
    // Constructs an instance with the default parameters.
    Game_config();

    // The dimensions of the whole window:
    ge211::geometry::Dims<int> scene_dims;

    // The T-rex's initial position (x,y). this is also the default position
    // when not jumping or sliding:
    ge211::geometry::Posn<int> trex_neutral_pos;

    // The T-rex's initial velocity {width, height}:
    ge211::geometry::Dims<int> trex_velocity_0;

    // The object's initial velocity {width, height}:
    ge211::geometry::Dims<int> obstacle_velocity_generated;

    // T-rex's position when sliding
    ge211::geometry::Posn<int> trex_sliding_pos;

    // y position of the 'floor'
    int floor;

    // The y-velocity when the T-rex jumps, make opposite sign for falling
    // velocity
    int jump_velocity;

    // The max height reached by the T-rex from one jump
    int one_jump_height;

    // The max height reached by the T-rex from double jumping
    int max_jump_height;

    // The maximum x-velocity of the obstacles
    int max_obstacle_velocity;

    // The boost velocity when using the mystery box
    int mb_velocity;

    // The amount that the x-velocity increases every 1000 points
    int obstacle_increase;

    // The amount that the x-velocity increases every 1000 points if boosted
    int obstacle_increase_boost;

    // sizes
    ge211::geometry::Dims<int> trex_size;
    ge211::geometry::Dims<int> trex_slide_size;
    ge211::Dims<int> smallcactus_size;
    ge211::Dims<int> bigcactus_size;
    ge211::Dims<int> bird_size;
    ge211::Dims<int> mysterybox_size;
};