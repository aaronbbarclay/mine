//#version 330 core

precision mediump float;

#define PI 3.14159265359

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float random (vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233)))*43758.543123);
}

float cyclinder(vec3 p, vec2 h) {
    vec2 d = abs(vec2(length(p.xz), p.y)) - h;
    return min(max(d.x, d.y), 0.0) + length(max(d, 0.0));
}

void main( )
{

    vec2 st = gl_FragCoord.xy/u_resolution.xy;

    st *= 10.0; //scale the coordinate sytem by 10

    vec2 ipos = floor(st);
    vec2 fpos = fract(st);

    vec3 colour = vec3(random(ipos));
    colour = vec3(fpos, 0.0);

    gl_FragColor = createTruchetPattern();

}