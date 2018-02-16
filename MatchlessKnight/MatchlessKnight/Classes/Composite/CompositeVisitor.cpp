
#include "CompositeVisitor.h"

using namespace std;
using namespace DirectX::SimpleMath;

// �R���X�g���N�^
INode::INode(Character* playerParts) : characterParts(playerParts)
{
}

// �R���X�g���N�^
Node::Node(Character* playerParts) : INode(playerParts)
{
}

// �e�I�u�W�F�N�g���擾����
std::weak_ptr<INode> INode::GetParent()
{
	return this->parent;
}

// �e�I�u�W�F�N�g��ݒ肷��
void INode::SetParent(const std::shared_ptr<INode>& parent)
{
	this->parent = parent;
}

// Node, Leaf�I�u�W�F�N�g��ǉ�����
void Node::Add(shared_ptr<INode>&& pNode)
{
	// Node, Leaf�I�u�W�F�N�g�ւ̃|�C���^��ǉ�����
	children.emplace_back(pNode);
	// �e�m�[�h��ݒ肷��
	pNode->SetParent(shared_from_this());
}

// �f�[�^������������
void Node::Initialize()
{
	characterParts->Initialize();

	for (auto node : children)
	{
		// �ċA�I��Print�֐����Ăяo��
		node->Initialize();
	}
}

// �f�[�^���X�V����
void Node::Update(Vector3 scale, Vector3 rot, Vector3 trans)
{
	characterParts->SetScale(scale);
	characterParts->SetRotation(rot);
	characterParts->SetTranslation(trans);
	characterParts->Update();
	characterParts->CalcMatrix();

	for (auto node : children)
	{
		// �ċA�I��Update�֐����Ăяo��
		node->Update(characterParts->GetScale(), characterParts->GetRotation(), characterParts->GetTranslation());
	}
}

// �f�[�^��\������
void Node::Render()
{
	characterParts->Render();

	for (auto node : children)
	{
		// �ċA�I��Render�֐����Ăяo��
		node->Render();
	}
}

void Node::Finalize()
{
	for (auto node : children)
	{
		node->Finalize();
	}

	delete characterParts;
	characterParts = nullptr;
}

// �R���X�g���N�^
Leaf::Leaf(Character* playerParts) : INode(playerParts)
{
}

// Leaf�I�u�W�F�N�g��ǉ�����
void Leaf::Add(shared_ptr<INode>&& pNode)
{
	 pNode->SetParent(shared_from_this());
}

// �f�[�^������������
void Leaf::Initialize()
{
	characterParts->Initialize();
}

// �f�[�^���X�V����
void Leaf::Update(Vector3 scale, Vector3 rot, Vector3 trans)
{
	characterParts->SetScale(scale);
	characterParts->SetRotation(rot);
	characterParts->SetTranslation(trans);
	characterParts->Update();
	characterParts->CalcMatrix();
}

// �f�[�^��\������
void Leaf::Render()
{
	characterParts->Render();
}

void Leaf::Finalize()
{
	delete characterParts;
	characterParts = nullptr;
}
