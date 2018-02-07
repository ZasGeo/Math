#ifndef _LIN_ALG_OPERATIONS_ZASGEO_
#define _LIN_ALG_OPERATIONS_ZASGEO_

#include "vector.h"
#include "matrix.h"

namespace esm {


	/*
	Lineary interpolates beetween A and B. If alpha is close to zero, then result is close to A, if alpha is close to one, then result is close to B.
	No restriction is aplied to alpha.
	*/
	template<typename pointType, typename floatingType>
	inline decltype(auto) lerp(const pointType& A, const pointType& B, const floatingType& alpha) noexcept
	{

		auto res{ A*(floatingType{ 1 }-alpha) + B * alpha };
		return res;
	}


	/*
	Lineary interpolates beetween set of given points based on time.
	Array of times must be sorted.
	No restriction is aplied to time.
	*/
	template<typename pointContainerType, typename timeContainerType, typename floatingType>
	decltype(auto) piecewiseLerp(const pointContainerType& points, const timeContainerType& times, const floatingType& time) noexcept
	{


		if (std::size(points) != std::size(times) || std::size(points) == 0) return vector<T, n>{T{ 0.0f }};

		auto cbeg = std::cbegin(times);
		auto cend = std::cend(times);
		auto rangeBeg = binary_search_range(cbeg, cend, [time](auto val) { return time < (*val); });

		floatingType alpha{ (time - (*rangeBeg)) / (*(rangeBeg + 1) - (*rangeBeg)) };

		auto pbeg = cbeg - rangeBeg;

		auto res{ lerp(points[pbeg], points[pbeg + 1], alpha) };

		return res;


	}


	//dot(left, right)=|left|*|right| *cos(left, right)
	template<typename T, std::size_t n>
	constexpr inline T dot(const vector<T, n>& left, const vector<T, n>& right) noexcept
	{
		constexpr std::size_t limit = n - 2;
		T res1{ 0 };
		T res2{ 0 };
		T res3{ 0 };
		std::size_t i{ 0 };
		
		for (; i < limit && limit<n; i+=3) {
			res1 += left[i] * right[i];
			res2 += left[i+1] * right[i+1];
			res3 += left[i+2] * right[i+2];
		}

		for (; i <n; ++i) {
			res1 += left[i] * right[i];
		}

		res1 += res2 + res3;
		return res1;

	}

	/*
	Returns part of vector V that is parrallel to vector W
	*/
	template<typename T, std::size_t n>
	constexpr inline vector<T, n> proj(const vector<T, n>& v, const vector<T, n>& w) noexcept
	{	 
		T lenSq = w.lenghtSquared();
		vec3 res{ (lenSq == 1.0f) ? dot(v, w)*w : ((dot(v, w)) / lenSq)*w };
		return res;
	}

	/*
	Returns part of vector V that is perpendicular to vector W
	*/
	template<typename T, std::size_t n>
	constexpr inline  vector<T, n> perp(const vector<T, n>& v, const vector<T, n>& w) noexcept
	{
		return v - proj(v, w);
	}

	/*
	Returns vector perpendicular to both
	*/
	template<typename T>
	constexpr inline  vector<T, 3> cross(const vector<T, 3>& left, const vector<T, 3>& right) noexcept
	{
		vector<T, 3> res{ left.y*right.z-right.y*left.z,  left.z*right.x- right.z*left.x, left.x*right.y - right.x*left.y };
		return res;
	}

	/*
	Returns transpose of square matrix n x n
	*/
	template<typename T, std::size_t m, std::size_t n>
	inline matrix<T, n, m> transpose(const matrix<T, m, n>& mat) noexcept
	{
		matrix<T, n, m> result;

		for (std::size_t row = 0; row < m; ++row)
			for(std::size_t col=0;col<n;++col) 
				result[row][col] = mat[col][row];

		return result;
	}

	


}

#endif // !_LIN_ALG_OPERATIONS_ZASGEO_

