#version 450

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(set = 1, binding = 0) uniform sampler2D texSampler;

layout(push_constant) uniform pushConstant{
    mat4 model;
}ps;


void main() {

    float z = (gl_FragCoord.z/gl_FragCoord.w);
    vec3 LightbulbPosition = vec3(ps.model[3][0],ps.model[3][1],ps.model[3][2]);
    vec3 FixedLightBulbPositon = LightbulbPosition/20;

    float transparentAlphaReducer = .5;


     float fogFactor = exp2( -.1 * 
                   .1 * 
                   z * 
                   z * 
                   1.442695);

    vec4 tempColor = texture(texSampler,fragTexCoord);


    if(tempColor[3] < 1){
       tempColor[3] -= ((transparentAlphaReducer-fogFactor/2.5));
    }
    
    if(tempColor[3] < 0){
        fogFactor = 1;
    }

    fogFactor = clamp(fogFactor, 0.0, 1.0);

    outColor = mix(vec4(0.02,0.01,0.02,1.0),tempColor,fogFactor);
}