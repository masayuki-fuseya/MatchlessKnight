//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayerPartsFactory.cpp
//!
//!	@brief	プレイヤーパーツ生成工場クラスのソースファイル
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "PlayerPartsFactory.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerBody.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerHead.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerLeftCalf.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerLeftFoot.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerLeftForeArm.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerLeftHand.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerLeftThigh.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerLeftUpperArm.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerRightCalf.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerRightFoot.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerRightForeArm.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerRightHand.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerRightThigh.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerRightUpperArm.h"

// ネームスペースの省略 ====================================================
using namespace std;


//**********************************************************************
//!	@brief		プレイヤーパーツを生成する
//!
//!	@param[in]	プレイヤーパーツの種類
//!
//!	@return		生成されたプレイヤーパーツ
//**********************************************************************
unique_ptr<Player>&& PlayerPartsFactory::Create(Player::PARTS parts)
{
	unique_ptr<Player> playerParts;

	switch (parts)
	{
	// 頭
	case Player::HEAD:
		playerParts = make_unique<PlayerHead>();
		break;
	// 体
	case Player::BODY:
		playerParts = make_unique<PlayerBody>();
		break;
	// 右上腕
	case Player::RIGHT_UPPER_ARM:
		playerParts = make_unique<PlayerRightUpperArm>();
		break;
	// 右前腕部
	case Player::RIGHT_FORE_ARM:
		playerParts = make_unique<PlayerRightForeArm>();
		break;
	// 右手
	case Player::RIGHT_HAND:
		playerParts = make_unique<PlayerRightHand>();
		break;
	// 左上腕
	case Player::LEFT_UPPER_ARM:
		playerParts = make_unique<PlayerLeftUpperArm>();
		break;
	// 左前腕部
	case Player::LEFT_FORE_ARM:
		playerParts = make_unique<PlayerLeftForeArm>();
		break;
	// 左手
	case Player::LEFT_HAND:
		playerParts = make_unique<PlayerLeftHand>();
		break;
	// 右大腿
	case Player::RIGHT_THIGH:
		playerParts = make_unique<PlayerRightThigh>();
		break;
	// 右ふくらはぎ
	case Player::RIGHT_CALF:
		playerParts = make_unique<PlayerRightCalf>();
		break;
	// 右足
	case Player::RIGHT_FOOT:
		playerParts = make_unique<PlayerRightFoot>();
		break;
	// 左大腿
	case Player::LEFT_THIGH:
		playerParts = make_unique<PlayerLeftThigh>();
		break;
	// 左ふくらはぎ
	case Player::LEFT_CALF:
		playerParts = make_unique<PlayerLeftCalf>();
		break;
	// 左足
	case Player::LEFT_FOOT:
		playerParts = make_unique<PlayerLeftFoot>();
		break;
	}

	// プレイヤーパーツを初期化する
	playerParts->Initialize();

	// 所有権を渡して返す
	return move(playerParts);
}
