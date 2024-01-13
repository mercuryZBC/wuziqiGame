#include <QPainter>
#include <QTimer>
#include <QSound>
#include <QMouseEvent>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <math.h>
#include<QTime>
#include "gamedialog.h"
#include "ui_gamedialog.h"



GameDialog::GameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameDialog)
{
    ui->setupUi(this);

    m_isOnlineGame = false;
    //设置棋盘布局
    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(3);
    ui->wdg_qipan->setLayout(m_layout);
    m_pChessboard = new ChessboardWidget(this);
    m_layout->addWidget(m_pChessboard);


    //设置玩家信息布局
    m_playerLayout1 = new QVBoxLayout;
    ui->wdg_player1->setLayout(m_playerLayout1);
    m_playerLayout2 = new QVBoxLayout;
    ui->wdg_player2->setLayout(m_playerLayout2);
    m_player1 = new PlayerInfo();
    m_player2 = new PlayerInfo();
    m_playerLayout1->addWidget(m_player1);
    m_playerLayout2->addWidget(m_player2);

    qsrand(QTime::currentTime().msec());
    gameStatus = WAIT;
    m_pTimer = new QTimer;

}

GameDialog::GameDialog(GameType gameType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameDialog)
{
    ui->setupUi(this);
    onlineGameStartFlag = false;
    connect(ui->pb_startGame,&QPushButton::clicked,this,&GameDialog::on_pb_startGame_clicked);
    //设置棋盘布局
    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(3);
    ui->wdg_qipan->setLayout(m_layout);
    m_pChessboard = new ChessboardWidget(this);
    m_layout->addWidget(m_pChessboard);


    //设置玩家信息布局
    m_playerLayout1 = new QVBoxLayout;
    ui->wdg_player1->setLayout(m_playerLayout1);
    m_playerLayout2 = new QVBoxLayout;
    ui->wdg_player2->setLayout(m_playerLayout2);
    m_player1 = new PlayerInfo();
    m_player2 = new PlayerInfo();
    m_playerLayout1->addWidget(m_player1);
    m_playerLayout2->addWidget(m_player2);

    qsrand(QTime::currentTime().msec());
    gameStatus = WAIT;
    m_pTimer = new QTimer;
    connect(m_pTimer,&QTimer::timeout,this,&GameDialog::setRemainTime);
    switch(gameType){
        case pvpGame:
        {
            initPVPGame();
            break;
        }

        case pveGame:
        {
            initPVEGame();
            break;
        }
        case onlineGame:
        {
        }
    }
}

GameDialog::~GameDialog()
{
    delete ui;
}

void GameDialog::initPVPGame()
{
    qDebug()<<"GameDialog::initPVPGame";
    // 己方下为true,对方下位false
    m_pTimer->stop();
    gameType = pvpGame;
    playerFlag = true;
    playerSide1 = qrand()%2;//随机确定白色方和黑色方
    p1Name = "本地玩家1";
    p2Name = "本地玩家2";
    remainMinP1 = 10;
    remainSecP1 = 0;
    remainMinP2 = 10;
    remainSecP2 = 0;
    m_player1->setPlayerInfo(p1Name,1,playerSide1);
    m_player2->setPlayerInfo(p2Name,1,!playerSide1);
    // 初始棋盘
    gameMapVec.clear();
    for (int i = 0; i < kBoardSizeNum; i++)
    {
            std::vector<int> lineBoard;
            for (int j = 0; j < kBoardSizeNum; j++)
                lineBoard.push_back(0);
            gameMapVec.push_back(lineBoard);
    }


}

void GameDialog::initPVEGame()
{
    qDebug()<<"GameDialog::initPVEGame";
    m_pTimer->stop();
    gameType = pveGame;
    playerFlag = true;
    playerSide1 = true;//默认真人玩家为黑色方
    p1Name = "本地玩家";
    p2Name = "AI";
    remainMinP1 = 10;
    remainSecP1 = 0;
    remainMinP2 = 10;
    remainSecP2 = 0;
    m_player1->setPlayerInfo(p1Name,1,playerSide1);
    m_player2->setPlayerInfo(p2Name,1,!playerSide1);
    // 初始棋盘
    gameMapVec.clear();
    for (int i = 0; i < kBoardSizeNum; i++)
    {
            std::vector<int> lineBoard;
            for (int j = 0; j < kBoardSizeNum; j++)
                lineBoard.push_back(0);
            gameMapVec.push_back(lineBoard);
    }
    //AI模式，需要初始化评分数组
    scoreMapVec.clear();
    for (int i = 0; i < kBoardSizeNum; i++)
    {
            std::vector<int> lineScores;
            for (int j = 0; j < kBoardSizeNum; j++)
                lineScores.push_back(0);
            scoreMapVec.push_back(lineScores);
    }
    if(!playerFlag){
            actionByAI(6,6);
    }
}

void GameDialog::initOnlineGame(QString myUserId,STRU_LOAD_EXIST_ROOM_RS roomInfo)
{
    gameType = onlineGame;
    ui->pb_startGame->hide();
    my_userId = myUserId;
    m_roomId = roomInfo.roomId;
    m_isOnlineGame = true;
    QString title = QString("房间%1").arg(roomInfo.roomId);
    setWindowTitle(title);
    if(roomInfo.user1Exist){
        m_player1->setPlayerInfo(roomInfo.user1Id,roomInfo.user1IconId,0);
        m_user1Id = roomInfo.user1Id;
        m_user1IsExist = true;
    }
    else{
        m_player1->setPlayerInfo("",999,0);
        m_user1IsExist = false;
    }
    if(roomInfo.user2Exist){
        m_player2->setPlayerInfo(roomInfo.user2Id,roomInfo.user2IconId,0);
        m_user2Id = roomInfo.user2Id;
        m_user2IsExist = true;
    }
    else{
       m_player2->setPlayerInfo("",999,0);
        m_user2IsExist = false;
    }
    if(m_user1IsExist&&m_user2IsExist) ui->pb_startGame->show();
    show();
}

void GameDialog::updateOnlineGame(STRU_LOAD_EXIST_ROOM_RS roomInfo)
{
    ui->pb_startGame->hide();
    if(roomInfo.user1Exist){
        m_player1->setPlayerInfo(roomInfo.user1Id,roomInfo.user1IconId,0);
        m_user1Id = roomInfo.user1Id;
        m_user1IsExist = true;
    }
    else{
        m_player1->setPlayerInfo("",999,0);
        m_user1IsExist = false;
    }
    if(roomInfo.user2Exist){
        m_player2->setPlayerInfo(roomInfo.user2Id,roomInfo.user2IconId,0);
        m_user2Id = roomInfo.user2Id;
        m_user2IsExist = true;
    }
    else{
        m_player2->setPlayerInfo("",999,0);
        m_user2IsExist = false;
    }
    if(m_user1IsExist&&m_user2IsExist) ui->pb_startGame->show();
}

void GameDialog::startGame()
{
    if(m_isOnlineGame == false){
       //开启定时器
       m_pTimer->start(1000);
       gameStatus = PLAYING;
    }
    else{
       gameMapVec.resize(15,std::vector<int>(kBoardSizeNum, 0));
       emit SIG_readyGame(m_roomId);

    }

}

void GameDialog::calculateScore()
{
    // 统计玩家或者电脑连成的子
    int personNum = 0; // 玩家连成子的个数
    int botNum = 0; // AI连成子的个数
    int emptyNum = 0; // 各方向空白位的个数

    // 清空评分数组
    scoreMapVec.clear();
    for (int i = 0; i < kBoardSizeNum; i++)
    {
            std::vector<int> lineScores;
            for (int j = 0; j < kBoardSizeNum; j++)
                lineScores.push_back(0);
            scoreMapVec.push_back(lineScores);
    }

    // 计分（此处是完全遍历，其实可以用bfs或者dfs加减枝降低复杂度，通过调整权重值，调整AI智能程度以及攻守风格）
    for (int row = 0; row < kBoardSizeNum; row++)
            for (int col = 0; col < kBoardSizeNum; col++)
            {
                // 空白点就算
                if (row > 0 && col > 0 &&
                    gameMapVec[row][col] == 0)
                {
                    // 遍历周围八个方向
                    for (int y = -1; y <= 1; y++)
                        for (int x = -1; x <= 1; x++)
                        {
                            // 重置
                            personNum = 0;
                            botNum = 0;
                            emptyNum = 0;

                            // 原坐标不算
                            if (!(y == 0 && x == 0))
                            {
                                // 每个方向延伸4个子

                                // 对玩家白子评分（正反两个方向）
                                for (int i = 1; i <= 4; i++)
                                {
                                    if (row + i * y > 0 && row + i * y < kBoardSizeNum &&
                                        col + i * x > 0 && col + i * x < kBoardSizeNum &&
                                        gameMapVec[row + i * y][col + i * x] == 1) // 玩家的子
                                    {
                                        personNum++;
                                    }
                                    else if (row + i * y > 0 && row + i * y < kBoardSizeNum &&
                                             col + i * x > 0 && col + i * x < kBoardSizeNum &&
                                             gameMapVec[row + i * y][col + i * x] == 0) // 空白位
                                    {
                                        emptyNum++;
                                        break;
                                    }
                                    else            // 出边界
                                        break;
                                }

                                for (int i = 1; i <= 4; i++)
                                {
                                    if (row - i * y > 0 && row - i * y < kBoardSizeNum &&
                                        col - i * x > 0 && col - i * x < kBoardSizeNum &&
                                        gameMapVec[row - i * y][col - i * x] == 1) // 玩家的子
                                    {
                                        personNum++;
                                    }
                                    else if (row - i * y > 0 && row - i * y < kBoardSizeNum &&
                                             col - i * x > 0 && col - i * x < kBoardSizeNum &&
                                             gameMapVec[row - i * y][col - i * x] == 0) // 空白位
                                    {
                                        emptyNum++;
                                        break;
                                    }
                                    else            // 出边界
                                        break;
                                }

                                if (personNum == 1)                      // 杀二
                                    scoreMapVec[row][col] += 10;
                                else if (personNum == 2)                 // 杀三
                                {
                                    if (emptyNum == 1)
                                        scoreMapVec[row][col] += 30;
                                    else if (emptyNum == 2)
                                        scoreMapVec[row][col] += 40;
                                }
                                else if (personNum == 3)                 // 杀四
                                {
                                    // 量变空位不一样，优先级不一样
                                    if (emptyNum == 1)
                                        scoreMapVec[row][col] += 60;
                                    else if (emptyNum == 2)
                                        scoreMapVec[row][col] += 110;
                                }
                                else if (personNum == 4)                 // 杀五
                                    scoreMapVec[row][col] += 10100;

                                // 进行一次清空
                                emptyNum = 0;

                                // 对AI黑子评分
                                for (int i = 1; i <= 4; i++)
                                {
                                    if (row + i * y > 0 && row + i * y < kBoardSizeNum &&
                                        col + i * x > 0 && col + i * x < kBoardSizeNum &&
                                        gameMapVec[row + i * y][col + i * x] == 1) // 玩家的子
                                    {
                                        botNum++;
                                    }
                                    else if (row + i * y > 0 && row + i * y < kBoardSizeNum &&
                                             col + i * x > 0 && col + i * x < kBoardSizeNum &&
                                             gameMapVec[row +i * y][col + i * x] == 0) // 空白位
                                    {
                                        emptyNum++;
                                        break;
                                    }
                                    else            // 出边界
                                        break;
                                }

                                for (int i = 1; i <= 4; i++)
                                {
                                    if (row - i * y > 0 && row - i * y < kBoardSizeNum &&
                                        col - i * x > 0 && col - i * x < kBoardSizeNum &&
                                        gameMapVec[row - i * y][col - i * x] == -1) // AI的子
                                    {
                                        botNum++;
                                    }
                                    else if (row - i * y > 0 && row - i * y < kBoardSizeNum &&
                                             col - i * x > 0 && col - i * x < kBoardSizeNum &&
                                             gameMapVec[row - i * y][col - i * x] == 0) // 空白位
                                    {
                                        emptyNum++;
                                        break;
                                    }
                                    else            // 出边界
                                        break;
                                }

                                if (botNum == 0)                      // 普通下子
                                    scoreMapVec[row][col] += 5;
                                else if (botNum == 1)                 // 活二
                                    scoreMapVec[row][col] += 10;
                                else if (botNum == 2)
                                {
                                    if (emptyNum == 1)                // 死三
                                        scoreMapVec[row][col] += 25;
                                    else if (emptyNum == 2)
                                        scoreMapVec[row][col] += 50;  // 活三
                                }
                                else if (botNum == 3)
                                {
                                    if (emptyNum == 1)                // 死四
                                        scoreMapVec[row][col] += 55;
                                    else if (emptyNum == 2)
                                        scoreMapVec[row][col] += 100; // 活四
                                }
                                else if (botNum >= 4)
                                    scoreMapVec[row][col] += 10000;   // 活五

                            }
                        }

                }
            }
}

void GameDialog::actionByPerson(int row, int col)
{
    updateGameMap(row,col);
    // 判断输赢
    if (isWin(row,col) && gameStatus == PLAYING)
    {
            qDebug() << "win";
            gameStatus = WIN;
            QSound::play(WIN_SOUND);
            QString str;
            if (gameMapVec[row][col] == 1)
                str = "white player";
            else if (gameMapVec[row][col] == -1)
                str = "black player";
            QMessageBox::StandardButton btnValue = QMessageBox::information(this, "congratulations", str + " win!");

            // 重置游戏状态，否则容易死循环
            if (btnValue == QMessageBox::Ok)
            {
                if(gameType == pvpGame) initPVPGame();
                if(gameType == pveGame) initPVEGame();
                startGame();
                gameStatus = PLAYING;
            }
    }
    // 判断死局
    else if (isDeadGame())
    {
            QSound::play(LOSE_SOUND);
            QMessageBox::StandardButton btnValue = QMessageBox::information(this, "oops", "dead game!");
            if (btnValue == QMessageBox::Ok)
            {
                if(gameType == pvpGame) initPVPGame();
                if(gameType == pveGame) initPVEGame();
                startGame();
                gameStatus = PLAYING;
            }
    }
    else if(gameType == pveGame){
        actionByAI(row, col);
    }

}

void GameDialog::actionByAI(int row, int col)
{
    // 计算评分
    calculateScore();

    // 从评分中找出最大分数的位置
    int maxScore = 0;
    std::vector<std::pair<int, int>> maxPoints;

    for (int row = 1; row < kBoardSizeNum; row++)
            for (int col = 1; col < kBoardSizeNum; col++)
            {
                // 前提是这个坐标是空的
                if (gameMapVec[row][col] == 0)
                {
                    if (scoreMapVec[row][col] > maxScore)          // 找最大的数和坐标
                    {
                        maxPoints.clear();
                        maxScore = scoreMapVec[row][col];
                        maxPoints.push_back(std::make_pair(row, col));
                    }
                    else if (scoreMapVec[row][col] == maxScore)     // 如果有多个最大的数，都存起来
                        maxPoints.push_back(std::make_pair(row, col));
                }
            }

    // 随机落子，如果有多个点的话
    srand((unsigned)time(0));
    int index = rand() % maxPoints.size();

    std::pair<int, int> pointPair = maxPoints.at(index);
    row = pointPair.first; // 记录落子点
    col = pointPair.second;
    updateGameMap(row, col);
    // 判断输赢
    if (isWin(row,col) && gameStatus == PLAYING)
    {
            qDebug() << "win";
            gameStatus = WIN;
            QSound::play(WIN_SOUND);
            QString str;
            if (gameMapVec[row][col] == 1)
                str = "white player";
            else if (gameMapVec[row][col] == -1)
                str = "black player";
            QMessageBox::StandardButton btnValue = QMessageBox::information(this, "congratulations", str + " win!");

            // 重置游戏状态，否则容易死循环
            if (btnValue == QMessageBox::Ok)
            {
                if(gameType == pvpGame) initPVPGame();
                if(gameType == pveGame) initPVEGame();
                ui->pb_startGame->show();
                gameStatus = PLAYING;
            }
    }
    // 判断死局
    if (isDeadGame())
    {
            QSound::play(LOSE_SOUND);
            QMessageBox::StandardButton btnValue = QMessageBox::information(this, "oops", "dead game!");
            if (btnValue == QMessageBox::Ok)
            {
                if(gameType == pvpGame) initPVPGame();
                if(gameType == pveGame) initPVEGame();
                ui->pb_startGame->show();
                gameStatus = PLAYING;
            }
    }
}

void GameDialog::updateGameMap(int row, int col)
{
    if (playerFlag)
            gameMapVec[row][col] = 1;
    else
            gameMapVec[row][col] = -1;

    // 换手
    playerFlag = !playerFlag;
}

bool GameDialog::isWin(int row, int col)
{
    // 横竖斜四种大情况，每种情况都根据当前落子往后遍历5个棋子，有一种符合就算赢
    // 水平方向
    for (int i = 0; i < 5; i++)
    {
            // 往左5个，往右匹配4个子，20种情况
            if (col - i > 0 &&
                col - i + 4 < kBoardSizeNum &&
                gameMapVec[row][col - i] == gameMapVec[row][col - i + 1] &&
                gameMapVec[row][col - i] == gameMapVec[row][col - i + 2] &&
                gameMapVec[row][col - i] == gameMapVec[row][col - i + 3] &&
                gameMapVec[row][col - i] == gameMapVec[row][col - i + 4])
                return true;
    }

    // 竖直方向(上下延伸4个)
    for (int i = 0; i < 5; i++)
    {
            if (row - i > 0 &&
                row - i + 4 < kBoardSizeNum &&
                gameMapVec[row - i][col] == gameMapVec[row - i + 1][col] &&
                gameMapVec[row - i][col] == gameMapVec[row - i + 2][col] &&
                gameMapVec[row - i][col] == gameMapVec[row - i + 3][col] &&
                gameMapVec[row - i][col] == gameMapVec[row - i + 4][col])
                return true;
    }

    // 左斜方向
    for (int i = 0; i < 5; i++)
    {
            if (row + i < kBoardSizeNum &&
                row + i - 4 > 0 &&
                col - i > 0 &&
                col - i + 4 < kBoardSizeNum &&
                gameMapVec[row + i][col - i] == gameMapVec[row + i - 1][col - i + 1] &&
                gameMapVec[row + i][col - i] == gameMapVec[row + i - 2][col - i + 2] &&
                gameMapVec[row + i][col - i] == gameMapVec[row + i - 3][col - i + 3] &&
                gameMapVec[row + i][col - i] == gameMapVec[row + i - 4][col - i + 4])
                return true;
    }

    // 右斜方向
    for (int i = 0; i < 5; i++)
    {
            if (row - i > 0 &&
                row - i + 4 < kBoardSizeNum &&
                col - i > 0 &&
                col - i + 4 < kBoardSizeNum &&
                gameMapVec[row - i][col - i] == gameMapVec[row - i + 1][col - i + 1] &&
                gameMapVec[row - i][col - i] == gameMapVec[row - i + 2][col - i + 2] &&
                gameMapVec[row - i][col - i] == gameMapVec[row - i + 3][col - i + 3] &&
                gameMapVec[row - i][col - i] == gameMapVec[row - i + 4][col - i + 4])
                return true;
    }

    return false;
}

bool GameDialog::isDeadGame()
{
    // 所有空格全部填满
    for (int i = 1; i < kBoardSizeNum; i++)
            for (int j = 1; j < kBoardSizeNum; j++)
            {
                if (!(gameMapVec[i][j] == 1 || gameMapVec[i][j] == -1))
                    return false;
            }
    return true;
}

void GameDialog::onlineMyChess(int row, int col)
{
    qDebug()<<"GameDialog::onlineMyChess";
    if(playerFlag == 1){
        gameMapVec[row][col] =1;
    }
    else{
        gameMapVec[row][col] =-1;
    }
    STRU_PLAYER_CHESS playerChess;
    playerChess.roomId = m_roomId;
    playerChess.side = playerFlag;//黑色方或白色方
    playerChess.chessRow = row;
    playerChess.chessCol = col;
    emit SIG_playerChess(playerChess);
    m_pChessboard->update();
    gameStatus = WAIT;
}
void GameDialog::setRemainTime()
{
    qDebug()<<"text";
    if(playerFlag == playerSide1){
        if(remainSecP1 == 0){
            remainSecP1 = 59;
            remainMinP1--;
        }
        else{
            remainSecP1--;
        }
        if(remainMinP1 == 0 && remainSecP1 == 0){

        }
        else m_player1->setRemainTime(remainMinP1,remainSecP1);
    }
    else{
        if(remainSecP2 == 0){
            remainSecP2 = 59;
            remainMinP2--;
        }
        else{
            remainSecP2--;
        }
        if(remainMinP2 == 0 && remainSecP2 == 0){

        }
        else m_player2->setRemainTime(remainMinP2,remainSecP2);
    }
}

void GameDialog::setOnlineRemainTime(STRU_SET_REMAIN_TIME setRemainTime)
{
    int remainTime = setRemainTime.remainTime;
    int minite = remainTime/600;
    int sec = (remainTime%600)/10;
    if(!setRemainTime.side){
        m_player1->setRemainTime(minite,sec);
    }
    else{
        m_player2->setRemainTime(minite,sec);
    }
}
void GameDialog::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    if(m_isOnlineGame == true){
        m_isOnlineGame = false;
        emit SIG_exitOnlineGameDialog(m_roomId);
    }
    emit SIG_gameDialogClose();
}



void GameDialog::on_pb_startGame_clicked()
{
    qDebug()<<"----------";
    ui->pb_startGame->hide();
    startGame();
}

void GameDialog::onlineGameStart(STRU_GAME_STRAT gameStartPack)
{

    m_player1->setSide(!gameStartPack.user1isBlack);
    m_player2->setSide(gameStartPack.user1isBlack);
    if(m_user1Id == my_userId){
        playerFlag = !gameStartPack.user1isBlack;
    }
    else{
        playerFlag = gameStartPack.user1isBlack;
    }
    if(playerFlag == true) gameStatus = PLAYING;
    for (int i = 0; i < kBoardSizeNum; i++)
    {
        std::vector<int> lineBoard;
        for (int j = 0; j < kBoardSizeNum; j++)
            lineBoard.push_back(0);
        gameMapVec.push_back(lineBoard);
    }
    onlineGameStartFlag = true;
}

void GameDialog::opponentChessComing(STRU_PLAYER_CHESS playerChess)
{
    qDebug()<<"GameDialog::opponentChessComing";
    if(playerFlag == true){//本方true
        gameMapVec[playerChess.chessRow][playerChess.chessCol] = -1;
    }
    else{
        gameMapVec[playerChess.chessRow][playerChess.chessCol] = 1;
    }
    gameStatus = PLAYING;
    m_pChessboard->update();
}

void GameDialog::gameOverComing(bool winSide)
{
    if(winSide == playerFlag){
        QSound::play(WIN_SOUND);
        QMessageBox::information(this,"游戏结束","你赢了");
    }
    else{
        QSound::play(LOSE_SOUND);
        QMessageBox::information(this,"游戏结束","强大的对手");
    }
    qDebug()<<"GameDialog::gameOverComing";
    ui->pb_startGame->show();
}

void GameDialog::gameclear()
{

}
