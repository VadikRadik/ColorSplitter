#version 330 core

in vec3 pos2d;
in vec3 color;
uniform mat4 pvm;

out vec4 colors;

void main(void){
   gl_Position = pvm * vec4(pos2d.x, pos2d.y, 1.0, 1.0);
   colors = vec4(color,1.0);
}
