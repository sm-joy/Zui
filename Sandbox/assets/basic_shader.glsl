#type vertext
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;
out vec3 v_LocalPos;

void main()
{
    v_LocalPos = aPos + 0.5;
    gl_Position = u_ViewProjection * u_Model * vec4(aPos, 1.0f);
}

#type fragment
#version 330 core
out vec4 FragColor;

in vec3 v_LocalPos;

void main()
{
    FragColor = vec4(v_LocalPos, 1.0);
}