#include "ball.hxx"
#include <catch.hxx>

Block const The_Paddle {100, 400, 100, 20};

TEST_CASE("Ball::Ball")
{
Game_config config;
Ball ball(The_Paddle, config);

CHECK(ball.center.x == 150);
CHECK(ball.center.y == 394);
}

TEST_CASE("Ball::hits_side")
{
Game_config config;
Ball ball(The_Paddle, config);

CHECK_FALSE(ball.hits_side(config));
ball.center.x = 1;
CHECK(ball.hits_side(config));
ball.center.x = config.scene_dims.width - 1;
CHECK(ball.hits_side(config));
ball.center.x = config.scene_dims.width / 2;
CHECK_FALSE(ball.hits_side(config));
ball.center.x = 0;
CHECK(ball.hits_side(config));
ball.center.x = ball.radius;
CHECK_FALSE(ball.hits_side(config));
ball.center.x = ball.radius - 1;
CHECK(ball.hits_side(config));

}

TEST_CASE("Ball::top_left")
{
    Game_config config;
    Ball ball(The_Paddle, config);
    ball.center.x = 4;
    ball.center.y = 7;
    ball.radius = 3;

    CHECK(1 == ball.top_left().x);
    CHECK(4 == ball.top_left().y);
}

TEST_CASE("Ball::hits top")
{
    Game_config config;
    Ball ball(The_Paddle, config);
    ball.center.x = 8;
    ball.center.y = config.scene_dims.height;
    ball.radius = 6;

    CHECK_FALSE(ball.hits_top(config));
    ball.center.y = 0;
    CHECK(ball.hits_top(config));
    ball.center.y = ball.radius;
    CHECK_FALSE(ball.hits_top(config));
    ball.center.y = ball.radius - 1;
    CHECK(ball.hits_top(config));
    ball.center.y = config.scene_dims.height;
    CHECK_FALSE(ball.hits_top(config));
    ball.center.y = 0 - ball.radius;
    CHECK(ball.hits_top(config));
    ball.center.y = config.scene_dims.height;
    ball.center.x = 0 - ball.radius;
    CHECK_FALSE(ball.hits_top(config));
}

TEST_CASE("Ball::hits top and Ball::hits side"){
    Game_config config;
    Ball ball(The_Paddle, config);
    ball.center.x = 0 - ball.radius;
    ball.center.y = 0 - ball.radius;
    CHECK(ball.hits_top(config));
    CHECK(ball.hits_side(config));
}

TEST_CASE("Ball::hits bottom")
{
    Game_config config;
    Ball ball(The_Paddle, config);
    ball.center.x = 8;
    ball.center.y = config.scene_dims.height;
    ball.radius = 6;

    CHECK(ball.hits_bottom(config));
    ball.center.y = config.scene_dims.height-10;
    CHECK_FALSE(ball.hits_bottom(config));
    ball.center.y = config.scene_dims.height - ball.radius;
    CHECK_FALSE(ball.hits_bottom(config));
    ball.center.y = config.scene_dims.height - ball.radius + 1;
    CHECK(ball.hits_bottom(config));
    ball.center.y = config.scene_dims.height - 1;
    CHECK(ball.hits_bottom(config));
    ball.center.y = 0;
    CHECK_FALSE(ball.hits_bottom(config));

}

TEST_CASE("Ball::next"){
    Game_config config;
    Ball ball(The_Paddle, config);
    ball.velocity = {4,7};
    ball.center = {0,0};
    ball = ball.next(1);
    CHECK(ball.center.x == 4);
    CHECK(ball.center.y == 7);
    ball = ball.next(1);
    CHECK_FALSE(ball.center.x == 4);
    CHECK_FALSE(ball.center.y == 7);
    ball.velocity = { 6, 8};
    ball = ball.next(0.5);
    CHECK(ball.center.x == 11);
    CHECK(ball.center.y == 18);
}

TEST_CASE("BALL:: hits block"){
    Game_config config;
    Ball ball(The_Paddle, config);
    Block b;
    b.x = 100;
    b.y = 100;
    b.width = 100;
    b.height = 40;
    ball.center.x = 10;
    ball.center.y = 10;
    ball.radius = 5;
    CHECK_FALSE(ball.hits_block(b));
    ball.center.x = 95;
    CHECK_FALSE(ball.hits_block(b));
    ball.center.y = 95;
    CHECK(ball.hits_block(b));
    ball.center.y = 95;
    ball.center.x = 95;
    CHECK(ball.hits_block(b));
    ball.center.y = 130;
    ball.center.x = 94;
    CHECK_FALSE(ball.hits_block(b));
    ball.center.x = 95;
    CHECK(ball.hits_block(b));
    ball.center.x = 205;
    CHECK(ball.hits_block(b));
    ball.center.x = 206;
    CHECK_FALSE(ball.hits_block(b));
    ball.center.x = 150;
    ball.center.y = 95;
    CHECK(ball.hits_block(b));
    ball.center.y = 94;
    CHECK_FALSE(ball.hits_block(b));
    ball.center.y = 140;
    CHECK(ball.hits_block(b));
    ball.center.y = 146;
    CHECK_FALSE(ball.hits_block(b));
    ball.center.y = 145;
    CHECK(ball.hits_block(b));




}

TEST_CASE("BALL: destroy block"){
    Game_config config;
    Ball ball(The_Paddle, config);
    Block b1;
    b1.x = 100;
    b1.y = 100;
    b1.width = 50;
    b1.height = 20;
    Block b2;
    b2.x = 200;
    b2.y = 20;
    b2.width = 50;
    b2.height = 20;
    Block b3;
    b3.x = 300;
    b3.y = 20;
    b3.width = 50;
    b3.height = 20;
    Block b4;
    b4.x = 400;
    b4.y = 100;
    b4.width = 50;
    b4.height = 20;
    Block b5;
    b4.x = 400;
    b4.y = 20;
    b4.width = 50;
    b4.height = 20;
    std::vector<Block> bv;
    bv.push_back(b1);
    bv.push_back(b2);
    bv.push_back(b3);
    bv.push_back(b4);
    bv.push_back(b5);
    CHECK(bv.size() == 5);
    ball.center.x = 8;
    ball.center.y = 4;
    ball.radius = 6;
    CHECK_FALSE(ball.destroy_brick(bv));
    ball.center.x = 400;
    ball.center.y = 20;
    CHECK(ball.destroy_brick(bv));
    CHECK(bv.size() == 4);
    CHECK_FALSE(ball.destroy_brick(bv));
    CHECK(bv.size() == 4);
    ball.center.x = 40;
    ball.center.y = 20;
    CHECK_FALSE(ball.destroy_brick(bv));
    ball.center.x = 300;
    ball.center.y = 20;
    CHECK(ball.destroy_brick(bv));
    CHECK(bv.size() == 3);
    ball.center.x = 100;
    ball.center.y = 100;
    CHECK(ball.destroy_brick(bv));
    CHECK(bv.size() == 2);
    ball.center.x = 200;
    ball.center.y = 20;
    CHECK(ball.destroy_brick(bv));
    CHECK(bv.size() == 1);
    bv.pop_back();
    CHECK(bv.size() == 0);
    CHECK_FALSE(ball.destroy_brick(bv));


}







TEST_CASE("Ball::equals Ball")
{
    Game_config config;
    Ball ball1(The_Paddle,config);
    Ball ball2(The_Paddle,config);
    ball1.center.x = 10;
    ball2.center.x = 10;
    CHECK(operator==(ball1, ball2));
    ball1.center.y = 5;
    ball2.center.y = 10;
    CHECK_FALSE(operator==(ball1, ball2));
    ball2.center.y = 5;
    ball1.live = true;
    CHECK_FALSE(operator==(ball1, ball2));
    ball1.velocity.width = 4;
    ball2.velocity.width = 4;
    CHECK_FALSE(operator==(ball1, ball2));
    ball1.live = false;
    CHECK(operator==(ball1, ball2));
    ball1.velocity.height = 6;
    ball2.velocity.height = 9;
    CHECK_FALSE(operator==(ball1, ball2));
    ball1.velocity.height = 9;
    CHECK(operator==(ball1, ball2));
    ball1.radius = 20;
    ball2.radius = 2;
    CHECK_FALSE(operator==(ball1, ball2));
    ball1.radius = 2;
    CHECK(operator==(ball1, ball2));

}



