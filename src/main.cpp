#include "main.h"
#include <iostream>

// Initialisation de la variable statique windowSize
Vector2u GameConfig::windowSize;

int main() {
        // Obtenir la résolution de l'écran
    VideoMode desktopMode = VideoMode::getDesktopMode();
        // Créer une fenêtre SFML sans bordure et en mode plein écran
    RenderWindow window(desktopMode, "Space Polynvaders", Style::Fullscreen | Style::None);
        // Initialiser la variable statique windowSize avec la résolution de l'écran
    GameConfig::windowSize = Vector2u(desktopMode.width, desktopMode.height);
        // Masquer le curseur de la souris
    window.setMouseCursorVisible(false);

             /***********************************************************
             *                                                          *
-----------------------------         Chargement       -------------------------------- 
             *                                                          *
             ***********************************************************/ 
        // Ecran de chargement
    loadingScreen(window);

                /*******************************************
                *              Loading images              *
                *******************************************/
    Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;

    t1.loadFromFile("resources/explosion/explo2.png");
    t2.loadFromFile("resources/fond_ecran/fond19.png");
    t3.loadFromFile("resources/interface/youwin.png");
    t4.loadFromFile("resources/interface/gameover.png");
    t5.loadFromFile("resources/joueur/fusée2.png");
    t6.loadFromFile("resources/mobs/méchant1.png");
    t7.loadFromFile("resources/projectile/missile1.png");
    t8.loadFromFile("resources/mobs/boss1.png");
    t9.loadFromFile("resources/projectile/méchant3.png");
    t10.loadFromFile("resources/coeur.png");

                /*******************************************
                *              Loading Sounds              *
                *******************************************/
    SoundBuffer explo_buffer, ambiance_buffer;

    explo_buffer.loadFromFile("resources/son/explo2.wav");
    Sound explo_sound;
    explo_sound.setBuffer(explo_buffer);
    ambiance_buffer.loadFromFile("resources/son/Space1.wav");
    Sound ambiance_sound;
    ambiance_sound.setBuffer(ambiance_buffer);
    ambiance_sound.setLoop(true);
    ambiance_sound.setVolume(100);
    ambiance_sound.play();

                /*******************************************
                *              Loading Fonts               *
                *******************************************/
    Font font;
    font.loadFromFile("resources/font/simply_sans/SimplySans-Bold.ttf");

                /*******************************************
                *                Set Sprites               *
                *******************************************/
    Sprite background(t2), mechant(t6), player(t5), heart1(t10), missileB(t9),
    missile(t7), explo(t1), looser(t4), explomob(t1), win(t3), boss(t8);
    background.setScale(window.getSize().x / 700.0f, window.getSize().y / 350.0f);
    looser.setScale(3,3);
    win.setScale(6,6);
    looser.setPosition((window.getSize().x-225*3)/2,(window.getSize().y-225*3)/2);
    win.setPosition((window.getSize().x-217*6)/2,(window.getSize().y-232*6)/2);
    player.setScale(ZOOM_PLAYER,ZOOM_PLAYER);
    missile.setScale(1,2);
    boss.setTextureRect(IntRect(0, 0, boss.getGlobalBounds().width, 200));

                /*******************************************
                *                Variables                 *
                *******************************************/
    // Usuals variables
    Time pause = milliseconds(1000/FRAME_RATE);
    float timer = 0, reload_timer_B = 0, reload_timer = 0, delay = 1, delay_rld = RELOAD_TIME;
    bool player_hit = false, winner = false;
    int tempo_clignottement = 0, delay_exploP = 0, flag_L = 0, level = 1, cycle = 0,
        affiche_explomob = 0, hitmob = 0, nbkilled = 0, exploP_played= 0, boss_hit_add = 0;
    Clock clock;
    // Barre de vie
    RectangleShape FondPV(Vector2f(window.getSize().x/2+20, 20));
    FondPV.setFillColor(Color(0, 0, 0, 255));
    FondPV.setPosition(window.getSize().x/4-10,10);
    RectangleShape GreenPV(Vector2f(window.getSize().x/2, 15));
    GreenPV.setFillColor(Color(0, 255, 0, 255));
    GreenPV.setPosition(window.getSize().x/4,12.5);
    RectangleShape RedPV(Vector2f(window.getSize().x/2, 15));
    RedPV.setFillColor(Color(255, 0, 0, 255));
    RedPV.setPosition(window.getSize().x/4,12.5);
    // My classes
        // Mobs
    Mobs armee(NOMBRE_MECHANT);
    armee.setSprites(mechant);
        // Boss
    Mob boss1(0,0,BOSS_PV);
    boss1.setSprite(boss);
        // Player
    Player player1(window.getSize().x/2 - 128/2, window.getSize().y- 128*2, PLAYER_PV);
    player1.setSprite(player);
    player1.setSpritePos(window.getSize().x/2 - 128/2 , window.getSize().y- 128*2);
        // Explosion of Player
    explo.setScale(player1.getWidth()*ZOOM_PLAYER/64,player1.getHeight()*ZOOM_PLAYER/64);
        // Missiles of Player
    Missiles salveP1(NOMBRE_MISSILES);
    salveP1.setPlayer(&player1);

    Missiles missileB1(NOMBRE_MISSILES_BOSS,1);
    missileB1.setMob(&boss1);

        // Help Menu
            // Help Menu Screen
    RectangleShape helpScreen(Vector2f(window.getSize().x, window.getSize().y));
    helpScreen.setFillColor(Color(0, 0, 0, 200)); // Couleur noire semi-transparente
            // Help Menu Text
    Text helpText("Arrows - Move\n R - Restart\n Q - Quit the game \n Escape - Fermer l'aide", font);
    helpText.setCharacterSize(30);
    helpText.setFillColor(Color::White);
    helpText.setPosition((window.getSize().x - helpText.getGlobalBounds().width) / 2.f, (window.getSize().y - helpText.getGlobalBounds().height) / 2.f);
    Text helptitle("Space Polynvaders' Menu", font, 64);
    helptitle.setFillColor(Color::White);
    helptitle.setStyle(Text::Bold);
    helptitle.setPosition(window.getSize().x / 2 - helptitle.getLocalBounds().width / 2,
                       window.getSize().y / 2 - helptitle.getLocalBounds().height * 2 - helpText.getGlobalBounds().height);
    bool isMenuOpen = false;

        // To appreciate my loading screen :)
    sf::sleep(seconds(1));

                /*******************************************
                *           Starting with intro            *
                *******************************************/
    Intro(window);

            /***********************************************************
             *                                                         *
-------------------------             MAIN LOOP              ------------------------- 
             *                                                         *
            ************************************************************/
    while (window.isOpen()) {
        window.clear();
        processEvents(window, isMenuOpen); // Traitement des events
                /*******************************************
                *                   Menu                   *
                *******************************************/
        // Dans le menu
        if (isMenuOpen) {
            window.draw(background); // Background
            if (level == 1){
                for (int i = 0; i < armee.length(); i++) { // Mobs
                    if ((*armee.getMob(i)).exists()) {
                        window.draw(armee.getSprites(i));
                    }
            }
            if (level == 2 && boss1.exists()){
                window.draw(boss1.getSprite());
            }
            }
            for (int i = 0; i < NOMBRE_MISSILES; i++) { // Missiles
                if ((*salveP1.getMissile(i)).getInmap() == true) {
                    window.draw(salveP1.getSprite(i));
                }
            }
            for (int i = 0; i < NOMBRE_MISSILES_BOSS; i++){
                if ((*missileB1.getMissile(i)).getInmap() == true) {
                    window.draw(missileB1.getSprite(i));
                }                
            }
            if (player1.getPV() > 0) { // Player
                if (timer > delay) {
                window.draw(player1.getSprite());
                }
            }
            if (winner == false && flag_L == 1){ // Loose image
                window.draw(looser);
            }
            if (winner == true){ // Win image
                window.draw(win);
            }
            window.draw(helpScreen); // Affichage de l'écran d'aide
            window.draw(helptitle);
            window.draw(helpText); // Affichage du texte d'aide
        }
        // Jeu en cours
        else {

                /*******************************************
                *            Set/Reset values              *
                *******************************************/
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;
            reload_timer += time;
            reload_timer_B += time;
            player_hit = false;

                /*******************************************
                *            Restart the game              *
                *******************************************/
            if (GameOver == true){
                if (Keyboard::isKeyPressed(Keyboard::R)){
                    // Réinitialisation des variables et des états du jeu
                    GameOver = false;
                    winner = false;
                    timer = 0;
                    reload_timer = 0;
                    reload_timer_B = 0;
                    nbkilled = 0;
                    hitmob = 0;
                    tempo_clignottement = 0;
                    delay_exploP = 0;
                    flag_L = 0;
                    affiche_explomob = 0;
                    exploP_played= 0;
                    level = 1;
                    boss_hit_add = 0;

                    // Réinitialisation des objets du jeu
                    armee.reset();
                    armee.setSprites(mechant);
                    player1.reset();
                    salveP1.reset();
                    missileB1.reset(1);
                    boss1.reset(0,0,BOSS_PV);

                    // Debut de la musique d'ambiance
                    ambiance_sound.stop();
                    ambiance_sound.play();

                    Intro(window);
                }
            }

                /*******************************************
                *             Player is playing            *
                *******************************************/
            if (GameOver == false){
                // Player move
                player_move(&player1);
                // Fire
                if (reload_timer > delay_rld) {
                    salveP1.NewMissile(missile);
                    reload_timer = 0;
                }
                
                if (level == 2){
                    if (cycle == 0 && reload_timer_B > RELOAD_TIME_BOSS){
                        missileB1.NewMissile(missileB);
                        missileB1.NewMissile(missileB);
                        missileB1.NewMissile(missileB);
                        missileB1.NewMissile(missileB);
                        missileB1.NewMissile(missileB);
                        missileB1.NewMissile(missileB);
                        missileB1.NewMissile(missileB);
                        reload_timer_B = 0;
                        //cycle = 1;
                    }/*
                    if (cycle == 1 && reload_timer_B > RELOAD_TIME_BOSS * 1.1){
                        missileB1.NewMissile(missileB);
                        cycle = 2;
                    }
                    if (cycle == 2 && reload_timer_B > RELOAD_TIME_BOSS * 1.2){
                        missileB1.NewMissile(missileB);
                        reload_timer_B = 0;
                        cycle = 0;
                    }*/
                }
            }
                /*******************************************
                *        Update entities' position         *
                *******************************************/
            if (level == 1 && nbkilled < NOMBRE_MECHANT) armee.serpantinAll(); // Mobs of 1st level
            //else if (level == 2 && boss1.exists() && (reload_timer_B < RELOAD_TIME_BOSS*0.80 || reload_timer_B > RELOAD_TIME_BOSS*1.15)) 
            else if (level == 2 && boss1.exists()) boss1.serpantin1(2,1.3);
            salveP1.ForwardAll();
            missileB1.BackwardAll(2);
            missileB1.DeviationAll();
                /*******************************************
                *       Interaction Mobs x Missiles        *
                *******************************************/
            if (level == 1){ // Interaction with mobs of 1st level
                int indexS = 0;
                while(indexS < NOMBRE_MISSILES && hitmob == 0){
                    int indexA = 0; 
                    while(indexA < NOMBRE_MECHANT && hitmob == 0){
                        if((*salveP1.getMissile(indexS)).getInmap() && (*armee.getMob(indexA)).exists() && CollisionMobMissile((*armee.getMob(indexA)),(*salveP1.getMissile(indexS)))){
                            (*armee.getMob(indexA)).hit(1);
                            (*salveP1.getMissile(indexS)).DesactivMissile();
                            if ((*armee.getMob(indexA)).getPV() < 1){
                                explomob.setPosition((*armee.getMob(indexA)).getX(),(*armee.getMob(indexA)).getY());
                                affiche_explomob = 20;
                                nbkilled ++;
                                if (nbkilled == NOMBRE_MECHANT){
                                    level ++; // Go next level
                                }
                                hitmob = 1;
                                // Mob explosion sound
                                explo_sound.setVolume(30);
                                explo_sound.play();
                            }
                        }
                        indexA++;
                    }
                    indexS++;
                }
            }
            if (level == 2){
                int indexS = 0;
                while (indexS < NOMBRE_MISSILES && hitmob == 0){
                    if((*salveP1.getMissile(indexS)).getInmap() && boss1.exists() && CollisionMobMissile(boss1,(*salveP1.getMissile(indexS)))){
                        boss1.hit(1);
                        (*salveP1.getMissile(indexS)).DesactivMissile();
                        explomob.setPosition((*salveP1.getMissile(indexS)).getX()-explomob.getGlobalBounds().width/2,
                            (*salveP1.getMissile(indexS)).getY()-explomob.getGlobalBounds().width);
                        if (boss1.getPV() > 0){
                        affiche_explomob = 20;
                        hitmob = 1;
                        }
                        else {
                            delay_exploP = 200;
                        }
                    }
                    indexS ++;
                }
            }
            hitmob = 0;

                /*******************************************
                *       Interaction Mobs x Players         *
                *******************************************/
            if (level == 1){
                int index = 0;
                while(index < armee.length()&& (timer > delay)) { // Collision ?
                    if((*armee.getMob(index)).exists() && CollisionPlayerMob(player1, (*armee.getMob(index)))){
                        player_hit = true;
                        timer = 0;
                    }
                    index++;
                }
            }
            if (level == 2){
                if (boss1.exists() && CollisionPlayerMob(player1,boss1) && (timer > delay)){
                    player_hit = true;
                    timer = 0;
                }
            }
            int indexM = 0; 
            while(indexM < NOMBRE_MISSILES_BOSS && (timer > delay)){
                        if((*missileB1.getMissile(indexM)).getInmap() && boss1.exists() && CollisionPlayerMissile(player1,(*missileB1.getMissile(indexM)))){
                            player_hit = true;
                            timer = 0;
                            boss_hit_add = 1;
                            (*missileB1.getMissile(indexM)).DesactivMissile();
                        }
                        indexM ++;
            }
            if (player_hit && player1.getPV() > 0){ //&& player1.getPV()>0) { // Player get damage
                player1.hit(1+boss_hit_add);
                boss_hit_add = 0;
                if (player1.getPV() > 0){
                    tempo_clignottement = 500;
                }
                else{
                    explo.setPosition(player1.getX(),player1.getY());
                    delay_exploP = 200;
                    //Player explosion sound
                    exploP_played = 1;
                }
            }
            // Player died ?
            if (player1.getPV() <= 0) {
                GameOver = true;
                flag_L = 1;
            }
            int k = 0;
            while (k < NOMBRE_MECHANT && level == 1){ // Next level ?
                if ((*armee.getMob(k)).outscreen()){
                level ++;               
                }
                k ++;
            }

            if (level == 2 && !boss1.exists()) level ++; // Next level ?
            if (level > LEVEL_MAX){ // Pas d'autres niveaux
                GameOver = true;
                winner = true;
            }
            if (affiche_explomob == 20){
                // Mob explosion sound
                explo_sound.setVolume(30);
                explo_sound.play();
            }
            if (exploP_played > 0) {
                explo_sound.setVolume(90);
                explo_sound.play();
                exploP_played --;
            }
                /*******************************************
                *                 Display                  *
                *******************************************/
            // Background
            window.draw(background);
            // Mobs
            if (level == 1){
                for (int i = 0; i < armee.length(); i++) {
                    if ((*armee.getMob(i)).exists()) {
                        window.draw(armee.getSprites(i));
                    }
                }
            } else if (level == 2){
                    if ((boss1.exists())){
                        window.draw(boss1.getSprite());
                        GreenPV.setSize(Vector2f(window.getSize().x/2*(float(boss1.getPV())/BOSS_PV),15));
                        window.draw(FondPV);
                        window.draw(RedPV);
                        window.draw(GreenPV);
                    }
            }
            // Missiles
            for (int i = 0; i < NOMBRE_MISSILES; i++) {
                if ((*salveP1.getMissile(i)).getInmap() == true) {
                    window.draw(salveP1.getSprite(i));
                }
            }
            for (int i = 0; i < NOMBRE_MISSILES_BOSS; i++) {
                if ((*missileB1.getMissile(i)).getInmap() == true) {
                    window.draw(missileB1.getSprite(i));
                }
            }
            // Player
            if (player1.getPV() > 0) {
                if (timer > delay) {
                window.draw(player1.getSprite());
                }
                else{
                    if (tempo_clignottement%50 < 25) {
                        window.draw(player1.getSprite());
                    }
                    tempo_clignottement --;
                }
            }
            if (delay_exploP > 0){ // Big explosion
                if (boss1.getPV() < 1){
                    explo.setPosition(boss1.getX()+20,boss1.getY());
                }
                else{
                    explo.setPosition(player1.getX(),player1.getY());
                    delay_exploP --;
                    if (delay_exploP == 0) flag_L = 1;
                }
                window.draw(explo);
                delay_exploP --;
            }
            if (affiche_explomob > 0){
                if (level == 1 || ((level == 2) && boss1.getPV() > 1)) window.draw(explomob);
                affiche_explomob --;
            }
            // Life
            for (int i = 0; i < player1.getPV(); i++){
                heart1.setPosition(window.getSize().x / 2 - ((1-i)+1/2)*heart1.getLocalBounds().width,
                    window.getSize().y  - heart1.getLocalBounds().height);
                window.draw(heart1);
            }
            // Final loosing screen
            if (winner == false && flag_L == 1) window.draw(looser);
            if (winner == true) window.draw(win);
        }
        window.display();
        sf::sleep(pause);
    }
    return 0;
}

void processEvents(RenderWindow& window, bool& isMenuOpen) {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Escape) {
                isMenuOpen = !isMenuOpen; // Inverse l'état du menu
            }
            if (event.key.code == Keyboard::Q){
                window.close();
            }
        }
    }
}
