#shader vertex

#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	TexCoords = aTexCoords;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}
#shader fragment

#version 460 core

out vec4 FragColor;

in vec2 TexCoords;

uniform vec4 u_Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform sampler2D textureIn;

void main()
{
	FragColor = texture(textureIn, TexCoords);
}