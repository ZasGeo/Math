#ifndef _LIN_ALG_TRASFOMATIONS_ZASGEO_
#define _LIN_ALG_TRASFOMATIONS_ZASGEO_

#include "vector.h"
#include "matrix.h"

namespace esm {

	/*
	Returns translation matrix.
	*/
	template<typename T>
	inline matrix<T, 4, 4> translation(const vector<T, 3>& vec) noexcept
	{

		matrix<T, 4, 4> res {
			T{ 1 }, T{ 0 }, T{ 0 }, T{ vec[0] },
			T{ 0 }, T{ 1 }, T{ 0 }, T{ vec[1] },
			T{ 0 }, T{ 0 }, T{ 1 }, T{ vec[2] },
			T{ 0 }, T{ 0 }, T{ 0 }, T{ 1 } 
		};
		
		return res;

	}

	/*
	Returns rotation matrix by Euler angles(z-y-x extrinsic/ x-y-z intrinsic).
	*/
	template<typename T>
	inline matrix<T, 4, 4> rotation(const T& rotx, const T& roty, const T& rotz) noexcept
	{
		T	Cx, Sx,
			Cy, Sy,
			Cz, Sz;

		SinCos(rotx, Sx, Cx);
		SinCos(roty, Sy, Cy);
		SinCos(rotz, Sz, Cz);

		//combine vals
		vector<T, 3> i{ Cy*Cz, Sx*Cz*Sy+Cx*Sz, -Cx*Sy*Cz + Sx*Sz };
		vector<T, 3> j{ -Cy*Sz, -Sx*Sy*Sz+Cx*Cz, Cx*Sy*Sz + Sx*Cz };
		vector<T, 3> k{ Sy, -Sx*Cy, Cx*Cy };

		matrix<T, 4, 4> res{ i, j,k };

		return res;

	}

	/*
	Returns rotation matrix around axis.
	*/
	template<typename T>
	inline matrix<T, 4, 4> rotation(const vector<T,3>& axis, const T& angle) noexcept
	{
		T C;
		T S;
		SinCos(angle, S, C);
		T t{ T{1}-C };
		
		vector<T, 3> i{ t*axis.x*axis.x+C, t*axis.x*axis.y+S*axis.z, t*axis.x*axis.z-S*axis.y };
		vector<T, 3> j{ t*axis.x*axis.y-S*axis.z, t*axis.y*axis.y +C, t*axis.y*axis.z + S*axis.x };
		vector<T, 3> k{ t*axis.x*axis.z+S*axis.y, t*axis.y*axis.z-S*axis.x, t*axis.z*axis.z+C};

		matrix<T, 4, 4> res{ i, j,k };

		return res;

	}

	/*
	Returns scale matrix by vector.
	*/
	template<typename T>
	inline matrix<T, 4, 4> scale(const vector<T, 3>& vec) noexcept
	{

		matrix<T, 4, 4> res {
			T{ vec[0] }, T{ 0 },	  T{ 0 },		T{ 0 },
			T{ 0 },		 T{ vec[1] }, T{ 0 },		T{ 0 },
			T{ 0 },		 T{ 0 },	  T{ vec[2] },  T{ 0 },
			T{ 0 },		 T{ 0 },	  T{ 0 },		T{ 1 }
		};

		return res;

	}


}


#endif // !_LIN_ALG_TRASFOMATIONS_ZASGEO_

