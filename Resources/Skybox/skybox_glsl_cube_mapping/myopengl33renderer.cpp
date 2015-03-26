#include "myopengl33renderer.h"

// ----------------------------------------------------------------------------------------------------------------------------

CMyOpenGL33Renderer::CMyOpenGL33Renderer()
{
	Camera = new CFirstPersonCamera();

	Camera->SetViewMatrixPointer(&ViewMatrix);

	Pause = false;
}

CMyOpenGL33Renderer::~CMyOpenGL33Renderer()
{
	delete Camera;
}

bool CMyOpenGL33Renderer::Init()
{
	bool Error = false;

	// load textures ----------------------------------------------------------------------------------------------------------

	char *CubeMapTextureFileNames[] = {"jajlands1_right.jpg", "jajlands1_left.jpg", "jajlands1_bottom.jpg", "jajlands1_top.jpg", "jajlands1_front.jpg", "jajlands1_back.jpg"};

	Error |= !Textures[0].LoadTextureCubeMap(CubeMapTextureFileNames);
	Error |= !Textures[1].LoadTexture2D("grass.jpg");
	Error |= !Textures[2].LoadTexture2D("crate.jpg");
	Error |= !Textures[3].LoadTexture2D("metalplate.jpg");

	// load shaders -----------------------------------------------------------------------------------------------------------
	
	Error |= !SkyBox.Load("skybox.vert", "skybox.frag");
	Error |= !Lighting.Load("lighting.vert", "lighting.frag");

	// if an error occured, return false --------------------------------------------------------------------------------------
	
	if(Error)
	{
		return false;
	}

	// get uniform and attribute locations ------------------------------------------------------------------------------------
	
	SkyBox.UniformLocations = new GLuint[2];
	SkyBox.UniformLocations[0] = glGetUniformLocation(SkyBox, "CameraPosition");
	SkyBox.UniformLocations[1] = glGetUniformLocation(SkyBox, "ViewProjectionMatrix");

	SkyBox.AttribLocations = new GLuint[1];
	SkyBox.AttribLocations[0] = glGetAttribLocation(SkyBox, "vert_Position");

	Lighting.UniformLocations = new GLuint[2];
	Lighting.UniformLocations[0] = glGetUniformLocation(Lighting, "NormalMatrix");
	Lighting.UniformLocations[1] = glGetUniformLocation(Lighting, "ModelViewProjectionMatrix");

	Lighting.AttribLocations = new GLuint[3];
	Lighting.AttribLocations[0] = glGetAttribLocation(Lighting, "vert_TexCoord");
	Lighting.AttribLocations[1] = glGetAttribLocation(Lighting, "vert_Normal");
	Lighting.AttribLocations[2] = glGetAttribLocation(Lighting, "vert_Position");

	// set constant uniforms --------------------------------------------------------------------------------------------------

	glUseProgram(Lighting);
	glUniform1f(glGetUniformLocation(Lighting, "Light.Ambient"), 0.333333f);
	glUniform1f(glGetUniformLocation(Lighting, "Light.Diffuse"), 0.666666f);
	vec3 LightDirection = vec3(0.467757f, 0.424200f, -0.775409f);
	glUniform3fv(glGetUniformLocation(Lighting, "Light.Direction"), 1, &LightDirection);
	glUseProgram(0);

	// init skybox ------------------------------------------------------------------------------------------------------------

	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 432, SkyBoxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &VAO[0]);
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glVertexAttribPointer(SkyBox.AttribLocations[0], 3, GL_FLOAT, GL_FALSE, 12, (void*)0);
	glEnableVertexAttribArray(SkyBox.AttribLocations[0]);
	glBindVertexArray(0);

	// init scene -------------------------------------------------------------------------------------------------------------

	CBuffer Buffer;

	VerticesCount[0] = 0;

	for(int i = 0; i < 6; i++)
	{
		Buffer.AddData(&GrassTexCoords[i], 8);
		vec3 GrassNormal = vec3(0.0f, 1.0f, 0.0f);
		Buffer.AddData(&GrassNormal, 12);
		Buffer.AddData(&GrassVertices[i], 12);
		VerticesCount[0]++;
	}

	VerticesCount[1] = 0;

	for(int y = 0; y < 8; y++)
	{
		for(int x = 0; x < 8 - y; x++)
		{
			vec3 offset = vec3(-5.5f + x * 1.5f + 0.75f * y, 0.5f + y, -5.0f);

			for(int i = 0; i < 36; i++)
			{
				Buffer.AddData(&CubeTexCoords[i % 6], 8);
				Buffer.AddData(&CubeNormals[i / 6], 12);
				vec3 Vertex = CubeVertices[i] + offset;
				Buffer.AddData(&Vertex, 12);
				VerticesCount[1]++;
			}
		}
	}

	VerticesCount[2] = GenerateTorus(Buffer, 1.0f, 0.25f, 32, 16, mat4x4());
	VerticesCount[2] += GenerateTorus(Buffer, 1.0f, 0.25f, 32, 16, rotate(90.0f, vec3(0.0f, 1.0f, 0.0f)));
	VerticesCount[2] += GenerateTorus(Buffer, 1.0f, 0.25f, 32, 16, rotate(90.0f, vec3(1.0f, 0.0f, 0.0f)));

	glGenBuffers(1, &VBO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, Buffer.GetDataSize(), Buffer.GetData(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Buffer.Empty();

	glGenVertexArrays(1, &VAO[1]);
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glVertexAttribPointer(Lighting.AttribLocations[0], 2, GL_FLOAT, GL_FALSE, 32, (void*)0);
	glEnableVertexAttribArray(Lighting.AttribLocations[0]);
	glVertexAttribPointer(Lighting.AttribLocations[1], 3, GL_FLOAT, GL_FALSE, 32, (void*)8);
	glEnableVertexAttribArray(Lighting.AttribLocations[1]);
	glVertexAttribPointer(Lighting.AttribLocations[2], 3, GL_FLOAT, GL_FALSE, 32, (void*)20);
	glEnableVertexAttribArray(Lighting.AttribLocations[2]);
	glBindVertexArray(0);

	// set camera--------------------------------------------------------------------------------------------------------------

	Camera->Look(vec3(0.0f, 1.75f, 0.0f), vec3(0.0f, 1.75f, -1.0f));

	// ------------------------------------------------------------------------------------------------------------------------

	return true;
}

void CMyOpenGL33Renderer::Resize(int Width, int Height)
{
	this->Width = Width;
	this->Height = Height;

	glViewport(0, 0, Width, Height);

	ProjectionMatrix = perspective(45.0f, (float)Width / (float)Height, 0.125f, 512.0f);
}

void CMyOpenGL33Renderer::Render()
{
	// clear frame buffer -----------------------------------------------------------------------------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set up matrices --------------------------------------------------------------------------------------------------------

	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

	// render skybox - depth test must be disabled ----------------------------------------------------------------------------

	glUseProgram(SkyBox);
	glUniform3fv(SkyBox.UniformLocations[0], 1, &Camera->Position);
	glUniformMatrix4fv(SkyBox.UniformLocations[1], 1, GL_FALSE, &ViewProjectionMatrix);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Textures[0]);
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glUseProgram(0);

	// render scene -----------------------------------------------------------------------------------------------------------
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glUseProgram(Lighting);

	ModelViewProjectionMatrix = ViewProjectionMatrix;

	glUniformMatrix3fv(Lighting.UniformLocations[0], 1, GL_FALSE, &mat3x3());
	glUniformMatrix4fv(Lighting.UniformLocations[1], 1, GL_FALSE, &ModelViewProjectionMatrix);

	glBindVertexArray(VAO[1]);
	
	// grass

	glBindTexture(GL_TEXTURE_2D, Textures[1]);
	glDrawArrays(GL_TRIANGLES, 0, VerticesCount[0]);

	// cubes

	glBindTexture(GL_TEXTURE_2D, Textures[2]);
	glDrawArrays(GL_TRIANGLES, VerticesCount[0], VerticesCount[1]);

	// tori

	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;

	glUniformMatrix3fv(Lighting.UniformLocations[0], 1, GL_FALSE, &NormalMatrix);
	glUniformMatrix4fv(Lighting.UniformLocations[1], 1, GL_FALSE, &ModelViewProjectionMatrix);

	glBindTexture(GL_TEXTURE_2D, Textures[3]);
	glDrawArrays(GL_TRIANGLES, VerticesCount[0] + VerticesCount[1], VerticesCount[2]);

	// unbind and disable what was bound and enabled

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	// set Text for testing purposes

	Text.Set("Camera.Position = vec3(%.03f, %.03f, %.03f)", Camera->Position.x, Camera->Position.y, Camera->Position.z);
}

bool CMyOpenGL33Renderer::Animate(float FrameTime)
{
	static float Angle = 0.0f;

	// increase angle - rotating object ---------------------------------------------------------------------------------------

	if(!Pause)
	{
		Angle += 22.5f * FrameTime;

		ModelMatrix = translate(0.0f, 1.75f, 5.0f) * rotate(Angle, vec3(0.0f, 1.0f, 0.0f));
		NormalMatrix = transpose(inverse(mat3x3(ModelMatrix)));
	}

	return !Pause;
}

void CMyOpenGL33Renderer::Destroy()
{
	for(int i = 0; i < 4; i++)
	{
		Textures[i].Destroy();
	}

	SkyBox.Destroy();
	Lighting.Destroy();

	glDeleteBuffers(2, VBO);

	glDeleteVertexArrays(2, VAO);
}

void CMyOpenGL33Renderer::OnKeyDown(UINT Key)
{
	switch(Key)
	{
		case 'P':
			Pause = !Pause;
			break;
	}

	COpenGL33Renderer::OnKeyDown(Key);
}

// ----------------------------------------------------------------------------------------------------------------------------

vec3 SkyBoxVertices[36] = 
{
	vec3( 1.0f, -1.0f, -1.0f), vec3( 1.0f, -1.0f,  1.0f), vec3( 1.0f,  1.0f,  1.0f), vec3( 1.0f,  1.0f,  1.0f), vec3( 1.0f,  1.0f, -1.0f), vec3( 1.0f, -1.0f, -1.0f),
	vec3(-1.0f, -1.0f,  1.0f), vec3(-1.0f, -1.0f, -1.0f), vec3(-1.0f,  1.0f, -1.0f), vec3(-1.0f,  1.0f, -1.0f), vec3(-1.0f,  1.0f,  1.0f), vec3(-1.0f, -1.0f,  1.0f),
	vec3(-1.0f,  1.0f, -1.0f), vec3( 1.0f,  1.0f, -1.0f), vec3( 1.0f,  1.0f,  1.0f), vec3( 1.0f,  1.0f,  1.0f), vec3(-1.0f,  1.0f,  1.0f), vec3(-1.0f,  1.0f, -1.0f),
	vec3(-1.0f, -1.0f,  1.0f), vec3( 1.0f, -1.0f,  1.0f), vec3( 1.0f, -1.0f, -1.0f), vec3( 1.0f, -1.0f, -1.0f), vec3(-1.0f, -1.0f, -1.0f), vec3(-1.0f, -1.0f,  1.0f),
	vec3( 1.0f, -1.0f,  1.0f), vec3(-1.0f, -1.0f,  1.0f), vec3(-1.0f,  1.0f,  1.0f), vec3(-1.0f,  1.0f,  1.0f), vec3( 1.0f,  1.0f,  1.0f), vec3( 1.0f, -1.0f,  1.0f), 
	vec3(-1.0f, -1.0f, -1.0f), vec3( 1.0f, -1.0f, -1.0f), vec3( 1.0f,  1.0f, -1.0f), vec3( 1.0f,  1.0f, -1.0f), vec3(-1.0f,  1.0f, -1.0f), vec3(-1.0f, -1.0f, -1.0f) 
};

vec2 GrassTexCoords[6] =
{
	vec2( 0.0f,  0.0f),
	vec2(10.0f,  0.0f),
	vec2(10.0f, 10.0f),
	vec2(10.0f, 10.0f),
	vec2( 0.0f, 10.0f),
	vec2( 0.0f,  0.0f)
};

vec3 GrassVertices[6] = 
{
	vec3(-10.0f, 0.0f,  10.0f),
	vec3( 10.0f, 0.0f,  10.0f),
	vec3( 10.0f, 0.0f, -10.0f),
	vec3( 10.0f, 0.0f, -10.0f),
	vec3(-10.0f, 0.0f, -10.0f),
	vec3(-10.0f, 0.0f,  10.0f)
};

vec2 CubeTexCoords[6] =
{
	vec2(0.0f, 0.0f),
	vec2(1.0f, 0.0f),
	vec2(1.0f, 1.0f),
	vec2(1.0f, 1.0f),
	vec2(0.0f, 1.0f),
	vec2(0.0f, 0.0f)
};

vec3 CubeNormals[6] =
{
	vec3( 1.0f,  0.0f,  0.0f),
	vec3(-1.0f,  0.0f,  0.0f),
	vec3( 0.0f,  1.0f,  0.0f),
	vec3( 0.0f, -1.0f,  0.0f),
	vec3( 0.0f,  0.0f,  1.0f),
	vec3( 0.0f,  0.0f, -1.0f)
};

vec3 CubeVertices[36] = 
{
	vec3( 0.5f, -0.5f,  0.5f), vec3( 0.5f, -0.5f, -0.5f), vec3( 0.5f,  0.5f, -0.5f), vec3( 0.5f,  0.5f, -0.5f), vec3( 0.5f,  0.5f,  0.5f), vec3( 0.5f, -0.5f,  0.5f),
	vec3(-0.5f, -0.5f, -0.5f), vec3(-0.5f, -0.5f,  0.5f), vec3(-0.5f,  0.5f,  0.5f), vec3(-0.5f,  0.5f,  0.5f), vec3(-0.5f,  0.5f, -0.5f), vec3(-0.5f, -0.5f, -0.5f),
	vec3(-0.5f,  0.5f,  0.5f), vec3( 0.5f,  0.5f,  0.5f), vec3( 0.5f,  0.5f, -0.5f), vec3( 0.5f,  0.5f, -0.5f), vec3(-0.5f,  0.5f, -0.5f), vec3(-0.5f,  0.5f,  0.5f),
	vec3(-0.5f, -0.5f, -0.5f), vec3( 0.5f, -0.5f, -0.5f), vec3( 0.5f, -0.5f,  0.5f), vec3( 0.5f, -0.5f,  0.5f), vec3(-0.5f, -0.5f,  0.5f), vec3(-0.5f, -0.5f, -0.5f),
	vec3(-0.5f, -0.5f,  0.5f), vec3( 0.5f, -0.5f,  0.5f), vec3( 0.5f,  0.5f,  0.5f), vec3( 0.5f,  0.5f,  0.5f), vec3(-0.5f,  0.5f,  0.5f), vec3(-0.5f, -0.5f,  0.5f),
	vec3( 0.5f, -0.5f, -0.5f), vec3(-0.5f, -0.5f, -0.5f), vec3(-0.5f,  0.5f, -0.5f), vec3(-0.5f,  0.5f, -0.5f), vec3( 0.5f,  0.5f, -0.5f), vec3( 0.5f, -0.5f, -0.5f)
};

// ----------------------------------------------------------------------------------------------------------------------------

int GenerateTorus(CBuffer &Buffer, float Radius, float TubeRadius, int SubDivAround, int SubDivTube, const mat4x4 &ModelMatrix)
{
	mat3x3 NormalMatrix = transpose(inverse(mat3x3(ModelMatrix)));

	int VerticesCount = 0;

	vec2 *TexCoords = new vec2[4];
	vec3 *Normals = new vec3[4];
	vec3 *Vertices = new vec3[4];

	int Indices[] = {0, 1, 2, 2, 3, 0};

	float pim2 = 6.283185f;

	float AddAngleAround = pim2 / (float)SubDivAround;
	float AddAngleTube = pim2 / (float)SubDivTube;

	float CurAngleAround = 0.0f;
	int StepsAround = 0;

	while(StepsAround < SubDivAround)
	{
		float NextAngleAround = CurAngleAround + AddAngleAround;

		vec3 Dir1(sin(CurAngleAround), cos(CurAngleAround), 0.0f);
		vec3 Dir2(sin(NextAngleAround), cos(NextAngleAround), 0.0f);

		float CurAngleTube = 0.0f;
		int StepsTube = 0;

		while(StepsTube < SubDivTube)
		{
			float SineTube = sin(CurAngleTube);
			float CosineTube = cos(CurAngleTube);

			float NextAngleTube = CurAngleTube + AddAngleTube;

			float NextSineTube = sin(NextAngleTube);
			float NextCosineTube = cos(NextAngleTube);

			vec3 Mid1 = Dir1 * (Radius - TubeRadius / 2.0f), Mid2 = Dir2 * (Radius - TubeRadius / 2.0f);

			TexCoords[0] = vec2(CurAngleAround / pim2, NextAngleTube / pim2);
			TexCoords[1] = vec2(CurAngleAround / pim2, CurAngleTube / pim2);
			TexCoords[2] = vec2(NextAngleAround / pim2, CurAngleTube / pim2);
			TexCoords[3] = vec2(NextAngleAround / pim2, NextAngleTube / pim2);

			Normals[0] = vec3(0.0f, 0.0f, -NextSineTube) + Dir1 * NextCosineTube;
			Normals[1] = vec3(0.0f, 0.0f, -SineTube) + Dir1 * CosineTube;
			Normals[2] = vec3(0.0f, 0.0f, -SineTube) + Dir2 * CosineTube;
			Normals[3] = vec3(0.0f, 0.0f, -NextSineTube) + Dir2 * NextCosineTube;

			Vertices[0] = Mid1 + vec3(0.0f, 0.0f, -NextSineTube * TubeRadius) + Dir1 * NextCosineTube * TubeRadius;
			Vertices[1] = Mid1 + vec3(0.0f, 0.0f, -SineTube * TubeRadius) + Dir1 * CosineTube * TubeRadius;
			Vertices[2] = Mid2 + vec3(0.0f, 0.0f, -SineTube * TubeRadius) + Dir2 * CosineTube * TubeRadius;
			Vertices[3] = Mid2 + vec3(0.0f, 0.0f, -NextSineTube * TubeRadius) + Dir2 * NextCosineTube * TubeRadius;

			for(int i = 0; i < 6; i++)
			{
				int Index = Indices[i];

				Buffer.AddData(&TexCoords[Index], 8);
				vec3 Normal = NormalMatrix * Normals[Index];
				Buffer.AddData(&Normal, 12);
				vec4 Vertex = ModelMatrix * vec4(Vertices[Index], 1.0f);
				Buffer.AddData(&Vertex, 12);

				VerticesCount++;
			}

			CurAngleTube += AddAngleTube;
			StepsTube++;
		}

		CurAngleAround += AddAngleAround;
		StepsAround++;
	}

	delete [] TexCoords;
	delete [] Normals;
	delete [] Vertices;

	return VerticesCount;
}
