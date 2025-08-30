#pragma once

#include <iostream>
#include <fstream>
#include <limits>

// If you're using VScode press 'alt'+'z' to wrap words to the next line.
static constexpr const char *prerequisite = "This program will calculate your CGPA, you can either enter your scored grade in a subject and the number of credits it holds.\nIn the format of:\nEnter your grades and credits:\n8 4\n\nAnything other than a positive integer will count as the end of subject lists and the CGPA will be calculated\nOr you can edit the file with name 'cgpa.txt' with the information in the same format and save it and then choose the file option to have your cgpa calculated.\nIf there are not enough pairs then the last number/grade would not be used to calculate the CGPA.\nAny wrong information type/format would be counted as an error and only the information before that will be used to calculate your CGPA.\n\n";

enum class Mode : bool {Console, File};

Mode get_mode(void) noexcept;
float get_cgpa(Mode m) noexcept;