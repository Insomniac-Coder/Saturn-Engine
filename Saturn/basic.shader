#shader vertex

#version 460 core

layout(location = 0) in vec4 vertexPos;
layout(location = 2) in vec2 texCoord;

out vec2 vTexCoord;

uniform mat4 projection;

void main()
{
	gl_Position = projection * vertexPos;
	vTexCoord = texCoord;
}

#shader fragment

#version 460 core

layout(location = 0) out vec4 color;

in vec2 vTexCoord;

uniform vec4 u_Color;
uniform sampler2D textureIn;

void main()
{
	//color = u_Color;
	color = texture(textureIn, vTexCoord);
}