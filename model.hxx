#pragma once

#include <ge211.hxx>
#include "trex.hxx"
#include "game_config.hxx"
#include <cstdlib>
#include "obstacle.hxx"
#include "mysterybox.hxx"

class Model
{
public:

    // CONSTRUCTOR
    explicit Model(Game_config const& config = Game_config());

    //MEMBER FUNCTIONS

    //makes trex jump
    void trex_jump();

    // restarting game
    void restart_game();

    // end game
    void end_game();

    // tells when to add a new obstacle/mystery box
    bool add_obstacle(Obstacle);
    bool add_mysterybox(MysteryBox);

    // collision detection
    bool hits_obstacle(Trex&, Obstacle&) const;
    bool hits_boost(Trex, MysteryBox) const;

    // point updater
    void add_points(Trex&);

    // obstacle booster for every 1000 points
    void boost_obstacles(Obstacle& o);

    // frames
    void on_frame(double dt);


    // MEMBER VARIABLES

    // configuration
    Game_config const config;

    // trex
    Trex trex;

    // vector of obstacles
    std::vector<Obstacle> obstacle_vector;

    // vector of mystery boxes
    std::vector<MysteryBox> mysterybox_vector;

    // states whether the game is over
    bool gameover;

    // checks whether the object is boosting from the mystery box
    bool boosting;

    // used to obtain the points at game over
    int finalpoints;

    // velocity of the obstacles
    Velocity generationvelocity;
};