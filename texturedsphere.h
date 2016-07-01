
#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glm/glm.hpp>

struct VertexData
{
    glm::vec3 position;
    glm::vec2 texCoord;
};

class TexturedSphere
{
public:
    TexturedSphere(int meridians, int latitudes);
	//~Sphere();

    const std::vector<VertexData>& getVertexData()
    { return m_vertices; }

    const std::vector<unsigned short>& getIndices()
    { return m_indices; }

    unsigned int getTriangleCount()
    { return m_triangleCount; }

private:
    unsigned int m_meridians;
    unsigned int m_latitudes;
    std::vector<VertexData> m_vertices;
    std::vector<unsigned short> m_indices;
    unsigned int m_triangleCount;

};

#endif
