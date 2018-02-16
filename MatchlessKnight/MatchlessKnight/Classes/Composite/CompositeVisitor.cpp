
#include "CompositeVisitor.h"

using namespace std;
using namespace DirectX::SimpleMath;

// コンストラクタ
INode::INode(Character* playerParts) : characterParts(playerParts)
{
}

// コンストラクタ
Node::Node(Character* playerParts) : INode(playerParts)
{
}

// 親オブジェクトを取得する
std::weak_ptr<INode> INode::GetParent()
{
	return this->parent;
}

// 親オブジェクトを設定する
void INode::SetParent(const std::shared_ptr<INode>& parent)
{
	this->parent = parent;
}

// Node, Leafオブジェクトを追加する
void Node::Add(shared_ptr<INode>&& pNode)
{
	// Node, Leafオブジェクトへのポインタを追加する
	children.emplace_back(pNode);
	// 親ノードを設定する
	pNode->SetParent(shared_from_this());
}

// データを初期化する
void Node::Initialize()
{
	characterParts->Initialize();

	for (auto node : children)
	{
		// 再帰的にPrint関数を呼び出す
		node->Initialize();
	}
}

// データを更新する
void Node::Update(Vector3 scale, Vector3 rot, Vector3 trans)
{
	characterParts->SetScale(scale);
	characterParts->SetRotation(rot);
	characterParts->SetTranslation(trans);
	characterParts->Update();
	characterParts->CalcMatrix();

	for (auto node : children)
	{
		// 再帰的にUpdate関数を呼び出す
		node->Update(characterParts->GetScale(), characterParts->GetRotation(), characterParts->GetTranslation());
	}
}

// データを表示する
void Node::Render()
{
	characterParts->Render();

	for (auto node : children)
	{
		// 再帰的にRender関数を呼び出す
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

// コンストラクタ
Leaf::Leaf(Character* playerParts) : INode(playerParts)
{
}

// Leafオブジェクトを追加する
void Leaf::Add(shared_ptr<INode>&& pNode)
{
	 pNode->SetParent(shared_from_this());
}

// データを初期化する
void Leaf::Initialize()
{
	characterParts->Initialize();
}

// データを更新する
void Leaf::Update(Vector3 scale, Vector3 rot, Vector3 trans)
{
	characterParts->SetScale(scale);
	characterParts->SetRotation(rot);
	characterParts->SetTranslation(trans);
	characterParts->Update();
	characterParts->CalcMatrix();
}

// データを表示する
void Leaf::Render()
{
	characterParts->Render();
}

void Leaf::Finalize()
{
	delete characterParts;
	characterParts = nullptr;
}
