#include "exam_la.hpp"

EXAM_LA::EXAM_LA() {}

EXAM_LA::~EXAM_LA() {}

bool EXAM_LA::Paper_1() {
    std::string paper_header= {
        "1.1 Опр-е матрицы.\n1.2 Линейнные операции над матрицами.\n1.3 Умножение матриц.\n1.4 Блочные матрицы.\n1.5 Элементарные преобр-я матрицы.\n\n"
    };
    std::string _1_1_part_start = {
        "1.1 Опр-е матрицы:\n\tМатрицей называется система m x n чисел(или других мат. объектов),\nрасположенных в прямоугольной таблице из m строк и n столбцов\n"
    };
    std::string _1_1_part_example_1 = {
        "\t\t|a11, a12, ... a1n|\n"
        "\t\t|a21, a22, ... a2n|\n"
        "A\t=\t|...  ...  ... ...|\n"
        "\t\t|...  ...  ... ...|\n"
        "\t\t|am1, am2, ... amn|\n"
    };
    std::string _1_1_part_sqrt_matrix_def = {
        "[!] Квадратной матрицей называют матрицу, у которой размерность строк совпадает с размерностью столбцов (m = n):\n"
        "P.S: обычно размерность квадратной матрицы обозначают за n.\n"
        "[!] У квадратной матрицы есть главная и побочная диагонали.\n\n"
    };
    std::string _1_1_part_sqrt_matrix_main_diag = {
        "[!] На главной диагонали расположены элементы у которых индекс строки(ряда) равен индексу столбца (i = j)\n"
    };
    std::string _1_1_part_sqrt_matrix_nmain_diag = {
        "[!] На главной диагонали расположены элементы у которых индекс строки и индекс столбца находятся в зависимости i = n - j + 1(если отсчитывать от нуля, то n - j - 1)\n"
    };
    std::string _1_1_part_example_2 = {
        "\t\t|a11, \t...  \t...  \t...|\n"
        "\t\t|...  \ta22, \t...  \t...|\n"
        "A\t=\t|...  \t...  \t...  \t...|\n"
        "\t\t|...  \t...  \takk, \t...|\n"
        "\t\t|...  \t...  \t...  \tann|\n\n"
    };
    std::string _1_1_part_example_3 = {
        "\t\t|...  \t...  \t...  \ta1n|\n"
        "\t\t|...  \t...  \ta2n+1, \t...|\n"
        "A\t=\t|...  \t...  \t... \t...|\n"
        "\t\t|...  \taik, \t...  \t...|\n"
        "\t\t|an1, \t...  \t...  \t...|\n\n"
    };
    printf(paper_header.c_str());
    printf(_1_1_part_start.c_str());
    printf(_1_1_part_example_1.c_str());
    printf(_1_1_part_sqrt_matrix_def.c_str());
    printf(_1_1_part_sqrt_matrix_main_diag.c_str());
    printf(_1_1_part_example_2.c_str());
    printf(_1_1_part_sqrt_matrix_nmain_diag.c_str());
    printf(_1_1_part_example_3.c_str());
    return true;
}