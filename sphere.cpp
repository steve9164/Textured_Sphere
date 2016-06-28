#include "sphere.h"
#include <cmath>
#include <iostream>

Sphere::Sphere(int meridians, int latitudes)
    : m_meridians(meridians), m_latitudes(latitudes)
{
	// Add 1 to meridians because the prime meridian is in there twice
	// Add 2 to latitudes because of the north and south poles (each meridian's poles have to be separate for texture coordinates)
	m_vertices.resize((m_meridians+1) * (m_latitudes+2));
	for (size_t i = 0; i < m_meridians + 1; i++)
	{
		for (size_t j = 0; j < m_latitudes + 2; j++)
		{
			double theta, phi;
			// theta = longitude from 0 to 2pi
			// phi = latitude from -pi/2 to pi/2
			theta = 2*M_PI * i/(double)m_meridians;
			phi = M_PI * j/(double)(m_latitudes+1) - M_PI_2;
			float x,y,z;
			// x depends on cos(theta) and cos(phi)
			// y depends solely on sin(phi)
			// z depends on sin(theta) and cos(phi)
			y = (float)std::sin(phi);
			x = (float)std::cos(phi) * std::cos(theta);
			z = (float)std::cos(phi) * std::sin(theta);

			m_vertices.push_back(glm::vec3({x,y,z}));
			std::cout /*<< "Meridian: " << i << ", Latitude: " << j << ", Position: "*/ <<x << " " << y << " " << z << std::endl;
		}
	}

	// Output polygons:
	// Polygons are for blender testing
	// for (int i = 0; i < m_meridians; i++)
	// {
	// 	// Make a polygon for the strip between meridian i and i+1
	// 	std::cout << 2 * (m_latitudes+2) << ' '; // latitudes + 2 vertices on each meridian that defines the polygon

	// 	// Meridian i
	// 	for (int j = 0; j < m_latitudes + 2; j++)
	// 	{
	// 		std::cout << i * (m_latitudes+2) + j << ' ';
	// 	}

	// 	// Meridian i+1
	// 	for (int j = 0; j < m_latitudes + 2; j++)
	// 	{
	// 		std::cout << (i+2) * (m_latitudes+2) - j - 1 << ' ';
	// 	}

	// 	std::cout << std::endl; // Newline
	// }

	// for (size_t i = 0; i < m_meridians; i++)
	// {
	// 	// Construct trapeziums between successive meridians
	// 	for (size_t j = 0; j < m_latitudes + 1; j++)
	// 	{
	// 		std::cout << "4 " 
	// 			<< i * (m_latitudes+2) + j << ' '
	// 			<< i * (m_latitudes+2) + j+1 << ' '
	// 			<< (i+1) * (m_latitudes+2) + j+1 << ' '
	// 			<< (i+1) * (m_latitudes+2) + j << std::endl;
	// 	}
	// }

	for (size_t i = 0; i < m_meridians; i++)
	{
		// Construct triangles between successive meridians
		for (size_t j = 0; j < m_latitudes + 1; j++)
		{
			std::cout << "3 " 
				<< i * (m_latitudes+2) + j << ' '
				<< i * (m_latitudes+2) + j+1 << ' '
				<< (i+1) * (m_latitudes+2) + j+1 << std::endl;

			std::cout << "3 " << (i+1) * (m_latitudes+2) + j+1 << ' '
			    << (i+1) * (m_latitudes+2) + j << ' '
			    << i * (m_latitudes+2) + j << std::endl;
		}
	}
}