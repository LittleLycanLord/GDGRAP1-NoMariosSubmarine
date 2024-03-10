#version 330 core

out vec4 FragmentColor;
uniform sampler2D modelTexture;
in vec3 normalCoordinate;
in vec2 textureCoordinate;
in vec3 fragmentPosition;

uniform vec3 lightPosition;
uniform vec3 lightColor;
// Take in Brightness
uniform float lightBrightness;

uniform float ambientStrength;
uniform vec3 ambientColor;

uniform vec3 cameraPosition;
uniform float specularStrength;
uniform float specularPhong;

void main() {
    // Add Attenuation while accounting for Brightness
    float distance    = length(lightPosition - fragmentPosition);
    float attenuation = 1.0 / (distance * distance) * lightBrightness;    

    vec3 normal = normalize(normalCoordinate);
    vec3 lightDirection = normalize(lightPosition - fragmentPosition);

    float diffusion = max(dot(normal, lightDirection), 0.0);
    vec3 diffusedLight = diffusion * lightColor;

    vec3 ambientLight = ambientStrength * ambientColor;

    vec3 viewDirection = normalize(cameraPosition - fragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);

    float specular = pow(max(dot(reflectDirection, viewDirection), 0.1), specularPhong);
    vec3 specularColor = specular * specularStrength * lightColor;

    // Apply the Attenuation
    diffusedLight *= attenuation;
    ambientLight *= attenuation;
    specularColor *= attenuation;

    //                       - Use Lighting -                     - Use Texture -
    FragmentColor = vec4(specularColor + diffusedLight + ambientLight, 1.0) * texture(modelTexture, textureCoordinate);
}