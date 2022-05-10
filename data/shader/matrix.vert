#version 330 core
layout(location=0) in vec3 vLocation;
layout(location=1) in vec3 vColor;
layout(location=2) in vec2 vTexLocation;
out vec3 myColor;
out vec2 myTexLocation;

uniform mat4 transform;
void main(){
    gl_Position= transform*vec4(vLocation,1.0f);
    myColor= vColor;
    myTexLocation=vec2(vTexLocation.x,vTexLocation.y);
}