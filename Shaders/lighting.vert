#version 330

uniform mat3x3 NormalMatrix;
uniform mat4x4 ModelViewProjectionMatrix;

in vec2 vert_TexCoord;
in vec3 vert_Normal;
in vec3 vert_Position;

out vec2 TexCoord;
out vec3 Normal;

void main()
{
	TexCoord = vert_TexCoord;
	Normal = NormalMatrix * vert_Normal;
	gl_Position = ModelViewProjectionMatrix * vec4(vert_Position, 1.0);
}
