//--- vertex shader: vertex.glvs

#version 330 
// in_Position was bound to attribute index 0 and 
// in_Color was bound to attribute index 1

in  vec3 in_Position; // ��ġ�Ӽ�
in  vec3 in_Color;

out vec3 ex_Color; // �����׸�Ʈ���̴���������

//  �� ���� �� �Ž������� ������Դϴ�.  
uniform mat4 transform;

void main(void) { 
	gl_Position = vec4 (in_Position.x, in_Position.y, in_Position.z, 1.0);
	ex_Color = vec3(0, 0, 0);
}
