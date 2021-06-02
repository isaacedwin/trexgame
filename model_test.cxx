//
// Created by Isaac Winoto on 30/05/21.
//

#include "model.hxx"
#include <catch.hxx>

using namespace ge211;
Game_config const config;

TEST_CASE("Check initial conditions for model and trex"){
    Model model(config);
    Trex trex = model.trex;
    CHECK(model.gameover == false);
    CHECK(model.boosting == false);
    CHECK(model.finalpoints == 0);
    CHECK(model.generationvelocity == config.obstacle_velocity_generated);
    CHECK(trex.trex_pos == config.trex_neutral_pos);
    CHECK(trex.pointtotal == 0);
    CHECK(trex.velocity == config.trex_velocity_0);
    CHECK(trex.trex_sliding_pos == config.trex_sliding_pos);
    CHECK(trex.slide == false);
    CHECK(trex.isdoublejump == false);
    CHECK(trex.trex_size == config.trex_size);
    CHECK(trex.trex_slide_size == config.trex_slide_size);
}

TEST_CASE("model colliding with obstacle"){
    Model model(config);
    Obstacle obstacle(config, config.obstacle_velocity_generated);
    double const dt = 10;
    Trex trex = model.trex;
    trex.trex_pos = {30,180};
    model.on_frame(dt);
    if(obstacle.obstacle_type == 1){
        trex.trex_pos = {config.scene_dims.width, config.floor - config.smallcactus_size.height};
        CHECK(model.hits_obstacle(trex, obstacle) == true);
    } else if(obstacle.obstacle_type == 2){
        trex.trex_pos = {config.scene_dims.width, config.floor - config.bigcactus_size.height};
        CHECK(model.hits_obstacle(trex, obstacle) == true);
    } else if(obstacle.obstacle_type == 3){
        trex.trex_pos = {config.scene_dims.width, config.floor - 105};
        CHECK(model.hits_obstacle(trex, obstacle) == true);
    }
}

TEST_CASE("restarting game"){
    Model model(config);
    double const dt = 10;
    Trex trex = model.trex;
    trex.trex_pos = {30,180};
    model.on_frame(dt);
    model.gameover = true;
    model.restart_game();
    CHECK (model.generationvelocity == config.obstacle_velocity_generated);
    CHECK(model.gameover == false);
}

TEST_CASE("boosting"){
    Model model(config);
    Obstacle obstacle(config, config.obstacle_velocity_generated);
    model.boosting = true;
    model.boost_obstacles(obstacle);
    CHECK(model.boosting == true);
    CHECK (obstacle.storage_velocity.width == -152);
}

TEST_CASE("mystery box"){
    Model model(config);
    Trex trex = model.trex;
    MysteryBox mysteryBox(config);
    CHECK(model.hits_boost(trex, mysteryBox) == false);
    mysteryBox.mysterybox_position = trex.trex_pos;
    CHECK(model.hits_boost(trex, mysteryBox) == true);
}

TEST_CASE("jump and point system"){
    Model model(config);
    Trex trex = model.trex;
    model.trex_jump();
    CHECK(model.trex.velocity == Velocity{0,config.jump_velocity * -1});
    CHECK(trex.pointtotal == 0);
    model.add_points(trex);
    CHECK(trex.pointtotal == 100);
}