#shader vertex

#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in float aInfo;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;
out float Info;

uniform mat4 model[27];
uniform mat4 view;
uniform mat4 projection;

void main()
{
    int index = int(aInfo);

    FragPos = vec3(model[index] * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model[index]))) * aNormal;
    gl_Position = projection * view * model[index] * vec4(aPos, 1.0);

	TexCoords = aTexCoords;
    Info = aInfo;
}

#shader fragment
#version 460 core

out vec4 FragColor;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in float Info;

uniform vec3 viewPos;
uniform sampler2D diffuse[27];
uniform sampler2D specular[27];
uniform float shininess[27];
uniform Light light;

void main()
{
    int index = int(Info);
    vec4 diffuseTexture, specularTexture;
    float shine;
    
    diffuseTexture = texture(diffuse[index], TexCoords);
    specularTexture = texture(specular[index], TexCoords);
    shine = shininess[index];

    // ambient
    vec3 ambient = light.ambient * diffuseTexture.rgb;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * diffuseTexture.rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shine);
    vec3 specular = light.specular * spec * specularTexture.rgb;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}