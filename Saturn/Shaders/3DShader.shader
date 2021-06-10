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

uniform mat4 model[28];
uniform mat4 view;
uniform mat4 projection;

void main()
{
	FragPos = vec3(model[int(aInfo)] * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model[int(aInfo)]))) * aNormal;
	TexCoords = aTexCoords;
    Info = aInfo;

	gl_Position = projection * view * model[int(aInfo)] * vec4(aPos, 1.0);
}

#shader fragment
#version 460 core

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

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
uniform Material material[28];
uniform Light light;

void main()
{
    highp int Index = int(Info);
    // ambient
    vec3 ambient = light.ambient * texture(material[Index].diffuse, TexCoords).rgb;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material[Index].diffuse, TexCoords).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material[Index].shininess);
    vec3 specular = light.specular * spec * texture(material[Index].specular, TexCoords).rgb;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}