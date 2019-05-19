#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <complex>
#include <cmath>
#include <fstream>

using namespace sf;



void menu(RenderWindow & window) {
    std::ofstream out, out1, out2; // файл для записи
    Image aboutImage;
    aboutImage.loadFromFile("images/AboutU.jpg");

	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/game.png");
	menuTexture2.loadFromFile("images/furi.png");
	menuTexture3.loadFromFile("images/exit.png");
	menuBackground.loadFromFile("images/backgroundmenu.png");



    ///////////////// FURI ////////////////////////
    aboutTexture.loadFromImage(aboutImage);

    std::cout << "X and Y ==" << aboutTexture.getSize().x << aboutTexture.getSize().y;

    const int WW = aboutTexture.getSize().x;
    const int HH = aboutTexture.getSize().x;
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
    if (!out.is_open())
    {
        std::cout << "Error opening file data_out_Furi.txt.\n";
        exit(EXIT_FAILURE);
    }

    out2.open("data_out_begin.txt");
    if (!out.is_open())
    {
        std::cout << "Error opening file data_out_Furi.txt.\n";
        exit(EXIT_FAILURE);
    }


    for(int i = 0; i < N; i += 1) {

        if(i % 64 == WW * 4){
            out2 << std::endl;
        }
        out2 << pixels1[i];
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

        if(i % 64 == WW * 4){
            out1 << std::endl;
        }
        out1 << Y[i];
    }


    aboutTexture.update(pixels);
    aboutTexture.copyToImage().saveToFile("totoFuri.png"); // Сохранение картиночки
    /////////////////// END FURI ///////////////////////



	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
    about.scale(9,9);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menuBg.setPosition(345, 0);
 
	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));
 
		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }
 
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3)  { window.close(); isMenu = false; }
 
		}
 
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		
		window.display();
	}
	////////////////////////////////////////////////////
}



/////////////////////////// Сохранение в файл картинки
/// https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Image.php#a51537fb667f47cbe80395cfd7f9e72a4 