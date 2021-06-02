//
// Created by Isaac Winoto on 31/05/21.
//

#include "mysterybox.hxx"
#include "game_config.hxx"

MysteryBox::MysteryBox(Game_config const& config)
        :mysterybox_velocity(config.obstacle_velocity_generated),
         mysterybox_position(Position {config.scene_dims.width, 40}),
         mysterybox_size(config.mysterybox_size),
         visiblesprite(true)
{
}

MysteryBox
MysteryBox::next(double dt) const
{
    MysteryBox result(*this);
    result.mysterybox_position.x += (mysterybox_velocity.width * dt);
    return result;
}


