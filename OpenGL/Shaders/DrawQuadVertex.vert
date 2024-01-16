#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

out vec2 o_uv;

layout (std140, binding = 6) uniform PiUpdate
{
    uint textureWidth;
    uint textureHeight;
    uint currentWidth;
    uint groupsOf;
    uint color;//0 = no, 1 = yes
    uint offset; 
    float zoom;
    float padding;
};

void main()
{
    gl_Position = vec4(position.xyz * zoom, 1.0);
    o_uv = uv;
}