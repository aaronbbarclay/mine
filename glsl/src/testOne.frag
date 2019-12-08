
precision mediump float;

#define PI 3.14159265359

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float plot(vec2 st, float pct) {
    return smoothstep( pct-0.02, pct, st.y) - smoothstep( pct, pct+0.02, st.y);
}

void main( )
{

    vec2 st = gl_FragCoord.xy/u_resolution;

    float y = pow(st.x, 5.0);
    vec3 colour = vec3(y);

    float pct = plot(st, y);
    colour = (1.0-pct)*colour + pct*vec3(0.0, 1.0, 0.0);



    gl_FragColor = vec4(colour, 1.0);

}