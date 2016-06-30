
#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glm/glm.hpp>

class Sphere
{
public:
    Sphere(int meridians, int latitudes);
	//~Sphere();

    const std::vector<glm::vec3>& getVertices()
    { return m_vertices; }

    const std::vector<unsigned short>& getIndices()
    { return m_indices; }

    unsigned int getTriangleCount()
    { return m_triangleCount; }

private:
    unsigned int m_meridians;
    unsigned int m_latitudes;
	std::vector<glm::vec3> m_vertices;
    std::vector<unsigned short> m_indices;
    unsigned int m_triangleCount;

};

#endif
