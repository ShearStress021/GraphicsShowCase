#version 450

layout(location = 0) out vec4 outColor;
layout(location = 0) in vec2 fragPos;


layout(push_constant) uniform Push {
    mat2 tranform;
    vec2 offset;
    vec3 color;
} push;
void main(){

    vec2 fragCord = fragPos ;


    float d = length(fragCord);
    outColor = vec4(push.color*vec3(d,0.0,0.0), 1.0);
}
