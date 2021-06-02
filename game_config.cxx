#include "game_config.hxx"
static int seventy = 70;
static int max_dimensions = 800;
Game_config::Game_config()
        : scene_dims{max_dimensions, 250},
          trex_neutral_pos{70,180},
          trex_velocity_0{0,0},
          obstacle_velocity_generated{-150,0},
          trex_sliding_pos{seventy,210},
          floor{238},
          jump_velocity{395},
          one_jump_height{seventy},
          max_jump_height{20},
          max_obstacle_velocity{-600},
          mb_velocity{-max_dimensions},
          obstacle_increase{1},
          obstacle_increase_boost{2},
          trex_size{50,58},
          trex_slide_size{59,28},
          smallcactus_size{17,25},
          bigcactus_size{38,55},
          bird_size{100,90},
          mysterybox_size{30, 30}
{ }

