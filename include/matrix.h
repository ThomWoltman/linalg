#ifndef KMINTFRAMEWORK_MATRIX_H
#define KMINTFRAMEWORK_MATRIX_H

#include <vector>
#include "point.h"

namespace linalg {
    class matrix {
    private:
        int _rows;
        int _columns;
        double **data;
    public:
        matrix();

        matrix(int row, int column);

        matrix(int row, int column, std::vector<point> points);

        ~matrix();

        matrix(const matrix &m);

        matrix &operator=(const matrix &m);

        matrix operator*(const matrix &m1);

        matrix operator-=(const matrix& m);

        matrix operator+=(const matrix& m);

        void alloc_space();

        static double dot_product(matrix, matrix);

        inline double& operator()(int x, int y) { return data[x][y]; }

        double get_value(int row, int column) { return data[row][column]; }

        int get_rows() const { return _rows; }

        int get_columns() const { return _columns; }

        static matrix create_translate_matrix_2d(double x, double y);

        static matrix create_rotate_matrix_2d(double degree);

        static matrix create_identity_matrix(int size);

        static matrix create_translate_matrix_3d(double x, double y, double z);

        static matrix create_extra_row(matrix m);

        static matrix remove_extra_row(matrix m);
    };
}

#endif //KMINTFRAMEWORK_MATRIX_H
