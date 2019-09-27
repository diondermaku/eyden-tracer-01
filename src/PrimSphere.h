// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Sphere Geaometrical Primitive class
 */
class CPrimSphere : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param center Position of the center of the sphere
	 * @param radius Radius of the sphere
	 */
	CPrimSphere(Vec3f color, Vec3f center, float radius)
		: CPrim(color)
		, m_center(center)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;

	virtual bool Intersect(Ray &ray) override
	{

				Vec3f diff = ray.org - m_center;
				float a = ray.dir.dot(ray.dir);
				float b = 2 * ray.dir.dot(diff);
				float c = diff.dot(diff) - m_radius * m_radius;
				
				float D = b * b - 4 * a * c; // D - discriminant
				if (D < 0){
					return false;
				}
				else{
					float x = (-b - sqrt(D)) / (2 * a);
					if (x > ray.t){
						return false;
					}
					else if (x < Epsilon) {
						x = (-b + sqrt(D)) / (2 * a);
						if (x < Epsilon || x > ray.t){
						return false;
						}
					}
					ray.t = x;
					return true;
				}
				
	}


private:
	Vec3f m_center;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};

