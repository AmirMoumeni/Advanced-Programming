#include <iostream>
#include <SFML/Graphics.hpp>
#include "StartScreen.h"
#include "Game.h"
#include "counting.h"

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(1792,1024), "Sheep Battle");
    window.setFramerateLimit(60);

    StartScreen startScreen(window);
    if (/*startScreen.run()*/ true){ 
        startScreen.stopMusic();
        Game game(window);
        IntroScreen intro(window);
        //intro.run();
        game.run();
        
    }

    return 0;
}
