//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	INode.h
//!
//!	@brief	のヘッダファイル
//!
//!	@date	2018/00/00
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef I_NODE
#define I_NODE

// ヘッダファイルの読み込み ================================================
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
	// コンストラクタ
	INode(Character* characterParts);

	// 再帰的にデータを初期化する
	virtual void Initialize() = 0;
	// 再帰的にデータを更新する
	virtual void Update(DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 rot, DirectX::SimpleMath::Vector3 trans) = 0;
	// 再帰的にデータを表示する
	virtual void Render() = 0;

	// Node, Leafオブジェクトを追加する
	virtual void Add(std::shared_ptr<INode>&& pNode) = 0;

	// 親オブジェクトを取得する
	std::weak_ptr<INode> GetParent();
	// 親オブジェクトを設定する
	void SetParent(const std::shared_ptr<INode>& parent);
};

#endif // !I_NODE
