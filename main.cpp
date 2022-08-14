#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Windows.h>
#include <cmath>
#include <vector>

using namespace sf;

#define PI 3.14159265

int main()
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_HIDE );
    RenderWindow window(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "SFML Project", Style::Fullscreen);
    ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
    Clock clock;

    Texture text;
    text.loadFromFile("character2.png");
    text.setSmooth(true);

    CircleShape circle1(50);
    circle1.setTexture(&text);
    circle1.setOrigin(50, 50);
    circle1.setPosition(VideoMode::getDesktopMode().width/2, VideoMode::getDesktopMode().height/2);
    int circleposX=VideoMode::getDesktopMode().width/2, circleposY=VideoMode::getDesktopMode().height/2, circleX=0, circleY=0, i;
    double angle, projangle;
    Vector2i mouseposition;

    std::vector<CircleShape> projectiles;
    std::vector<int> xtarg;
    std::vector<int> ytarg;

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::W) {
                    circleY=1;
                }
                if (event.key.code == Keyboard::S) {
                    circleY=2;
                }
                if (event.key.code == Keyboard::A) {
                    circleX=1;
                }
                if (event.key.code == Keyboard::D) {
                    circleX=2;
                }
            }
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::W) {
                    circleY=0;
                }
                if (event.key.code == Keyboard::S) {
                    circleY=0;
                }
                if (event.key.code == Keyboard::A) {
                    circleX=0;
                }
                if (event.key.code == Keyboard::D) {
                    circleX=0;
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    CircleShape tmpcircle(10);
                    tmpcircle.setOrigin(10, 10);
                    tmpcircle.setPosition(circleposX, circleposY);
                    projectiles.push_back(tmpcircle);
                    mouseposition = Mouse::getPosition();
                    projangle = atan2(mouseposition.y-(circleposY), mouseposition.x-(circleposX));
                    xtarg.push_back(cos(projangle)*(VideoMode::getDesktopMode().width+VideoMode::getDesktopMode().height)*2);
                    ytarg.push_back(sin(projangle)*(VideoMode::getDesktopMode().width+VideoMode::getDesktopMode().height)*2);
                }
            }
        }

        if (clock.getElapsedTime().asSeconds()>0.001f) {
            if (circleY==1 && circleposY!=50) {
                circleposY--;
            }
            if (circleY==2 && circleposY!=VideoMode::getDesktopMode().height-50) {
                circleposY++;
            }
            if (circleX==1 && circleposX!=50) {
                circleposX--;
            }
            if (circleX==2 && circleposX!=VideoMode::getDesktopMode().width-50) {
                circleposX++;
            }
            mouseposition = Mouse::getPosition();
            angle = atan2(mouseposition.y-(circleposY), mouseposition.x-(circleposX)) * 180 / PI;
            circle1.setRotation(angle);
            circle1.setPosition(circleposX, circleposY);
            for (i=0;i<projectiles.size();i++) {
                if (projectiles[i].getPosition().x>5 && projectiles[i].getPosition().y>5 && projectiles[i].getPosition().x<VideoMode::getDesktopMode().width-5 && projectiles[i].getPosition().y<VideoMode::getDesktopMode().height-5) {
                    projectiles[i].setPosition(projectiles[i].getPosition().x+xtarg[i]/1000, projectiles[i].getPosition().y+ytarg[i]/1000);
                } else {
                    projectiles.erase(projectiles.begin()+i);
                    xtarg.erase(xtarg.begin()+i);
                    ytarg.erase(ytarg.begin()+i);
                }
            }
            clock.restart();
        }
        window.clear(Color(6, 92, 0));
        window.draw(circle1);
        for (i=0;i<projectiles.size();i++) {
            window.draw(projectiles[i]);
        }
        window.display();
    }

    return 0;
}