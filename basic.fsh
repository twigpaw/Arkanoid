#version 100
#define PI 3.14159

precision highp float;

varying vec2 v_position;

void main() {
    vec2 uv = v_position.xy;
    gl_FragColor = vec4(1.0, 0.5, 0.9, 0.5);
}
