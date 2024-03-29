#version 150

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 eyePosition;
uniform vec3 playerPosition;

in vec3 inPosition;
in vec3 inColor;

out vec3 fragColor;
out vec3 eyeRelativePosition;
out vec3 playerRelativePosition;

void main(void)
{
    gl_Position = projectionMatrix * viewMatrix * vec4(inPosition, 1.0);
	fragColor = inColor;
    eyeRelativePosition = inPosition - eyePosition;
    playerRelativePosition = inPosition - playerPosition;
}
