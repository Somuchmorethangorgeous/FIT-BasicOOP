#include "window.h"
#include <iostream>

Window::Window() {
    if (init() == EXIT_FAILURE)
        is_closed = true;
}

Window::Window(std::string title_, int width_, int height_) 
: title(title_), width(width_), height(height_) {
    if (init() == EXIT_FAILURE)
        is_closed = true;
}

int Window::init() {
    if((SDL_Init(SDL_INIT_VIDEO)==-1)) {
        std::cerr << "Could't initialize SDL: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow(
        title.c_str(), 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        width, height, 0);
    if (nullptr == window) {
        std::cerr << "Couldn't create window" << std::endl;
        return EXIT_FAILURE;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == renderer) {
        std::cerr << "Couldn't create renderer" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

bool Window::isClosed() const {
    return is_closed;
}

void Window::PoolEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event))
        switch(event.type) {
            case SDL_QUIT : is_closed = true;
                            break;
        }
}

void Window::drawRect(const SDL_Rect *rect, const Color &color) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, rect);
}

void Window::drawLine(int x1, int y1, int x2, int y2, const Color &color) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Window::present() const {
    SDL_RenderPresent(renderer);
}

void Window::clear() const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

int Window::getWidth() const {
    return width;
}

int Window::getHeight() const {
    return height;
}

Window::operator SDL_Renderer *() const {
    return renderer;
}

Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
