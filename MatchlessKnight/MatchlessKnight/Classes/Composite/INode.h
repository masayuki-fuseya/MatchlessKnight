//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	INode.h
//!
//!	@brief	�̃w�b�_�t�@�C��
//!
//!	@date	2018/00/00
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef I_NODE
#define I_NODE

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Objects\Character\Character.h"
#include <d3d11.h>
#include <memory>
#include <SimpleMath.h>


class INode
{
private:
	std::weak_ptr<INode> parent;
protected:
	Character* characterParts;
public:
	// �R���X�g���N�^
	INode(Character* characterParts);

	// �ċA�I�Ƀf�[�^������������
	virtual void Initialize() = 0;
	// �ċA�I�Ƀf�[�^���X�V����
	virtual void Update(DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 rot, DirectX::SimpleMath::Vector3 trans) = 0;
	// �ċA�I�Ƀf�[�^��\������
	virtual void Render() = 0;

	// Node, Leaf�I�u�W�F�N�g��ǉ�����
	virtual void Add(std::shared_ptr<INode>&& pNode) = 0;

	// �e�I�u�W�F�N�g���擾����
	std::weak_ptr<INode> GetParent();
	// �e�I�u�W�F�N�g��ݒ肷��
	void SetParent(const std::shared_ptr<INode>& parent);
};

#endif // !I_NODE
