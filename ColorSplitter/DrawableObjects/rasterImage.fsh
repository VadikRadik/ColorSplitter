#version 330 core

in vec2 textureCoord;
uniform sampler2D sampler;

void main(){
   gl_FragColor = vec4(texture2D(sampler, textureCoord));
}
