#version 150

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

in vec3 inPosition;
in vec3 inColor;
in vec3 inNormal;

out vec3 fragColor;
out vec3 fragNormal;

void main(void)
{
	fragColor = inColor;
	fragNormal = inNormal;	//	if transformation is done, this line will need to be adjusted (by transformation matrix and rotation matrix for example)
	gl_Position = projectionMatrix * viewMatrix * vec4(inPosition, 1.0);
}
