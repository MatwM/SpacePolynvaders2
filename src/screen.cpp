#include "screen.h"

void loadingScreen(RenderWindow& window) {
    Font font;
    font.loadFromFile("resources/font/simply_sans/SimplySans-Bold.ttf");
    Texture back;
    back.loadFromFile("resources/fond_ecran/fond19.png");
    Sprite background(back);
    background.setScale(window.getSize().x / 700.0f, window.getSize().y / 350.0f);

    RectangleShape helpScreen(Vector2f(window.getSize().x, window.getSize().y));
    helpScreen.setFillColor(Color(0, 0, 0, 200));
    // Ajoutez un gros titre
    Text title("Space Polynvaders", font, 128);
    title.setFillColor(Color::White);
    title.setStyle(Text::Bold);
    title.setPosition(window.getSize().x / 2 - title.getLocalBounds().width / 2,
                       window.getSize().y / 2 - title.getLocalBounds().height * 2);

    // Chargement
    Text loadingText("Loading...", font, 48);
    loadingText.setFillColor(Color::White);
    loadingText.setPosition(window.getSize().x / 2 - loadingText.getLocalBounds().width / 2,
                             window.getSize().y / 2 - loadingText.getLocalBounds().height*2 / 2 + title.getLocalBounds().height);

    window.clear(Color::Black);
    window.draw(background);
    window.draw(helpScreen);
    window.draw(title);
    window.draw(loadingText);
    window.display();
}

void Intro(RenderWindow& window) {
    Font font;
    if (!font.loadFromFile("resources/font/simply_sans/SimplySans-Bold.ttf")) {
        // Gestion d'erreur si la police ne peut pas être chargée
        std::cerr << "Erreur lors du chargement de la police." << std::endl;
        return;
    }

    Texture back;
    if (!back.loadFromFile("resources/fond_ecran/fond19.png")) {
        // Gestion d'erreur si la texture ne peut pas être chargée
        std::cerr << "Erreur lors du chargement de la texture de fond." << std::endl;
        return;
    }
    Texture vaisseau_t;
    if (!vaisseau_t.loadFromFile("resources/joueur/fusée2.png")){
        std::cerr << "Erreur lors du chargement de la texture de fond." << std::endl;
        return;
    }
    Texture boss_t;
    if (!boss_t.loadFromFile("resources/mobs/boss1.png")){
        std::cerr << "Erreur lors du chargement de la texture de fond." << std::endl;
        return;
    }
    Sprite background(back), vaisseau(vaisseau_t), boss(boss_t);
    background.setScale(window.getSize().x / 700.0f, window.getSize().y / 350.0f);
    vaisseau.setScale(5,5);
    vaisseau.setPosition(window.getSize().x / 2 - vaisseau.getLocalBounds().width*5 / 2,
    window.getSize().y  - vaisseau.getLocalBounds().height*5);
    boss.setScale(5,5);

    RectangleShape helpScreen(Vector2f(window.getSize().x, window.getSize().y));
    helpScreen.setFillColor(Color(0, 0, 0, 200));

    Text text1("Bienvenue sur Space Polynvaders !", font, 100);
    text1.setFillColor(Color::White);
    text1.setPosition(window.getSize().x / 2 - text1.getLocalBounds().width / 2,
                       window.getSize().y / 2 - text1.getLocalBounds().height / 2);
    Text text1bis("(Appuyez sur une touche pour commencer)", font, 30);
    text1bis.setFillColor(Color::White);
    text1bis.setStyle(Text::Italic);
    text1bis.setPosition(window.getSize().x / 2 - text1bis.getLocalBounds().width / 2,
    window.getSize().y / 2 - text1bis.getLocalBounds().height / 2 + text1.getLocalBounds().height);

    Text text2("Polytech est menace par d'etranges creatures...", font, 80);
    text2.setFillColor(Color::White);
    text2.setPosition(window.getSize().x / 2 - text2.getLocalBounds().width / 2,
                       window.getSize().y / 2 - text2.getLocalBounds().height / 2);

    Text text3("Montez a bord de votre vaisseau, et detruisez-les !", font, 80);
    text3.setFillColor(Color::White);
    text3.setPosition(window.getSize().x / 2 - text3.getLocalBounds().width / 2,
                       window.getSize().y / 2 - text3.getLocalBounds().height / 2);

    window.clear(Color::Black);

    window.draw(background);
    window.draw(text1);
    window.draw(text1bis);
    window.display();
    Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed || event.type == Event::MouseButtonPressed || event.type == Event::Closed) {
                if (Keyboard::isKeyPressed(Keyboard::Q) || event.type == Event::Closed){
                    window.close();
                }
                else {
                    boss.setPosition(-boss.getGlobalBounds().width,window.getSize().y/2-boss.getGlobalBounds().height/2);
                    while (boss.getPosition().x < window.getSize().x){
                        boss.move(2,0);
                        window.clear(Color::Black);
                        window.draw(background);
                        window.draw(boss);
                        window.display();
                        sf::sleep(milliseconds(1000/FRAME_RATE));
                    }
                    // L'événement clé enfoncée, clic de souris ou fermeture de la fenêtre fait avancer l'intro
                    window.clear(Color::Black);
                    window.draw(background);
                    window.draw(text2);
                    window.display();
                    sf::sleep(seconds(2)); // Pause pour afficher le texte
                    window.clear(Color::Black);
                    window.draw(background);
                    window.draw(text3);
                    window.draw(vaisseau);
                    window.display();
                    sf::sleep(seconds(2)); // Pause pour afficher le texte
                    return; // Sortie de la fonction après l'intro
                }
            }
        }
    }
}