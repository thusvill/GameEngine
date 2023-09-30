#version 330 core

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
uniform mat4 scale;
uniform mat4 translationMatrix;
uniform mat4 rotationMatrix;
uniform float newScale;

void main()
{
	// Combine all transformation matrices including the new translationMatrix
        mat4 modelMatrix = model * translation * rotation* rotationMatrix * scale * translationMatrix ;

        // Calculate the final position by applying the transformation matrices
        gl_Position = modelMatrix * vec4(aPos * newScale, 1.0f);

        data_out.Normal = aNormal;
        data_out.color = aColor;
        data_out.texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
        data_out.projection = camMatrix;
}