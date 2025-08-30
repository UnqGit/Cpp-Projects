#include "cgpa.hpp"

namespace {
    inline void cin_clear(void) noexcept {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void get_infof(std::ifstream &info_file, unsigned int &total_grade, unsigned int &total_credit) noexcept {
        // Getting total grade and credit from the file.
        static const char *end_sess = "Ending session in file.\n";
        std::string grade_, credit_;
        unsigned int num_subject = 0, grade, credit;
        while (info_file >> grade_ && info_file >> credit_) {
            num_subject++;
            try {
                grade = std::stoi(grade_);
                if (grade < 0 || grade > 10) { // Max grade is 10.
                    std::cerr << "Grade cannot be negative or greater than 10, the entry #" << num_subject << '\n';
                    std::cerr << end_sess;
                    break;
                }
                credit = std::stoi(credit_);
                if (credit < 0) {
                    std::cerr << "Credit cannot be negative, the entry #" << num_subject << '\n';
                    std::cerr << end_sess;
                    break;
                }
                total_grade += grade * credit;
                total_credit += credit;
            }
            catch (...) {
                break;
            }
        }
    }

    unsigned int get_num(void) noexcept {
        static const char *err_text = "There was an error regarding your number, enter again: ";
        unsigned int result;
        while (!(std::cin >> result)) {
            std::cerr << err_text;
            ::cin_clear();
        }
        return result;
    }

    unsigned int get_grade(void) noexcept {
        static const char *err_text = "Subject grade cannot be greater than 10.\nEnter again: ";
        unsigned int result = ::get_num();
        while (result > 10) {
            std::cerr << err_text;
            result = ::get_num();
        }
        return result;
    }

    void get_infoc(unsigned int num_subjects, unsigned int &total_grade, unsigned int &total_credit) noexcept {
        unsigned int grade, credit;
        static const char *pre_text = "Enter subject #";
        for (unsigned int i = 0; i < num_subjects; i++) {
            std::cout << pre_text << (i + 1) << " grade: ";
            grade = ::get_grade();
            std::cout << pre_text << (i + 1) << " credit: ";
            credit = ::get_num();
            total_grade += grade * credit;
            total_credit += credit;
        }
    }

    float file_cgpa(void) noexcept {
        std::ifstream info_file("cgpa.txt");
        if (!info_file.is_open()) {
            std::cerr << "Could not open the 'cgpa.txt' file.\n";
            return 0.0f;
        }
        unsigned int total_grade, total_credit;
        ::get_infof(info_file, total_grade, total_credit);
        return total_credit == 0 ? 0 : (float) total_grade / total_credit;
    }

    float console_cgpa(void) noexcept {
        std::cout << "Enter the number of subjects: ";
        unsigned int num_subjects = 0, total_grade = 0, total_credit = 0;
        num_subjects = ::get_num();
        if (num_subjects == 0) return 0;
        ::get_infoc(num_subjects, total_grade, total_credit);
        return total_credit == 0 ? 0 : (float) total_grade / total_credit;
    }
}

Mode get_mode(void) noexcept {
    bool mode;
    std::cout << "Enter 0 for console mode and 1 for file system: ";
    while (!(std::cin >> mode)) {
        std::cout << "Please enter a valid integer(0 for console and 1 for file): ";
        ::cin_clear();
    }
    return mode ? Mode::File : Mode::Console;
}

float get_cgpa(Mode m) noexcept {
    // Choose the correct method to do the job.
    return m == Mode::Console ? ::console_cgpa() : ::file_cgpa();
}