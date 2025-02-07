#version 330 core

layout(location = 0) in vec3 aPos;        // Vertex position
layout(location = 1) in vec3 aNormal;     // Normal vector
layout(location = 2) in vec2 aTexCoords;  // Texture coordinates

out vec3 FragPos;   // Pass to fragment stage
out vec3 Normal;    
out vec2 TexCoords;

uniform mat4 model;      // Object transform
uniform mat4 view;       // Camera transform
uniform mat4 projection; // Projection transform

void main()
{
    // Transform the vertex position
    FragPos = vec3(model * vec4(aPos, 1.0));

    // Correctly transform the normal
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // Pass through texture coordinates
    TexCoords = aTexCoords;
    
    // Final position in clip space
    gl_Position = projection * view * vec4(FragPos, 1.0);
}