#include <iostream>
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "box.h"
#include "bar.h"
#include "block.h"

using namespace std;

int main()
{
    
    
    
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");

    sf::Texture tex;
    sf::Font font;
    font.loadFromFile("resources/sansation.ttf");
    
    int bloques = 12;
    std::ostringstream os;
    os << "Bloques por destruir: "<<bloques;
    sf::Text text(os.str(),font);
    text.setString(os.str());
    
    text.setPosition(200,1);
    text.setCharacterSize(22);
    text.setStyle(sf::Text::Bold);
    
//Revisar y entender
    sf::Rect<float> rightWall = sf::Rect<float> (639,0,1,480);
    sf::Rect<float> leftWall = sf::Rect<float> (0,0,1,480);
    sf::Rect<float> topWall = sf::Rect<float> (0,0,640,1);
    sf::Rect<float> bottomWall = sf::Rect<float> (0,479,640,1);
    
    if (!font.loadFromFile("resources/sansation.ttf")){
        std::cerr << "Error cargando la fuente sansation.ttf";
        exit(0);
    }
    if (!tex.loadFromFile("resources/textura_arkanoid.png")) {
        std::cerr << "Error cargando la imagen textura_arkanoid.png";
        exit(0);
    }
    
    bar space=bar(90,15,6.0f);
    space.loadSprite(tex,0,0);
    space.setPosition(275,450);
    
    int mX=0;
    int mY=2;
    
    box ball=box(15,15,2.0f);
    ball.loadSprite(tex, 140,0);
    ball.setPosition(315,120);
    
    srand(time(NULL));
    int x= rand() % 3;
    int rows = rand() % 3 + 1;
    block bloque = block(50,15);
        
    bloque.loadSprite(tex,90,0+(15*x));
    
    
    bloques = bloques * rows;
    vector<block> blocks(bloques,bloque);
    int aux=3;
    int cont=0;
    int num = 0;
    srand(time(NULL));
    for(int y=0; y<rows ; y++){
        aux = 3;
        cont = 0;
        for(int i=0; i<blocks.size(); i++){
            if(cont < 12){
                blocks[num].setPosition((50*i)+aux,30+18*y);
                aux=aux+3;
                cont++;
                num++;
            }
        }
    }
    
    window.setFramerateLimit(100);
    bool broken=false;
    //Bucle del juego
    while (window.isOpen())
    {
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            switch(event.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
            
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                    }
                break;
            }
            
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(space.getX()<549)space.move(1,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(space.getX()>1)space.move(-1,0);
        }
        
        
        int col=space.collision(ball.getHit());
        if(col == 0){
            mX=-2;
            mY=-1;
        }else if(col == 1){
            mX=-1;
            mY=-2;
        }else if(col == 2){
            mX=0;
            mY=-2;
        }else if(col == 3){
            mX=1;
            mY=-2;
        }else if(col == 4){
            mX=2;
            mY=-1;
        }
        
        
        if (ball.collision(topWall)) mY = mY*-1;
        if (ball.collision(leftWall)) mX = mX*-1;
        if (ball.collision(rightWall)) mX = mX*-1;
        if (ball.collision(bottomWall)) {mY = 0; mX = 0; }
        
        ball.move(mX,mY);
        
        window.clear();
        window.draw(space.getSprite());
        window.draw(ball.getSprite());
        broken=false;
        for(int i=0; i<blocks.size() ; i++){
            if(blocks[i].getVisible()==true){
                window.draw(blocks[i].getSprite());
                if(blocks[i].collision(ball.getHit()) && broken==false){
                    mY=mY*-1;
                    broken=true;
                    blocks[i].invisible();
                    bloques--;
                    os.str(std::string());
                    os << "Bloques por destruir: "<<bloques;
                    text.setString(os.str());
                    ball.setSpeed(ball.getS()+0.2f);
                }
            }
        }
        window.draw(text);
        window.display();
    }

    return 0;
}