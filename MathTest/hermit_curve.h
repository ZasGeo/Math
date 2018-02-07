#ifndef _MATH_CURVES_ZASGEO_
#define _MATH_CURVES_ZASGEO_

#include <vector>
#include "vector.h"
#include "operations.h"

namespace esm {


	template<typename interpolationType, typename floatingType>
	class HermitCurve {

	public:

		struct HermitPoint {

			interpolationType position;
			interpolationType inTangent;
			interpolationType outTangent;
			floatingType time;

		};

		HermitCurve() noexcept = default;

		HermitCurve(const std::vector<HermitPoint> &points) : points {points} {}

		HermitCurve(std::vector<HermitPoint> &&points) noexcept : points {std::move(points)} {}

		HermitCurve(const HermitCurve &other): points { other.points } {	}

		HermitCurve(HermitCurve &&other) noexcept : points{ std::move(other.points) } {	}

		HermitCurve& operator=(const HermitCurve &other)
		{

			points = other.points;
			return *this;
		}

		HermitCurve& operator=(HermitCurve &&other) noexcept
		{

			points = std::move(other.points);
			return *this;
		}

		HermitCurve& Init(std::vector<HermitPoint> &&points) noexcept
		{

			points = std::move(points);
			return *this;
		}

		HermitCurve& Clean()
		{

			points.clear();
			return *this;
		}

		interpolationType Evaluate(floatingType time) noexcept
		{

			if (points.size() <= 0) return interpolationType{ 0 };


			auto beg = binary_search_range(points.cbegin(), points.cend(), [time](auto val) { return time < val->time; });
			
			

			floatingType t0 = beg->time;
			floatingType t1 = (beg + 1)->time;
			floatingType u = (time - (t0)) / ((t1) - (t0));

			interpolationType P0{ beg->position };
			interpolationType P1{ (beg+1)->position };
			interpolationType T0{ beg->outTangent };
			interpolationType T1{ (beg + 1)->inTangent };

			interpolationType A{ floatingType{2}*P0
				- floatingType{ 2 }*P1
				+T0
				+ T1 };
			interpolationType B{ floatingType {-3}*P0
				+ floatingType{3}*P1
				- T0
				- floatingType{ 2 }*T1 };

			interpolationType res{ P0 + u * (T1 + u * (B + u * A)) };

			return res;

		}

		/*interpolationType Velocity(floatingType time) noexcept
		{


		}

		interpolationType Acceleration(floatingType time) noexcept
		{


		}*/
		

	private:

		std::vector<HermitPoint> points;

	};


}


#endif