#version 330 core

out vec4 FragmentColor;
uniform sampler2D tex0;
in vec3 normalCoordinate;
in vec2 textureCoordinate;
in vec3 fragmentPosition;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform float ambientStr;
uniform vec3 ambientColor;

uniform vec3 cameraPos;
uniform float specStr;
uniform float specPhong;

void main() {
    vec3 normal = normalize(normalCoordinate);
    vec3 lightDirection = normalize(lightPos - fragmentPosition);

    float diffusion = max(dot(normal, lightDirection), 0.0);
    vec3 diffusedLight = diffusion * lightColor;

    vec3 ambientLight = ambientStr * ambientColor;

    vec3 viewDirection = normalize(cameraPos - fragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);

    float specular = pow(max(dot(reflectDirection, viewDirection), 0.1), specPhong);
    vec3 specularColor = specular * specStr * lightColor;

    //FragmentColor = vec4(0.37f, 0.56f, 0.92f, 1.0f);
    //                       - Use Lighting -                     - Use Texture -
    FragmentColor = vec4(specularColor + diffusedLight + ambientLight, 1.0) * texture(tex0, textureCoordinate);
}