#version 150

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 eyePosition;
uniform mat4 scaleMatrix;
uniform mat4 rotationMatrix;
uniform mat4 transformationMatrix;

in vec3 inPosition;
in vec3 inColor;

out vec3 fragColor;
out vec3 eyeRelativePosition;

void main(void)
{
    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * rotationMatrix * scaleMatrix * vec4(inPosition, 1.0);
	fragColor = inColor;
    eyeRelativePosition = inPosition - eyePosition;
}
