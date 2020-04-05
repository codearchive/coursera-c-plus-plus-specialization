#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>

using namespace std;

class Matrix
{
public:
    Matrix()
    {
        row_count = 0;
        column_count = 0;
    }

    Matrix(const int& num_rows, const int& num_cols)
    {
        Reset(num_rows, num_cols);
    }

    void Reset(const int& new_num_rows, const int& new_num_cols)
    {
        if (new_num_rows < 0 || new_num_cols < 0)
        {
            throw out_of_range("out of range");
        }
        if (new_num_rows == 0 || new_num_cols == 0)
        {
            row_count = 0;
            column_count = 0;
        }
        else
        {
            row_count = new_num_rows;
            column_count = new_num_cols;
        }
        _storage.assign(row_count, vector<int>(column_count));
    }

    int At(const int& row_number, const int& col_number) const
    {
        if (row_number < 0 || col_number < 0 || row_number >= row_count || col_number >= column_count)
        {
            throw out_of_range("out of range");
        }
        return _storage[row_number][col_number];
    }

    int& At(const int& row_number, const int& col_number)
    {
        if (row_number < 0 || col_number < 0 || row_number >= row_count || col_number >= column_count)
        {
            throw out_of_range("out of range");
        }
        return _storage[row_number][col_number];
    }

    int GetNumRows() const
    {
        return row_count;
    }

    int GetNumColumns() const
    {
        return column_count;
    }


private:
    int row_count;
    int column_count;
    vector<vector<int>> _storage;
};

ostream& operator<<(ostream& stream, const Matrix& matrix)
{
    stream << matrix.GetNumRows() << ' ' << matrix.GetNumColumns() << endl;
    const int last_col = matrix.GetNumColumns() - 1;
    for (int i = 0; i < matrix.GetNumRows(); ++i)
    {
        for (int j = 0; j < matrix.GetNumColumns(); ++j)
        {
            stream << matrix.At(i, j);
            if (j != last_col)
            {
                 stream << ' ';
            }
        }
        stream << endl;;
    }
    return stream;
}

istream& operator>>(istream& stream, Matrix& matrix)
{
    int rows, cols;
    stream >> rows >> cols;
    matrix.Reset(rows, cols);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            stream >> matrix.At(i, j);
        }
        while (stream.peek() != '\n')
        {
            stream.ignore(1);
        }
    }
    return stream;
}

bool operator==(const Matrix& lhs, const Matrix& rhs)
{
    if (lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns())
    {
        for (int i = 0; i < lhs.GetNumRows(); ++i)
        {
            for (int j = 0; j < lhs.GetNumColumns(); ++j)
            {
                if (lhs.At(i, j) != rhs.At(i, j))
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
    if (lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns())
    {
        Matrix result_matrix(lhs.GetNumRows(), lhs.GetNumColumns());
        for (int i = 0; i < lhs.GetNumRows(); ++i)
        {
            for (int j = 0; j < lhs.GetNumColumns(); ++j)
            {
                result_matrix.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
            }
        }
        return result_matrix;
    }
    throw invalid_argument("invalid argument");
}

int main()
{
    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;
    return 0;
}