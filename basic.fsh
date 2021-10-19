#version 100
#define PI 3.14159

precision highp float;
uniform float u_time;
varying vec2 v_position;

void main() {
    vec2 uv = v_position.xy;
    gl_FragColor = vec4(abs(sin(u_time)), 0.0, 0.5, 1.0);
}
