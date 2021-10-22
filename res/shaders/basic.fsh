#version 100
#define PI 3.14159

precision mediump float;

uniform float u_time;

void main() {
    gl_FragColor = vec4(abs(sin(u_time)), 0.0, 0.5, 1.0);
}
