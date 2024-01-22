#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>
#include"chessboardwidget.h"
#include<QVBoxLayout>
#include"playerinfo.h"
#include<GameModel.h>
#include"Config/GameConfig.h"
#include"gameroomwidgetitem.h"
namespace Ui {
class GameDialog;
}

class GameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GameDialog(QWidget *parent = nullptr);
    explicit GameDialog(GameType gameType,QWidget *parent = nullptr);
    ~GameDialog();
public:
    QTimer* m_pTimer;//本地游戏定时器
    QString p1Name;
    QString p2Name;
    QString m_user1Id;
    QString m_user2Id;
    bool m_user1IsExist;
    bool m_user2IsExist;
    int remainMinP1;//玩家p1剩余分钟数
    int remainSecP1;//玩家p1剩余秒数
    int remainMinP2;//玩家p2剩余分钟数
    int remainSecP2;//玩家p2剩余秒数
    bool playerFlag; // 标示下棋方
    bool playerSide1;//设置玩家是是否先手(白色方or黑色方)
    GameType gameType; // 游戏模式
    GameStatus gameStatus; // 游戏状态
    std::vector<std::vector<int>> gameMapVec; // 存储当前游戏棋盘和棋子的情况,空白为0，白子1，黑子-1
    std::vector<std::vector<int>> scoreMapVec; // 存储各个点位的评分情况，作为AI下棋依据
    QLayout* m_layout;
    QLayout* m_playerLayout1;
    QLayout* m_playerLayout2;
    PlayerInfo* m_player1;
    PlayerInfo* m_player2;
    ChessboardWidget* m_pChessboard;
    int m_roomId;
    bool m_isOnlineGame;
    bool onlineGameStartFlag;
    QString my_userId;

public:
    //本地游戏相关
    void initPVPGame();
    void initPVEGame();
    void actionByPerson(int row, int col); // 人执行下棋
    void actionByAI(int clickRow, int clickCol); // 机器执行下棋
    void updateGameMap(int row, int col); // 每次落子后更新游戏棋盘
    bool isWin(int row, int col); // 判断游戏是否胜利
    bool isDeadGame(); // 判断是否和棋
    void calculateScore(); // 计算评分
    //--------------------------------------------------------------
    void startGame(); // 开始游戏
    //在线游戏相关
    void initOnlineGame(QString myUserId,STRU_LOAD_EXIST_ROOM_RS widgetItem);
    void updateOnlineGame(STRU_LOAD_EXIST_ROOM_RS roomInfo);
    void onlineMyChess(int row,int col);
public slots:
    void setRemainTime();
    void setOnlineRemainTime(STRU_SET_REMAIN_TIME setRemainTime);
    void on_pb_startGame_clicked();
    void onlineGameStart(STRU_GAME_STRAT gameStartPack);
    void opponentChessComing(STRU_PLAYER_CHESS palyerChess);
    void gameOverComing(bool winSide);//游戏结束
    void gameclear();
private:
    Ui::GameDialog *ui;
    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
signals:
    void SIG_exitOnlineGameDialog(int roomId);
    void SIG_readyGame(int roomId);
    void SIG_playerChess(STRU_PLAYER_CHESS);
    void SIG_gameDialogClose();
};

#endif // GAMEDIALOG_H
