#version 330 core
layout(location=0) in vec3 vLocation;
layout(location=1) in vec3 vTexLocation;
out vec2 myTexLocation;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main(){
    gl_Position= projection*view*model*vec4(vLocation,1.0f);
    myTexLocation=vec2(vTexLocation.x,vTexLocation.y);
}