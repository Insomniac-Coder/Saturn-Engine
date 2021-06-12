#shader vertex

#version 330 core

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
#version 330 core

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
    int index = int(Info);

    vec3 ambient, diffuse, specular;
    vec3 norm, lightDir, viewDir, reflectDir;
    float spec, diff;

    switch (index)
    {
    case 0: 
        // ambient
        ambient = light.ambient * texture(material[0].diffuse, TexCoords).rgb;

        // diffuse 
        norm = normalize(Normal);
        lightDir = normalize(light.position - FragPos);
        diff = max(dot(norm, lightDir), 0.0);
        diffuse = light.diffuse * diff * texture(material[0].diffuse, TexCoords).rgb;

        // specular
        viewDir = normalize(viewPos - FragPos);
        reflectDir = reflect(-lightDir, norm);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material[0].shininess);
        specular = light.specular * spec * texture(material[0].specular, TexCoords).rgb;
        break;
    case 1:
        // ambient
        ambient = light.ambient * texture(material[1].diffuse, TexCoords).rgb;

        // diffuse 
        norm = normalize(Normal);
        lightDir = normalize(light.position - FragPos);
        diff = max(dot(norm, lightDir), 0.0);
        diffuse = light.diffuse * diff * texture(material[1].diffuse, TexCoords).rgb;

        // specular
        viewDir = normalize(viewPos - FragPos);
        reflectDir = reflect(-lightDir, norm);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material[1].shininess);
        specular = light.specular * spec * texture(material[1].specular, TexCoords).rgb;
        break;
    case 2:
        // ambient
        ambient = light.ambient * texture(material[2].diffuse, TexCoords).rgb;

        // diffuse 
        norm = normalize(Normal);
        lightDir = normalize(light.position - FragPos);
        diff = max(dot(norm, lightDir), 0.0);
        diffuse = light.diffuse * diff * texture(material[2].diffuse, TexCoords).rgb;

        // specular
        viewDir = normalize(viewPos - FragPos);
        reflectDir = reflect(-lightDir, norm);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material[2].shininess);
        specular = light.specular * spec * texture(material[2].specular, TexCoords).rgb;
        break;
    case 3: 
        // ambient
        ambient = light.ambient * texture(material[3].diffuse, TexCoords).rgb;

        // diffuse 
        norm = normalize(Normal);
        lightDir = normalize(light.position - FragPos);
        diff = max(dot(norm, lightDir), 0.0);
        diffuse = light.diffuse * diff * texture(material[3].diffuse, TexCoords).rgb;

        // specular
        viewDir = normalize(viewPos - FragPos);
        reflectDir = reflect(-lightDir, norm);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material[3].shininess);
        specular = light.specular * spec * texture(material[3].specular, TexCoords).rgb;
        break;
    case 4: 
        // ambient
        ambient = light.ambient * texture(material[4].diffuse, TexCoords).rgb;

        // diffuse 
        norm = normalize(Normal);
        lightDir = normalize(light.position - FragPos);
        diff = max(dot(norm, lightDir), 0.0);
        diffuse = light.diffuse * diff * texture(material[4].diffuse, TexCoords).rgb;

        // specular
        viewDir = normalize(viewPos - FragPos);
        reflectDir = reflect(-lightDir, norm);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material[4].shininess);
        specular = light.specular * spec * texture(material[4].specular, TexCoords).rgb;
        break;
    }

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}