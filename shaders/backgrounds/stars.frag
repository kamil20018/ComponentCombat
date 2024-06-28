uniform vec2 u_resolution;
uniform float u_time;

float getIntensity(){
  vec2 pos = gl_FragCoord.xy - u_resolution.xy / 2.;
	float dist = length(pos) + sin(atan(pos.x, pos.y)*9000.)*100.;
  float scale = 0.01;
  float timeScale = -1.;
  float result = sin(dist * scale + u_time * timeScale);
  result += 1.;
  result /=2.;

  return result;
}

void main() {
  vec2 st = (gl_FragCoord.xy )/u_resolution.xy;

	vec3 color1 = vec3(1.900,0.704,0.000);
	vec3 color2 = vec3(0.296,0.048,0.615);

	float mixValue = distance(st,vec2(0,1));
	vec3 color = mix(color1,color2,mixValue);
	// gl_FragColor = vec4(color, 1);
    
	gl_FragColor = vec4(color * getIntensity(), 1);
} 