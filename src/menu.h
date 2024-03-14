#include <SFML/Graphics.hpp>

#include "config.h"

using namespace sf;

// Classe pour le menu d'aide
class HelpMenu {
private:
    RenderWindow& m_window;
    Font m_font;

public:
    HelpMenu(RenderWindow& window) : m_window(window) {
        m_font.loadFromFile("arial.ttf");
    }
    // Afficher le menu
    void show() {
        RenderWindow menuWindow(VideoMode(400, 300), "Menu d'aide", Style::Close);
        menuWindow.setFramerateLimit(60);

        while (menuWindow.isOpen()) {
            Event event;
            while (menuWindow.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    menuWindow.close();
                }
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                    menuWindow.close();
                }
            }

            menuWindow.clear(Color::White);

            // Dessinez votre menu ici (par exemple, affichez les commandes)
            Text text("Commandes :\n\nW - Avancer\nA - Aller à gauche\nS - Reculer\nD - Aller à droite\nEchap - Fermer le menu", m_font, 16);
            text.setFillColor(Color::Black);
            text.setPosition(20.f, 20.f);
            menuWindow.draw(text);

            menuWindow.display();
        }
    }
};