#version 150

uniform vec3 backgroundColor;

in vec3 fragColor;
in vec3 eyeRelativePosition;
in vec3 playerRelativePosition;

out vec4 outColor;

void main(void)
{
    vec3 dFdxPos = dFdx( eyeRelativePosition );
    vec3 dFdyPos = dFdy( eyeRelativePosition );
	vec3 facenormal = normalize( cross(dFdxPos,dFdyPos ));

	outColor = vec4(facenormal*0.5 + 0.5,1.0);
	outColor.rgb *= fragColor;

	float howMuchNM = max(1.0 - length(playerRelativePosition) * 0.025, 0.4);
	float howMuchBG =  1.0 - howMuchNM;

	vec3 colorNM = outColor.rgb * howMuchNM;
	vec3 colorBG = backgroundColor * howMuchBG;

	outColor.rgb = colorNM + colorBG;

}
