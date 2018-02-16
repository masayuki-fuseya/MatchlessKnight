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


// INode抽象クラスを宣言する
class INode
{
private:
	std::weak_ptr<INode> parent;
protected:
	Character* characterParts;
public:
	// コンストラクタ
	INode(Character* playerParts);

	// 再帰的にデータを初期化する
	virtual void Initialize() = 0;
	// 再帰的にデータを更新する
	virtual void Update(DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 rot, DirectX::SimpleMath::Vector3 trans) = 0;
	// 再帰的にデータを表示する
	virtual void Render() = 0;
	// 再帰的にデータを削除する
	virtual void Finalize() = 0;

	// Node, Leafオブジェクトを追加する
	virtual void Add(std::shared_ptr<INode>&& pNode) = 0;

	// 親オブジェクトを取得する
	std::weak_ptr<INode> GetParent();
	// 親オブジェクトを設定する
	void SetParent(const std::shared_ptr<INode>& parent);
};



class Node : public INode, public std::enable_shared_from_this<Node>
{
private:
	// Node, Leafオブジェクトへのポインタを格納する
	std::vector<std::shared_ptr<INode>> children;
public:
	// コンストラクタ
	Node(Character* playerParts);

	// 再帰的にデータを初期化する
	void Initialize() override;
	// 再帰的にデータを更新する
	void Update(DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 rot, DirectX::SimpleMath::Vector3 trans) override;
	// 再帰的にデータを表示する
	void Render() override;
	// 再帰的にデータを削除する
	void Finalize() override;

	// Node, Leafオブジェクトを追加する
	void Add(std::shared_ptr<INode>&& pNode) override;
};


class Leaf : public INode, public std::enable_shared_from_this<Leaf>
{
public:
	// コンストラクタ
	Leaf(Character* playerParts);

	// 再帰的にデータを初期化する
	void Initialize() override;
	// 再帰的にデータを更新する
	void Update(DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 rot, DirectX::SimpleMath::Vector3 trans) override;
	// データを表示する
	void Render() override;
	// 再帰的にデータを削除する
	void Finalize() override;

	// Leafオブジェクトを追加する
	void Add(std::shared_ptr<INode>&& pNode) override;
};

#endif	// COMPOSITE_VISITOR
