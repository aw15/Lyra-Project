//--- vertex shader: vertex.glvs

#version 330 
// in_Position was bound to attribute index 0 and 
// in_Color was bound to attribute index 1

in  vec3 in_Position; // 위치속성
in  vec2 in_TexCoord; // 위치속성
in  vec3 in_Normal; // 위치속성

out vec4 ex_Color; 
out vec3 ex_Normal; 
out vec3 ex_SunLight; 

//  이 값은 한 매쉬동안은 상수적입니다.  
uniform mat4 u_finalMatrix;
uniform mat4 u_worldMatrix;
uniform vec4 u_color;


uniform vec3 u_sunLight;

void main(void) { 
	gl_Position =  u_finalMatrix * vec4(in_Position,1);

	vec4 worldPosition = u_worldMatrix * vec4(in_Position,1);

	ex_SunLight = normalize(vec3(worldPosition) - u_sunLight);
	ex_Normal = vec3(u_worldMatrix * vec4(in_Normal, 1));
	ex_Normal = normalize(ex_Normal);


	ex_Color = u_color;
}
