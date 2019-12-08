
precision mediump float;

#define PI 3.14159265359

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;


void main( )
{

    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 colour = vec3(0.0);

    // Each result will return 1.0 (white) or 0.0 (black).
    float left = step(0.1,st.x);   // Similar to ( X greater than 0.1 )
    float bottom = step(0.1,st.y); // Similar to ( Y greater than 0.1 )

    vec2 borders = step(vec2(0.1), st);
    float pct = borders.x * borders.y;

    // The multiplication of left*bottom will be similar to the logical AND.
    colour = vec3(pct);


    gl_FragColor = vec4(colour, 1.0);

}