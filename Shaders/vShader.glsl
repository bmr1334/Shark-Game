#version 430

out vec3 fragmentLoc;
out vec3 fragmentNorm;
out vec2 fragmentUV;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) uniform vec3 cameraLoc;
layout (location = 4) uniform mat4 worldViewMat;
layout (location = 5) uniform vec3 lightLoc;
layout (location = 6) uniform mat4 modelWorldMat;	//model world matrix (transform)

void main(){
	
	fragmentLoc = position;
	fragmentNorm = vec3(
		transpose(inverse(modelWorldMat)) *
		vec4(normal,0)
	 ); 
	fragmentUV = uv;

	gl_Position = worldViewMat * modelWorldMat * vec4(position,1);
}