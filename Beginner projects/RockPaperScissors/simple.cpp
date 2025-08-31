#include <iostream>
#include <string>

int main() {
    std::string p1, p2;
    std::cout << "Player 1 (rock/paper/scissors): ";
    std::cin >> p1;
    std::cout << "Player 2 (rock/paper/scissors): ";
    std::cin >> p2;
    
    if (p1 == p2) 
        std::cout << "Draw!\n";
    else if ((p1 == "rock" && p2 == "scissors") || (p1 == "scissors" && p2 == "paper") || (p1 == "paper" && p2 == "rock")) 
        std::cout << "Player 1 wins!\n";
    else 
        std::cout << "Player 2 wins!\n";
}