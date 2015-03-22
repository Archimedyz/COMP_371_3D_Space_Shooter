#version 330

struct DirectionalLight
{
	float Ambient, Diffuse;
	vec3 Direction;
};

uniform sampler2D Texture;
uniform DirectionalLight Light;

in vec2 TexCoord;
in vec3 Normal;

out vec4 frag_Color;

void main()
{
	frag_Color = texture(Texture, TexCoord);
	float NdotLD = max(dot(normalize(Normal), Light.Direction), 0.0);
	frag_Color.rgb *= Light.Ambient + Light.Diffuse * NdotLD;
}
