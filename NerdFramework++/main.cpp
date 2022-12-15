#include <iostream>
#include <SDL.h>
#undef main
#include "CaesarCipher.h"
#include "VigenereCipher.h"
#include "Interface.h"
#include "String.h"
#include "BinaryGrid2.h"
#include "ImageLabel.h"
#include "Tester.h"
#include "TileBatcher.h"

int main() {
	std::cout << CaesarCipher::encrypt("If he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out.", 7) << std::endl;
	std::cout << VigenereCipher::encrypt("If he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out.", "cryptii") << std::endl;

    BinaryGrid2 grid(10, 10, false);
    grid.setTile(2, 5, true);
    std::cout << grid;

    String test = std::string("Once upon a time, this was a string. Now it is a String. The End.");

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
        frame.children.push_back(&frame2);
        Image4 image(100, 100, Color4::red);
        ImageLabel imageLabel(std::move(image), { 0.5, 0.5 }, { 0, 100, 0, 100 });

        Image4 image2(1, 1, Color4::lightGreen);
        Image4 image3(1, 1, Color4::lightBlue);
        Image4 image4(1, 1, Color4::lightRed);

        TileBatcher* batcher;
        Grid2<uint8_t> grid(10, 10, {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
            { 0, 1, 0, 2, 0, 0, 2, 0, 1, 0 },
            { 0, 1, 0, 2, 0, 0, 2, 0, 1, 0 },
            { 0, 1, 0, 2, 0, 0, 2, 0, 1, 0 },
            { 0, 1, 0, 2, 0, 0, 2, 0, 1, 0 },
            { 0, 1, 0, 2, 2, 2, 2, 0, 1, 0 },
            { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        });
        std::map<uint8_t, Image4> map;
        map[0] = image2;
        map[1] = image3;
        map[2] = image4;
        std::cout << (short)grid.get(3, 3) << std::endl;

        Interface interface([&](Interface& interface, SDL_Renderer* renderer)-> void{
            interface.frame.setColor(Color3::blue);
            interface.frame.setBorderColor(Color3::blue);

            interface.frame.children.push_back(&frame);
            interface.frame.children.push_back(&imageLabel);

            batcher = new TileBatcher(renderer, std::move(grid), std::move(map));
        });
        interface.onDrawSDL = [&](Interface& interface, SDL_Renderer* renderer, const Rect2<double>& bounds) -> void {
            batcher->draw(renderer, Rect2<double>{200.0, 200.0, 20.0, 20.0});
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

                interface.drawSDL();
            }
        }
        delete batcher;
    }

    SDL_Quit();

	return 0;
}