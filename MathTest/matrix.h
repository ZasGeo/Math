#ifndef _LIN_ALG_MATRIX_ZASGEO_
#define _LIN_ALG_MATRIX_ZASGEO_


#include <array>
#include <algorithm>
#include "vector.h"



namespace esm {

	


	template<typename T, std::size_t m, std::size_t n>
	class matrix {

	public:
		union {


			std::array<T, m*n> data;


			vector<vector<T, m>, n> column;

		};


		/*
		/----------------------------------------/
		Use perfect forward constructor except any arg is the same type as constructed object.
		SFINAE.
		*/
		template<typename... Ts,
			typename = std::enable_if_t<!are_all_same<matrix<T, m,n>, std::decay_t<Ts>...>::value>
		>
			constexpr matrix(Ts&&... args) noexcept : data{ std::forward<Ts>(args)... } {}
		/*
		/----------------------------------------/
		*/

		constexpr matrix() noexcept {
		
			Zero();
		}


		constexpr matrix(const matrix& other) noexcept = default;

		matrix& operator=(const matrix& other) noexcept = default;

		matrix(matrix&& other) noexcept = default;

		matrix& operator=(matrix&& other) noexcept = default;

		matrix& operator+=(const matrix& other) noexcept
		{


			std::size_t i{ 0 };
			constexpr std::size_t limit = n - 4;

			for (; i < limit && n>limit; i += 5) {

				column[i] += other[i];
				column[i + 1] += other[i + 1];
				column[i + 2] += other[i + 2];
				column[i + 3] += other[i + 3];
				column[i + 4] += other[i + 4];
			}

			for (; i < n; ++i) {

				column[i] += other[i];

			}

			return *this;

		}

		matrix& operator-=(const matrix& other) noexcept
		{

			std::size_t i{ 0 };
			/*constexpr std::size_t limit = n - 4;

			for (; i < limit && n>limit; i += 5) {

				column[i] -= other[i];
				column[i + 1] -= other[i + 1];
				column[i + 2] -= other[i + 2];
				column[i + 3] -= other[i + 3];
				column[i + 4] -= other[i + 4];
			}*/

			for (; i < n; ++i) {

				column[i] -= other[i];

			}

			return *this;
		}

		matrix& operator*=(const matrix& other) noexcept
		{

			constexpr std::size_t limit = rows - 2;

			matrix<T, rows, cols> res;

			for (std::size_t j{ 0 }; j < cols; ++j) {

				for (std::size_t k{ 0 }; k < n; ++k) {
					auto tmp = right[j][k];
					std::size_t i{ 0 };
					for (; i < limit && limit < rows; i += 3) {

						res[j][i] += tmp * left[k][i];
						res[j][i + 1] += tmp * left[k][i + 1];
						res[j][i + 2] += tmp * left[k][i + 2];

					}

					for (; i < rows; ++i) {

						res[j][i] += tmp * left[k][i];

					}
				}
			}
			(*this) = res;

			return *this;
		}

		vector<T, m> operator*(const vector<T, n>& vec) const noexcept
		{

			constexpr std::size_t limit = n - 2;
			vector<T, m> result{ T{ 0 } };


			for (std::size_t j{ 0 }; j < m; ++j) {
				auto tmp = vec[j];
				std::size_t row{ 0 };
				for (; row < limit && limit<n; row += 3) {
					result[row] += mat[j][row] * tmp;
					result[row + 1] += mat[j][row + 1] * tmp;
					result[row + 2] += mat[j][row + 2] * tmp;
				}
				for (; row < n; ++row) {
					result[row] += mat[j][row] * tmp;
				}
			}

			return result;

		}

		vector<T, m>& operator[](std::size_t index) noexcept
		{

			return column[index];
		}


		const vector<T, m>& operator[](std::size_t index) const  noexcept
		{

			return column[index];
		}

		void Identity() noexcept
		{


			/*constexpr std::size_t limit = m - 4;

			for (std::size_t j = 0; j < n; ++j) {

				std::size_t i{ 0 };

				for (; i<limit && m>limit; i += 5) {

					column[j][i] = (j == i) ? T{ 1 } : T{ 0 };
					column[j][i + 1] = (j == i + 1) ? T{ 1 } : T{ 0 };
					column[j][i + 2] = (j == i + 2) ? T{ 1 } : T{ 0 };
					column[j][i + 3] = (j == i + 3) ? T{ 1 } : T{ 0 };
					column[j][i + 4] = (j == i + 4) ? T{ 1 } : T{ 0 };
				}
				for (; i < m; ++i) {
					column[j][i] = (j == i) ? T{ 1 } : T{ 0 };
				}
			}*/

			for (std::size_t j = 0; j < n; ++j) {

				for (std::size_t i{ 0 }; i<m ; ++i) {

					column[j][i] = (j == i) ? T{ 1 } : T{ 0 };
				}
			}

		}

		void Zero() noexcept 
		{

			constexpr std::size_t size = n * m;
			constexpr std::size_t limit = size - 4;
			std::size_t i{ 0 };

			for (; i < limit && size>limit; i += 5) {

				data[i] = T(0.0f);
				data[i + 1] = T(0.0f);
				data[i + 2] = T(0.0f);
				data[i + 3] = T(0.0f);
				data[i + 4] = T(0.0f);

			}

			for (; i < n; ++i) {

				data[i] = T(0.0f);

			}



		}
	};

		
				
	
	template<typename T>
	class matrix<T, 3, 3> {

	public:

		static  const matrix<T, 3, 3> ident;

		union {

			std::array<T, 9> data;

			vector<vector<T, 3>, 3> column;

		};

		template<typename... Ts,
			typename = std::enable_if_t<!are_all_same<matrix<T, 3, 3>, std::decay_t<Ts>...>::value>
		>
			constexpr matrix(Ts&&... args) noexcept : data{ std::forward<Ts>(args)... } {}

		constexpr matrix() noexcept : column{ T{0} } {};

		constexpr matrix(const vector<T, 3>& i, const vector<T, 3>& j, const vector<T, 3>& k ) noexcept
			:column{i, j,k}	{}


		constexpr matrix(const matrix& other) noexcept = default;

		matrix& operator=(const matrix& other) noexcept = default;

		matrix(matrix&& other) noexcept = default;

		matrix& operator=(matrix&& other) noexcept = default;

		vector<T, 3>& operator[](std::size_t index) noexcept
		{

			return column[index];
		}


		const vector<T, 3>& operator[](std::size_t index) const  noexcept
		{

			return column[index];
		}

		matrix& operator+=(const matrix& other) noexcept
		{

			column[0] += other[0];
			column[1] += other[1];
			column[2] += other[2];
			return *this;

		}

		matrix& operator-=(const matrix& other) noexcept
		{

			column[0] -= other[0];
			column[1] -= other[1];
			column[2] -= other[2];
			return *this;

		}

		matrix& operator*=(const matrix& other) noexcept
		{

			matrix res;
			auto tmp = other[0][0];
			res[0][0] += tmp * column[0][0];
			res[0][1] += tmp * column[0][1];
			res[0][2] += tmp * column[0][2];
			tmp = other[0][1];
			res[0][0] += tmp * column[1][0];
			res[0][1] += tmp * column[1][1];
			res[0][2] += tmp * column[1][2];
			tmp = other[0][2];
			res[0][0] += tmp * column[2][0];
			res[0][1] += tmp * column[2][1];
			res[0][2] += tmp * column[2][2];

			tmp = other[1][0];
			res[1][0] += tmp * column[0][0];
			res[1][1] += tmp * column[0][1];
			res[1][2] += tmp * column[0][2];
			tmp = other[1][1];
			res[1][0] += tmp * column[1][0];
			res[1][1] += tmp * column[1][1];
			res[1][2] += tmp * column[1][2];
			tmp = other[1][2];
			res[1][0] += tmp * column[2][0];
			res[1][1] += tmp * column[2][1];
			res[1][2] += tmp * column[2][2];
		

			tmp = other[2][0];
			res[2][0] += tmp * column[0][0];
			res[2][1] += tmp * column[0][1];
			res[2][2] += tmp * column[0][2];
			tmp = other[2][1];
			res[2][0] += tmp * column[1][0];
			res[2][1] += tmp * column[1][1];
			res[2][2] += tmp * column[1][2];
			tmp = other[2][2];
			res[2][0] += tmp * column[2][0];
			res[2][1] += tmp * column[2][1];
			res[2][2] += tmp * column[2][2];
		
			(*this) = res;
			return *this;

		}

		vector<T,3> operator*(const vector<T, 3>& vec) const noexcept
		{
			vector<T, 3> res{ T{0} };

			auto tmp = vec[0];
			res[0] += tmp * column[0][0];
			res[1] += tmp * column[0][1];
			res[2] += tmp * column[0][2];
			tmp = vec[1];
			res[0] += tmp * column[1][0];
			res[1] += tmp * column[1][1];
			res[2] += tmp * column[1][2];
			tmp = vec[2];
			res[0] += tmp * column[2][0];
			res[1] += tmp * column[2][1];
			res[2] += tmp * column[2][2];

			return res;

		}

		void Zero() noexcept 
		{
			
			column[0] = T{ 0 };
			column[1] = T{ 0 };
			column[2] = T{ 0 };

		}

		void Identity() noexcept
		{

			*this = ident;

		}

	};

	template<typename T>
	const matrix<T, 3, 3> matrix<T, 3, 3>::ident(

		T{ 1 }, T{ 0 }, T{ 0 }, 
		T{ 0 }, T{ 1 }, T{ 0 }, 
		T{ 0 }, T{ 0 }, T{ 1 }

	);

	
	/*
	Specializasion for 4x4 matrix
	*/
	template<typename T>
	class matrix<T, 4,4> {

	public:

		static const matrix<T, 4, 4> ident;
			
		

		union {


			std::array<T, 16> data;


			vector<vector<T, 4>, 4> column;

		};

		template<typename... Ts,
			typename = std::enable_if_t<!are_all_same<matrix<T, 4, 4>, std::decay_t<Ts>...>::value>
		>
			constexpr matrix(Ts&&... args) noexcept : data{ std::forward<Ts>(args)... } {}

		constexpr matrix() noexcept : column{ T{0} } {	}

		matrix(const vector<T, 3>& i, const vector<T, 3>& j, const vector<T, 3>& k) 
			: column{ {i, T{ 0.0f } }, { j, T{ 0 } }, { k, T{ 0 } }, { T{ 0 },T{ 0 },T{ 0 }, T{ 1 } } }	{}

		matrix(const matrix<T, 3, 3>& mat3) noexcept : 
			column{ {mat3[0],T{ 0 } }, { mat3[1],T{ 0 } }, { mat3[2],T{ 0 } }, { T{ 0.0f },T{ 0 },T{ 0 }, T{ 1 } } } {}
			
		constexpr matrix(const matrix& other) noexcept = default;

		matrix& operator=(const matrix& other) noexcept = default;

		matrix(matrix&& other) noexcept = default;

		matrix& operator=(matrix&& other) noexcept = default;


		matrix& operator+=(const matrix& other) noexcept 
		{


			column[0] += other[0];
			column[1] += other[1];
			column[2] += other[2];
			column[3] += other[4];

			return *this;

		}

		matrix& operator-=(const matrix& other) noexcept 
		{


			column[0] -= other[0];
			column[1] -= other[1];
			column[2] -= other[2];
			column[3] -= other[4];

			return *this;

		}

		constexpr matrix& operator*=(const matrix& other) noexcept
		{

			matrix res;
			auto tmp = other[0][0];
			res[0][0] += tmp * column[0][0];
			res[0][1] += tmp * column[0][1];
			res[0][2] += tmp * column[0][2];
			res[0][3] += tmp * column[0][3];
			tmp = other[0][1];
			res[0][0] += tmp * column[1][0];
			res[0][1] += tmp * column[1][1];
			res[0][2] += tmp * column[1][2];
			res[0][3] += tmp * column[1][3];
			tmp = other[0][2];
			res[0][0] += tmp * column[2][0];
			res[0][1] += tmp * column[2][1];
			res[0][2] += tmp * column[2][2];
			res[0][3] += tmp * column[2][3];
			tmp = other[0][3];
			res[0][0] += tmp * column[3][0];
			res[0][1] += tmp * column[3][1];
			res[0][2] += tmp * column[3][2];
			res[0][3] += tmp * column[3][3];

			tmp = other[1][0];
			res[1][0] += tmp * column[0][0];
			res[1][1] += tmp * column[0][1];
			res[1][2] += tmp * column[0][2];
			res[1][3] += tmp * column[0][3];
			tmp = other[1][1];
			res[1][0] += tmp * column[1][0];
			res[1][1] += tmp * column[1][1];
			res[1][2] += tmp * column[1][2];
			res[1][3] += tmp * column[1][3];
			tmp = other[1][2];
			res[1][0] += tmp * column[2][0];
			res[1][1] += tmp * column[2][1];
			res[1][2] += tmp * column[2][2];
			res[1][3] += tmp * column[2][3];
			tmp = other[1][3];
			res[1][0] += tmp * column[3][0];
			res[1][1] += tmp * column[3][1];
			res[1][2] += tmp * column[3][2];
			res[1][3] += tmp * column[3][3];

			tmp = other[2][0];
			res[2][0] += tmp * column[0][0];
			res[2][1] += tmp * column[0][1];
			res[2][2] += tmp * column[0][2];
			res[2][3] += tmp * column[0][3];
			tmp = other[2][1];
			res[2][0] += tmp * column[1][0];
			res[2][1] += tmp * column[1][1];
			res[2][2] += tmp * column[1][2];
			res[2][3] += tmp * column[1][3];
			tmp = other[2][2];
			res[2][0] += tmp * column[2][0];
			res[2][1] += tmp * column[2][1];
			res[2][2] += tmp * column[2][2];
			res[2][3] += tmp * column[2][3];
			tmp = other[2][3];
			res[2][0] += tmp * column[3][0];
			res[2][1] += tmp * column[3][1];
			res[2][2] += tmp * column[3][2];
			res[2][3] += tmp * column[3][3];

			tmp = other[3][0];
			res[3][0] += tmp * column[0][0];
			res[3][1] += tmp * column[0][1];
			res[3][2] += tmp * column[0][2];
			res[3][3] += tmp * column[0][3];
			tmp = other[3][1];
			res[3][0] += tmp * column[1][0];
			res[3][1] += tmp * column[1][1];
			res[3][2] += tmp * column[1][2];
			res[3][3] += tmp * column[1][3];
			tmp = other[3][2];
			res[3][0] += tmp * column[2][0];
			res[3][1] += tmp * column[2][1];
			res[3][2] += tmp * column[2][2];
			res[3][3] += tmp * column[2][3];
			tmp = other[3][3];
			res[3][0] += tmp * column[3][0];
			res[3][1] += tmp * column[3][1];
			res[3][2] += tmp * column[3][2];
			res[3][3] += tmp * column[3][3];

			(*this) = res;
			return *this;

		}

		constexpr vector<T, 4> operator*(const vector<T, 4>& vec) const noexcept
		{
			vector<T, 4> res{ T{ 0 } };

			auto tmp = vec[0];
			res[0] += tmp * column[0][0];
			res[1] += tmp * column[0][1];
			res[2] += tmp * column[0][2];
			res[3] += tmp * column[0][3];
			tmp = vec[1];
			res[0] += tmp * column[1][0];
			res[1] += tmp * column[1][1];
			res[2] += tmp * column[1][2];
			res[3] += tmp * column[1][3];
			tmp = vec[2];
			res[0] += tmp * column[2][0];
			res[1] += tmp * column[2][1];
			res[2] += tmp * column[2][2];
			res[3] += tmp * column[2][3];
			tmp = vec[3];
			res[0] += tmp * column[3][0];
			res[1] += tmp * column[3][1];
			res[2] += tmp * column[3][2];
			res[3] += tmp * column[3][3];

			return res;

		}

		constexpr vector<T, 4>& operator[](std::size_t index) noexcept
		{

			return column[index];
		}


		constexpr const vector<T, 4>& operator[](std::size_t index) const  noexcept
		{

			return column[index];
		}


		void Zero() noexcept
		{

			column[0] = T{ 0 };
			column[1] = T{ 0 };
			column[2] = T{ 0 };
			column[3] = T{ 0 };

		}

		void Identity() noexcept
		{

			*this = ident;

		}

	};


	template<typename T>
	const matrix<T, 4, 4> matrix<T, 4, 4>::ident (

		T{ 1 }, T{ 0 }, T{ 0 }, T{ 0 },
		T{ 0 }, T{ 1 }, T{ 0 }, T{ 0 },
		T{ 0 }, T{ 0 }, T{ 1 }, T{ 0 },
		T{ 0 }, T{ 0 }, T{ 0 }, T{ 1 }

	);


	using mat2 = matrix<float, 2, 2>;
	using mat3 = matrix<float, 3, 3>;
	using mat4 = matrix<float, 4, 4>;



	template<typename T, std::size_t m, std::size_t n>
	inline matrix<T, m, n> operator+(const matrix<T, m, n>& left, const matrix<T, m, n>& right) noexcept
	{

		matrix<T, m, n> result{ left };
		result += right;
		return result;
		
	}

	template<typename T, std::size_t m, std::size_t n>
	inline matrix<T, m, n> operator-(const matrix<T, m, n>& left, const matrix<T, m, n>& right) noexcept
	{


		matrix<T, m, n> result{ left };
		result -= right;
		return result;

	}


	/*template<typename T, std::size_t m, std::size_t n>
	inline vector<T, m> operator*(const matrix<T, m, n>& mat, const vector<T, n>& vec) noexcept
	{

		constexpr std::size_t limit =n - 2;
		vector<T, m> result{ T{0} };

		
		for (std::size_t j{0}; j < m; ++j) {
			auto tmp = vec[j];
			std::size_t row{ 0 };
			for (; row < limit && limit<n; row+=3) {
				result[row] += mat[j][row] * tmp;
				result[row+1] += mat[j][row+1] * tmp;
				result[row+2] += mat[j][row+2] * tmp;
			}
			for (; row < n; ++row ) {
				result[row] += mat[j][row] * tmp;
			}
		}
		
		return result;

	}*/


	template<typename T, std::size_t rows, std::size_t n, std::size_t cols>
	inline matrix<T, rows, cols> operator*(const matrix<T, rows, n>& left,const matrix<T, n, cols>& right) noexcept
	{

		/*constexpr std::size_t limit = rows - 2;

		matrix<T, rows, cols> res;

		for (std::size_t j{ 0 }; j < cols; ++j) {

			for (std::size_t k{ 0 }; k < n; ++k) {
				auto tmp = right[j][k];
				std::size_t i{ 0 };
				for (; i < limit && limit < rows; i+=3) {

					res[j][i] += tmp *left[k][i];
					res[j][i+1] += tmp * left[k][i+1];
					res[j][i+2] += tmp * left[k][i+2];

				}

				for (; i < rows; ++i) {

					res[j][i] += tmp * left[k][i];

				}
			}
		}*/

	
		matrix<T, rows, cols> res{ left };
		res *= right;
		return res;

	}



	
}

#endif