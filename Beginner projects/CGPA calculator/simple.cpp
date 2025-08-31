// This is the simple version.

#include <iostream>

int main(void) {
    std::cout << "Enter the number of subjects: ";
    unsigned int num_sub, totol_grade = 0, total_credit = 0, grade, credit;
    std::cin >> num_sub;
    for (int i = 0; i < num_sub; i++) {
        std::cout << "Enter grade scored(out of 10) and credit of the subject #" << i << ": ";
        std::cin >> grade >> credit;
        total_credit += credit;
        totol_grade += credit * grade;
    }
    std::cout << "Your CGPA scored is: " << (total_credit == 0 ? 0 : (double) totol_grade / total_credit);
}