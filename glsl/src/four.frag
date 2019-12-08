
precision mediump float;

#define PI 3.14159265359
#define TWO_PI 6.28318530718

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

vec4 drawCircle() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    float pct = 0.0;
    float pct2 = 0.0;
    float pct3 = 0.0;

    // The distance from the pixel to the centre.
    pct = distance(st, vec2(0.5));

    // The length of the vector from the pixel to the centre.
    vec2 toCentre = vec2(0.5)-st;
    pct2 = length(toCentre);

    // The square root of the vector from the pixel to the centre.
    vec2 tC = vec2(0.5) - st;
    pct3 = sqrt(tC.x*tC.x+tC.y*tC.y);

    float innerF = sin(u_time);
    float outerF = innerF + (0.2 * u_time);

    vec3 colour = vec3(1.0) - smoothstep(vec3(innerF, innerF, innerF), vec3(outerF, outerF, outerF), vec3(pct3*2.0)) ;
    //vec3 colour = vec3(pct3*2.0);

    return vec4(colour, 1.0);

}

vec4 drawCircle2 () {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    float pct = 0.0;
    float pct2 = 0.0;
    float pct3 = 0.0;

    // The distance from the pixel to the centre.
    pct = distance(st, vec2(0.5));

    // The length of the vector from the pixel to the centre.
    vec2 toCentre = vec2(0.5)-st;
    pct2 = length(toCentre);

    // The square root of the vector from the pixel to the centre.
    vec2 tC = vec2(sin(u_time), sin(u_time)) - st;
    pct3 = sqrt(tC.x*tC.x+tC.y*tC.y);

    float innerF = sin(u_time);
    float outerF = innerF + (0.1);

    vec3 colour = vec3(1.0) - smoothstep(vec3(innerF, innerF, innerF), vec3(outerF, outerF, outerF), vec3(pct3*2.0)) ;
    //vec3 colour = vec3(pct3*2.0);

    return vec4(colour, 1.0);
}

float circle(in vec2 _st, in float _radius) {
    vec2 dist = _st-vec2(0.5);
    return 1.0 - smoothstep(_radius-(_radius*0.01),
    _radius+(_radius*0.01),
    dot(dist, dist)*4.0);
}

vec4 distance_field() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.x *= u_resolution.x/u_resolution.y;
    vec3 colour = vec3(0.0);
    float d = 0.0;

    // remap the space to -1 to 1
    st = st * 2.-1.;

    // Make the distnce field
    d = length( abs(st)-.3);

    //Visualise the distance field
    return vec4(vec3(fract(d*20.0)), 1.0);

}

vec4 shape1() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 colour = vec3(0.0);

    vec2 pos = vec2(0.5)-st;

    float r = length(pos)*2.0;
    float a = atan(pos.y, pos.x);

    float f  = cos(a*3.);

    colour = vec3(1.0 - smoothstep(f, f+0.04, r));

    return vec4(colour, 1.0);
}

vec3 triangle() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.x *= u_resolution.x/u_resolution.y;
    vec3 colour = vec3(0.0);
    float d = 0.0;

    st = st * 2.0 - 1.0;

    int N = 3;

    float a = atan(st.x, st.y) + PI;
    float r = TWO_PI/float(N);

    float d1 = cos(floor(.5 + a/r) * r - a) * length(st);
    d = cos(floor(.5+a/r)*r-a)*length(st);
    vec3 result1 = vec3(1.0-smoothstep(.4, .41, d));
    return mix(vec3(d), result1, sin(u_time));
    //return vec3(d);
}

void main( )
{

    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 colour = vec3(circle(st, sin(u_time)));

    gl_FragColor = vec4(triangle(), 1.0);

}