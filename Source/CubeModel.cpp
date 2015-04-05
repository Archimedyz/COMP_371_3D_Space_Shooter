//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "CubeModel.h"
#include "Renderer.h"

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>

using namespace glm;

CubeModel::CubeModel(vec3 size) : Model()
{

	ka = 0.5f;
	kd = 0.1f;
	ks = 0.7f;
	n = 10.0f;

	// Create Vertex Buffer for all the verices of the Cube
	vec3 halfSize = size * 0.5f;
	
	Vertex vertexBuffer[] = {  // position,                normal,                  color
								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) }, //left - red
								{ vec3(-halfSize.x,-halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },

								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },
								{ vec3(-halfSize.x, halfSize.y,-halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },

								{ vec3( halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(0.0f, 0.0f, 1.0f) }, // far - blue
								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(0.0f, 0.0f, 1.0f) },
								{ vec3(-halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(0.0f, 0.0f, 1.0f) },

								{ vec3( halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(0.0f, 0.0f, 1.0f) },
								{ vec3( halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(0.0f, 0.0f, 1.0f) },
								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(0.0f, 0.0f, 1.0f) },

								{ vec3( halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) }, // bottom - turquoise
								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },
								{ vec3( halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },
																
								{ vec3( halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },
								{ vec3(-halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },
								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },

								{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) }, // near - green
								{ vec3(-halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3( halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },

								{ vec3( halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },
								{ vec3( halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f) },

								{ vec3( halfSize.x, halfSize.y, halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) }, // right - purple
								{ vec3( halfSize.x,-halfSize.y,-halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) },
								{ vec3( halfSize.x, halfSize.y,-halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) },

								{ vec3( halfSize.x,-halfSize.y,-halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) },
								{ vec3( halfSize.x, halfSize.y, halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) },
								{ vec3( halfSize.x,-halfSize.y, halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f) },

								{ vec3( halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) }, // top - yellow
								{ vec3( halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) },
								{ vec3(-halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) },

								{ vec3( halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) },
								{ vec3(-halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) },
								{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f) }
						};

	for (Vertex v : vertexBuffer){
		vertex_array.push_back(v.position);
	}

	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);
}

CubeModel::~CubeModel()
{
	// Free the GPU from the Vertex Buffer
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);
}

void CubeModel::Update(float dt)
{
	// If you are curious, un-comment this line to have spinning cubes!
	// That will only work if your world transform is correct...
	//mRotationAngleInDegrees += 90 * dt; // spins by 90 degrees per second

	Model::Update(dt);
}

void CubeModel::Draw()
{
	Model::Draw();
	// Draw the Vertex Buffer
	// Note this draws a unit Cube
	// The Model View Projection transforms are computed in the Vertex Shader
	glBindVertexArray(mVertexArrayID);

	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform"); 
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);
	
	// 1st attribute buffer : vertex Positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(	0,				// attribute. No particular reason for 0, but must match the layout in the shader.
							3,				// size
							GL_FLOAT,		// type
							GL_FALSE,		// normalized?
							sizeof(Vertex), // stride
							(void*)0        // array buffer offset
						);

	// 2nd attribute buffer : vertex normal
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(	1,
							3,
							GL_FLOAT,
							GL_FALSE,
							sizeof(Vertex),
							(void*)sizeof(vec3)    // Normal is Offseted by vec3 (see class Vertex)
						);


	// 3rd attribute buffer : vertex color
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(	2,
							3,
							GL_FLOAT,
							GL_FALSE,
							sizeof(Vertex),
							(void*) (2* sizeof(vec3)) // Color is Offseted by 2 vec3 (see class Vertex)
						);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices: 3 * 2 * 6 (3 per triangle, 2 triangles per face, 6 faces)

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

bool CubeModel::ParseLine(const std::vector<ci_string> &token)
{
	if (token.empty())
	{
		return true;
	}
	else
	{
		return Model::ParseLine(token);
	}
}

void CubeModel::RenderShadowVolume(glm::vec4 lightPos){

	glm::vec3 my_world_position = vec3(GetWorldMatrix() * vec4(0.0f, 0.0f, 0.0f, 1.0f));

	// for each triangle compsing the model:
	for (int i = 0; i < vertex_array.size(); i += 3) {
		// For this model, we store vertices for indvivdual triangle at a time, not a strip
		glm::vec3 vertices[3] = {
			vertex_array[i],
			vertex_array[i+1],
			vertex_array[i+2]
		};

		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);
		glEnable(GL_CULL_FACE);
		glEnable(GL_STENCIL_TEST);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(0.0f, 100.0f);

		// First passthrough, shadow everything from shadow volume (far) to camera

		glCullFace(GL_FRONT);
		glStencilFunc(GL_ALWAYS, 0x0, 0xff);
		glStencilOp(GL_KEEP, GL_INCR, GL_KEEP);
		Renderer::RenderTriangleSurfaceShadowVolume(vertices, my_world_position, lightPos);

		// Second passthrough, remove shadows from shadow volume (near) to camera 
		glCullFace(GL_BACK);
		glStencilFunc(GL_ALWAYS, 0x0, 0xff);
		glStencilOp(GL_KEEP, GL_DECR, GL_KEEP);
		Renderer::RenderTriangleSurfaceShadowVolume(vertices, my_world_position, lightPos);

		// finish off by resetting gl stencil values.

		glDisable(GL_POLYGON_OFFSET_FILL);
		glDisable(GL_CULL_FACE);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);

		glStencilFunc(GL_NOTEQUAL, 0x0, 0xff);
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
		//draw_shadow();
		glDisable(GL_STENCIL_TEST);
	}
}
