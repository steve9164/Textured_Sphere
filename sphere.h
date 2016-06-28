
#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glm/glm.hpp>

class Sphere
{
public:
    Sphere(int meridians, int latitudes);
	//~Sphere();

private:
    unsigned int m_meridians;
    unsigned int m_latitudes;
	std::vector<glm::vec3> m_vertices;

};

#endif
