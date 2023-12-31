#shader vertex
#version 460

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Normals (not necessarily normalized)
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture Coordinates
layout (location = 3) in vec2 aTex;


out DATA
{
	vec3 Pos;
	vec3 crntPos;
	vec3 Normal;
	vec3 color;
	vec2 texCoord;
	mat4 projection;
} data_out;

// Imports the camera matrix
uniform mat4 camMatrix;
// Imports the transformation matrices
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale = mat4(1.0f);

uniform vec3 newPos;
uniform vec3 newRot = vec3(0.0001f);
uniform vec3 newScale = vec3(1.0f);

void main()
{
	gl_Position = model * translation * rotation * scale*vec4(newRot, 1.0f)*vec4(newScale, 1.0f) * vec4(newPos, 1.0f)*vec4(aPos, 1.0f);
	data_out.Pos = aPos;
	data_out.crntPos = vec3(model * vec4(aPos, 1.0f));
	data_out.Normal = aNormal;
	data_out.color = aColor;
	data_out.texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	data_out.projection = camMatrix;
}

#shader fragment
#version 460

// Outputs colors in RGBA
out vec4 FragColor;

in vec3 Pos;
in vec3 crntPos;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;



// Gets the Texture Units from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos = vec3(1.0f);

uniform int type = 0;

uniform float intensity = 1.0f;

//in vec3 crntPos;

vec4 pointLight()
{
	// used in two variables so I calculate it here to not have to do it twice
	vec3 lightVec = lightPos - crntPos;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 0.01;
	float b = 0.09;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor*intensity;
}


vec4 spotLight()
{
	// controls how big the area that is lit up is
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// calculates the intensity of the crntPos based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor*intensity;
}

vec4 directLight()
{
	// ambient lighting
	float ambient = 0.50f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor*intensity;
}



void main()
{

	if(type == 0){
		FragColor = directLight();
	}else if(type == 1){
		FragColor =pointLight();
	}else if(type ==2 ){
		FragColor =spotLight();
	}else{
		FragColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
}

#shader geom
#version 460

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 Pos;
out vec3 Normal;
out vec3 color;
out vec2 texCoord;
out vec3 crntPos;

in DATA
{
	vec3 Pos;
	vec3 crntPos;
vec3 Normal;
vec3 color;
vec2 texCoord;
mat4 projection;
} data_in[];

// Default main function
void main()
{
	for (int i = 0; i < 3; ++i) {
		gl_Position = data_in[i].projection * gl_in[i].gl_Position;
		Pos = data_in[i].Pos;
		Normal = data_in[i].Normal;
		color = data_in[i].color;
		texCoord = data_in[i].texCoord;
		//crntPos = data_in[i].crntPos;
		EmitVertex();
	}

	EndPrimitive();
}