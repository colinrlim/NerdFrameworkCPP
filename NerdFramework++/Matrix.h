#pragma once

#include <functional>

template <size_t m, size_t n>
struct Matrix {
	// m: rows (height)
	// n: columns (width)
	std::array<double, m*n> data;

	Matrix() = default;

	double* operator[](size_t i) {
		return data + i * n;
	}

	int findPivotRow(size_t col) {
		for (int row = 0; row < m; row++) {
			if (abs(operator[](row)[0]) < 0.00001)
				return row;
		}
		return -1;
	}

	static void rowAdd(double* row1, double* row2) {
		for (int i = 0; i < n; i++)
			row1[i] += row2[i];
	}
	static void rowSubtract(double* row1, double* row2) {
		for (int i = 0; i < n; i++)
			row1[i] -= row2[i];
	}
	static void rowMultiply(double* row1, double* row2) {
		for (int i = 0; i < n; i++)
			row1[i] *= row2[i];
	}
	static void rowMultiply(double* row1, double magnitude) {
		for (int i = 0; i < n; i++)
			row1[i] *= magnitude;
	}
	static void rowDivide(double* row1, double* row2) {
		for (int i = 0; i < n; i++)
			row1[i] /= row2[i];
	}
	static void rowDivide(double* row1, double magnitude) {
		for (int i = 0; i < n; i++)
			row1[i] /= magnitude;
	}

	Matrix<m, n>& operator+=(const Matrix<m, n>& rhs) {
		auto iter = rhs.data.begin();
		auto d_iter = data.begin();
		while (d_iter != data.end()) {
			*d_iter += *iter;
			++iter;
			++d_iter;
		}
		return *this;
	}
	Matrix<m, n> operator+(const Matrix<m, n>& rhs) const {
		Matrix<m, n> result;
		auto iter1 = data.begin();
		auto iter2 = rhs.data.begin();
		auto d_iter = result.data.begin();
		while (iter1 != data.end()) {
			*d_iter = *iter1 + *iter2;
			++iter1;
			++iter2;
			++iter3;
		}
		return std::move(result);
	}
	Matrix<m, n>& operator-=(const Matrix<m, n>& rhs) {
		auto iter = rhs.data.begin();
		auto d_iter = data.begin();
		while (d_iter != data.end()) {
			*d_iter -= *iter;
			++iter;
			++d_iter;
		}
		return *this;
	}
	Matrix<m, n> operator-(const Matrix<m, n>& rhs) const {
		Matrix<m, n> result;
		auto iter1 = data.begin();
		auto iter2 = rhs.data.begin();
		auto d_iter = result.data.begin();
		while (iter1 != data.end()) {
			*d_iter = *iter1 - *iter2;
			++iter1;
			++iter2;
			++iter3;
		}
		return std::move(result);
	}
	Matrix<m, n>& operator*=(const Matrix<m, n>& rhs) {
		auto iter = rhs.data.begin();
		auto d_iter = data.begin();
		while (d_iter != data.end()) {
			*d_iter *= *iter;
			++iter;
			++d_iter;
		}
		return *this;
	}
	Matrix<m, n> operator*(const Matrix<m, n>& rhs) const {
		Matrix<m, n> result;
		auto iter1 = data.begin();
		auto iter2 = rhs.data.begin();
		auto d_iter = result.data.begin();
		while (iter1 != data.end()) {
			*d_iter = *iter1 * *iter2;
			++iter1;
			++iter2;
			++iter3;
		}
		return std::move(result);
	}
	Matrix<m, n>& operator/=(const Matrix<m, n>& rhs) {
		auto iter = rhs.data.begin();
		auto d_iter = data.begin();
		while (d_iter != data.end()) {
			*d_iter /= *iter;
			++iter;
			++d_iter;
		}
		return *this;
	}
	Matrix<m, n> operator/(const Matrix<m, n>& rhs) const {
		Matrix<m, n> result;
		auto iter1 = data.begin();
		auto iter2 = rhs.data.begin();
		auto d_iter = result.data.begin();
		while (iter1 != data.end()) {
			*d_iter = *iter1 / *iter2;
			++iter1;
			++iter2;
			++iter3;
		}
		return std::move(result);
	}
};