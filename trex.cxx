//
// Created by Nicole Fay on 30/05/21.
//

#include "trex.hxx"
#include "game_config.hxx"

Trex::Trex(Game_config const& config)
        : trex_pos(config.trex_neutral_pos),
          trex_sliding_pos(config.trex_sliding_pos),
          velocity(config.trex_velocity_0),
          slide(false),
          isdoublejump(false),
          trex_size(config.trex_size),
          trex_slide_size(config.trex_slide_size),
          pointtotal(0)
{ }


Trex
Trex::next(double dt) const
{
    Trex result(*this);
    result.trex_pos.y += (velocity.height * dt);
    return result;
}


bool
Trex::hits_top(const Game_config& config)
{
    return trex_pos.y < config.max_jump_height;
}


bool
Trex::hits_middle(const Game_config& config)
{
    return trex_pos.y < config.one_jump_height;
}


bool
Trex::hits_floor(const Game_config& config)
{
    return trex_pos.y >= config.trex_neutral_pos.y;
}


bool
operator==(Trex const& a, Trex const& b)
{
    if (a.trex_pos == b.trex_pos && a.velocity == b.velocity && a.slide == b
            .slide){
        return true;
    }
    return false;
}


bool
operator!=(Trex const& a, Trex const& b)
{
    return !(a == b);
}