
precision mediump float;

#define PI 3.14159265359

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

const int MAX_MARCHING_STEPS = 255;
const float MIN_DIST = 0.0;
const float MAX_DIST = 100.0;
const float EPSILON = 0.0001;

// http://jamie-wong.com/2016/07/15/ray-marching-signed-distance-functions/
// https://www.shadertoy.com/view/llt3R4

/**
* Signed distance function for a sphere centered at the origin with radius 1.0;
*/

float sphereSDF(vec3 samplePoint) {
    return length(samplePoint) - 0.5;
}


/*
* Signed distance function describing the scene
*
* Absolute value of the return value indicates the distance to the surface.
* Sign indicates wethere the point is inside or outside the surface.
*/
float sceneSDF(vec3 samplePoint) {
    return sphereSDF(samplePoint);
}

/**
 * Using the gradient of the SDF, estimate the normal on the surface at point p.
 */
vec3 estimateNormal(vec3 p) {
    float result1 = sceneSDF(vec3(p.x + EPSILON, p.y, p.z));
    float result2 = sceneSDF(vec3(p.x - EPSILON, p.y, p.z));
    float result3 = sceneSDF(vec3(p.x, p.y + EPSILON, p.z));
    float result4 = sceneSDF(vec3(p.x, p.y - EPSILON, p.z));
    float result5 = sceneSDF(vec3(p.x, p.y, p.z + EPSILON));
    float result6 = sceneSDF(vec3(p.x, p.y, p.z - EPSILON));

    return normalize(vec3(result1 - result2, result3 - result4, result5 - result6));
}

/**
 * Return the shortest distance from the eyepoint to the scene surface along
 * the marching direction. If no part of the surface is found between start and end,
 * return end.
 *
 * eye: the eye point, acting as the origin of the ray
 * marchingDirection: the normalized direction to march in
 * start: the starting distance away from the eye
 * end: the max distance away from the ey to march before giving up
 */
float shortestDistanceToSurface(vec3 eye, vec3 marchingDirection, float start, float end) {
    float depth = start;
    for (int i = 0; i < MAX_MARCHING_STEPS; i++) {
        float dist = sceneSDF(eye + depth * marchingDirection);

        if (dist < EPSILON) {
            return depth;
        }

        depth += dist;
        if (depth >= end) {
            return end;
        }
    }
    return end;
}

/**
 * Return the normalized direction to march in from the eye point for a single pixel.
 *
 * fieldOfView: vertical field of view in degrees
 * size: resolution of the output image
 * fragCoord: the x,y coordinate of the pixel in the output image
 */
vec3 rayDirection(float fieldOfView, vec2 size, vec2 fragCoord) {
    vec2 xy = fragCoord - size / 2.0;
    float z = size.y / tan(radians(fieldOfView) / 2.0);
    return normalize(vec3(xy, -z));
}

/**
 * Lighting contribution of a single point light source via Phong illumination.
 *
 * The vec3 returned is the RGB color of the light's contribution.
 *
 * k_a: Ambient color
 * k_d: Diffuse color
 * k_s: Specular color
 * alpha: Shininess coefficient
 * p: position of point being lit
 * eye: the position of the camera
 * lightPos: the position of the light
 * lightIntensity: color/intensity of the light
 *
 * See https://en.wikipedia.org/wiki/Phong_reflection_model#Description
 */
vec3 phongContribForLight(vec3 k_d, vec3 k_s, float alpha, vec3 p, vec3 eye, vec3 lightPos, vec3 lightIntensity) {
    vec3 N = estimateNormal(p);
    vec3 L = normalize(lightPos - p);
    vec3 V = normalize(eye - p);
    vec3 R = normalize(reflect(-L, N));

    float dotLN = dot(L, N);
    float dotRV = dot(R, V);

    if (dotRV < 0.0) {
        // Light reflection in opposite direction as viewer, apply only diffuse
        // component
        return lightIntensity * (k_d * dotLN);
    }
    return lightIntensity * (k_d * dotLN + k_s * pow(dotRV, alpha));
}

/**
 * Lighting via Phong illumination.
 *
 * The vec3 returned is the RGB color of that point after lighting is applied.
 * k_a: Ambient color
 * k_d: Diffuse color
 * k_s: Specular color
 * alpha: Shininess coefficient
 * p: position of point being lit
 * eye: the position of the camera
 *
 * See https://en.wikipedia.org/wiki/Phong_reflection_model#Description
 */
vec3 phongIllumination(vec3 k_a, vec3 k_d, vec3 k_s, float alpha, vec3 p, vec3 eye) {
    const vec3 ambientLight = 0.5 * vec3(1.0, 1.0, 1.0);
    vec3 colour = ambientLight * k_a;

    vec3 light1Pos = vec3(4.0 * sin(u_time),
    2.0,
    4.0 * cos(u_time));

    vec3 light1Intensity = vec3(1.0, 0.1, 0.1);

    colour += phongContribForLight(k_d, k_s, alpha, p, eye,
    light1Pos, light1Intensity);

    vec3 light2Pos = vec3(2.0 * sin(0.37 * u_time),
    2.0 * cos(0.37 * u_time),
    2.0);

    vec3 light2Intensity = vec3(0.4, 0.4, 0.4);

    colour += phongContribForLight(k_d, k_s, alpha, p, eye,
    light2Pos,  light2Intensity);

    return colour;
}

void main() {

    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 dir = rayDirection(45.0, u_resolution.xy, gl_FragCoord.xy);
    vec3 eye = vec3(0.0, 0.0, 5.0);
    float dist = shortestDistanceToSurface(eye, dir, MIN_DIST, MAX_DIST);

    if (dist > MAX_DIST - EPSILON) {
        //Didn't hit anything
        gl_FragColor = vec4(0.1, 0.1, 0.1, 0.0);
        return;
    }

    // The closest point on the surface to the eyepoint along the view ray
    vec3 p = eye + dist * dir;

    vec3 K_a = vec3(0.2, 0.2, 0.2);
    vec3 K_d = vec3(0.7, 0.7, 0.7);
    vec3 K_s = vec3(1.0, 1.0, 1.0);
    float shininess = 10.0;

    vec3 colour = phongIllumination(K_a, K_d, K_s, shininess, p, eye);

    gl_FragColor = vec4(colour, 1.0);
}