#include "sphere.h"
#include <cmath>
#include <iostream>

Sphere::Sphere(int meridians, int latitudes)
    : m_meridians(meridians), m_latitudes(latitudes), m_triangleCount(0)
{
	// Add 1 to meridians because the prime meridian is in there twice
	// Add 2 to latitudes because of the north and south poles (each meridian's poles have to be separate for texture coordinates)
    m_vertices.reserve((m_meridians+1) * (m_latitudes+2));
	for (size_t i = 0; i < m_meridians + 1; i++)
	{
		for (size_t j = 0; j < m_latitudes + 2; j++)
		{
            // theta = longitude from 0 to 2pi
            // phi = latitude from -pi/2 to pi/2
			double theta, phi;
			theta = 2*M_PI * i/(double)m_meridians;
			phi = M_PI * j/(double)(m_latitudes+1) - M_PI_2;
			float x,y,z;
			y = (float)std::sin(phi);
			x = (float)std::cos(phi) * std::cos(theta);
			z = (float)std::cos(phi) * std::sin(theta);

            m_vertices.push_back(glm::vec3(x,y,z));
		}
	}

	// Output polygons:
	// Polygons are for blender testing

	for (size_t i = 0; i < m_meridians; i++)
	{
		// Construct triangles between successive meridians
		for (size_t j = 0; j < m_latitudes + 1; j++)
		{
            m_indices.push_back(i * (m_latitudes+2) + j);
            m_indices.push_back(i * (m_latitudes+2) + j+1);
            m_indices.push_back((i+1) * (m_latitudes+2) + j+1);

            m_triangleCount++;

            m_indices.push_back((i+1) * (m_latitudes+2) + j+1);
            m_indices.push_back((i+1) * (m_latitudes+2) + j);
            m_indices.push_back(i * (m_latitudes+2) + j);

            m_triangleCount++;
		}
	}
}
