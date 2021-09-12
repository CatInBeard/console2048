#include <main-header.h>
#include <game-class.h>
Game* game;

void exiting(){
    delete ::game;
}
int main(){
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::srand(std::time(0));
    ::game = new Game();
    ::game->init();
    exiting();
    return 0;
}