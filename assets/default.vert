#version 430

layout(location=0) in vec3 iPosition;
layout(location=1) in vec3 iColor;
layout(location=2) in vec3 iNormal;
layout(location=3) in float alpha;
layout(location=4) in vec2 iTexCoord;

layout(location=0) uniform mat4 uProjCameraWorld;
layout(location=1) uniform mat3 uNormalMatrix;
layout(location=2) uniform mat4 model2world;


out float Alpha;
out vec3 v2fColor;
out vec3 v2fNormal;
out vec3 ModelPos;
out vec2 v2fTexCoord;
out vec3 viewPos;

void main() {

	v2fColor = iColor;

	gl_Position = uProjCameraWorld * vec4( iPosition, 1.0 );

	v2fNormal = normalize(uNormalMatrix * iNormal);
	
	ModelPos = (model2world * vec4(iPosition,1.0)).xyz;
	Alpha = alpha;
	v2fTexCoord = iTexCoord;
}