#ifndef _MATH_ZASGEO_
#define _MATH_ZASGEO_



#include <math.h>

//#define EPSILION    1.0e-6f
//#define PI     3.1415926535897932384626433832795f
//#define HalfPI 1.5707963267948966192313216916398f
//#define TwoPI  2.0f*PI

constexpr float  EPSILION = 1.0e-6f;
constexpr float PI = 3.1415926535897932384626433832795f;
constexpr float HalfPI = 1.5707963267948966192313216916398f;
constexpr float TwoPI = 2.0f*PI;

namespace esm {


	/*
	temporary wrapping functions
	-----------------------------------------------------------------
	*/
	inline bool isZero(float val, float epsilion = EPSILION) noexcept
	{

		return (fabsf(val) <= epsilion);
	}

	inline bool areEqual(float a, float b, float epsilion = EPSILION) noexcept
	{

		return (fabsf(a-b) <= epsilion);
	}

	inline void SinCos(float a, float &sina, float &cosa) noexcept
	{


		sina = sinf(a);
		cosa = cosf(a);

	}

	/*constexpr*/ inline float sqrt(float val) noexcept
	{
		
		return sqrtf(val);
	}

	inline float  recipSqrt(float val) noexcept
	{

		return 1.0f / sqrt(val);

	}

	template<typename T>
	constexpr inline T pow2(T val) noexcept
	{

		return val * val;

	}

	/*
	------------------------------------------------------------------
	*/

	/*
	Returns pointer/iterator to a beggining of the nearest range defined by predicate.
	Predicate takes pointer/iterator.
	*/
	template<typename It, typename Pr>
	inline decltype(auto) binary_search_range(const It& _beg, const It& _end, Pr _pred) noexcept
	{

		It beg{ _beg };
		It end{ _end-1 };
		
		while (std::distance(beg, end)>1) {

			auto mid = beg + std::distance(beg, end) / 2;

			if (_pred(mid)) {

				end = mid;
			}
			else {

				beg = mid;
			}
		}

		return beg;

	}

	
}

#endif // !_MATH_ZASGEO_

