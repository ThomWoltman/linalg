#include "matrix.h"
#include <iostream>

namespace linalg{
    matrix::matrix() : _rows{1}, _columns{1} {
        alloc_space();
        data[0][0] = 0;
    }

    matrix::matrix(int row, int column, std::vector<point> points) : _rows{row}, _columns{column} {
        alloc_space();
        if(points.size() != column && row != 2){
            throw "bad call on matrix constructor";
        }

        int i = 0;

        if(row == 2){
            for(point p : points){
                data[0][i] = p.x();
                data[1][i] = p.y();
                i++;
            }
        }
        else if(row == 3){
            for(point p : points){
                data[0][i] = p.x();
                data[1][i] = p.y();
                data[2][i] = p.z();
                i++;
            }
        }
        else if(row == 4){
            for(point p : points){
                data[0][i] = p.x();
                data[1][i] = p.y();
                data[2][i] = p.z();
                data[3][i] = p.w();
                i++;
            }
        }
    }

    matrix::matrix(int row, int column) : _rows{row}, _columns{column} {
        alloc_space();
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                data[i][j] = 0;
            }
        }
    }

    matrix::matrix(const matrix &m) : _rows{m._rows}, _columns{m._columns}{
        alloc_space();
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _columns; ++j) {
                data[i][j] = m.data[i][j];
            }
        }
    }

    matrix& matrix::operator=(const matrix &m) {
        if (this == &m) {
            return *this;
        }

        if (_rows != m._rows || _columns != m._columns) {
            for (int i = 0; i < _rows; ++i) {
                delete[] data[i];
            }
            delete[] data;

            _rows = m._rows;
            _columns = m._columns;
            alloc_space();
        }

        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _columns; ++j) {
                data[i][j] = m.data[i][j];
            }
        }
        return *this;
    }

    matrix matrix::operator*(const matrix &m1) {
        matrix temp(m1._rows, _columns);
        for (int i = 0; i < temp._rows; ++i) {
            for (int j = 0; j < temp._columns; ++j) {
                for (int k = 0; k < m1._columns; ++k) {
                    temp.data[i][j] += (m1.data[i][k] * data[k][j]);
                }
            }
        }
        return temp;
    }

    matrix matrix::operator-=(const matrix &m) {
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _columns; ++j) {
                data[i][j] -= m.data[i][j];
            }
        }
        return *this;
    }

    matrix matrix::operator+=(const matrix &m) {
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _columns; ++j) {
                data[i][j] += m.data[i][j];
            }
        }
        return *this;
    }

    matrix::~matrix() {
        for (int i = 0; i < _rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }


    void matrix::alloc_space()
    {
        data = new double*[_rows];
        for (int i = 0; i < _rows; ++i) {
            data[i] = new double[_columns];
        }
    }

    double matrix::dot_product(matrix, matrix) {

    }

    matrix matrix::create_rotate_matrix_2d(double degree) {
        matrix m = create_identity_matrix(3);
        point a { cos(degree), sin(degree)};
        point b { -sin(degree), cos(degree)};

        m.data[0][0] = a.x();
        m.data[1][0] = a.y();
        m.data[0][1] = b.x();
        m.data[1][1] = b.y();

        return m;
    }

    matrix matrix::create_translate_matrix_2d(double x, double y) {
        matrix temp = matrix::create_identity_matrix(3);
        temp.data[0][2] = x;
        temp.data[1][2] = y;

        return temp;
    }

    matrix matrix::create_translate_matrix_3d(double x, double y, double z) {
        matrix temp = matrix::create_identity_matrix(4);
        temp.data[0][3] = x;
        temp.data[1][3] = y;
        temp.data[2][3] = z;

        return temp;
    }

    matrix matrix::create_scale_matrix_3d(double x, double y, double z) {
        matrix temp = matrix::create_identity_matrix(4);
        temp.data[0][0] = x;
        temp.data[1][1] = y;
        temp.data[2][2] = z;

        return temp;
    }

    matrix matrix::create_rotate_x_matrix_3d(double degree) {
        matrix m = create_identity_matrix(4);
        m.data[1][1] = cos(degree);
        m.data[1][2] = -sin(degree);
        m.data[2][1] = sin(degree);
        m.data[2][2] = cos(degree);

        return m;
    }

    matrix matrix::create_rotate_y_matrix_3d(double degree) {
        matrix m = create_identity_matrix(4);

        m.data[0][0] = cos(degree);
        m.data[2][0] = -sin(degree);
        m.data[0][2] = sin(degree);
        m.data[2][2] = cos(degree);

        return m;
    }

    matrix matrix::create_rotate_z_matrix_3d(double degree) {
        matrix m = create_identity_matrix(4);

        m.data[0][0] = cos(degree);
        m.data[0][1] = -sin(degree);
        m.data[1][0] = sin(degree);
        m.data[1][1] = cos(degree);

        return m;
    }

    matrix matrix::create_identity_matrix(int size)
    {
        matrix temp(size, size);
        for (int i = 0; i < temp._rows; ++i) {
            for (int j = 0; j < temp._columns; ++j) {
                if (i == j) {
                    temp.data[i][j] = 1;
                } else {
                    temp.data[i][j] = 0;
                }
            }
        }
        return temp;
    }

    matrix matrix::create_extra_row(matrix m) {
        matrix temp{m.get_rows()+1, m.get_columns()};

        for (int i = 0; i < temp._rows; ++i) {
            for (int j = 0; j < temp._columns; ++j) {
                if(i == temp._rows-1){
                    temp.data[i][j] = 1;
                }
                else{
                    temp.data[i][j] = m.data[i][j];
                }
            }
        }

        return temp;
    }

    matrix matrix::remove_extra_row(matrix m) {
        matrix temp{m.get_rows()-1, m.get_columns()};

        for (int i = 0; i < temp._rows; ++i) {
            for (int j = 0; j < temp._columns; ++j) {
                    temp.data[i][j] = m.data[i][j];
            }
        }

        return temp;
    }
}