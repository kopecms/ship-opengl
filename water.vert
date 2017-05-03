#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec3 vecColor;
out vec2 TexCoord;
  
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float deltatime;

void main()
{
	vec3 position2 = vec3(position.x,sin(deltatime*2*3.14/6+2*3.14/10+position.x),position.z);
    gl_Position = projection * view * model * vec4(position2, 1.0f);
    TexCoord = texCoord;
} 