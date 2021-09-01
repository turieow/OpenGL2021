#pragma once
/**
* @file Actor.h
*/
#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include <glad/glad.h>
#include "Primitive.h"
#include "Texture.h"
#include "ProgramPipeline.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <memory>

/**
* ��11��e�L�X�g�������j:
* �G���W���N���X�ւ̓����̓R�X�g���������ߌ�����.
* 1. actors �z��� shared_ptr �z�񉻂���.
* 2. OnHit���z�֐�������.
* 3. EnemyActor�N���X���쐬���AOnHit���I�[�o�[���C�h.
* 4. BulletActor�N���X���쐬���AOnHit���I�[�o�[���C�h.
* 5. Tick���z�֐�������.
* 7. ElevetorActor�N���X���쐬���ATick���I�[�o�[���C�h.
* 8. EnemyActor�N���X��Tick���I�[�o�[���C�h.
* 9. PlayerActor�N���X���쐬���ATick���I�[�o�[���C�h.
*/

/**
* ������.
*/
struct Box
{
    glm::vec3 min = glm::vec3(0);
    glm::vec3 max = glm::vec3(0);
};

/**
* �\�����C���[
*/
enum class Layer
{
    Default,
    UI,
};
static const size_t layerCount = 2; // ���C���[��

/**
* ���̂𐧌䂷��p�����[�^.
*/
class Actor
{
public:
    Actor(
        const std::string& name,
        const Primitive& prim,
        std::shared_ptr<Texture> tex,
        const glm::vec3& position,
        const glm::vec3& scale,
        float rotation,
        const glm::vec3& adjustment);

    virtual ~Actor() = default;
    virtual void OnUpdate(float deltaTime);
    virtual void OnCollision(const struct Contact& contact);

    std::string name;                // �A�N�^�[�̖��O
    Primitive prim;                  // �`�悷��v���~�e�B�u
    std::shared_ptr<Texture> tex;    // �`��Ɏg���e�N�X�`��
    glm::vec3 position;              // ���̂̈ʒu
    glm::vec3 scale;                 // ���̂̊g��k����
    float rotation;                  // ���̂̉�]�p�x
    glm::vec3 adjustment;            // ���̂����_�Ɉړ����邽�߂̋���

    glm::vec3 velocity = glm::vec3(0);// ���x(���[�g�����b)
    glm::vec3 oldVelocity = glm::vec3(0); // �ȑO�̑��x(���[�g�����b)
    float lifespan = 0;              // ����(�b�A0�ȉ��Ȃ�����Ȃ�)
    float health = 10;               // �ϋv�l
    bool isDead = false;             // false=���S(�폜�҂�) true=������

    Box collider;                    // �Փ˔���
    float mass = 1;                  // ����(kg)
    float cor = 0.4f;                // �����W��
    float friction = 0.7f;           // ���C�W��
    bool isStatic = false;           // false=�������镨�� true=�������Ȃ����� 
    bool isBlock = true;             // false=�ʉ߂ł��� true=�ʉ߂ł��Ȃ�

    Layer layer = Layer::Default;    // �\�����C���[

    bool isOnActor = false;
};

void Draw(
    const Actor& actor,              // ���̂̐���p�����[�^
    const ProgramPipeline& pipeline, // �`��Ɏg���v���O�����p�C�v���C��
    glm::mat4 matProj,               // �`��Ɏg���v���W�F�N�V�����s��
    glm::mat4 matView);              // �`��Ɏg���r���[�s��  

std::shared_ptr<Actor> Find(std::vector<std::shared_ptr<Actor>>& actors, const char* name);

/**
* �Փˏ��
*/
struct Contact
{
    Actor* a = nullptr;
    Actor* b = nullptr;
    glm::vec3 velocityA;   // �Փˎ��_�ł̃A�N�^�[A�̃x���V�e�B
    glm::vec3 velocityB;   // �Փˎ��_�ł̃A�N�^�[B�̃x���V�e�B
    glm::vec3 accelA;      // �Փˎ��_�ł̃A�N�^�[A�̉����x
    glm::vec3 accelB;      // �Փˎ��_�ł̃A�N�^�[B�̉����x
    glm::vec3 penetration; // �Z������
    glm::vec3 normal;      // �Փ˖ʂ̖@��
    glm::vec3 position;    // �Փ˖ʂ̍��W
    float penLength;       // �Z�������̒���
};

bool DetectCollision(Actor& a, Actor& b, Contact& pContact);
void SolveContact(Contact& contact);
bool Equal(const Contact& ca, const Contact& cb);

#endif // ACTOR_H_INCLUDED