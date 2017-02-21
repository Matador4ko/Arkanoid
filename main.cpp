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
    sf::Texture background;
    sf::Font font;
    //Añadimos un background
    
    
    srand(time(NULL));
    int x= rand() % 3; //Para el color del sprite
    int mX=0; //direccion inicial en X de la bola
    int mY=2; //direccion inicial en Y para la bola
    int espacios=3; //espacio entre bloques
    int cont=0; //usado para no superar el numero de bloques por linea en el for que los coloca
    int num = 0; //para continuar a partir del ultimo bloque usado del array de blocks en el for
    bool broken=false; //para no destruir dos al mismo tiempo
    srand(time(NULL));
    int rows = rand() % 3 + 1;
    int bloques = 12 * rows; // numero de bloques (segun el numero de filas habran mas o menos bloques, esto indica que hay 12 por fila)
    std::ostringstream os; //para mostrar la frase de bloques restantes
    int vidas = rows;
    std::ostringstream osl; //para mostrar la frase de vidas restantes
    bool endg=false; //para poder saber cuando hemos llegado a 0 vida, lo volveremos tre y al final mostraremos un texto de finalizacion
    std::ostringstream ose; //mostrar la frase de final del juego
    int ballSpeed; //para bajar la velocidad de la bola cuando se perda una vida
    bool wing=false; //para saber cuando mostrar el texto de victoria al llegar a bloques 0
    std::ostringstream osw; //mostrar la frase de ganar del juego
    
    if (!font.loadFromFile("resources/sansation.ttf")){
        std::cerr << "Error cargando la fuente sansation.ttf";
        exit(0);
    }
    
    ose << "Has perdido";
    sf::Text endgame(ose.str(),font);
    endgame.setString(ose.str());
    endgame.setPosition(260,200);
    endgame.setCharacterSize(22);
    endgame.setFillColor(sf::Color::Red);
    endgame.setStyle(sf::Text::Bold);
    
    osw << "Has ganado";
    sf::Text wingame(osw.str(),font);
    wingame.setString(osw.str());
    wingame.setPosition(260,200);
    wingame.setCharacterSize(22);
    wingame.setFillColor(sf::Color::Red);
    wingame.setStyle(sf::Text::Bold);
    
    osl << "|        Vidas restantes: "<<vidas;
    sf::Text lifes(osl.str(),font);
    lifes.setString(osl.str());
    lifes.setPosition(350,1);
    lifes.setCharacterSize(22);
    lifes.setFillColor(sf::Color::Green);
    lifes.setStyle(sf::Text::Bold);
    
    os << "Bloques por destruir: "<<bloques;
    sf::Text text(os.str(),font);
    text.setString(os.str());
    text.setPosition(50,1);
    text.setCharacterSize(22);
    text.setFillColor(sf::Color::Green);
    text.setStyle(sf::Text::Bold);
    
    //Revisar y entender
    sf::Rect<float> rightWall = sf::Rect<float> (639,0,1,480);
    sf::Rect<float> leftWall = sf::Rect<float> (0,0,1,480);
    sf::Rect<float> topWall = sf::Rect<float> (0,0,640,1);
    sf::Rect<float> bottomWall = sf::Rect<float> (0,479,640,1);
    
    
    if (!tex.loadFromFile("resources/textura_arkanoid.png")) {
        std::cerr << "Error cargando la imagen textura_arkanoid.png";
        exit(0);
    }
    if (!background.loadFromFile("resources/background.png")) {
        std::cerr << "Error cargando la imagen background.png";
        exit(0);
    }
    
    sf::Sprite s_background(background);
    
    bar space=bar(90,15,6.0f);
    space.loadSprite(tex,5,5);
    space.setPosition(275,450);
    
    
    box ball=box(15,15,1.2f);
    ball.loadSprite(tex, 155,5);
    ball.setPosition(315,120);
    block bloque = block(50,15);
    if(x == 0){
       bloque.loadSprite(tex,100,5); 
    } else if(x == 1){
       bloque.loadSprite(tex,100,24); 
    }else if(x == 2){
       bloque.loadSprite(tex,100,43); 
    }
    vector<block> blocks(bloques,bloque);
    
    for(int y=0; y<rows ; y++){
        espacios = 3;
        cont = 0;
        for(int i=0; i<blocks.size(); i++){
            if(cont < 12){
                blocks[num].setPosition((50*i)+espacios,30+30*y);
                espacios=espacios+3;
                cont++;
                num++;
            }
        }
    }
    
    window.setFramerateLimit(120); //para limitar los fps y no gastar recursos de mas
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
        
        //colisiones de la bola con la barra
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
        
        //colision de la bola con las paredes
        if (ball.collision(topWall)) mY = mY*-1;
        if (ball.collision(leftWall)) mX = mX*-1;
        if (ball.collision(rightWall)) mX = mX*-1;
        if (ball.collision(bottomWall)) {
            if(vidas > 0){
                vidas--; 
                mX = 0;
                osl.str(std::string());
                osl << "|        Vidas restantes: "<<vidas;
                lifes.setString(osl.str());
                if(vidas >= 1){
                    space.setPosition(275,450);
                    mY = 2;  
                    ball.setPosition(315,120);
                    int ballSpeed = ball.getS() - 0.5f;
                    if(ballSpeed < 1.2f){
                        ball.setSpeed(1.2f);
                    }else{
                        ball.setSpeed(ballSpeed);
                    }
                }else{
                    endg=true;
                    mY=0;
                }
            }
        }
        
        //mostrar los textos
        window.clear();
        window.draw(s_background);
        window.draw(lifes);
        window.draw(text);
        window.draw(space.getSprite());
        window.draw(ball.getSprite());
        
        //mover la bola
        ball.move(mX,mY);
        
        //las colisiones con los bloques de arriba
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
                    ball.setSpeed(ball.getS()+0.1f);
                    if(ball.getS() > 3){
                        space.setSpeed(space.getS()+0.1f);
                    }
                    if(bloques == 0){
                        wing = true;
                        ball.setPosition(315,120);
                        mY=0;
                        mX=0;
                    }
                }
            }
        }
        
        if(endg == true){
            window.draw(endgame);
        }
        if(wing == true){
            window.draw(wingame);
        }
        
        window.display();
    }

    return 0;
}