#pragma once
#include <stdio.h>

#include <cmath>
#include <cstring>
#include <fstream>

template <class T>
class Matris {
   public:
    // constructors
    explicit Matris(const size_t n) {
        this->m_rows = n;
        this->m_cols = n;
        n > 0 ? this->m_vec = new T[n * n]{0} : this->m_vec = new T[n * n];
    }

    Matris() {
        this->m_rows = 0;
        this->m_cols = 0;
        this->m_vec = new T[0];
    }

    Matris(const size_t n, const size_t m)
        : m_rows(n), m_cols(m), m_capacity(n * m) {
        m_vec = new T[m_capacity];
        for (size_t i = 0; i < m_capacity; i++) {
            m_vec[i] = T();
        }
    }

    // copy constructor
    Matris(const Matris &other)
        : m_rows(other.m_rows),
          m_cols(other.m_cols),
          m_capacity(m_rows * m_cols) {
        // if (this == &other) return *this;
        m_vec = new T[m_capacity];
        // memcpy(m_vec, other.m_vec, m_capacity);
        // std::copy(other.m_vec, other.m_vec + other.m_capacity, m_vec);
        for (size_t i = 0; i < m_capacity; i++) {
            m_vec[i] = other[i];
        }
    }

    // move constructor
    Matris(Matris &&other)
        : m_rows(other.m_rows),
          m_cols(other.m_cols),
          m_capacity(m_rows * m_cols),
          m_vec(other.m_vec) {
        other.m_vec = nullptr;
        other.m_capacity = 0;
    }

    Matris(std::initializer_list<T> list) {
        if (floor(sqrt(list.size())) != sqrt(list.size()))
            throw std::out_of_range("not square root");

        m_rows = sqrt(list.size());
        m_cols = sqrt(list.size());
        m_capacity = list.size();
        m_vec = new T[m_capacity];
        int i = 0;
        for (auto it = list.begin(); it < list.end(); ++it) {
            m_vec[i] = *it;
            ++i;
        }
    }

    // this formula works only for lab4, otherwise
    // it must be [x*m_cols+y]
    T get(const size_t x, const size_t y) {
        /* if (x > m_rows || y > m_cols) {
            throw std::out_of_range("index out of range");
        } */

        return m_vec[y * m_cols + x];
    }

    void set(const size_t x, const size_t y, T val) {
        /* if (x > m_rows || y > m_cols) {
            throw std::out_of_range("index out of range");
        } */

        m_vec[x * m_cols + y] = val;
    }

    // destructor
    ~Matris() {
        if (this->m_vec) {
            delete[] this->m_vec;
        }
    }

    // operators
    T &operator[](const size_t rhs) const {
        //if (rhs >= m_capacity) throw std::out_of_range("index out of range");
        return m_vec[rhs];
    }

    T &operator[](const size_t rhs) {
        // if (rhs >= m_capacity) throw std::out_of_range("index out of range");
        return m_vec[rhs];
    }

    // copy operator
    Matris<T> &operator=(const Matris<T> &other) {
        // Guard self assignment
        if (this == &other) return *this;

        // assume *this manages a reusable resource, such as a heap-allocated buffer
        // mArray
        if (m_capacity != other.m_capacity) {  // resource in *this cannot be reused
            delete[] m_vec;                    // release resource in *this
            m_vec = nullptr;
            m_capacity = 0;                   // preserve invariants in case next line throws
            m_vec = new T[other.m_capacity];  // allocate resource in *this
            m_capacity = other.m_capacity;
            m_rows = other.m_rows;
            m_cols = other.m_cols;
        }

        std::copy(other.m_vec, other.m_vec + other.m_capacity, m_vec);
        return *this;
    }

    // move operator
    Matris<T> &operator=(Matris<T> &&other) noexcept {
        // Guard self assignment
        if (this == &other) return *this;  // delete[]/size=0 would also be ok

        //delete[] m_vec;  // release resource in *this
        m_vec = other.m_vec;
        other.m_vec = nullptr;
        m_capacity = other.m_capacity;
        other.m_capacity = 0;
        m_rows = other.m_rows;
        other.m_rows = 0;
        m_cols = other.m_cols;
        other.m_cols = 0;
        return *this;
    }

    // scalar multiplication operator
    Matris<T> &operator*(const T &rhs) const {
        Matris<T> *mult = new Matris(m_rows, m_cols);
        for (size_t i = 0; i < m_capacity; i++) {
            mult->m_vec[i] = rhs * m_vec[i];
        }
        // for (size_t i = 0; i < m_capacity; i++) std::cout << mult->m_vec[i] << "
        // , " << m_vec[i] << std::endl;
        return *mult;
    }

    // matrix multiplication operator
    Matris<T> &operator*(const Matris &rhs) const {
        size_t cols_rhs = rhs.get_number_of_cols();
        size_t rows_rhs = rhs.get_number_of_rows();
        // size_t size = m_rows * cols_rhs;

        if (m_cols != rows_rhs) {
            throw std::out_of_range("Incorrect size of matrices");
        }

        Matris<T> *mult = new Matris(m_rows, cols_rhs);

        for (size_t i = 0; i < m_rows; i++) {
            for (size_t j = 0; j < cols_rhs; j++) {
                int sum = 0;
                for (size_t k = 0; k < m_cols; k++)
                    sum = sum + m_vec[i * m_cols + k] * rhs[k * cols_rhs + j];
                mult->m_vec[i * cols_rhs + j] = sum;
            }
        }
        return *mult;
    }

    // matrix addition operator
    Matris<T> &operator+(const Matris &rhs) const {
        size_t cols_rhs = rhs.get_number_of_cols();
        size_t rows_rhs = rhs.get_number_of_rows();

        if ((m_rows != rows_rhs) || (m_cols != cols_rhs)) {
            throw std::out_of_range("Incorrect size of matrices");
        }

        Matris<T> *add = new Matris(m_capacity);

        for (size_t i = 0; i < m_capacity; i++) {
            add->m_vec[i] = m_vec[i] + rhs[i];
        }
        return *add;
    }

    // matrix difference operator
    Matris<T> &operator-(const Matris &rhs) const {
        size_t cols_rhs = rhs.get_number_of_cols();
        size_t rows_rhs = rhs.get_number_of_rows();

        if ((m_rows != rows_rhs) || (m_cols != cols_rhs)) {
            throw std::out_of_range("Incorrect size of matrices");
        }

        Matris<T> *diff = new Matris(m_capacity);

        for (size_t i = 0; i < m_capacity; i++) {
            diff->m_vec[i] = m_vec[i] - rhs[i];
        }
        return *diff;
    }

    // scalar multiplication operator
    void operator*=(const T &rhs) {
        for (size_t i = 0; i < m_capacity; i++) {
            m_vec[i] = rhs * m_vec[i];
        }
    }

    // matrix multiplication operator
    void operator*=(const Matris &rhs) {
        size_t cols_rhs = rhs.get_number_of_cols();
        size_t rows_rhs = rhs.get_number_of_rows();

        if (m_cols != rows_rhs) {
            throw std::out_of_range("Incorrect size of matrices");
        }

        Matris<T> mult(*this);
        // for (size_t i = 0; i < m_capacity; i++) std::cout << mult->m_vec[i] << "
        // , " << m_vec[i] << std::endl;

        for (size_t i = 0; i < m_rows; i++) {
            for (size_t j = 0; j < cols_rhs; j++) {
                int sum = 0;
                for (size_t k = 0; k < m_cols; k++)
                    sum = sum + mult.m_vec[i * m_cols + k] * rhs[k * cols_rhs + j];
                m_vec[i * cols_rhs + j] = sum;
            }
        }
    }

    void operator+=(const Matris &rhs) {
        size_t cols_rhs = rhs.get_number_of_cols();
        size_t rows_rhs = rhs.get_number_of_rows();

        if ((m_rows != rows_rhs) || (m_cols != cols_rhs)) {
            throw std::out_of_range("Incorrect size of matrices");
        }

        for (size_t i = 0; i < m_capacity; i++) {
            m_vec[i] = m_vec[i] - rhs[i];
        }
    }

    void operator-=(const Matris &rhs) {
        size_t cols_rhs = rhs.get_number_of_cols();
        size_t rows_rhs = rhs.get_number_of_rows();

        if ((m_rows != rows_rhs) || (m_cols != cols_rhs)) {
            throw std::out_of_range("Incorrect size of matrices");
        }

        for (size_t i = 0; i < m_capacity; i++) {
            m_vec[i] = m_vec[i] - rhs[i];
        }
    }

    // ostream &operator<<(ostream &out, const Matris m) {}

    // methods
    size_t get_number_of_rows() const { return m_rows; }

    size_t get_number_of_cols() const { return m_cols; }

    void reset() {
        for (size_t i = 0; i < m_capacity; i++) {
            m_vec[i] = T();
        }
    }

    Matris<T> identity(unsigned int x) {
        Matris<T> m(x);
        size_t j = 0;
        for (size_t i = 0; i < x * x; i++) {
            if (j == i) {
                m[i] = 1;
                j = j + x + 1;
            } else
                m[i] = 0;
        }
        return m;
    }

    void insert_row(size_t row) {
        size_t newCap = m_capacity + m_cols;
        T *newMatrix = new T[newCap];

        int k = row * m_cols;
        if (row == 0) {
            for (size_t i = 0; i < m_cols; i++) {
                newMatrix[i] = 0;
            }
            for (size_t i = m_cols; i < newCap; i++) {
                newMatrix[i] = m_vec[i - m_cols];
            }
        } else {
            for (int i = 0; i < k; i++) {
                newMatrix[i] = m_vec[i];
            }
            for (size_t i = k; i < k + m_cols; i++) {
                newMatrix[i] = 0;
            }
            for (size_t i = k + m_cols; i < newCap; i++) {
                newMatrix[i] = m_vec[i - m_cols];
            }
        }
        delete[] m_vec;
        m_vec = nullptr;

        m_vec = new T[newCap];
        m_capacity = newCap;
        m_rows += 1;
        std::copy(newMatrix, newMatrix + newCap, m_vec);
        delete[] newMatrix;
        newMatrix = nullptr;
    }

    // add a row of 0 after the specified row number
    void append_row(size_t row) {
        if ((row < 0) || (row > m_rows)) {
            throw std::out_of_range("Incorrect row number for append.");
        }

        size_t newCap = m_capacity + m_cols;

        T *newMatrix = new T[newCap];

        int k = row * m_cols + m_cols;

        for (int i = 0; i < k; i++) {
            newMatrix[i] = m_vec[i];
        }

        for (size_t i = k; i < k + m_cols; i++) {
            newMatrix[i] = 0;
        }
        for (size_t i = k + m_cols; i < newCap; i++) {
            newMatrix[i] = m_vec[i - m_cols];
        }

        delete[] m_vec;
        m_vec = nullptr;

        m_vec = new T[newCap];
        m_capacity = newCap;
        m_rows += 1;
        std::copy(newMatrix, newMatrix + newCap, m_vec);
        delete[] newMatrix;
        newMatrix = nullptr;
    }

    void remove_row(size_t row) {
        if ((row < 0) || (row > m_rows)) {
            throw std::out_of_range("Incorrect row number for append.");
        }

        size_t newCap = m_capacity - m_cols;

        T *newMatrix = new T[newCap];

        size_t start = row * m_cols;

        size_t finish = start + m_cols;

        for (size_t i = 0; i < m_capacity; i++) {
            if (i < start)
                newMatrix[i] = m_vec[i];

            else if (i >= start && i < finish)
                continue;
            else
                newMatrix[i - m_cols] = m_vec[i];
        }

        delete[] m_vec;
        m_vec = nullptr;

        m_vec = new T[newCap];
        m_capacity = newCap;
        m_rows -= 1;
        std::copy(newMatrix, newMatrix + newCap, m_vec);
        delete[] newMatrix;
        newMatrix = nullptr;
    }

    // insert a column of 0 before the given column number
    void insert_col(size_t col) {
        if ((col < 0) || (col >= m_cols)) {
            throw std::out_of_range("Incorrect col number for append (insert).");
        }

        size_t newCap = m_capacity + m_rows;
        T *newMatrix = new T[newCap];

        for (size_t i = 0; i < m_capacity; i++) {
            newMatrix[i] = m_vec[i];
        }
        for (size_t i = m_capacity; i < newCap; i++) {
            newMatrix[i] = 0;
        }
        int n = m_capacity;
        for (size_t i = 0; i < newCap; i++) {
            if (i == col) {
                for (size_t j = n; j > i; j--) {
                    newMatrix[j] = newMatrix[j - 1];
                }
                newMatrix[i] = 0;
                col += m_cols + 1;
                n++;
            }
        }

        delete[] m_vec;
        m_vec = nullptr;

        m_vec = new T[newCap];
        m_capacity = newCap;
        m_cols += 1;
        std::copy(newMatrix, newMatrix + newCap, m_vec);
        delete[] newMatrix;
        newMatrix = nullptr;
    }

    // add a column of 0 after the specified column number
    void append_col(size_t col) {
        if ((col < 0) || (col >= m_cols)) {
            throw std::out_of_range("Incorrect col number for append.");
        }

        size_t newCap = m_capacity + m_rows;
        T *newMatrix = new T[newCap];

        for (size_t i = 0; i < m_capacity; i++) {
            newMatrix[i] = m_vec[i];
        }
        for (size_t i = m_capacity; i < newCap; i++) {
            newMatrix[i] = 0;
        }
        int n = m_capacity;
        for (size_t i = 0; i < newCap; i++) {
            if (i == col + 1) {
                for (size_t j = n; j > i; j--) {
                    newMatrix[j] = newMatrix[j - 1];
                }
                newMatrix[i] = 0;
                col += m_cols + 1;
                n++;
            }
        }

        delete[] m_vec;
        m_vec = nullptr;

        m_vec = new T[newCap];
        m_capacity = newCap;
        m_cols += 1;
        std::copy(newMatrix, newMatrix + newCap, m_vec);
        delete[] newMatrix;
        newMatrix = nullptr;
    }

    void remove_col(size_t col) {
        if ((col < 0) || (col >= m_cols)) {
            throw std::out_of_range("Incorrect col number for remove.");
        }

        size_t newCap = m_capacity - m_rows;
        T *newMatrix = new T[newCap];

        for (size_t i = 0; i < m_capacity; i++) {
            if (i == col) {
                for (size_t j = i; j < m_capacity; j++) {
                    m_vec[j] = m_vec[j + 1];
                }
                col += m_cols - 1;
            }
        }

        for (size_t i = 0; i < newCap; i++) {
            newMatrix[i] = m_vec[i];
        }

        delete[] m_vec;
        m_vec = nullptr;

        m_vec = new T[newCap];
        m_capacity = newCap;
        m_cols -= 1;
        std::copy(newMatrix, newMatrix + newCap, m_vec);
        delete[] newMatrix;
        newMatrix = nullptr;
    }

    typedef T *it;

    it begin() { return &m_vec[0]; }
    it end() { return &m_vec[m_capacity]; }

    friend std::ostream &operator<<(std::ostream &out, const Matris &m) {
        for (size_t i = 1; i <= m.m_capacity; i++) {
            out << m.m_vec[i - 1];
            if (i % m.get_number_of_cols() == 0) out << std::endl;
        }
        return out;
    }

    friend std::istream &operator>>(std::istream &in, Matris &m) {
        for (size_t i = 0; i < m.m_capacity; i++) {
            if (!(in >> m.m_vec[i])) return in;
        }
        return in;
    }

   private:
    size_t m_rows;
    size_t m_cols;
    size_t m_capacity;
    T *m_vec;
};