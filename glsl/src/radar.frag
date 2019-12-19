
precision mediump float;

#define PI 3.14159265359

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float box(in vec2 _st, in vec2 _size) {
    _size = vec2(0.5) - _size*0.5;
    vec2 uv = smoothstep(_size,
                         _size+vec2(0.001),
                         _st);

    uv *= smoothstep(_size,
                     _size+vec2(0.001),
                     vec2(1.0)-_st);

    return uv.x*uv.y;
}

float cross(in vec2 _st, float _size) {
    return box(_st, vec2(_size, _size/4.0)) +
           box(_st, vec2(_size/4.0, _size));
}

mat2 rotate2d(float _angle) {
    return mat2(cos(_angle), -sin(_angle), sin(_angle), cos(_angle));
}

mat2 scale(vec2 _scale) {
    return mat2(_scale.x, 0.0, 0.0, _scale.y);
}

void moveCrossAround() {

    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 colour = vec3(0.0);

    vec2 translate = vec2(cos(u_time*10.0), sin(u_time*.05));
    st += translate*0.30;

    // view the translate space
    //colour = vec3(st.x, st.y, 0.0);
    colour = (vec3(0.5, 1.5, sin(u_time)));

    vec3 myCross = cross(st, 0.25) * vec3(sin(u_time), cos(u_time), tan(u_time));
    colour += myCross;
    //colour.g = 0.0;
    //colour.b = 0.0;

    gl_FragColor = vec4(colour, 1.0);

}

void rotateCross() {
    // Rotate the coordinate system
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 colour = vec3(0.0);

    // move space from the centre to vec2(0, 0);
    st -= vec2(0.5);

    // rotate the space
    st = rotate2d(sin(u_time)*PI) * st;
    st += sin(u_time)/2.0;
    // move it back to the centre.
    st += vec2(0.5);

    colour += vec3(cross(st, 0.4));
    gl_FragColor = (vec4(colour, 1.0));
}


void scaleCross() {
    // Scale the coordinate system
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 colour = vec3(0.0);

    st -= vec2(0.5);
    st = scale( vec2(sin(u_time)+1.0)) * st;
    st += vec2(0.5);

    colour += vec3(cross(st, 0.05));
    gl_FragColor = vec4(colour, 1.0);

}

vec4 radarCircle() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    float pct = 0.0;
//    float pct2 = 0.0;
//    float pct3 = 0.0;

    // The distance from the pixel to the centre.
    pct = distance(st, vec2(0.5));

    // The length of the vector from the pixel to the centre.
    //vec2 toCentre = vec2(0.5)-st;
    //pct2 = length(toCentre);

    // The square root of the vector from the pixel to the centre.
    //vec2 tC = vec2(sin(u_time), sin(u_time)) - st;
    //pct3 = sqrt(tC.x*tC.x+tC.y*tC.y);

    float innerF = sin(u_time);
    float outerF = innerF + (0.1);

    vec3 colour = vec3(1.0) - smoothstep(vec3(innerF, innerF, innerF), vec3(outerF, outerF, outerF), vec3(pct*2.0)) ;
    //vec3 colour = vec3(pct3*2.0);

    return vec4(colour, 1.0);
}

void main( )
{
    radarCircle();
}