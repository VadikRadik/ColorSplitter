#version 330 core

in vec2 pos2d;
in vec2 textureCoords;
out vec2 textureCoord;
uniform mat4 pvm;

void main(void){
   gl_Position = pvm * vec4(pos2d.x, pos2d.y, 0.0, 1.0);
   textureCoord = textureCoords;
}
