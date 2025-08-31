#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <algorithm>

static constexpr const char *_instruction = "You can type 'rock', 'paper', 'scissor', 'stone'; It will not show up on the terminal, so that the other player cannot see what you typed. It will show up after the second player has typed their answer(works only if you're on windows, linux or apple).\n\n";

void game(unsigned int &p1score, unsigned int &p2score) noexcept;
void display_score(const unsigned int p1score, const unsigned int p2score) noexcept;