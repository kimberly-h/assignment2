#version 440

in vec4 vs_position;
in vec3 vs_normal;
in vec2 vs_texcoord;

out vec4 fs_colour;

uniform vec3 camPos;

uniform sampler2D albedo;

uniform vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 ambientColor = vec3(1.0f, 1.0f, 1.0f);
uniform float ambientPower  = 1.0f;
uniform float specularPower = 1.0f;
uniform float diffusePower  = 1.0f;

void main()
{
    vec4 texCol = texture(albedo, vs_texcoord);
    vec3 normal = normalize(vs_normal);

    vec3 ambient = ambientPower * ambientColor;

    vec3 lightDir = normalize(vec3(0.0f, 0.0f, 0.0f) - vs_position.xyz);
    float diff = max(dot(lightDir, normal), 0.0f);

    vec3 viewDir = normalize(camPos - vec3(vs_position));
    vec3 reflectDir = reflect(-lightDir, vs_normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularPower * spec * lightColor;

    vec3 result = (ambient + (diffusePower * diff * lightColor) + specular) * texCol.rgb;
    fs_colour = vec4(result, texCol.a);
}