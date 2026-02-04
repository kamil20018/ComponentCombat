uniform vec2 u_resolution;
uniform float u_time;
void main() {
    float pi = 3.141592;
    
	vec2 st = gl_FragCoord.xy/u_resolution.xy;
    float duplicates = 1.0;
	st = mod(st, 1. / duplicates)*duplicates;
	st *= 2.0;
	if(st.x > 1.0){
	    st.x = -st.x + 2.0;
	}
	if(st.y > 1.0){
	    st.y = -st.y + 2.0;
	}
    float intensity = sin(u_time * 1.7)*.45-.7;
	float color = pow(st.x, intensity) / (pow(2.0 - st.y, 4.0)) * pow(st.y, intensity) / (pow(2.0 - st.x, 4.0));
    // color = clamp(color, 0.3, 1.0);
    gl_FragColor = gl_Color * color;

}
