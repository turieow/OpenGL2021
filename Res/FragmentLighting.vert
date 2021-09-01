#version 450

// ���͕ϐ�
layout(location=0) in vec3 vPosition;
layout(location=1) in vec4 vColor;
layout(location=2) in vec2 vTexcoord;
layout(location=3) in vec3 vNormal;

// �o�͕ϐ�
layout(location=0) out vec4 outColor;
layout(location=1) out vec2 outTexcoord;
layout(location=2) out vec3 outNormal;
out gl_PerVertex {
  vec4 gl_Position;
};

// ���j�t�H�[���ϐ�
layout(location=0) uniform mat4 matTRS;
layout(location=1) uniform mat4 matModel;

// ���_�V�F�[�_�[�v���O����
void main() {
// ��]�s������o��.
  mat3 matNormal = transpose(inverse(mat3(matModel)));

  // ���[���h���W�n�̖@�����v�Z.
  outNormal = normalize(matNormal * vNormal);

  outColor = vColor;
  outTexcoord = vTexcoord;
  gl_Position = matTRS * vec4(vPosition, 1.0);
}