#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <complex>
#include <cmath>
#include <fstream>

using namespace sf;



void menu(RenderWindow & window) {
    std::ofstream out, out1, out2, outlast; // файл для записи
    Image aboutImage, furi2Image, hero1;
    aboutImage.loadFromFile("images/AboutU.jpg");
    furi2Image.loadFromFile("images/dadzai.jpg");
    hero1.loadFromFile("images/animal.png");

	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground, furi2Texture, menuTexture4, texturehero1;
	menuTexture1.loadFromFile("images/game.png");
	menuTexture2.loadFromFile("images/furi.png");
	menuTexture3.loadFromFile("images/exit.png");
    menuTexture4.loadFromFile("images/furi2.png");
	menuBackground.loadFromFile("images/backgroundmenu.png");



    ///////////////// FURI ////////////////////////
    aboutTexture.loadFromImage(aboutImage);
    furi2Texture.loadFromImage(furi2Image);
    texturehero1.loadFromImage(hero1);

    std::cout << "X and Y ==" << aboutTexture.getSize().x << aboutTexture.getSize().y;

    const int WW = aboutTexture.getSize().x;
    const int HH = aboutTexture.getSize().y;
    //const int N = 800*600*4;
    //int NN = 800*600*4;
    const int N = 64*64*4;
    int NN = 64*64*4;

    //1920000
    sf::Uint8 *pixels = new sf::Uint8[64*64*4];
    const sf::Uint8 *pixels1 = new sf::Uint8[64*64*4];

    pixels1 = aboutImage.getPixelsPtr();

    //std::cout << "LALALA" << aboutImage.getPixelsPtr() << "N === " << N << "NN === " << NN; 
    for(int i = 0; i < N; i++) {
        pixels[i] = pixels1[i];
    }

    // std::complex<int> G[1920000];
    // std::complex<int> Y[1920000];

    std::complex<double> G[64*64*4];
    std::complex<double> Y[64*64*4];
    //int G[64*64*4];


    for(int u=0; u<N; ++u){
        for (int n = 0; n < N; ++n)
        {
            double w = -2 * 3.1415 * u * n / N;
            std::complex<double> c(cos(w), sin(w));//= std::complex(sin(w), cos(w));
            double pixn = pixels[n];
            G[u] += ((real(c) * pixn)  / NN);
        } 
        //G[u] = G[u] / N;
    }

    //Записть в файл
    out.open("data_out.txt");
    if (!out.is_open())
    {
        std::cout << "Error opening file data_out_Furi.txt.\n";
        exit(EXIT_FAILURE);
    }

    out1.open("data_out_to_sho_bilo.txt");
    if (!out1.is_open())
    {
        std::cout << "Error opening file data_out_Furi.txt.\n";
        exit(EXIT_FAILURE);
    }

    out2.open("data_out_begin.txt");
    if (!out2.is_open())
    {
        std::cout << "Error opening file data_out_Furi.txt.\n";
        exit(EXIT_FAILURE);
    }


    for(int i = 0; i < N; i += 1) {

        if(i % 64 == WW * 4){
            out2 << std::endl;
        }
        out2 << " " << (int)pixels[i];
    }

    

    for(int i = 0; i < N; i += 1) {
        // Заполняем массив для текстурки
        pixels[i] = real(G[i]);
        // Записываем значения в файл
        if(i % 64 == WW * 4){
            out << std::endl;
        }
        out << G[i];
    }

    for(int n=0; n<N; ++n){
        for (int u = 0; u < N; ++u)
        {
            double w = 2 * 3.1415 * u * n / N;
            std::complex<double> c(cos(w), sin(w));//= std::complex(sin(w), cos(w));
            Y[n] += (G[u] * c);
        } 
    }

    for(int i = 0; i < N; i += 1) {
       pixels[i] = real(Y[i]);
        if(i % 64 == WW * 4){
            out1 << std::endl;
        }
        out1 << Y[i];
    }


    aboutTexture.update(pixels);
    aboutTexture.copyToImage().saveToFile("totoFuri.png"); // Сохранение картиночки
    /////////////////// END FURI ///////////////////////








    /////////////////////FURI 2 AAAAAAAAAA//////////////////////
    furi2Texture.loadFromImage(furi2Image);
    
    sf::Uint8 *pixelss = new sf::Uint8[64*64*4];
    const sf::Uint8 *pixelss1 = new sf::Uint8[64*64*4];
    sf::Uint8 pixelsss[64][64*4];

    std::complex<double> GG[64][64*4];
    std::complex<double> YY[64][64*4];
    std::complex<double> YYY[64*64*4];

    pixelss1 = furi2Image.getPixelsPtr();

    for(int i = 0; i < N; i++) {
        pixelss[i] = pixelss1[i];

    }


    int k = 0;
    for(int i = 0; i < 64; ++i){
        for(int j = 0; j < 64*4; ++j){

            pixelsss[i][j] = pixelss[k++];

        }
    }
    k = 0;

    for(int i = 0; i < 64; ++i){
        for(int j = 0; j < 64*4; ++j){

            double w = -2 * 3.1415 * i * j / N;
            std::complex<double> c(cos(w), sin(w));//= std::complex(sin(w), cos(w));
            double pixn = pixelsss[i][j];
            GG[i][j] += ((c * pixn)  / (double)NN);
            //std::cout << " " << (GG[i][j]);
        }
    }



    //Сохранение промежуточного варианта
    for(int i = 0; i < 64; ++i){
        for(int j = 0; j < 64*4; ++j){

            YYY[k++] = GG[i][j];

        }
    }

    k=0;

    for(int i = 0; i < N; i += 1) {
        pixelss[i] = real(YYY[i]);
    }


    furi2Texture.update(pixelss);
    furi2Texture.copyToImage().saveToFile("FurieshkaPromej.png");
    //-------------------------------------------------

    for(int j = 0; j < 64*4; ++j){
        for(int i = 0; i < 64; ++i){

            double w = -2 * 3.1415 * i * j / N;
            std::complex<double> c(cos(w), sin(w));//= std::complex(sin(w), cos(w));
            double pixn = real(GG[i][j]);
            YY[i][j] += ((c * pixn)  / (double)NN);

        }
    }

    for(int i = 0; i < 64; ++i){
        for(int j = 0; j < 64*4; ++j){

            YYY[k++] = YY[i][j];

        }
    }


    // for(int u=0; u<N; ++u){
    //     for (int n = u/(4*WW)*4*WW; n < (u/(4*WW)*4*WW)+4*WW; ++n)
    //     {
    //         double w = -2 * 3.1415 * u * n / N;
    //         std::complex<double> c(cos(w), sin(w));//= std::complex(sin(w), cos(w));
    //         double pixn = pixels[n];
    //         GG[u] += ((c * pixn)  / (double)NN);
    //     } 
    //     //G[u] = G[u] / N;
    // }

    // for(int u=0; u<N; ++u){
    //     for (int n = 0; n < HH * 4; ++n)
    //     {
    //         double w = -2 * 3.1415 * u * n / N;
    //         std::complex<double> c(cos(w), sin(w));//= std::complex(sin(w), cos(w));
    //         //double pixn = pixels[n];
    //         //Y[u] += ((c * G[n * (u/(WW*4)+WW*4)])  / (double)NN);
    //         YY[u] += ((c * G[(n*WW*4)+u%(WW*4)])  / (double)NN);
    //     } 
    //     //G[u] = G[u] / N;
    // }

    outlast.open("data_outlast.txt");
    if (!outlast.is_open())
    {
        std::cout << "Error opening file last_Furi_dvum.txt.\n";
        exit(EXIT_FAILURE);
    }


    for(int i = 0; i < N; i += 1) {
        pixelss[i] = real(YYY[i]);

        if(i % 64 == WW * 4){
            outlast << std::endl;
        }
        outlast << (int)pixelss[i];
    }

    furi2Texture.update(pixelss);
    furi2Texture.copyToImage().saveToFile("Furieshka2.png");








    /////////////////////END FURI 2 AAAAAAAAAA//////////////////////



    //////////////// FILTERS ////////////////////////

    //1920000
    sf::Uint8 *pixelsh = new sf::Uint8[150*150*4];
    const sf::Uint8 *pixelsh1 = new sf::Uint8[150*150*4];


    ////////////// 1 Негатив /////////////

    pixelsh1 = hero1.getPixelsPtr();

    for(int i = 0; i < 150*150*4; i++) {
        pixelsh[i] = pixelsh1[i];
    }

    for(int i = 0; i < 150*150*4; i += 1) {

        pixelsh[i] = 255 - pixelsh[i];
        i++;
        pixelsh[i] = 255 - pixelsh[i]; 
        i++;
        pixelsh[i] = 255 - pixelsh[i];
        i++;
    }


    texturehero1.update(pixelsh);
    texturehero1.copyToImage().saveToFile("images/animal1.png"); // Сохранение картиночки



    /////////// 2 ЧБ ///////////////

    pixelsh1 = hero1.getPixelsPtr();

    for(int i = 0; i < 150*150*4; i++) {
        pixelsh[i] = pixelsh1[i];
    }

    for(int i = 0; i < 150*150*4; i += 1) {

        int s = (pixelsh[i] + pixelsh[i+1] + pixelsh[i+2])/3;
        pixelsh[i] = s;
        i++;
        pixelsh[i] = s; 
        i++;
        pixelsh[i] = s;
        i++;
    }


    texturehero1.update(pixelsh);
    texturehero1.copyToImage().saveToFile("images/animal2.png"); // Сохранение картиночки

    ////////// 3 Глупый фильтр ///////////////

    pixelsh1 = hero1.getPixelsPtr();

    for(int i = 0; i < 150*150*4; i++) {
        pixelsh[i] = pixelsh1[i];
    }

    for(int i = 0; i < 150*150*4; i += 1) {

        pixelsh[i] += 50;
        i++;
        pixelsh[i] = 10; 
        i++;
        pixelsh[i] = 10;
        i++;
    }


    texturehero1.update(pixelsh);
    texturehero1.copyToImage().saveToFile("images/animal3.png"); // Сохранение картиночки



    /////////////// FILTERS END ////////////////////

    // Texture animalT0, animalT1, animalT2; //animalT3;

    // animalT0.loadFromFile("images/animal1.png");
	// animalT1.loadFromFile("images/animal2.png");
	// animalT2.loadFromFile("images/animal3.png");
    // //animalT3.loadFromFile("images/animal2.png");
    // texturehero1.loadFromImage(hero1);


	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground), menu4(menuTexture4), about2furi(furi2Texture);
    //Sprite animal0(texturehero1), animal1(animalT0), animal2(animalT1), animal3(animalT2);
    about.scale(9,9);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
    menu3.setPosition(100, 210);
    menu4.setPosition(100, 150);
    menuBg.setPosition(345, 0);
 
	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
        menu4.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));
 
		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(100, 210, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }
        if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu4.setColor(Color::Blue); menuNum = 4; }
 
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
            if (menuNum == 4) { window.draw(about2furi); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3)  { window.close(); isMenu = false; }
 
		}
 
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
        window.draw(menu4);
		window.draw(menu3);

		window.display();
	}
	////////////////////////////////////////////////////
}



/////////////////////////// Сохранение в файл картинки
/// https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Image.php#a51537fb667f47cbe80395cfd7f9e72a4 