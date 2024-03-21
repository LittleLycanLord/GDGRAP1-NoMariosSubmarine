#version 330 core

out vec4 FragmentColor;
uniform sampler2D modelTexture;
uniform sampler2D modelNormalTexture;
in vec3 normalCoordinate;
in vec2 textureCoordinate;
in vec3 fragmentPosition;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform float ambientStr;
uniform vec3 ambientColor;

uniform vec3 cameraPosition;
uniform float specStr;
uniform float specPhong;

uniform int directionalLightCount;
struct DirectionalLight {    
    vec3 direction;
    vec3 color;
    float ambientStrength;
    vec3 ambientColor;
    float specularStrength;
    float specularPhong;
    float brightness;
};  
uniform DirectionalLight directionalLights[1];

void main() {
    vec3 normal = normalize(normalCoordinate);
    //vec3 lightDirection = normalize(lightPos - fragmentPosition);

    float diffusion = max(dot(normal, directionalLights[0].direction), 0.0);
    //vec3 diffusedLight = diffusion * lightColor;
    vec3 diffusedLight = diffusion * directionalLights[0].color;

    vec3 ambientLight = ambientStr * ambientColor;

    vec3 viewDirection = normalize(cameraPosition - fragmentPosition);
    vec3 reflectDirection = reflect(-directionalLights[0].direction, normal);

    float specular = pow(max(dot(reflectDirection, viewDirection), 0.1), specPhong);
    //vec3 specularColor = specular * specStr * lightColor;
    vec3 specularColor = specular * specStr * directionalLights[0].color;

    //FragmentColor = vec4(0.37f, 0.56f, 0.92f, 1.0f);
    //                       - Use Lighting -                     - Use Texture -
    FragmentColor = vec4(specularColor + diffusedLight + ambientLight, 1.0) * texture(modelTexture, textureCoordinate);
}