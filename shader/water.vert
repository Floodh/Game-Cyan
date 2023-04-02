#version 150

in vec3 inPosition;
in vec3 inColor;
out vec3 fragColor;

void main(void)
{
	fragColor = inColor;
	gl_Position = vec4(inPosition, 1.0);
}
