#pragma once
#ifndef COMPOSITE_VISITOR
#define COMPOSITE_VISITOR

#include "..\Objects\Character\Character.h"
#include <d3d11.h>
#include <iostream>
#include <list>
#include <memory>
#include <SimpleMath.h>
#include <vector>


class Node;
class Leaf;


// INode���ۃN���X��錾����
class INode
{
private:
	std::weak_ptr<INode> parent;
protected:
	Character* characterParts;
public:
	// �R���X�g���N�^
	INode(Character* playerParts);

	// �ċA�I�Ƀf�[�^������������
	virtual void Initialize() = 0;
	// �ċA�I�Ƀf�[�^���X�V����
	virtual void Update(DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 rot, DirectX::SimpleMath::Vector3 trans) = 0;
	// �ċA�I�Ƀf�[�^��\������
	virtual void Render() = 0;
	// �ċA�I�Ƀf�[�^���폜����
	virtual void Finalize() = 0;

	// Node, Leaf�I�u�W�F�N�g��ǉ�����
	virtual void Add(std::shared_ptr<INode>&& pNode) = 0;

	// �e�I�u�W�F�N�g���擾����
	std::weak_ptr<INode> GetParent();
	// �e�I�u�W�F�N�g��ݒ肷��
	void SetParent(const std::shared_ptr<INode>& parent);
};



class Node : public INode, public std::enable_shared_from_this<Node>
{
private:
	// Node, Leaf�I�u�W�F�N�g�ւ̃|�C���^���i�[����
	std::vector<std::shared_ptr<INode>> children;
public:
	// �R���X�g���N�^
	Node(Character* playerParts);

	// �ċA�I�Ƀf�[�^������������
	void Initialize() override;
	// �ċA�I�Ƀf�[�^���X�V����
	void Update(DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 rot, DirectX::SimpleMath::Vector3 trans) override;
	// �ċA�I�Ƀf�[�^��\������
	void Render() override;
	// �ċA�I�Ƀf�[�^���폜����
	void Finalize() override;

	// Node, Leaf�I�u�W�F�N�g��ǉ�����
	void Add(std::shared_ptr<INode>&& pNode) override;
};


class Leaf : public INode, public std::enable_shared_from_this<Leaf>
{
public:
	// �R���X�g���N�^
	Leaf(Character* playerParts);

	// �ċA�I�Ƀf�[�^������������
	void Initialize() override;
	// �ċA�I�Ƀf�[�^���X�V����
	void Update(DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 rot, DirectX::SimpleMath::Vector3 trans) override;
	// �f�[�^��\������
	void Render() override;
	// �ċA�I�Ƀf�[�^���폜����
	void Finalize() override;

	// Leaf�I�u�W�F�N�g��ǉ�����
	void Add(std::shared_ptr<INode>&& pNode) override;
};

#endif	// COMPOSITE_VISITOR
