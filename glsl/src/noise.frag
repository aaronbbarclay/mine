
precision mediump float;

#define PI 3.14159265359

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float random (vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233)))*43758.543123);
}

vec2 truchetPattern(in vec2 _st, in float _index) {
    _index = fract(((_index-0.5)*2.0));

    if (_index > 0.75) {
        _st = vec2(1.0) - _st;
    } else if (_index > 0.5){
        _st = vec2(1.0 - _st.x, _st.y);
    } else if (_index > 0.25) {
        _st = 1.0 - vec2(1.0-_st.x, _st.y);
    }

    return _st;
}

vec4 createTruchetPattern() {

    vec2 st = gl_FragCoord.xy/u_resolution.xy;

    st *= 10.0; //scale the coordinate sytem by 10

    vec2 ipos = floor(st);
    vec2 fpos = fract(st);

    vec2 tile = truchetPattern(fpos, random(ipos));
    float colour = 0.0;

    colour = smoothstep(tile.x-0.3, tile.x, tile.y) - smoothstep(tile.x,tile.x+0.3, tile.y);

    return vec4(vec3(colour), 1.0);

}

vec4 createNoise() {

    vec2 st = gl_FragCoord.xy/u_resolution.xy;

    st *= 10.0; //scale the coordinate sytem by 10

    vec2 ipos = floor(st);
    vec2 fpos = fract(st);

    vec3 colour = vec3(random(ipos));
    //colour = vec3(fpos, 0.0);

    return vec4(colour, 1.0);

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