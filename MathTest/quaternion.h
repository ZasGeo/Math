#ifndef  _LIN_ALG_QUATERNION_ZASGEO_
#define  _LIN_ALG_QUATERNION_ZASGEO_



#include "vector.h"
#include "operations.h"


namespace esm {

	template<typename floatingType>
	class quaternion {

	public:
		union {

			struct {
				floatingType w;

				union {

					struct {

						floatingType x;
						floatingType y;
						floatingType z;
					};
					vector<floatingType, 3> vec;

				};
			};

			std::array<floatingType, 4> data;


		};

		constexpr quaternion() noexcept:
		w{ floatingType {0} }, x{ floatingType{ 0 } }, y{ floatingType{ 0 } }, z{ floatingType{ 0 } } { }

		constexpr quaternion(floatingType w, floatingType x, floatingType y, floatingType z) noexcept
			: w{ w }, x{ x }, y{ y }, z{ z } { }

		quaternion(floatingType angle, const vector<floatingType, 3>& axis) noexcept
		{
			Set(angle, axis);
		}

		quaternion(const vector<floatingType, 3>& axis) noexcept
		{
			Set(axis);
		}

		constexpr quaternion(const quaternion& other) noexcept = default;

		quaternion& operator=(const quaternion& other) noexcept = default;

		quaternion& operator+=(const quaternion& other) noexcept
		{
			w += other.w;
			vec += other.vec;
			return *this
		}


		quaternion& operator-=(const quaternion& other) noexcept
		{
			w -= other.w;
			vec -= other.vec;
			return *this;

		}

		quaternion& operator*=(const quaternion& other) noexcept
		{
			floatingType w_w = w * other.w - dot(vec, other.vec);
			vec = w * other.vec + other.w*vec + cross(other.vec, vec);
			w = w_w;
			return *this;
		}

		quaternion& operator*=(floatingType arg) noexcept
		{
			w *= arg;
			vec *= arg;
			return *this;
		}

		quaternion& operator-() noexcept
		{
			w = -w;
			x = -x;
			y = -y;
			z = -z;
			return *this;
		}


		constexpr floatingType Norm() const noexcept
		{

			return w*w + x*x + y*y + z*z;
		}

		constexpr floatingType Magnitude() const noexcept
		{

			return sqrt(Norm());
		}

		quaternion& Normilize() noexcept
		{
			floatingType recipLen = floatingType{ 1.0 } / Magnitude();
			w *= recipLen;
			x *= recipLen;
			y *= recipLen;
			z *= recipLen;
			return *this;
		}

		quaternion& Inverse() noexcept
		{
			x = -x;
			y = -y;
			z = -z;
			return *this;
		}

		constexpr mat3 ToMatrix() const noexcept
		{
			
			floatingType s, xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;

			s = floatingType{ 2.0 } / Norm();

			xs = s * x;  ys = s * y;  zs = s * z;
			wx = w * xs; wy = w * ys; wz = w * zs;
			xx = x * xs; xy = x * ys; xz = x * zs;
			yy = y * ys; yz = y * zs; zz = z * zs;

			matrix<floatingType, 3> res{
				floatingType {1} -(yy + zz), xy + wz, xz - wy,
				xy - wz, floatingType{ 1 } -(xx + zz),yz + wx,
				xz + wy, yz - wx, floatingType{ 1 } -(xx + yy)
			};


			return res;
		}

		void Set(floatingType w, floatingType x, floatingType y, floatingType z) noexcept
		{
			w = w;
			x = x;
			y = y;
			z = z;
		}

		void Set(floatingType angle, const vector<floatingType,3> & axis) noexcept
		{
			loat len = axis.lenghtSquared();

			if (isZero(len)) {

				Identity();
				return;
			}


			angle *= floatingType{ 0.5 };
			floatingType sintheta, costheta;
			SinCos(angle, sintheta, costheta);

			floatingType scale = sintheta * recipSqrt(len);

			w = costheta;
			x = axis.x*scale;
			y = axis.y*scale;
			z = axis.z*scale;
		}

		void Set(const vector<floatingType,3>& axis) noexcept
		{
			floatingType len = axis.lenghtSquared();

			if (isZero(len)) {

				Identity();
				return;
			}
			floatingType scale = recipSqrt(len);
			w = floatingType{ 1 };
			x = axis.x*scale;
			y = axis.y*scale;
			z = axis.z*scale;
		}

		void Set(const vector<floatingType, 3>& from, const vector<floatingType, 3>& to) noexcept
		{
			floatingType d = dot(from, to);
			vector<floatingType, 3> axis = cross(from, to);

			Set(d, axis.x, axis.y, axis.z);

			Normilize();

			w += floatingType{ 1 };
			Normilize();

		}

		void Identity() noexcept
		{
			w = floatingType{ 1 };
			x = y = z = floatingType{ 1 };
		}

		void Zero() noexcept
		{
			w = x = y = z = floatingType{ 1 };
		}

		bool isUnit() const noexcept
		{

			return isZero(floatingType{ 1 } - Norm());
		}



	};

	template<typename floatingType>
	constexpr inline quaternion<floatingType> operator+(const quaternion<floatingType>& left, const quaternion<floatingType>& right) noexcept
	{
		quaternion<floatingType> res{ left.w + right.w, left.x + right.x, left.y + right.y, left.z + right.z };
		return res;
	}

	template<typename floatingType>
	constexpr inline quaternion<floatingType> operator-(const quaternion<floatingType>& left, const quaternion<floatingType>& right) noexcept
	{
		quaternion<floatingType> res{ left.w - right.w, left.x - right.x, left.y - right.y, left.z - right.z };
		return res;
	}

	template<typename floatingType>
	constexpr inline quaternion<floatingType> operator*(const quaternion<floatingType>& left, const quaternion<floatingType>& right) noexcept
	{
		floatingType w = left.w*right.w - dot(left.vec, right.vec);
		vector<floatingType,3> vec = left.w*right.vec + right.w*left.vec + cross(right.vec, left.vec);
		return { w, vec.x, vec.y, vec.z };
	}

	template<typename floatingType>
	constexpr inline quaternion<floatingType> operator*(const quaternion<floatingType>& left, floatingType right) noexcept
	{
		quaternion<floatingType> res{ left.w * right, left.x * right, left.y * right, left.z * right };
		return res;
	}

	template<typename floatingType>
	constexpr inline quaternion<floatingType> operator*(floatingType  left, const quaternion<floatingType>& right) noexcept
	{
		quaternion<floatingType> res{ left * right.w, left * right.x, left * right.y, left * right.z };
		return res;
	}

	template<typename floatingType>
	constexpr inline floatingType dot(const quaternion<floatingType>& left, const quaternion<floatingType>& right) noexcept
	{
		floatingType res{ left.w*right.w + left.x*right.x + left.y*right.y + left.z*right.z };
		return res;
	}

	template<typename floatingType>
	constexpr inline quaternion<floatingType> normilize(const quaternion<floatingType>& quat) noexcept
	{
		floatingType recipLen = floatingType{ 1 } / quat.Magnitude();
		quaternion<floatingType> res{ quat.w*recipLen, quat.x*recipLen, quat.y*recipLen, quat.z*recipLen };
		return res;
	}

	template<typename floatingType>
	constexpr inline quaternion<floatingType> inverse(const quaternion<floatingType>& quat) noexcept
	{
		quaternion<floatingType> res{ quat.w, -quat.x,-quat.y,-quat.z };
		return res;
	}

	template<typename floatingType>
	constexpr inline quaternion<floatingType> negate(const quaternion<floatingType>& quat) noexcept
	{
		quaternion<floatingType> res{ -quat.w, -quat.x, -quat.y, -quat.z };
		return res;
	}

	/*
	Rp= qpq^-1.
	Expanded formula: Rp=(2*w^2-1)*p+2*dot(v,p)*v+2*w*cross(v,p);
	*/
	template<typename floatingType>
	constexpr inline vector<floatingType, 3> rotate(const quaternion<floatingType>& quat, const vector<floatingType, 3>& vec) noexcept
	{
		if (!quat.isUnit()) return vec;

		floatingType vMult = floatingType{ 2 }*dot(quat.vec, vec);
		floatingType crossMult = floatingType{ 2 }*quat.w;
		floatingType pMult = crossMult * quat.w - floatingType{ 1 };

		vector<floatingType, 3> res{ pMult*vec + vMult * quat.vec + crossMult * cross(quat.vec, vec) };

		return res;
	}

}

#endif // ! _LIN_ALG_QUATERNION_ZASGEO_

