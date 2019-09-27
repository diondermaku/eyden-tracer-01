// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h"

/**
 * @brief Perspective Camera class
 */
class CCameraPerspective : public ICamera
{
public:
	/**
	 * @brief Constructor
	 * @param pos Camera origin (center of projection)
	 * @param dir Camera viewing direction
	 * @param up Up-vector
	 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
	 * @param resolution The image resolution
	 */
	CCameraPerspective(Vec3f pos, Vec3f dir, Vec3f up, float angle, Size resolution)
		: ICamera(resolution)
		, m_pos(pos)
		, m_dir(dir)
		, m_up(up)
	{
			// assign x and y axis

			m_xAxis = dir.cross(m_up);
			m_yAxis = dir.cross(m_xAxis);
			
			m_xAxis = normalize(m_xAxis);
			m_yAxis = normalize(m_yAxis);
			dir = normalize(dir);
			
			m_aspect = (float)(resolution.width) / resolution.height;
			m_focus = 1 / tan(angle * Pif / 360);

    }
	virtual ~CCameraPerspective(void) = default;

	virtual bool InitRay(float x, float y, Ray& ray) override
	{
		// following the slides

		float ndcx = (x + 0.5) / getResolution().width;
		float ndcy = (y + 0.5) / getResolution().height;
		float sscx = (2 * ndcx - 1) * m_aspect;
		float sscy = (2 * ndcy - 1);

		ray.dir = m_dir * m_focus + sscx * m_xAxis + sscy * m_yAxis;
		ray.dir = normalize(ray.dir);
		ray.org = m_pos;
		ray.t = std::numeric_limits<float>::infinity();
		return true;
	}

private:
	// input values
	Vec3f m_pos;
	Vec3f m_dir;
	Vec3f m_up;

	// preprocessed values
	float m_focus;
	Vec3f m_xAxis;
	Vec3f m_yAxis;
	Vec3f m_zAxis;
	float m_aspect;
};

