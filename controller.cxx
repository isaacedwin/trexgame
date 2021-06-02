#include "controller.hxx"

Controller::Controller()
        : view_(model_)
{ }

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        quit();
    } else if (key == ge211::Key::up()){
        model_.trex_jump();
    } else if (key == ge211::Key::code(' ')){
        model_.trex_jump();
        model_.trex.isdoublejump = true;
    }
}

void
Controller::on_key_down(ge211::Key key) {
    if (key == ge211::Key::down() &&
        model_.trex.trex_pos.y == model_.config.trex_neutral_pos.y - 1) {
        model_.trex.slide = true;
    }
}

void
Controller::on_key_up(ge211::Key key) {
    if (key == ge211::Key::down()) {
        model_.trex.slide = false;
    }
}

void
Controller::on_mouse_up(ge211::Mouse_button, ge211::Posn<int>) {
    if (model_.gameover){
        model_.gameover = false;
        model_.restart_game();
    }
}

void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
}

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}