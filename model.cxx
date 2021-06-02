#include "model.hxx"
#include "obstacle.hxx"
#include <iostream>
#include "mysterybox.hxx"

Model::Model(Game_config const& config)
        : config(),
          trex(config),
          gameover(false),
          boosting(false),
          finalpoints{0},
          generationvelocity(config.obstacle_velocity_generated)
{
    obstacle_vector.push_back(Obstacle(config,generationvelocity));
    mysterybox_vector.push_back(MysteryBox(config));
}


// generates distances at which obstacles & MBs spawn
static int obstaclehigh = 450;
static int margins = 50;
static ge211::Random_source<int> obstacle_space(350,obstaclehigh);
static ge211::Random_source<int> mysterybox_space(420,obstaclehigh);


void
Model::trex_jump()
{
    trex.velocity = {0,config.jump_velocity * -1};
}


void
Model::restart_game()
{
    gameover = false;
    generationvelocity = config.obstacle_velocity_generated;
    obstacle_vector.push_back(Obstacle(config,generationvelocity));
    mysterybox_vector.push_back(MysteryBox(config));
}


void
Model::end_game()
{
    obstacle_vector.clear();
    mysterybox_vector.clear();
    finalpoints = trex.pointtotal;
    trex.pointtotal = 0;
}


bool
Model::add_obstacle(Obstacle o)
{
    return o.obstacle_position.x <
           config.scene_dims.width - obstacle_space.next() + margins
           && o.obstacle_position.x >
              config.scene_dims.width - obstacle_space.next() - margins;
}


bool
Model::add_mysterybox(MysteryBox m)
{
    return m.mysterybox_position.x <
           config.scene_dims.width - 3*mysterybox_space.next() + margins
           && m.mysterybox_position.x >
              config.scene_dims.width - 3*mysterybox_space.next() - margins;
}


bool
Model::hits_obstacle(Trex& t, Obstacle& o) const
{
    int xpos = 0;
    int ypos = 0;
    int twidth = 0;
    int theight = 0;

    if (t.slide){
        xpos = t.trex_sliding_pos.x;
        ypos = t.trex_sliding_pos.y;
        twidth = t.trex_slide_size.width;
        theight = t.trex_slide_size.height;
    } else {
        xpos = t.trex_pos.x;
        ypos = t.trex_pos.y;
        twidth = t.trex_size.width;
        theight = t.trex_size.height;
    }

    if (xpos > (o.obstacle_position.x + o.obstacle_size.width)) {
        return false;
    } else if (xpos + twidth < o.obstacle_position.x) {
        return false;
    } else if (ypos > (o.obstacle_position.y + o.obstacle_size.height)) {
        return false;
    } else if (ypos + theight < o.obstacle_position.y) {
        return false;
    }
    else {
        return true;
    }
}


bool
Model::hits_boost(Trex t, MysteryBox m) const
{
    if (t.trex_pos.x > m.mysterybox_position.x + m.mysterybox_size.width){
        return false;
    } else if (t.trex_pos.x + t.trex_size.width < m.mysterybox_position.x){
        return false;
    } else if (t.trex_pos.y > m.mysterybox_position.y + m.mysterybox_size.height){
        return false;
    }else if (t.trex_pos.y + t.trex_size.height < m.mysterybox_position.y){
        return false;
    } else {
        return true;
    }
}


void
Model::add_points(Trex& t)
{
    t.pointtotal += 100;
}


void
Model::boost_obstacles(Obstacle &o)
{
    if (o.obstacle_velocity.width > config.max_obstacle_velocity){
        if (boosting){
            o.storage_velocity.width -= config.obstacle_increase_boost;
        } else {
            o.obstacle_velocity.width -= config.obstacle_increase;
            o.storage_velocity.width -= config.obstacle_increase;
        }
    }
}


void Model::on_frame(double dt)
{
    // TREX
    if (trex.hits_middle(config) && !trex.isdoublejump){
        trex.velocity = {0, config.jump_velocity};
    } else if (trex.hits_top(config)){
        trex.velocity = {0, config.jump_velocity};
        trex.isdoublejump = false;
    }

    if (trex.hits_floor(config)){
        trex.velocity = config.trex_velocity_0;
        trex.trex_pos.y -= 1;
    }
    trex = trex.next(dt);


    // OBSTACLE
    // if MB boosting, make obstacles fast and don't implement collisions
    // if not, implement collision detection
    for (Obstacle& o: obstacle_vector) {
        if (boosting) {
            o.obstacle_velocity.width = config.mb_velocity;
        } else {
            o.obstacle_velocity.width = o.storage_velocity.width;
            if (hits_obstacle(trex, o)) {
                gameover = true;
                end_game();
            }
        }
    }

    // implement obstacle speed increase
    if (trex.pointtotal > 0 && trex.pointtotal % 1000 == 0) {
        for (Obstacle &o: obstacle_vector) {
            boost_obstacles(o);
        }

        if (boosting){
            generationvelocity.width -= config.obstacle_increase_boost;
        } else {
            generationvelocity.width -= config.obstacle_increase;
        }
    }

    // advance obstacles
    for (Obstacle &o: obstacle_vector){
        o = o.next(dt);
    }

    // obstacle vector management
    Obstacle lastadded = obstacle_vector.back();
    Obstacle firstadded = obstacle_vector.front();

    if (add_obstacle(lastadded)){
        obstacle_vector.push_back(Obstacle(config,generationvelocity));
    }

    if (firstadded.obstacle_position.x < -50){
        obstacle_vector.erase(obstacle_vector.begin());
        add_points(trex);
    }

    //MYSTERY BOX
    // boost
    for (MysteryBox& m: mysterybox_vector){
        m = m.next(dt);
        if (Model::hits_boost(trex, m)){
            boosting = true;
            m.visiblesprite = false;
            finalpoints = trex.pointtotal;
        }
    }

    // end boost when 400 points have been gained
    if (trex.pointtotal == (finalpoints+400)){
        boosting = false;
    }

    // mystery box vector management
    MysteryBox mblastadded = mysterybox_vector.back();

    if (add_mysterybox(mblastadded)){
        mysterybox_vector.push_back(MysteryBox(config));
    }

    if (mysterybox_vector.size() > 1){
        mysterybox_vector.erase(mysterybox_vector.begin());
    }
}

