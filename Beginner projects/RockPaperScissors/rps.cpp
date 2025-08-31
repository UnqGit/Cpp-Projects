#include "game.hpp"

int main(void) {
    std::cout << _instruction;
    std::string is_play;
    unsigned int player_1_score = 0, player_2_score = 0;
    do {
        game(player_1_score, player_2_score);
        std::cout << "Enter 'q' if you want to quit playing: ";
        std::getline(std::cin, is_play);
    } while (is_play.empty() || (std::tolower(is_play[0]) != 'q'));
    display_score(player_1_score, player_2_score);
}