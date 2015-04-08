#pragma once
#include "C:\Users\Nick\Source\Repos\COMP_371_3D_Space_Shooter\Source\NewAsteroid.h"
class SmallAsteroid :
	public NewAsteroid
{
public:
	SmallAsteroid();
	~SmallAsteroid();

	static void LoadBuffers();
	std::vector<glm::vec3> get_varray() { return SmallAsteroid::vArray; }

private:
	// drawing buffers. each subclass has a set of these buffers which contain the modelspace coordinates of the vertices. 
	static std::vector<glm::vec3> vArray;
	static unsigned int vertexbuffer;
	static unsigned int uvbuffer;
	static unsigned int normalbuffer;
	static unsigned int elementbuffer;
	static std::vector<unsigned short> indices;
};

