#include "view.hxx"
#include "model.hxx"

// text positions
static ge211::Posn<int> const game_over_posn{320, 100};
static ge211::Posn<int> const repeat_posn{335, 150};
static ge211::Posn<int> const points_posn{500, 10};

View::View(Model const& model)
        : model_(model),
          trex_sprite("trex_neutral.png"),
          sliding_sprite("trex_slide.png"),
          smallcactus_sprite("o_scactus.png"),
          bigcactus_sprite("o_bcactus.png"),
          bird_sprite("o_bird.png"),
          mystery_box_sprite("mystery_box.png"),
          game_over_font_("sans.ttf", 31),
          game_over_message_(ge211::Text_sprite::Builder(game_over_font_)
                                     .add_message("GAME OVER")
                                     .color(ge211::Color::white())
                                     .build()),
          points_font_("sans.ttf", 21),
          points_message_(ge211::Text_sprite::Builder(points_font_)
                                  .color(ge211::Color::white())
                                  .build()),
          repeat_message_(ge211::Text_sprite::Builder(points_font_)
                                  .add_message("click to try again")
                                  .color(ge211::Color::white())
                                  .build())
{ }

ge211::Dims<int>
View::initial_window_dimensions() const
{
    return model_.config.scene_dims;
}

void
View::draw(ge211::Sprite_set& set)
{

    if (model_.gameover){
        // game over
        set.add_sprite(game_over_message_, game_over_posn, 1);
        set.add_sprite(repeat_message_,repeat_posn,1);

        // final points
        ge211::Text_sprite::Builder builder{points_font_};
        builder << "Score: " << model_.finalpoints;
        points_message_.reconfigure(builder);
        set.add_sprite(points_message_, points_posn, 1);
    } else {
        //point counter
        ge211::Text_sprite::Builder builder{points_font_};
        builder << "Score: " << model_.trex.pointtotal;
        points_message_.reconfigure(builder);
        set.add_sprite(points_message_, points_posn, 1);

        // trex sprite
        if (!model_.trex.slide){
            set.add_sprite(trex_sprite,{model_.trex.trex_pos}, 2);
        } else if (model_.trex.slide){
            set.add_sprite(sliding_sprite, {model_.config.trex_sliding_pos});
        }

        // obstacle sprites
        for (Obstacle o:model_.obstacle_vector){
            if (o.obstacle_type == 1){
                set.add_sprite(smallcactus_sprite,o.obstacle_position);
            } else if (o.obstacle_type == 2){
                set.add_sprite(bigcactus_sprite,o.obstacle_position);
            } else if (o.obstacle_type == 3){
                set.add_sprite(bird_sprite, o.obstacle_position);
            }
        }

        // mystery box sprites
        for (MysteryBox m:model_.mysterybox_vector){
            if (m.visiblesprite){
                set.add_sprite(mystery_box_sprite, m.mysterybox_position, 1);
            }
        }
    }
}