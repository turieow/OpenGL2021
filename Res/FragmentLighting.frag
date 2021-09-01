#version 450

// ���͕ϐ�
layout(location=0) in vec4 inColor; 
layout(location=1) in vec2 inTexcoord;
layout(location=2) in vec3 inNormal;

// �o�͕ϐ�
out vec4 fragColor; 

// ���j�t�H�[���ϐ�
layout(binding=0) uniform sampler2D texColor;

// ���s����
struct DirectionalLight {
  vec3 direction; // ���C�g�̌���
  vec3 color;     // ���C�g�̐F(���邳)
};
DirectionalLight light = {
  { 0.65,-0.63,-0.43},
  { 1.81, 1.16, 0.32},
};

// �����̐F(���邳)
vec3 ambientLight = { 0.15, 0.10, 0.20 };

// �t���O�����g�V�F�[�_�[�v���O����
void main() {
  vec4 tc = texture(texColor, inTexcoord);
  fragColor = inColor * tc;

  // ���`��Ԃɂ���Ē�����1�ł͂Ȃ��Ȃ��Ă���̂ŁA���K�����Ē�����1�ɕ�������.
  vec3 worldNormal = normalize(inNormal);

  // �ʂ��������̏ꍇ�A�@���̌������t�ɂ���.
  if (gl_FrontFacing == false) {
    worldNormal = -worldNormal;
  }

  // ������ݒ�.
  vec3 lightColor = ambientLight;

  // �����o�[�g���˂ɂ�閾�邳���v�Z.
  float cosTheta = max(dot(worldNormal, -light.direction), 0);
  lightColor += light.color * cosTheta;

  fragColor.rgb *= lightColor;
}