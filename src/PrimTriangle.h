// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Triangle Geaometrical Primitive class
 */
class CPrimTriangle : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param a Position of the first vertex
	 * @param b Position of the second vertex
	 * @param c Position of the third vertex
	 */
	CPrimTriangle(Vec3f color, Vec3f a, Vec3f b, Vec3f c)
		: CPrim(color)
		, m_a(a)
		, m_b(b)
		, m_c(c)
  	{}
	virtual ~CPrimTriangle(void) = default;

	virtual bool Intersect(Ray& ray) override
	{

		// following the slides

		Vec3f n_ab = (m_b - ray.org).cross(m_a - ray.org);
		Vec3f n_bc = (m_c - ray.org).cross(m_b - ray.org);
		Vec3f n_ac = (m_a - ray.org).cross(m_c - ray.org);

		float l1_Star = n_bc.dot(ray.dir);
		float l2_Star = n_ac.dot(ray.dir);
		float l3_Star = n_ab.dot(ray.dir);
		float lsum_Star = l1_Star + l2_Star + l3_Star;

		float l1  = l1_Star / lsum_Star;
		float l2  = l2_Star / lsum_Star;
		float l3  = l3_Star / lsum_Star;

		// checking all possible intersections
		if(l1 < 0 || l2 < 0 || l3 < 0){
			return false;
		}
		else{
			Vec3f P = (m_b - m_a).cross(m_c - m_a);
			if(P.dot(ray.dir) == 0){
				return false;
			}
			else{
				float t = P.dot(ray.org - m_a) / P.dot(ray.dir); 
				if(fabs(t) < Epsilon || fabs(t) > ray.t){
					return false;
				}
				else{
					ray.t = t;
					return true;
				}

			}
		}	
		
	}


private:
	Vec3f m_a;	///< Position of the first vertex
	Vec3f m_b;	///< Position of the second vertex
	Vec3f m_c;	///< Position of the third vertex
};
