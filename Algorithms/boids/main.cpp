#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <ctime>

using namespace std;
using namespace sf;

// All units are in pixel

default_random_engine engine;
uniform_real_distribution<float> positionGenerator(-200, 200);
uniform_real_distribution<float> speedGenerator(-1, 1);
uniform_real_distribution<float> noiseGenerator(-1, 1);

Texture huier("./huier.jpg");

const unsigned winWidth = 1000;
const unsigned winHeight = 800;
const unsigned width = 3 * 20;
const unsigned height = 4 * 20; 
const float camSpeed = 100.0f;
const float boidSpeed = 5.0f;
const float deltaTime = 0.2f;

const float seprationRadius = 20;
const float sperationSpeed = 10;
const float alignmentRadius = 200;
const float cohesionRadius = 400;
const float cohesionSpeed = 10;
const float noiseSpeed = 0;


class Boid : public Drawable
{
private:
    /* data */
    RectangleShape shape;
    Vector2f speed;
    Vector2f newSpeed;
public:
    Boid(/* args */);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Vector2f getPosition();
    Vector2f getSpeed();
    void update(float time);
    void apply(vector<Boid> boids);
    ~Boid();
};

Boid::Boid(/* args */){
    shape = RectangleShape();
    shape.setOrigin({width/2, height/2});
    shape.setSize({width, height});
    shape.setTexture(&huier);
    shape.setPosition({positionGenerator(engine), positionGenerator(engine)});

    speed = {speedGenerator(engine), speedGenerator(engine)};
}

void Boid::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(shape, states);
}

Vector2f Boid::getPosition(){
    return shape.getPosition();
}

Vector2f Boid::getSpeed(){
    return speed;
}

void Boid::update(float time){
    if (!isnan(newSpeed.x) && ! isnan(newSpeed.y))
        speed = newSpeed;
    Vector2f position = getPosition();
    position += speed.normalized()*boidSpeed*time;
    shape.setPosition(position);
    shape.setRotation(-speed.angleTo({0, -1}));
}

void Boid::apply(vector<Boid> boids){
    // TODO three rules
    newSpeed = Vector2f();
    Vector2f position = getPosition();

    // apply speration rule
    unsigned sperationNum = 0;
    Vector2f sperationCenter;
    for (auto& i : boids){
        if ((position - i.getPosition()).length() < seprationRadius){
            sperationCenter += i.getPosition();
            sperationNum++;
        }
    }
    sperationCenter.x /= sperationNum;
    sperationCenter.y /= sperationNum;
    if (sperationNum != 0)
        newSpeed += (position - sperationCenter).normalized()*sperationSpeed;

    // apply cohesion rule
    unsigned cohesiontNum = 0;
    Vector2f cohesionCenter;
    for (auto& i : boids){
        if ((position - i.getPosition()).length() < cohesionRadius){
            cohesionCenter += i.getPosition();
            cohesiontNum++;
        }
    }
    cohesionCenter.x /= cohesiontNum;
    cohesionCenter.y /= cohesiontNum;
    if (cohesiontNum != 0)
        newSpeed += (cohesionCenter - position).normalized()*cohesionSpeed;

    // apply alignment rule
    unsigned alignmentNum = 0;
    Vector2f alignmentSpeed;
    for (auto& i : boids){
        if ((position - i.getPosition()).length() < alignmentRadius){
            alignmentSpeed += i.getSpeed();
            alignmentNum++;
        }
    }
    alignmentSpeed.x /= alignmentNum;
    alignmentSpeed.y /= alignmentNum;
    if (alignmentNum != 0)
        newSpeed += alignmentSpeed;

    // apply noise speed
    Vector2f noiseSpeedV({noiseGenerator(engine), noiseGenerator(engine)});
    newSpeed += noiseSpeedV*noiseSpeed;
}

Boid::~Boid(){

}

int main()
{
    engine.seed(time(0));

    // create the window
    sf::RenderWindow window(sf::VideoMode({winWidth, winHeight}), "boids");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);
    View view({0, 0}, {winWidth, winHeight});
    bool isPaused = false;

    vector<Boid> boids(100);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()){
                window.close();
            }else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                    window.close();
                }
                switch (keyPressed->code){
                case Keyboard::Key::W:
                    view.move({0, -camSpeed});
                    break;
                case Keyboard::Key::S:
                    view.move({0, camSpeed});
                    break;
                case Keyboard::Key::A:
                    view.move({-camSpeed, 0});
                    break;
                case Keyboard::Key::D:
                    view.move({camSpeed, 0});
                    break;
                case Keyboard::Key::Hyphen:
                    view.zoom(1.5f);
                    break;
                case Keyboard::Key::Equal:
                    view.zoom(0.8f);
                    break;
                case Keyboard::Key::P:
                    isPaused = !isPaused;
                    break;
                default:
                    break;
                }
            }else if(const auto* resized = event->getIf<sf::Event::Resized>()){
                view.setSize(Vector2f(resized->size.x, resized->size.y));
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        if (!isPaused){
            // boids algo
            for (auto& i: boids){
                i.apply(boids);
            }

            // update boids' postion
            for (auto& i: boids){
                i.update(deltaTime);
            }
        }

        // draw everything here...
        // window.draw(...);
        window.setView(view);
        
        for (auto& i : boids){
            window.draw(i);
        }

        // end the current frame
        window.display();
    }
}