#include "Engine.h"
#include <chrono>
#include <stdio.h>

/*Call create on m_Window to populate the RenderWindow member variable
You can assign a custom resolution or you can call VideoMode::getDesktopMode() to get the screen resolution;*/
Engine::Engine(){
    int pixelWidth = VideoMode::getDesktopMode().width / 2;
    int pixelHeight = VideoMode::getDesktopMode().height / 2;
    VideoMode vm(pixelWidth,pixelHeight);
    m_Window.create(vm, "Particle", Style::Default);
    
}

void Engine::run(){
    Clock time_per_frame;
    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;
    while(m_Window.isOpen()){
        Time dt = time_per_frame.restart();
        float dtAsSeconds = dt.asSeconds();
        input();
        update(dtAsSeconds);
        draw();
    }
    
}
void Engine::input(){
        Event event;
        while(m_Window.pollEvent(event)){
            if(event.type == sf::Event::Closed) {m_Window.close();}
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    for(int i = 0; i < 5; i++){
                        int num_Points = rand() % (50 + 1 - 25) + 25;
                        Particle newParticle(m_Window, num_Points, {event.mouseButton.x, event.mouseButton.y});
                        m_particles.push_back(newParticle);
                    }
                }
            }
            if(Keyboard::isKeyPressed(Keyboard::Escape)){
                m_Window.close();
            }
        }
}
void Engine::update(float dtAsSeconds){
    vector<Particle>::iterator iter;
    for(iter = m_particles.begin(); iter != m_particles.end();){
        if( iter->getTTL() > 0.0){
            iter->update(dtAsSeconds);
            ++iter;
        }
        else{
            iter = m_particles.erase(iter);
        }
    }
}
void Engine::draw(){
    m_Window.clear();
    for(int i = 0; i < m_particles.size();i++){
        m_Window.draw(m_particles[i]);
    }
    m_Window.display();
}
