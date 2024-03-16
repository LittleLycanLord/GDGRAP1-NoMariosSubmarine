#version 330 core
#extension GL_EXT_debug_printf : enable

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
uniform DirectionalLight directionalLights[10];

// uniform int pointLightCount;
// struct PointLight {    
//     vec3 position;
//     vec3 color;
//     float ambientStrength;
//     vec3 ambientColor;
//     float specularStrength;
//     float specularPhong;
//     float brightness;
// };  
// uniform PointLight pointLights[pointLightCount];

// uniform int spotLightCount;
// struct SpotLight {    
//     vec3 position;
//     vec3 direction;
//     float coneSize;
//     vec3 color;
//     float ambientStrength;
//     vec3 ambientColor;
//     float specularStrength;
//     float specularPhong;
//     float brightness;
// };  
// uniform SpotLight spotLights[spotLightCount];

vec4 directionalLighting(int i, vec3 normal, vec3 viewDirection) {
    float diffusion = max(dot(normal, directionalLights[i].direction), 0.0);
    vec3 diffusedLight = diffusion * directionalLights[i].color;

    vec3 ambientLight = directionalLights[i].ambientStrength * directionalLights[i].ambientColor;
    
    vec3 reflectDirection = reflect(-directionalLights[i].direction, normal);

    float specular = pow(max(dot(reflectDirection, viewDirection), 0.1), directionalLights[i].specularPhong);
    vec3 specularColor = specular * directionalLights[i].specularStrength * directionalLights[i].color;

    return vec4(specularColor + diffusedLight + ambientLight, 1.0) * directionalLights[i].brightness;
}


// vec4 pointLighting(PointLight light, vec3 normal, vec3 viewDirection) {
// // Add Attenuation while accounting for Brightness
//     float distance    = length(light.position - fragmentPosition);
//     float attenuation = 1.0 / (distance * distance) * light.brightness;    

//     vec3 lightDirection = normalize(light.position - fragmentPosition);

//     float diffusion = max(dot(normal, lightDirection), 0.0);
//     vec3 diffusedLight = diffusion * light.color;

//     vec3 ambientLight = light.ambientStrength * light.ambientColor;
//     vec3 reflectDirection = reflect(-lightDirection, normal);

//     float specular = pow(max(dot(reflectDirection, viewDirection), 0.1), light.specularPhong);
//     vec3 specularColor = specular * light.specularStrength * light.color;

//     // Apply the Attenuation
//     diffusedLight *= attenuation;
//     ambientLight *= attenuation;
//     specularColor *= attenuation;

//     //     - Use Lighting -                     - Use Texture -
//     return vec4(specularColor + diffusedLight + ambientLight, 1.0);
// }

// vec4 spotLighting(SpotLight light, vec3 normal, vec3 viewDirection) {
	
// }


void main() {
    vec3 normal = normalize(normalCoordinate);
    vec3 viewDirection = normalize(cameraPosition - fragmentPosition);

    for(int i = 0; i < 10; i++) {
        FragmentColor += directionalLighting(i, normal, viewDirection);
    }

    // float diffusion = max(dot(normal, directionalLights[0].direction), 0.0);
    // vec3 diffusedLight = diffusion * directionalLights[0].color;

    // vec3 ambientLight = directionalLights[0].ambientStrength * directionalLights[0].ambientColor;
    
    // vec3 reflectDirection = reflect(-directionalLights[0].direction, normal);

    // float specular = pow(max(dot(reflectDirection, viewDirection), 0.1), directionalLights[0].specularPhong);
    // vec3 specularColor = specular * directionalLights[0].specularStrength * directionalLights[0].color;

    //                       - Use Lighting -                     - Use Texture -
    FragmentColor = FragmentColor * texture(modelTexture, textureCoordinate);
}