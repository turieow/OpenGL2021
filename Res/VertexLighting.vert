#version 450

// ���͕ϐ�
layout(location=0) in vec3 vPosition;
layout(location=1) in vec4 vColor;
layout(location=2) in vec2 vTexcoord;
layout(location=3) in vec3 vNormal;

// �o�͕ϐ�
layout(location=0) out vec4 outColor;
layout(location=1) out vec2 outTexcoord;
out gl_PerVertex {
  vec4 gl_Position;
};

// ���j�t�H�[���ϐ�
layout(location=0) uniform mat4 matTRS;
layout(location=1) uniform mat4 matModel;

// ���s����
struct DirectionalLight {
  vec3 direction; // ���C�g�̌���
  vec3 color;     // ���C�g�̐F(���邳)
};
DirectionalLight light = {
  { 0.65,-0.63,-0.43 },
  { 1.81, 1.16, 0.32 },
};

// �����̐F(���邳)
vec3 ambientLight = { 0.15, 0.10, 0.20 };

// ���_�V�F�[�_�[�v���O����
void main() {
// ��]�s������o��.
  mat3 matNormal = transpose(inverse(mat3(matModel)));

  // ���[���h���W�n�̖@�����v�Z.
  vec3 worldNormal = normalize(matNormal * vNormal);

  // ������ݒ�.
 vec3 lightColor = ambientLight;
  
  // �����o�[�g���˂ɂ�閾�邳���v�Z.
  float cosTheta = max(dot(worldNormal, -light.direction), 0);
  lightColor += light.color * cosTheta;
  
  // ���̂̐F�ƃ��C�g�̐F����Z.
  outColor.rgb = vColor.rgb * lightColor;

  // �s�����x�͕��̂̒l�����̂܂܎g��.
  outColor.a = vColor.a;

  outTexcoord = vTexcoord;
  gl_Position = matTRS * vec4(vPosition, 1.0);
}