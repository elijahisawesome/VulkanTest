#version 450

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(set = 1, binding = 0) uniform sampler2D texSampler;


void main() {
    //outColor = texture(texSampler, fragTexCoord);
    float z = (gl_FragCoord.z/gl_FragCoord.w);

    float fogFactor = exp2( -.5 * 
                   .5 * 
                   z * 
                   z * 
                   1.442695);
    fogFactor = clamp(fogFactor, 0.0, 1.0);

    vec4 tempColor = texture(texSampler,fragTexCoord);
    //tempColor.xyz = tempColor.xyz*z;

    outColor = mix(vec4(0.02,0.01,0.02,1.0),tempColor,fogFactor);
    //outColor = vec4(fogFactor,fogFactor,fogFactor,1.0);
    
}