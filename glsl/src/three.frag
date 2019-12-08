
precision mediump float;

#define PI 3.14159265359

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;


void main( )
{
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 colour = vec3(0.0);


    vec2 b1 = step(vec2(0.1), st);
    float pct = b1.x * b1.y;

    vec2 tr = step(vec2(0.1), 1.0-st);
    pct *= tr.x * tr.y;

    colour = vec3( pct );

    gl_FragColor = vec4(colour, 1.0);

}