#version 420

in vec2 TexCoords;

out vec4 frag_color;

layout (binding = 0) uniform sampler2D s_screenTex;
uniform float u_Transparency = 1.0f;

void main() 
{
	vec4 source = texture(s_screenTex, TexCoords);

	frag_color.rgb = source.rgb;
	frag_color.a = source.a * u_Transparency;
}