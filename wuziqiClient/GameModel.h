#ifndef GAMEMODEL_H
#define GAMEMODEL_H

// ---- 五子棋游戏模型类 ---- //
#include <vector>
#include <QObject>
#include<QTimer>
#include<qrandom.h>
#include"Config/GameConfig.h"
// 游戏类型，双人还是AI（目前固定让AI下黑子）




class GameModel: public QObject
{
    Q_OBJECT
public:
    GameModel();
    GameModel(GameType gameType);
public:
    QTimer* m_pTimer;
    int remainMinP1;//玩家p1剩余分钟数
    int remainSecP1;//玩家p1剩余秒数
    int remainMinP2;//玩家p2剩余分钟数
    int remainSecP2;//玩家p2剩余秒数
    std::vector<std::vector<int>> gameMapVec; // 存储当前游戏棋盘和棋子的情况,空白为0，白子1，黑子-1
    std::vector<std::vector<int>> scoreMapVec; // 存储各个点位的评分情况，作为AI下棋依据
    bool playerFlag; // 标示下棋方
    GameType gameType; // 游戏模式
    GameStatus gameStatus; // 游戏状态
    void initPVPGame();
    void initPVEGame();
    void initOnlineGame();
    void startGame(GameType type); // 开始游戏
    void calculateScore(); // 计算评分
    void actionByPerson(int row, int col); // 人执行下棋
    void actionByAI(int clickRow, int clickCol); // 机器执行下棋
    void updateGameMap(int row, int col); // 每次落子后更新游戏棋盘
    bool isWin(int row, int col); // 判断游戏是否胜利
    bool isDeadGame(); // 判断是否和棋
private slots:
    void setRemainTime();
signals:
    void SIG_timeout();
    void SIG_playerSide(bool);
};

#endif // GAMEMODEL_H
