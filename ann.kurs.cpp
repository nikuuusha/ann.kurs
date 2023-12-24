#include <fstream>
#include <iostream>
#include <string>


class matrix {
public:
    matrix() = default;
    explicit matrix(std::size_t size) : size_(size), data_(nullptr) {
        allocate();
    }
    ~matrix() { deallocate(); }

    int** get_data() const { return data_; }

    std::size_t get_size() const { return size_; }

    void input_from_stdin() {
        std::cout << "enter size: ";
        std::cin >> size_;
        allocate();

        std::cout << "enter matrix:\n";
        for (std::size_t i = 0; i < size_; ++i) {
            for (std::size_t j = 0; j < size_; ++j) {
                std::cin >> data_[i][j];
            }
        }
    }

    void input_from_file(const std::string& filename) {
        std::ifstream ifs(filename);
        if (!ifs.is_open()) {
            std::cout << "input file error\n";
            return;
        }

        ifs >> size_;
        allocate();

        for (std::size_t i = 0; i < size_; ++i) {
            for (std::size_t j = 0; j < size_; ++j) {
                ifs >> data_[i][j];
            }
        }
    }

    void print_to_stdout() {
        for (std::size_t i = 0; i < size_; ++i) {
            for (std::size_t j = 0; j < size_; ++j) {
                std::cout << data_[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }

    void print_to_file(const std::string& filename) {
        std::ofstream ofs(filename);
        if (!ofs.is_open()) {
            std::cout << "output file error\n";
            return;
        }
        ofs << size_ << '\n';
        for (std::size_t i = 0; i < size_; ++i) {
            for (std::size_t j = 0; j < size_; ++j) {
                ofs << data_[i][j] << ' ';
            }
            ofs << '\n';
        }
    }

    void edit() {
        std::size_t i;
        std::size_t j;

        std::cout << "indexes: <> <>: ";
        std::cin >> i >> j;
        if (i >= size_ || j >= size_) {
            std::cout << "index out of range\n";
            return;
        }

        std::cout << "replace to value: ";
        int value;
        std::cin >> value;

        data_[i][j] = value;
    }

    void copy_cols(const matrix& A, const matrix& B) {
        if (A.get_size() != B.get_size()) {
            std::cout << "size doens't match\n";
            return;
        }

        auto internal_A = A.get_data();
        auto internal_B = B.get_data();

        for (std::size_t j = 0; j < size_; ++j) {
            bool is_same = false;
            for (std::size_t i = 0; i < size_; ++i) {
                if (internal_A[i][j] != internal_B[i][j]) {
                    is_same = false;
                    continue;
                }
                else {
                    is_same = true;
                }
            }
            if (is_same) {
                continue;
            }

            for (std::size_t i = 0; i < size_; ++i) {
                data_[i][j] = internal_B[i][j];
            }
        }
    }

private:
    void allocate() {
        data_ = new int* [size_];
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = new int[size_];
        }
    }

    void deallocate() {
        for (std::size_t i = 0; i < size_; ++i) {
            delete data_[i];
        }
        delete[] data_;
    }

private:
    std::size_t size_;
    int** data_;
};

int main() {
    bool is_run = true;
    matrix A{};
    matrix B{};


    while (is_run) {
        std::cout << "enter number to perform an operation:\n"
            "1: enter matrix A from stdin\n"
            "2: enter matrix A from file\n"
            "3: enter matrix B from stdin\n"
            "4: enter matrix B from file\n"
            "5: print matrix A to stdout\n"
            "6: print matrix A to file\n"
            "7: print matrix B to stdout\n"
            "8: print matrix B to file\n"
            "9: edit matrix A\n"
            "10: edit matrix B\n"
            "11: go brrrr\n"
            "0: exit\n";
        int choice;
        std::cin >> choice;
        switch (choice) {
        case 0:
            is_run = false;
            break;
        case 1:
            A.input_from_stdin();
            break;
        case 2:
            A.input_from_file("input_A.txt");
            break;
        case 3:
            B.input_from_stdin();
            break;
        case 4:
            B.input_from_file("input_B.txt");
            break;
        case 5:
            A.print_to_stdout();
            break;
        case 6:
            A.print_to_file("output_A.txt");
            break;
        case 7:
            B.print_to_stdout();
            break;
        case 8:
            B.print_to_file("output_B.txt");
            break;
        case 9:
            A.edit();
            break;
        case 10:
            B.edit();
            break;
        case 11: {
            matrix C(A.get_size());
            C.copy_cols(A, B);
            C.print_to_stdout();
            break;
        }
        default:
            break;
        }
    }

    return 0;
}
