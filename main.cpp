#include <SFML/Graphics.hpp>

const sf::Keyboard::Key controls[4] = {
    sf::Keyboard::A, //Player1 UP
    sf::Keyboard::Z, //Player1 DOWN
    sf::Keyboard::Up, //Player2 UP
    sf::Keyboard::Down, //Player2 DOWN
};

//Parameters
const sf::Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;
const float time_step = 0.017f; //60 fps

sf::Vector2f ball_velocity;
bool is_player_serving = true;
const float initial_velocity_x = 100.f; //horizontal velocity
const float initial_velocity_y = 60.f; //vertical velocity
const float velocity_multiplier = 1.1f; //how much the ball will speed up everytime it hits a paddle. Here, 10% every time.


//Objects of the game
sf::CircleShape ball;
sf::RectangleShape paddles[2];

void reset();

void init() {
    // Set size and origin of paddles
    for (sf::RectangleShape &p : paddles) {
        p.setSize(paddleSize);
        p.setOrigin(paddleSize / 2.f);
    }
    // Set size and origin of ball
        ball.setRadius(ballRadius);
        ball.setOrigin(ballRadius,ballRadius); //Should be half the ball width and height

    // reset paddle position
    paddles[0].setPosition(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f);
    paddles[1].setPosition(gameWidth - (paddleOffsetWall + paddleSize.x / 2.f), gameHeight / 2.f); //
    // reset Ball Position
    ball.setPosition(gameWidth / 2.f, gameHeight / 2.f); //

    ball_velocity = { (is_player_serving ? initial_velocity_x : -initial_velocity_x), initial_velocity_y };

}

void update(float dt){
    // handle paddle movement
    float direction = 0.0f;
    if (sf::Keyboard::isKeyPressed(controls[0])) {
        direction--;
    }
    if (sf::Keyboard::isKeyPressed(controls[1])) {
        direction++;
    }
    paddles[0].move(sf::Vector2f(0.f, direction * paddleSpeed * dt));
    paddles[1].move(sf::Vector2f(0.f, direction * paddleSpeed * dt)); //
    ball.move(ball_velocity * dt);

    // check ball collision
    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;
    if (by > gameHeight) { //bottom wall
        // bottom wall
        ball_velocity.x *= velocity_multiplier;
        ball_velocity.y *= -velocity_multiplier;
        ball.move(sf::Vector2f(0.f, -10.f));
    } else if (by < 0) { //top wall
        // top wall
        ball_velocity.x *= velocity_multiplier;
        ball_velocity.y *= -velocity_multiplier;
        ball.move(sf::Vector2f(0.f, 10.f)); 
    } 
    else if (bx > gameWidth) {
        // right wall
        reset();
    } else if (bx < 0) {
        // left wall
        reset();
    }

    else if (
        //ball is inline or behind paddle AND
        bx < paddleSize.x + paddleOffsetWall && 
        //ball is below top edge of paddle AND
        by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
        //ball is above bottom edge of paddle
        by < paddles[0].getPosition().y + (paddleSize.y * 0.5)){
    {
        // bounce off left paddle
    } else if (...) {
        // bounce off right paddle
    }


}

void render(sf::RenderWindow &window) {
    // Draw Everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
}

int main(){
    sf::RenderWindow window(sf::VideoMode({gameWidth, gameHeight}), "SFML works!");
    sf::Clock clock;
    init();

    while (window.isOpen()){
        float dt = clock.restart().asSeconds(); 
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        update(dt);
        window.clear();
        render(window);
        window.display();
    }  
    
  return 0;
}
