#version 150

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

in vec3 inPosition;
in vec3 inColor;
out vec3 fragColor;


void main(void)
{
	fragColor = inColor;
	//gl_Position = projectionMatrix * viewMatrix * vec4(inPosition, 1.0);
	gl_Position = vec4(inPosition, 1.0);
}
