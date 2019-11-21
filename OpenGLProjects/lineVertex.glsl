//--- vertex shader: vertex.glvs

#version 330 
// in_Position was bound to attribute index 0 and 
// in_Color was bound to attribute index 1

in  vec3 in_Position; // ��ġ�Ӽ�
in  vec3 in_Color;

out vec3 ex_Color; // �����׸�Ʈ���̴���������

//  �� ���� �� �Ž������� ������Դϴ�.  
uniform vec3 startPosition;
uniform vec3 endPosition;
uniform mat4 u_transform;

void main(void) { 
    if(gl_VertexID == 0)
		gl_Position =   vec4(startPosition,1);
	if(gl_VertexID == 1)
		gl_Position =   vec4(endPosition,1);
	


	ex_Color = in_Color;
}
