//
// Created by Nicole Fay on 29/05/21.
//

#include "obstacle.hxx"
#include "game_config.hxx"


// determine obstacle position
static Position
obstacle_pos(int i,
             Game_config const& config)
{
    int xpos = config.scene_dims.width;
    int ypos = config.floor;
    if (i == 1){
        ypos -= config.smallcactus_size.height;
    } else if (i == 2){
        ypos -= config.bigcactus_size.height;
    } else if (i == 3){
        ypos = 105;
    }
    return {xpos, ypos};
}


// random obstacle generator
static ge211::Random_source<int> random_obstacle(1,3);


Obstacle::Obstacle(Game_config const& config, Velocity v)
        :obstacle_type(random_obstacle.next()),
         obstacle_velocity(v),
         storage_velocity(v),
         obstacle_position{obstacle_pos(obstacle_type,config)}
{
    if (obstacle_type == 1){
        obstacle_size = config.smallcactus_size;
    } else if (obstacle_type == 2){
        obstacle_size = config.bigcactus_size;
    } else if (obstacle_type == 3){
        obstacle_size = config.bird_size;
    }
}


Obstacle
Obstacle::next(double dt) const
{
    Obstacle result(*this);
    result.obstacle_position.x += (obstacle_velocity.width * dt);
    return result;
}
