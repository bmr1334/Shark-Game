#version 430

layout(location = 1)uniform float time;
uniform vec3 lightLoc;
uniform vec3 cameraLoc;
uniform sampler2D myTexture;

in vec3 fragmentLoc;
in vec3 fragmentNorm;
in vec2 fragmentUV;

float grayAmount;

void main(){
	//calculate fragment to light (L)
	vec3 L = normalize(lightLoc - fragmentLoc);
	
	//calculate fragment to camera (V)
	vec3 V = normalize(cameraLoc - fragmentLoc);
	
	//calculate halfway between (H) add them and normalize
	vec3 H = normalize(L + V);
	vec3 N = normalize(fragmentNorm);

	//calculate ambient, diffuse, specular
	float ambient = 0.2f;
	float diffuse = 0.75 * max(dot(L,N), 0);
	float specular =0.25 * pow(max(dot(H,N), 0),16);
	
	float brightness = ambient + diffuse + specular + 2;
	
	vec3 color = vec3(1,1,1);
	
	vec4 texVal = texture(myTexture, fragmentUV);
	texVal.x /= 5;
	texVal.y /= 2;
	
	gl_FragColor = vec4(texVal.rgb * brightness, texVal.a);
}