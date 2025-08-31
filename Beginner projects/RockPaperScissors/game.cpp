#include "game.hpp"

#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
#elif defined(__linux__) || defined(__APPLE__)
    #include <termios.h>
    #include <unistd.h>
#endif

namespace {
    inline void cin_clear(void) noexcept {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    typedef enum MoveCode : char {
        Stone, Paper, Scissor, None
    } CD;

    std::string get_hidden_input(void) noexcept {
        std::string in;
        in.reserve(5);
        #if defined(_WIN32) || defined(_WIN64)
            char c;
            while((c = _getch()) != '\r' && c != '\n') {
                if (c == '\b') {
                    if (!in.empty()) in.pop_back();
                }
                else in.push_back(c);
            }
        #elif defined(__linux__) || defined(__APPLE__)
            termios oldt, newt;
            // Get current terminal settings.
            tcgetattr(STDIN_FILENO, &oldt);
            // Turning of echo.
            newt = oldt;
            newt.c_lflag &= -ECHO;
            // Setting terminal settings to without echo.
            tcsetattr(STDIN_FILENO, TCANOW, &newt);
            std::getline(std::cin, in);
            // Turning old settings back on.
            tcsetattr(STDIN_FILENO, TCANOW, &oldt);
            std::cout << '\n';
        #else
            std::getline(std::cin, in);
        #endif
        std::transform(in.begin(), in.end(), in.begin(), ::tolower);
        return in;
    }

    inline void inc_score(unsigned int score[3], const char c) noexcept {
        switch (c) { // For spelling errors and mixed up words...basically a really simple fuzzy finding mechanism.
            case 's':
                score[::CD::Stone]++;
                score[::CD::Scissor]++;
                break;
            case 't':
                score[::CD::Stone]++;
                break;
            case 'o':
                score[::CD::Stone]++;
                score[::CD::Scissor]++;
                break;
            case 'n':
                score[::CD::Stone]++;
                break;
            case 'e':
                score[::CD::Stone]++;
                score[::CD::Paper]++;
                break;
            case 'c':
                score[::CD::Scissor]++;
                break;
            case 'i':
                score[::CD::Scissor]++;
                break;
            case 'r':
                score[::CD::Scissor]++;
                score[::CD::Stone]++;
                score[::CD::Paper]++;
                break;
            case 'k':
                score[::CD::Stone]++;
                break;
            case 'p':
                score[::CD::Paper]++;
                break;
            default:;
        }
    }

    inline ::MoveCode int_cd_map(const unsigned int a) noexcept {
        switch (a) {
            case 0:
                return ::CD::Stone;
            case 1:
                return ::CD::Paper;
            default:
                return ::CD::Scissor;
        }
    }

    inline ::MoveCode choose_option(const unsigned int score[3]) noexcept {
        unsigned int winning_index = 0, i = 1;
        for (; i < 3; i++) {
            if (score[winning_index] < score[i]) {
                winning_index = i;
            }
            else if (score[winning_index] == score[i]) break;
        }
        return (i != 3) ? ::CD::None : ::int_cd_map(winning_index);
    }

    ::MoveCode is_invalid_input(const std::string_view sv) noexcept {
        static unsigned int score[3] {};
        for (int i = 0; i < 3; i++) score[i] = 0;
        for (const auto &c: sv) ::inc_score(score, c);
        return ::choose_option(score);
    }

    ::MoveCode get_input(void) noexcept {
        std::string in;
        std::cout << "enter your choice: \n";
        static const char *err_txt = "The word provided did not relate to any notable keyword('stone', 'rock', 'paper', 'scissor')\nEnter again: \n";
        ::MoveCode res;
        while ((res = ::is_invalid_input(in = ::get_hidden_input())) == ::CD::None)
            std::cerr << err_txt;
        return res;
    }

    const char* &mode_to_str(const ::MoveCode m) noexcept {
        static const char *_stone = "stone";
        static const char *_paper = "paper";
        static const char *_scissor = "scissor";
        if (m == ::CD::Stone) return _stone;
        else if (m == ::CD::Paper) return _paper;
        else return _scissor;
    }

    typedef enum StateWin : char {Draw, Player1, Player2} ST;

    inline bool p1win(const ::MoveCode p1, const ::MoveCode p2) noexcept {
        return (p1 == ::CD::Stone && p2 == ::CD::Scissor) || (p1 == ::CD::Scissor && p2 == ::CD::Paper) || (p1 == ::CD::Paper && p2 == ::CD::Stone);
    }

    ::StateWin is_win(const ::MoveCode p1, const ::MoveCode p2) noexcept {
        if (p1 == p2) return ::ST::Draw;
        else if (::p1win(p1, p2)) return ::ST::Player1;
        return ::ST::Player2;
    }
}

void game(unsigned int &p1score, unsigned int &p2score) noexcept {
    std::cout << "Player 1; ";
    ::MoveCode p1 = ::get_input();
    std::cout << "Player 2; ";
    ::MoveCode p2 = ::get_input();
    ::cin_clear(); // Because in the main function we have getline so entering an empty input will cause trouble.
    const unsigned char who_won = ::is_win(p1, p2);
    std::cout << "Player 1 chose '" << ::mode_to_str(p1) << "'\n";
    std::cout << "Player 2 chose '" << ::mode_to_str(p2) << "'\n";
    if (who_won == ::ST::Draw) {
        p1score++;
        p2score++;
        std::cout << "So, it is a draw.\n\n";
    }
    else if (who_won == ::ST::Player1) {
        p1score++;
        std::cout << "So, Player 1 won.\n\n";
    }
    else {
        p2score++;
        std::cout << "Sp, Player 2 won.\n\n";
    }
}

void display_score(const unsigned int p1score, const unsigned int p2score) noexcept {
    std::cout << "So, at the end of the game.\n";
    if (p1score == p2score) std::cout << "It is draw with an equal score of: " << p1score;
    else if (p1score > p2score) std::cout << "Player 1 won with scores of " << p1score << " to " << p2score;
    else std::cout << "Player 2 won with scores of " << p2score << " to " << p1score;
}