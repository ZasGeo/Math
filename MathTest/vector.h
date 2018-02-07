#ifndef _LIN_ALG_VECTOR_ZASGEO_
#define _LIN_ALG_VECTOR_ZASGEO_

#include <array>
#include "metaprog.h"
#include "math.h"



namespace esm {

	
	/*
	
	n-dimensional vector template
	
	*/
	template<typename T, std::size_t n> 
	class vector {

	public:

		std::array<T, n> data;

		
		/*
		/----------------------------------------/
		Use perfect forward constructor except any arg is the same type as constructed object.
		SFINAE.
		*/
		template<typename... Ts,
			typename = std::enable_if_t<!are_all_same<vector<T, n>, std::decay_t<Ts>...>::value && count<Ts...>::value-1>
		>
		constexpr vector(Ts&&... args) noexcept : data{ std::forward<Ts>(args)... } {}
		/*
		/----------------------------------------/
		*/

		vector(const T& arg) noexcept 
		{
			for (std::size_t i{ 0 }; i < n; ++i)
				data[i] = arg;
		}

		constexpr vector() noexcept = default;

		constexpr vector(const vector &other) noexcept = default;

		vector(vector &&other) noexcept = default;

		vector& operator=(const vector &other) noexcept = default;
		
		vector& operator=(vector &&other) noexcept = default;
		
		constexpr const T& operator[](std::size_t index) const noexcept
		{

			return data[index];
			
		}

		constexpr T& operator[](std::size_t index) noexcept
		{

			return data[index];

		}

		/*
		Want to implement compile time cycle via metaprogramming someday
		--------------------------------------------------------
		*/
		vector& operator+=(const vector &other) noexcept
		{

			std::size_t i{ 0 };
			constexpr std::size_t limit = n - 4;

			for (; i < limit && n>limit; i += 5) {

				data[i] += other[i];
				data[i+1] += other[i + 1];
				data[i+2] += other[i + 2];
				data[i+3] += other[i + 3];
				data[i+4] += other[i + 4];
			}

			for (; i < n; ++i ) {

				data[i] += other[i];
				
			}

			return *this;

		}

		vector& operator-=(const vector &other) noexcept
		{

			std::size_t i{ 0 };
			constexpr std::size_t limit = n - 4;

			for (; i < limit && n>limit; i += 5) {
				data[i] -= other[i];
				data[i + 1] -= other[i + 1];
				data[i + 2] -= other[i + 2];
				data[i + 3] -= other[i + 3];
				data[i + 4] -= other[i + 4];
			}

			for (; i < n; ++i) {

				data[i] -= other[i];

			}
			return *this;

		}

		vector& operator*=(const vector &other) noexcept
		{

			std::size_t i{ 0 };
			constexpr std::size_t limit = n - 4;

			for (; i < limit && n>limit; i += 5) {
				data[i] *= other[i];
				data[i + 1] *= other[i + 1];
				data[i + 2] *= other[i + 2];
				data[i + 3] *= other[i + 3];
				data[i + 4] *= other[i + 4];
			}

			for (; i < n; ++i) {

				data[i] *= other[i];

			}

			return *this;

		}

		vector& operator/=(const vector &other) noexcept
		{

			std::size_t i{ 0 };
			constexpr std::size_t limit = n - 4;

			for (; i < limit && n>limit; i += 5) {
				data[i] /= other[i];
				data[i + 1] /= other[i + 1];
				data[i + 2] /= other[i + 2];
				data[i + 3] /= other[i + 3];
				data[i + 4] /= other[i + 4];
			}

			for (; i < n; ++i) {

				data[i] /= other[i];

			}
			return *this;

		}

		vector& operator+=(const T &other) noexcept
		{

			std::size_t i{ 0 };
			constexpr std::size_t limit = n - 4;

			for (; i < limit && n>limit; i += 5) {
				data[i] += other;
				data[i + 1] += other;
				data[i + 2] += other;
				data[i + 3] += other;
				data[i + 4] += other;
			}

			for (; i < n; ++i) {

				data[i] += other;

			}
			return *this;

		}

		vector& operator-=(const T &other) noexcept
		{

			std::size_t i{ 0 };
			constexpr std::size_t limit = n - 4;

			for (; i < limit && n>limit; i += 5) {
				data[i] -= other;
				data[i + 1] -= other;
				data[i + 2] -= other;
				data[i + 3] -= other;
				data[i + 4] -= other;
			}

			for (; i < n; ++i) {

				data[i] -= other;

			}
			return *this;

		}

		vector& operator*=(const T &other) noexcept
		{

			std::size_t i{ 0 };
			constexpr std::size_t limit = n - 4;

			for (; i < limit && n>limit; i += 5) {
				data[i] *= other;
				data[i + 1] *= other;
				data[i + 2] *= other;
				data[i + 3] *= other;
				data[i + 4] *= other;
			}

			for (; i < n; ++i) {

				data[i] *= other;

			}
			return *this;

		}

		vector& operator/=(const T &other) noexcept
		{

			
			T recip{ T{1} / other };

			(*this )*= (recip);
			
			return *this;

		}

		vector<T, n> operator-() const noexcept
		{

			vector<T, n> result;

			std::size_t i{ 0 };
			constexpr std::size_t limit = n - 4;

			for (; i < limit && n>limit; i += 5) {
				result[i] = -data[i];
				result[i + 1] = -data[i+1];
				result[i + 2] = -data[i+2];
				result[i + 3] = -data[i+3];
				result[i + 4] = -data[i+4];
			}

			for (; i < n; ++i) {

				result[i] = -data[i];

			}
			return result;

		}

		T lenghtSquared() const noexcept
		{

			T res1{ 0 };
			T res2{ 0 };
			T res3{ 0 };
			T res4{ 0 };
			T res5{ 0 };

			std::size_t i{ 0 };
			constexpr std::size_t limit = n - 4;

			for (; i < limit && n>limit; i += 5) {
				
				
				res1 += pow2(data[i]);
				res2 += pow2(data[i+1]);
				res3 += pow2(data[i+2]);
				res4 += pow2(data[i+3]);
				res5 += pow2(data[i+4]);

			}
			for (; i < n; ++i) {

				res1 += pow2(data[i]);

			}

			res1 += res2 + (res3 + (res4+res5));
			return res1;

		}
		/*
		--------------------------------------------------------
		*/

		T Lenght() const noexcept
		{

			return sqrt(lenghtSquared());
			

		}

		vector<T, n>& Normilize() noexcept
		{

			T len= Lenght();
			(*this) /= len;
			return *this;

		}

	};

	
	
	/*
	
	
	2-dimensional vector template specialization
	
	
	*/
	template<typename T>
	class vector<T, 2> {

	public:

		/*
		to access data by different names
		*/
		union {
		
			std::array<T, 2> data;
		
			struct {

				T x;
				T y;
			};
			struct {

				T u;
				T v;
			};
			struct {

				T s;
				T t;
			};

		};
	
		constexpr vector() noexcept = default;

		constexpr vector(const T& arg) noexcept : data{{arg, arg}} {}

		constexpr vector(const T& _x, const T& _y) noexcept : x{ _x }, y{ _y } {}

		constexpr vector(const vector& other) noexcept = default;

		vector& operator=(const vector &other) noexcept = default;

		vector(vector&& other) noexcept = default;

		vector& operator=(vector &&other) noexcept = default;

		vector& operator=(const T& arg) noexcept 
		{
			
			x = arg;
			y = arg;
			return *this;
		}

		constexpr T& operator[](std::size_t index) noexcept
		{

			
			return data[index];
			
		}

		constexpr const T& operator[](std::size_t index)  const noexcept
		{

			return data[index];
			
		}

		vector& operator+=(const vector &other) noexcept 
		{

			x += other.x;
			y += other.y;
			return *this;

		}

		vector& operator-=(const vector &other) noexcept 
		{

			x -= other.x;
			y -= other.y;
			return *this;

		}

		vector& operator*=(const vector &other) noexcept
		{

			x *= other.x;
			y *= other.y;
			return *this;

		}

		vector& operator/=(const vector &other) noexcept
		{

			x /= other.x;
			y /= other.y;
			return *this;

		}

		vector& operator+=(const T &other) noexcept
		{

			x += other;
			y += other;
			return *this;

		}

		vector& operator-=(const T &other) noexcept 
		{

			x -= other;
			y -= other;
			return *this;

		}

		vector& operator*=(const T &other) noexcept 
		{

			x *= other;
			y *= other;
			return *this;

		}

		vector& operator/=(const T &other) noexcept 
		{


			T recip{ T{1} / other };
			x *= recip;
			y *= recip;
			return *this;

		}

		constexpr T lenghtSquared() const noexcept 
		{

			
			return x*x+y*y;
			

		}

		/*constexpr*/ T Lenght() const noexcept 
		{

			return sqrt(lenghtSquared());


		}

		vector& Normilize() noexcept {

			T len = Lenght();
			T recipLen = 1 / len;
			x *= recipLen;
			y *= recipLen;
			return *this;

		}
		
		vector operator-() const noexcept 
		{
		
			return vector{ -x, -y };

		}

	};


	/*


	3-dimensional vector template specialization


	*/
	template<typename T>
	class vector<T, 3> {

	public:

		union {

			std::array<T, 3> data;

			struct {

				T x;
				T y;
				T z;
			};
			struct {

				T r;
				T g;
				T b;
			};
			struct {

				T s_T;
				T t_T;
				T r_T;
			};
			struct {

				vector<T, 2> xy;
				T z;
			};
			struct {

				T x;
				vector<T, 2> yz;
				
			};
						

		};
		//union end

		
		constexpr vector() noexcept = default;

		constexpr vector(const T& arg) noexcept : data{ { arg, arg,arg } } {}
		
		constexpr vector(const T& x, const T& y, const T& z) noexcept : data{ { x,y,z } } {}

		constexpr vector(const vector<T,2> &xy, const T& z) noexcept :xy{xy}, z{z} {}

		constexpr vector(const T &x, const vector<T, 2> &yz) noexcept :x{ x }, yz{ yz } {}

		constexpr vector(const vector& other) noexcept = default;

		vector& operator=(const vector &other) noexcept = default;

		vector(vector&& other) noexcept = default;

		vector& operator=(vector &&other) noexcept = default;
		
		vector& operator=(const T& arg) noexcept
		{

			x = arg;
			y = arg;
			z = arg;
			return *this;
		}

		constexpr T& operator[](std::size_t index) noexcept 
		{

			return data[index];
			
		}

		constexpr const T& operator[](std::size_t index)  const noexcept 
		{

			return data[index];
		}
		
		vector& operator+=(const vector &other) noexcept 
		{

			x += other.x;
			y += other.y;
			z += other.z;
			return *this;

		}

		vector& operator-=(const vector &other) noexcept
		{

			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;

		}

		vector& operator*=(const vector &other) noexcept 
		{

			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;

		}

		vector& operator/=(const vector &other) noexcept 
		{

			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;

		}

		vector& operator+=(const T &other) noexcept
		{

			x += other;
			y += other;
			z += other;
			return *this;

		}

		vector& operator-=(const T &other) noexcept 
		{

			x -= other;
			y -= other;
			z -= other;
			return *this;

		}

		vector& operator*=(const T &other) noexcept 
		{

			x *= other;
			y *= other;
			z *= other;
			return *this;

		}

		vector& operator/=(const T &other) noexcept 
		{

			T recip = T{ 1 } / other;
			x *= recip;
			y *= recip;
			z *= recip;
			return *this;

		}

		constexpr T lenghtSquared()  const noexcept
		{


			return x*x + y*y + z*z;

		}

		/*constexpr*/ T lenght()  const noexcept
		{

			return sqrt(lenghtSquared());


		}

		vector& Normilize() noexcept
		{

			T len = lenght();
			T recipLen = T{ 1 } / len;
			x *= recipLen;
			y *= recipLen;
			z *= recipLen;
			return *this;

		}

		vector operator-() const noexcept
		{



			return vector{ -x, -y,-z };

		}

	};


	
	/*


	4-dimensional vector template specialization


	*/
	template<typename T>
	class vector<T, 4> {

	public:

		union {

			std::array<T, 4> data;

			struct {

				T x;
				T y;
				T z;
				T w;
			};
			struct {

				T r;
				T g;
				T b;
				T a;
			};
			struct {

				vector<T, 2> xy;
				T z;
				T w;
			};
			struct {

				T x;
				vector<T, 2> yz;
				T w;

			};
			struct {

				vector<T, 3> xyz;
				T w;

			};


		};
		

		constexpr vector() noexcept = default;

		constexpr vector(const T& arg) noexcept : data{ { arg, arg,arg,arg } } {}

		constexpr vector(const T& x, const T& y, const T& z, const T& w) noexcept : data{ { x,y,z,w} } {}

		constexpr vector(const vector<T, 2> &xy, const T& z, const T& w) noexcept :xy{ xy }, z{ z }, w{ w } {}

		constexpr vector(const T &x, const vector<T, 2> &yz, const T& w) noexcept :x{ x }, yz{ yz }, w{ w } {}

		constexpr vector(const vector<T, 3> &xyz, const T& w) noexcept : xyz{ xyz }, w{ w } {}

		constexpr vector(const vector& other) noexcept = default;

		vector& operator=(const vector &other) noexcept = default;

		vector& operator=(const T& arg) noexcept
		{

			x = arg;
			y = arg;
			z = arg;
			w = arg;
			return *this;

		}

		constexpr T& operator[](std::size_t index) noexcept 
		{

			return data[index];
		
		}

		constexpr const T& operator[](std::size_t index) const noexcept 
		{

			return data[index];
		
		}

		vector& operator+=(const vector &other) noexcept 
		{

			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;

		}

		vector& operator-=(const vector &other) noexcept 
		{

			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;

		}

		vector& operator*=(const vector &other) noexcept 
		{

			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
			return *this;

		}

		vector& operator/=(const vector &other) noexcept 
		{

			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
			return *this;

		}

		vector& operator+=(const T &other) noexcept
		{

			x += other;
			y += other;
			z += other;
			w += other;
			return *this;

		}

		vector& operator-=(const T &other) noexcept
		{

			x -= other;
			y -= other;
			z -= other;
			w -= other;
			return *this;

		}

		vector& operator*=(const T &other) noexcept 
		{

			x *= other;
			y *= other;
			z *= other;
			w *= other;
			return *this;

		}

		vector& operator/=(const T &other) noexcept
		{

			T recip{ T{1} / other };
			x *= recip;
			y *= recip;
			z *= recip;
			w *= recip;
			return *this;

		}


		constexpr T lenghtSquared() const noexcept 
		{


			return x*x + y*y + z*z + w*w;

		}

		/*constexpr*/ T lenght() const noexcept 
		{

			return sqrt(lenghtSquared());

		}

		vector& Normilize() noexcept 
		{

			T len = lenght();
			T recipLen = T{ 1 } / len;
			x *= recipLen;
			y *= recipLen;
			z *= recipLen;
			w *= recipLen;
			return *this;

		}

		vector operator-() const noexcept
		{

			return vector{ -x, -y,-z, -w };

		}

	};

	using vec2 = vector<float, 2>;
	using vec3 = vector<float, 3>;
	using vec4 = vector<float, 4>;

	/*
	additions
	---------------------------------------------------------------------------------------
	*/
	template<typename T, std::size_t n>
	constexpr inline vector<T, n> operator+(const vector<T,n> &left,const vector<T,n> &right) noexcept 
	{
		vector<T, n> res{ left };
		res += right;
		return res;
	}

	template<typename T, std::size_t n>
	constexpr inline vector<T, n> operator+(const vector<T, n> &left, const T &right) noexcept
	{
		vector<T, n> res{ left };
		res += right;
		return res;
	}

	template<typename T, std::size_t n>
	constexpr inline vector<T, n> operator+(const T &left, const vector<T, n> &right) noexcept 
	{
		vector<T, n> res{ right };
		res += left;
		return res;
	}
	/*
	---------------------------------------------------------------------------------------
	*/

	/*
	substructions
	---------------------------------------------------------------------------------------
	*/
	template<typename T, std::size_t n>
	constexpr inline vector<T, n> operator-(const vector<T, n> &left, const vector<T, n> &right) noexcept 
	{
		vector<T, n> res{ left };
		res -= right;
		return res;
	}

	template<typename T, std::size_t n>
	constexpr inline vector<T, n> operator-(const vector<T, n> &left, const T &right) noexcept
	{
		vector<T, n> res{ left };
		res -= right;
		return res;
	}

	template<typename T, std::size_t n>
	constexpr inline vector<T, n> operator-(const T &left, const vector<T, n> &right) noexcept 
	{
		vector<T, n> res{ left };
		res -= right;
		return res;
	}
	/*
	---------------------------------------------------------------------------------------
	*/

	/*
	multiplications
	---------------------------------------------------------------------------------------
	*/
	template<typename T, std::size_t n>
	constexpr inline vector<T, n> operator*(const vector<T, n> &left, const vector<T, n> &right) noexcept
	{
		vector<T, n> res{ left };
		res *= right;
		return res;
	}

	template<typename T, std::size_t n>
	constexpr inline vector<T, n> operator*(const vector<T, n> &left, const T &right) noexcept
	{
		vector<T, n> res{ left };
		res *= right;
		return res;
	}

	template<typename T, std::size_t n>
	constexpr inline vector<T, n> operator*(const T &left, const vector<T, n> &right) noexcept
	{
		vector<T, n> res{ right };
		res *= left;
		return res;
	}
	/*
	---------------------------------------------------------------------------------------
	*/

	//division
	template<typename T, std::size_t n>
	constexpr inline vector<T, n> operator/(const vector<T, n> &left, const vector<T, n> &right) noexcept
	{
		vector<T, n> res{ left };
		res /= right;
		return res;
	}

	template<typename T, std::size_t n>
	constexpr inline vector<T, n> operator/(const vector<T, n> &left, const T &right) noexcept
	{
		T recip = T{ 1 } / right;
		vector<T, n> res{ left };
		res *= recip;
		return res;
	}

	template<typename T, std::size_t n>
	constexpr inline vector<T, n> operator/(const T &left, const vector<T, n> &right) noexcept
	{
		T recip = T{ 1 } / left;
		vector<T, n> res{ recip };
		res *= right;
		return res;
	}

	template<typename T, std::size_t n>
	inline vector<T, n> normilize(const vector<T, n>& vec) noexcept
	{

		vector<T, n> result{ vec };
		result.Normilize();
		return result;

	}

}



#endif // !_LIN_ALG_VECTOR_ZASGEO_
