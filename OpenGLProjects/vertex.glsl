//--- vertex shader: vertex.glvs

#version 330 
// in_Position was bound to attribute index 0 and 
// in_Color was bound to attribute index 1

in  vec3 in_Position; // ��ġ�Ӽ�
in  vec3 in_Color;

out vec3 ex_Color; 

//  �� ���� �� �Ž������� ������Դϴ�.  
uniform mat4 u_transform;

void main(void) { 
	gl_Position =  u_transform * vec4(in_Position,1);

	ex_Color = in_Color;
}
