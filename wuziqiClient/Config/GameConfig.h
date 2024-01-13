
#ifndef GAMECONFIG_H
#define GAMECONFIG_H

// -------全局遍历-------//
#define CHESS_ONE_SOUND ":/res/sound/chessone.wav"
#define WIN_SOUND ":/res/sound/win.wav"
#define LOSE_SOUND ":/res/sound/lose.wav"

const int kBoardMargin = 30; // 棋盘边缘空隙
const int kRadius = 15; // 棋子半径
const int kMarkSize = 6; // 落子标记边长
const int kBlockSize = 40; // 格子的大小
const int kPosDelta = 20; // 鼠标点击的模糊距离上限
const int kBoardSizeNum = 15; // 棋盘尺寸
const int kAIDelay = 700; // AI下棋的思考时间

// -------------------- //
enum GameType{
    pvpGame = 0,
    pveGame = 1,
    onlineGame = 2
};

// 游戏状态
enum GameStatus
{
    PLAYING,
    WAIT,
    WIN,
    DEAD
};

#endif // GAMECONFIG_H
