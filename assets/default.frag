#version 430

in vec3 v2fColor;
in vec3 v2fNormal;
in vec3 ModelPos;
in float Alpha;
in vec2 v2fTexCoord;


layout(binding = 0) uniform sampler2D uTexture;

layout(location = 5) uniform vec3 uCameraPos_1;

// Light 1
layout(location = 6) uniform vec3 uLightPos_1;
layout(location = 7) uniform vec3 uLightSpecular_1;
layout(location = 8) uniform vec3 uLightDiffuse_1;
layout(location = 9) uniform vec3 uLightAmbient_1;
layout(location = 10) uniform vec3 uLightColor_1;

// Light 2
layout(location = 11) uniform vec3 uLightPos_2;
layout(location = 12) uniform vec3 uLightSpecular_2;
layout(location = 13) uniform vec3 uLightDiffuse_2;
layout(location = 14) uniform vec3 uLightAmbient_2;
layout(location = 15) uniform vec3 uLightColor_2;


// Light 3
layout(location = 16) uniform vec3 uLightPos_3;
layout(location = 17) uniform vec3 uLightSpecular_3;
layout(location = 18) uniform vec3 uLightDiffuse_3;
layout(location = 19) uniform vec3 uLightAmbient_3;
layout(location = 20) uniform vec3 uLightColor_3;


layout(location = 30) uniform vec3 materialSpec;
layout(location = 31) uniform vec3 materialDiff;
layout(location = 32) uniform vec3 materialAmb;
layout(location = 33) uniform float materialShininess;
layout(location = 34) uniform vec3 materialEmissive;

layout(location = 40) uniform float linear;
layout(location = 41) uniform float quadratic;
layout(location = 42) uniform float constant;

layout(location = 0) out vec4 oColor;

vec3 pointLight(vec3 LightPos, vec3 LightAmbient, vec3 LightDiffse, vec3 LightSpecular, vec3 LightColor) {


			// Ambient
			vec3 ambient = LightAmbient * materialAmb;
			vec3 normal = normalize(v2fNormal);

			// Diffusion
			vec3 lightDirection = normalize(LightPos - ModelPos);
			float diffusion = max( dot(v2fNormal, lightDirection),0.0);
			vec3 diffuse = LightDiffse * (diffusion * materialDiff);
			
			// Specular
			vec3 viewDir = normalize(uCameraPos_1 - ModelPos);
			//halfway direction
			vec3 halfwayDir= normalize(lightDirection+viewDir);
			float spec = pow(max(dot(v2fNormal,halfwayDir ), 0.0), materialShininess);
			vec3 specular = LightSpecular * (spec * materialSpec); 
			 // from learn opengl
			 //attenuation represents the fall off of the intensity of the LightAmbient
			float distance    = length(LightPos - ModelPos);
			float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance)); 

			ambient*= attenuation;
			diffuse*= attenuation;
			specular*= attenuation;

			return (diffuse + ambient + specular ) * LightColor;
		}
void main()
		{
			vec4 texColor = texture(uTexture, v2fTexCoord);

			//point light
			vec3 result = { 0,0,0 };

			// light color
			result+= pointLight(uLightPos_1,uLightAmbient_1, uLightDiffuse_1, uLightSpecular_1, uLightColor_1);
			result+= pointLight(uLightPos_2,uLightAmbient_2, uLightDiffuse_2, uLightSpecular_2, uLightColor_2);
			result+= pointLight(uLightPos_3,uLightAmbient_3, uLightDiffuse_3, uLightSpecular_3, uLightColor_3);
			// light color * object color
			result*= v2fColor;		
			result+= materialEmissive;
			// adding alpha
			vec4 result2 = vec4(result, Alpha);

			// light color * object color * texture color
			result2 *= texColor;
			// final color
			oColor = result2;

		}