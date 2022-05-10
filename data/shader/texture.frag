#version 330 core
out vec4 FragColor;

in vec3 myColor;
in vec2 myTexLocation;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
    FragColor=mix(texture(texture1, myTexLocation), texture(texture2, myTexLocation), 0.5);
}