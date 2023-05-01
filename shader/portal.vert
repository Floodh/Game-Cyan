#version 150

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 transformMatrix;

uniform vec3 eyePosition;

in vec3 inPosition;
in vec3 inColor;

out vec3 fragColor;
out vec3 eyeRelativePosition;

void main(void)
{
    gl_Position = projectionMatrix * viewMatrix * transformMatrix * vec4(inPosition, 1.0);
	fragColor = inColor;
    eyeRelativePosition = inPosition - eyePosition;
}
