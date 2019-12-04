#version 330 
in  vec4 ex_Color; 
in vec3 ex_Normal;
in vec3 ex_SunLight;
in float ex_diffuse;

out vec4 gl_FragColor;

uniform float u_ambientLight;

void main(void) {

	//float diffuse = clamp(dot(normalize(ex_SunLight) ,normalize(ex_Normal)),0.0,1.0);

	

	vec3 finalColor = vec3(u_ambientLight);

	finalColor += (vec3(ex_Color) * ex_diffuse);

	gl_FragColor = vec4(finalColor,1); 
}