#pragma once

#include "model.hxx"

class View
{
public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);
    ge211::Dims<int> initial_window_dimensions() const;


private:
    Model const& model_;
    // sprites & fonts
    ge211::Image_sprite const trex_sprite;
    ge211::Image_sprite const sliding_sprite;
    ge211::Image_sprite const smallcactus_sprite;
    ge211::Image_sprite const bigcactus_sprite;
    ge211::Image_sprite const bird_sprite;
    ge211::Image_sprite const mystery_box_sprite;
    ge211::Font const game_over_font_;
    ge211::Text_sprite game_over_message_;
    ge211::Font const points_font_;
    ge211::Text_sprite points_message_;
    ge211::Text_sprite repeat_message_;
};