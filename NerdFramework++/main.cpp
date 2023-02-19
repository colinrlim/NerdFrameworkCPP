#include <iostream>
#include <SDL.h>
#undef main
#include "CaesarCipher.h"
#include "VigenereCipher.h"
#include "Interface.h"
#include "String.h"
#include "BinaryGrid2.h"
#include "ImageLabel.h"
#include "Timer.h"
#include "TileBatcher.h"

//#include "ignore/Detention/game.h"
#include "Math.h"
#include "PaletteImageStamper.h"
#include "ImageStamper.h"
#include "ParticleBatcher.h"
#include "MathParser.h"

int main() {
    std::cout << (double)MathParser::toExpressionTree("((0.2*3^0.5)^2+(3^2^3/2^(1/2)))")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("2+4/5*(5-3)^5^4")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("3+4*2/(1-5)^2^3")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("e")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("pi")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("e0")->getValue() << std::endl;
    std::cout << std::endl << "yuh" << std::endl;
    std::cout << (double)MathParser::toExpressionTree("sinpi")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("sin(pi)")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("cos(pi)")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("sin(0)")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("cos(0)")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("sinpi/2")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("cospi/2")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("sin(pi/4)")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("cos(pi/4)")->getValue() << std::endl;
    std::cout << "nah" << std::endl;
    std::cout << (double)MathParser::toExpressionTree("max(3,2)")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("min(3,2)")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("sin(min(2,3)/3*pi)")->getValue() << std::endl;

    std::cout << (double)MathParser::toExpressionTree("(2^10+162)%256")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("mod(2^10+162,256)")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("max(3+2,1+2)")->getValue() << std::endl;
    std::cout << (double)MathParser::toExpressionTree("abs(32-1904)")->getValue() << std::endl;
    //MathParser::toExpressionTree("A+B/C*(D-A)^F^H", 15);
    //MathParser::toExpressionTree("A*(B+C*D)+E", 11);
    
    /*launch1();
	PaletteImage ghost_right(16, 16, std::vector<uint8_t>{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
		0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,1,1,1,3,3,1,1,1,1,3,3,1,0,0,
		0,0,1,1,3,3,3,3,1,1,3,3,3,3,0,0,
		0,0,1,1,3,3,2,2,1,1,3,3,2,2,0,0,
		0,1,1,1,3,3,2,2,1,1,3,3,2,2,1,0,
		0,1,1,1,1,3,3,1,1,1,1,3,3,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	});

    Color4 black(0, 0, 0, 0);
    Color4 red(252, 0, 0);
    Color4 brown(216, 144, 85);
    Color4 pink(252, 180, 255);
    Color4 cyan(0, 252, 255);
    Color4 blue(72, 180, 255);
    Color4 orange(252, 180, 85);
    Color4 yellow(252, 252, 0);
    Color4 indigo(36, 36, 255);
    Color4 green(0, 252, 0);
    Color4 teal(72, 180, 170);
    Color4 salmon(252, 180, 170);
    Color4 white(252, 252, 255);
    std::vector<Palette<Color4>> palettes{
        { { Color4::none, black, black, black } },		// 0
        { { Color4::none, indigo, black, salmon } },	// 1 frightened1
        { { Color4::none, white, brown, red } },		// 2 frightened2
        { { Color4::none, yellow, pink, cyan } },		// 3
        { { Color4::none, black, black, black } },		// 4
        { { Color4::none, red, indigo, white } },		// 5 blinky
        { { Color4::none, cyan, indigo, white } },		// 6 inky
        { { Color4::none, yellow, red, indigo } },		// 7
        { { Color4::none, salmon, indigo, green } },	// 8
        { { Color4::none, brown, green, orange } },		// 9
        { { Color4::none, black, indigo, white } },		// 10 eyes
        { { Color4::none, red, salmon, white } },		// 11
        { { Color4::none, salmon, black, white } },		// 12
        { { Color4::none, red, white, green } },		// 13
        { { Color4::none, white, blue, yellow } },		// 14
        { { Color4::none, indigo, black, salmon } },	// 15
        { { Color4::none, salmon, indigo, white } },	// 16
        { { Color4::none, pink, indigo, white } },		// 17 pinky
        { { Color4::none, orange, indigo, white } },	// 18 clyde
        { { Color4::none, white, green, red } },		// 19
        { { Color4::none, white, green, teal } },		// 20
        { { Color4::none, indigo, black, salmon } },	// 21
        { { Color4::none, white, black, salmon } },		// 22
    };
    //launch();
	std::cout << CaesarCipher::encrypt("If he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out.", 7) << std::endl;
	std::cout << VigenereCipher::encrypt("If he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out.", "cryptii") << std::endl;

    BinaryGrid2 grid(10, 10, false);
    grid.setTile(2, 5, true);
    std::cout << grid;

    String test = std::string("Once upon a time, this was a string. Now it is a String. The End.");

    PaletteImageStamper* paletteImageStamper = nullptr;
    ImageStamper* imageStamper = nullptr;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        Frame frame({ 0, 100, 0, 100 }, { 0, 200, 0, 100 });
        frame.setColor(Color3::black);
        frame.setBorderColor(Color3::red);
        frame.borderWidth = 2;
        Frame frame2({ 0.5, 10, 0.5, 10 }, { 0.5, -20, 0.5, -20 });
        frame2.setColor(Color3::lightRed);
        frame2.setBorderColor(Color3::green);
        frame2.borderWidth = 2;
        //frame.addChild(&frame2);
    
        uint32_t r = Color4::red.toInteger();
        uint32_t g = Color4::green.toInteger();
        uint32_t b = Color4::blue.toInteger();
        uint32_t y = Color4::yellow.toInteger();
        uint32_t m = Color4::magenta.toInteger();
        uint32_t c = Color4::cyan.toInteger();
        Image4 image(10, 10, std::vector<uint32_t>{
            0,0,0,0,0,0,0,0,0,0,
            0,r,r,r,r,r,r,r,r,0,
            0,g,g,g,g,g,g,g,g,0,
            0,b,b,b,b,b,b,b,b,0,
            0,r,g,r,g,r,g,r,g,0,
            0,b,r,b,r,b,r,b,r,0,
            0,g,g,r,g,g,r,g,g,0,
            0,y,y,y,y,y,y,y,y,0,
            0,m,m,m,m,m,m,m,m,0,
            0,c,c,c,c,c,c,c,c,0,
        });
        //ImageLabel imageLabel(std::move(image), { 0.5, 0.5 }, { 0, 100, 0, 100 });

        Image4 image2(1, 1, Color4::lightGreen);
        Image4 image3(1, 1, Color4::lightBlue);
        Image4 image4(1, 1, Color4::lightRed);

        TileBatcher* batcher;
        Grid2<uint8_t> grid(10, 10, {
            0,0,0,0,0,0,0,0,0,0,
            0,1,1,1,1,1,1,1,1,0,
            0,1,0,0,0,0,0,0,1,0,
            0,1,0,2,0,0,2,0,1,0,
            0,1,0,2,0,0,2,0,1,0,
            0,1,0,2,0,0,2,0,1,0,
            0,1,0,2,0,0,2,0,1,0,
            0,1,0,2,2,2,2,0,1,0,
            0,1,0,0,0,0,0,0,1,0,
            0,0,0,0,0,0,0,0,0,0,
        });
        std::map<uint8_t, Image4> map;
        map[0] = image2;
        map[1] = image3;
        map[2] = image4;
        std::cout << (short)grid.get(3, 3) << std::endl;

        Kinematics<Vector2> position;
        Kinematics<double> size(3.0, 0.1, 50.0);
        ParticleBatcher* particleBatcher;

        Interface interface([&](Interface& interface, SDL_Renderer* renderer)-> void{
            interface.frame.setColor(Color3::blue);
            interface.frame.setBorderColor(Color3::blue);

            interface.frame.addChild(&frame);
            //interface.frame.addChild(&imageLabel);

            batcher = new TileBatcher(renderer);
            batcher->setGrid(std::move(grid));
            batcher->setTileTypes(std::move(map));

            paletteImageStamper = new PaletteImageStamper(renderer, std::move(ghost_right));
            paletteImageStamper->defaultPalette = &palettes[5];
            Image4 test(1, 1, Color4::red);
            imageStamper = new ImageStamper(renderer, std::move(test));
            particleBatcher = new ParticleBatcher(paletteImageStamper, NumericRange<Kinematics<Vector2>>(
                Kinematics<Vector2>(Vector2(100, 0), Vector2(-100, -10), Vector2(0, 0)),
                Kinematics<Vector2>(Vector2(100, 0), Vector2(100, 10), Vector2(0, 0))
            ), NumericRange<Kinematics<double>>(
                Kinematics<double>(0, -10, -1),
                Kinematics<double>(0, 10, 1)
            ), size);
            particleBatcher->particleRate = 0.001;
            particleBatcher->position = Vector2(200, 200);
            particleBatcher->rotationOrigin = Vector2i(5, 5);
        });
        interface.onDraw = [&](Interface& interface, Image4& screen, const Rect2<double>& bounds) -> void {
            batcher->draw(screen, Rect2<double>{200.0, 200.0, 20.0, 20.0});
            paletteImageStamper->draw(palettes[5], screen, Rect2<double>{ 50.0, 100.0, 100.0, 150.0 }, 45, Vector2i(8, 8), Stamper::ImageFlipOptions::FLIP_HORIZONTALLY, Stamper::ImageScaleType::CROP);
            paletteImageStamper->draw(palettes[5], screen, Rect2<double>{ 150.0, 100.0, 100.0, 150.0 }, 45, Vector2i(8, 8), Stamper::ImageFlipOptions::FLIP_VERTICALLY, Stamper::ImageScaleType::FIT);
            paletteImageStamper->draw(palettes[5], screen, Rect2<double>{ 250.0, 100.0, 100.0, 150.0 }, 45, Vector2i(8, 8), Stamper::ImageFlipOptions::FLIP_NONE, Stamper::ImageScaleType::STRETCH);
            paletteImageStamper->draw(palettes[5], screen, Rect2<double>{ 350.0, 100.0, 100.0, 150.0 }, 45, Vector2i(8, 8), Stamper::ImageFlipOptions::FLIP_NONE, Stamper::ImageScaleType::TILE);
            particleBatcher->draw(screen, Rect2<double>{ 0.0, 0.0, 16.0, 16.0 });
        };
        interface.onDrawSDL = [&](Interface& interface, SDL_Renderer* renderer, const Rect2<double>& bounds) -> void {
            batcher->draw(renderer, Rect2<double>{200.0, 200.0, 20.0, 20.0});
            paletteImageStamper->draw(palettes[5], renderer, Rect2<double>{ 50.0, 100.0, 100.0, 150.0 }, 45, Vector2i(8, 8), Stamper::ImageFlipOptions::FLIP_HORIZONTALLY, Stamper::ImageScaleType::CROP);
            paletteImageStamper->draw(palettes[5], renderer, Rect2<double>{ 150.0, 100.0, 100.0, 150.0 }, 45, Vector2i(8, 8), Stamper::ImageFlipOptions::FLIP_VERTICALLY, Stamper::ImageScaleType::FIT);
            paletteImageStamper->draw(palettes[5], renderer, Rect2<double>{ 250.0, 100.0, 100.0, 150.0 }, 45, Vector2i(8, 8), Stamper::ImageFlipOptions::FLIP_NONE, Stamper::ImageScaleType::STRETCH);
            paletteImageStamper->draw(palettes[5], renderer, Rect2<double>{ 350.0, 100.0, 100.0, 150.0 }, 45, Vector2i(8, 8), Stamper::ImageFlipOptions::FLIP_NONE, Stamper::ImageScaleType::TILE);
            particleBatcher->draw(renderer, Rect2<double>{ 0.0, 0.0, 16.0, 16.0 });
        };
        interface.onUpdate = [&](Interface& interface, double delta) -> void {
            particleBatcher->update(delta);
            SDL_Delay(1000 / 60);
        };

        if (interface.window == nullptr)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            SDL_Quit();
            return 0;
        }
        else
        {
            bool running = true;
            while (running) {
                SDL_Event ev;
                while (SDL_PollEvent(&ev))
                {
                    if ((SDL_QUIT == ev.type) ||
                        (SDL_KEYDOWN == ev.type && SDL_SCANCODE_ESCAPE == ev.key.keysym.scancode))
                    {
                        running = false;
                        break;
                    }
                }

                interface.update();
                interface.drawSDL();
            }
        }
        delete batcher;
    }

    SDL_Quit();

	return 0;*/
}