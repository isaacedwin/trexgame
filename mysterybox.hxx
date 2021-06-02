//
// Created by Isaac Winoto on 31/05/21.
//

#pragma once
#include <ge211.hxx>
#include "game_config.hxx"
#include <iostream>
#include "trex.hxx"

using Position = ge211::geometry::Posn<int>;
using Velocity = ge211::geometry::Dims<int>;
using Dimensions = ge211::geometry::Dims<int>;

struct MysteryBox {

    // CONSTRUCTOR
    MysteryBox(Game_config const&);

    // MEMBER FUNCTIONS
    MysteryBox next(double dt) const;

    // MEMBER VARIABLES
    Velocity mysterybox_velocity;
    Position mysterybox_position;
    Dimensions mysterybox_size;
    bool visiblesprite; //helps to remove sprite when the box is hit
};