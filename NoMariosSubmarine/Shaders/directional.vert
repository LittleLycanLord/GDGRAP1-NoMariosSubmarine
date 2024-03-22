#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 vertexNormal;
out vec3 normalCoordinate;
layout(location = 2) in vec2 aTexture;
out vec2 textureCoordinate;

out vec3 fragmentPosition;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main() {
    normalCoordinate = mat3(transpose(inverse(transform))) * vertexNormal;

    textureCoordinate = aTexture;

    fragmentPosition = vec3(transform * vec4(aPosition, 1.0f));
    gl_Position = projection * view * transform * vec4(aPosition, 1.0);
}