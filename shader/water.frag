#version 150

in vec3 fragColor;
in vec3 eyeRelativePosition;

out vec4 outColor;

void main(void)
{
    vec3 dFdxPos = dFdx( eyeRelativePosition );
    vec3 dFdyPos = dFdy( eyeRelativePosition );
	vec3 facenormal = normalize( cross(dFdxPos,dFdyPos ));

	outColor = vec4(facenormal*0.5 + 0.5,1.0);
	outColor.rgb *= fragColor;
}
