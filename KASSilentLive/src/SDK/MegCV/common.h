#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <utility>
#include <iostream>
#include <iomanip>
#include <vector>
#include <iostream>

namespace megcv {

class Size {
    public:
        Size(size_t rows, size_t cols):
            m_rows(rows), m_cols(cols)
        {}
        Size():
            m_rows(0), m_cols(0)
        {}

		size_t rows() const { return m_rows; }
        size_t &rows() { return m_rows; }
		size_t cols() const { return m_cols; }
        size_t &cols() { return m_cols; }
		size_t height() const { return rows(); }
		size_t &height() { return rows(); }
		size_t width() const { return cols(); }
		size_t &width() { return cols(); }

		bool operator == (const Size &rhs) const {
			return rows() == rhs.rows() && cols() == rhs.cols();
		}

	private:
        size_t m_rows, m_cols;
};

class MatShape: public Size {
	public:
		MatShape(size_t rows, size_t cols, size_t channels):
			Size(rows, cols), m_channels(channels)
		{ }

		size_t channels() const { return m_channels; }

		bool operator == (const MatShape &rhs) const {
			return Size::operator==(rhs) && channels() == rhs.channels();
		}


	private:
		size_t m_channels;
};


/*!
 * A row-major device matrix wrapper
 */
template <typename T>
class Mat {
    private:
        size_t m_rows, m_cols;
        size_t m_channels;
        size_t m_step;

        std::shared_ptr<T> m_data;

        size_t m_offset;

        T *raw_ptr()
        { return m_data.get() + m_offset; }
        const T *raw_ptr() const
        { return m_data.get() + m_offset; }
    public:
        Mat() = default;
        Mat(size_t rows, size_t cols, size_t channels, size_t step);
        Mat(size_t rows, size_t cols, size_t channels);
        // do not try to manage data by shared_ptr
        Mat(size_t rows, size_t cols, size_t channels, T *data);
        Mat(size_t rows, size_t cols, size_t channels, size_t step, T *data);
        // shallow-copy constructor
        Mat(const Mat<T> &rhs);
        Mat(const Mat<T> &rhs, size_t row_offset, size_t row_count,
                size_t col_offset, size_t col_count);
        Mat<T> &operator=(const Mat<T> &rhs);

        T &at(size_t r, size_t c, size_t ch);
        const T &at(size_t r, size_t c, size_t ch) const;

        Mat<T> clone() const;

        // read data from src
        void read(const T *src);
        // write data to dst
        void write(T *dst) const;

        const T *ptr(size_t r = 0) const
        {
            return raw_ptr() + r * m_step;
        }
        T *ptr(size_t r = 0)
        {
            return raw_ptr() + r * m_step;
        }
        size_t height() const
        {
            return rows();
        }
        size_t width() const
        {
            return cols();
        }
        size_t rows() const
        {
            return m_rows;
        }
        size_t cols() const
        {
            return m_cols;
        }
        size_t channels() const
        {
            return m_channels;
        }
        size_t step() const
        {
            return m_step;
        }
        size_t total_nr_elem() const
        {
            return rows() * cols() * channels();
        }
        size_t total_span_elem() const
        {
            return rows() * step();
        }
        bool equals(const Mat<T> &rhs) const;
        bool is_continuous() const;

		Size size() const { return {rows(), cols()}; }
		MatShape shape() const { return {rows(), cols(), channels()}; }
};

class Rect {
    public:
        size_t y, x, height, width;
        Rect(size_t _y, size_t _x, size_t _height, size_t _width):
            y(_y), x(_x), height(_height), width(_width)
        {}
        Rect():
            y(0), x(0), height(0), width(0)
        {}
};

template <class scalar_t>
struct Point {
	scalar_t x, y;

	Point() { }
	Point(scalar_t x, scalar_t y): x(x), y(y) { }

	Point operator + (const Point &rhs) const { return {x + rhs.x, y + rhs.y}; }
	Point operator - (const Point &rhs) const { return {x - rhs.x, y - rhs.y}; }
	Point operator * (scalar_t f) const { return {x * f, y * f}; }
	Point operator / (scalar_t f) const { return {x / f, y / f}; }
};


template <typename T>
std::ostream &operator<<(std::ostream &os, const Mat<T> &m);

// type aliases
using uchar = unsigned char;
using ushort = unsigned short;
using Mat8u = Mat<uchar>;
using Mat32f = Mat<float>;
using Mat64f = Mat<double>;

extern template class Mat<uchar>;
extern template class Mat<float>;
extern template class Mat<double>;
extern template class Mat<short>;
extern template class Mat<unsigned short>;
extern template
std::ostream &operator<<(std::ostream &os, const Mat<uchar> &m);
extern template
std::ostream &operator<<(std::ostream &os, const Mat<float> &m);
extern template
std::ostream &operator<<(std::ostream &os, const Mat<double> &m);

}
