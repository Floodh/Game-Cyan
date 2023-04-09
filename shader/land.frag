#version 150

in vec3 fragColor;
out vec4 out_Color;

void main(void)
{
	out_Color = vec4(fragColor.r, fragColor.g, fragColor.b, 1.0);
}
