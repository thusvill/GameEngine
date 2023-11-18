#shader vertex
#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out DATA
{
    vec3 Pos;
    vec3 Normal;
    vec3 color;
    vec2 texCoord;
    mat4 projection;
} data_out;

uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
    gl_Position = camMatrix * model * translation * rotation * scale * vec4(aPos, 1.0);
    data_out.Normal = aNormal;
    data_out.color = aColor;
    data_out.texCoord = aTex;
    data_out.projection = camMatrix;
    data_out.Pos = aPos;
}

#shader fragment
#version 460

out vec4 FragColor;

in vec3 Pos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform int type;
uniform float intensity;

vec4 pointLight()
{
    vec3 lightVec = lightPos - Pos;
    float dist = length(lightVec);
    float a = 0.01;
    float b = 0.09;
    float inten = 1.0 / (a * dist * dist + b * dist + 1.0);

    float ambient = 0.20;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightVec);
    float diffuse = max(dot(normal, lightDirection), 0.0);

    float specularLight = 0.50;
    vec3 viewDirection = normalize(camPos - Pos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 16);
    float specular = specAmount * specularLight;

    return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor * intensity;
}

void main()
{
    if (type == 0) {
        FragColor = pointLight();
    } else {
        // Handle other lighting types here if needed
        FragColor = vec4(1.0, 1.0, 1.0, 1.0); // Default color if type is not recognized
    }
}
