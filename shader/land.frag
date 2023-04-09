#version 150

uniform vec3 lightSourceDirection;
uniform vec3 lightSourceColor;

in vec3 fragColor;
in vec3 fragNormal;

out vec4 outColor;

void main(void)
{

	outColor = max(0.0, dot(lightSourceDirection, normalize(fragNormal))) * vec4(fragColor, 1.0);
	outColor.rgb *= lightSourceColor.rgb;

}
