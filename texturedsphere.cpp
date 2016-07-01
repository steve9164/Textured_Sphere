#include "texturedsphere.h"
#include <cmath>
#include <iostream>

TexturedSphere::TexturedSphere(int meridians, int latitudes)
    : m_meridians(meridians), m_latitudes(latitudes), m_triangleCount(0)
{
	// Add 1 to meridians because the prime meridian is in there twice
	// Add 2 to latitudes because of the north and south poles (each meridian's poles have to be separate for texture coordinates)
    m_vertices.reserve((m_meridians+1) * (m_latitudes+2));
	for (size_t i = 0; i < m_meridians + 1; i++)
	{
		for (size_t j = 0; j < m_latitudes + 2; j++)
		{
            // texCoord in the range [(0,0), (1,1)]
            glm::vec2 texCoord((float)i / m_meridians, (float)j / (m_latitudes+1));
            // theta = longitude from 0 to 2pi
            // phi = latitude from -pi/2 to pi/2
			double theta, phi;
            theta = 2*M_PI * texCoord.x;
            phi = M_PI * texCoord.y - M_PI_2;
            glm::vec3 pos;
            pos.y = (float)std::sin(phi);
            pos.x = (float)std::cos(phi) * std::cos(theta);
            pos.z = (float)std::cos(phi) * std::sin(theta);

            m_vertices.push_back({pos, texCoord});
		}
	}

    // Calculate triangle indices

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
