#version 150


uniform vec3 inColor;

in vec3 inPosition;

out vec3 fragColor;


void main(void)
{
    gl_Position = vec4(inPosition, 1.0);
	fragColor = inColor;
}
