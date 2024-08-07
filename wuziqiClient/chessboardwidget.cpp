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
#include "chessboardwidget.h"
#include "ui_chessboardwidget.h"
#include"Config/GameConfig.h"
#include"gamedialog.h"



ChessboardWidget::ChessboardWidget(GameDialog* gameDialog,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessboardWidget)
{
    ui->setupUi(this);
    m_pGameDialog = gameDialog;
//    setStyleSheet("background-image:url(:/res/image/chessboardBack.png)");
//    setFixedSize(kBoardMargin * 2 + kBlockSize * kBoardSizeNum, kBoardMargin * 2 + kBlockSize * kBoardSizeNum);
    // 开启鼠标hover功能，这两句一般要设置window的
    setMouseTracking(true);
    isStart = false;

}

ChessboardWidget::~ChessboardWidget()
{
    delete ui;
}

void ChessboardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 绘制棋盘
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
    painter.drawPixmap(rect(),QPixmap(":/res/image/chessboardBack.png"));
    QPen pen; // 调整线条宽度
    pen.setWidth(4);
    painter.setPen(pen);
    for (int i = 0; i < kBoardSizeNum + 1; i++)
    {
        painter.drawLine(kBoardMargin + kBlockSize * i, kBoardMargin, kBoardMargin + kBlockSize * i, size().height() - kBoardMargin);
        painter.drawLine(kBoardMargin, kBoardMargin + kBlockSize * i, size().width() - kBoardMargin, kBoardMargin + kBlockSize * i);
    }
    if(m_pGameDialog->gameStatus != PLAYING &&
        !m_pGameDialog->onlineGameStartFlag) return;//如果游戏未开始，直接return
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    // 绘制落子标记(防止鼠标出框越界)
    if (clickPosRow > 0 && clickPosRow < kBoardSizeNum &&
        clickPosCol > 0 && clickPosCol < kBoardSizeNum &&
        m_pGameDialog->gameMapVec[clickPosRow][clickPosCol] == 0)
    {
        if (!m_pGameDialog->playerFlag)
            brush.setColor(Qt::white);
        else
            brush.setColor(Qt::black);
        painter.setBrush(brush);
        painter.drawRect(kBoardMargin + kBlockSize * clickPosCol - kMarkSize / 2, kBoardMargin + kBlockSize * clickPosRow - kMarkSize / 2, kMarkSize, kMarkSize);
    }

    // 绘制棋子
    for (int i = 0; i < kBoardSizeNum; i++){
        for (int j = 0; j < kBoardSizeNum; j++)
        {
            if (m_pGameDialog->gameMapVec[i][j] == -1)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius, kRadius * 2, kRadius * 2);
            }
            else if (m_pGameDialog->gameMapVec[i][j] == 1)
            {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius, kRadius * 2, kRadius * 2);
            }
        }
    }
}

void ChessboardWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_pGameDialog->gameStatus != PLAYING) return;
    // 通过鼠标的hover确定落子的标记
    int x = event->x();
    int y = event->y();

    // 棋盘边缘不能落子
    if (x >= kBoardMargin + kBlockSize / 2 &&
        x < size().width() - kBoardMargin &&
        y >= kBoardMargin + kBlockSize / 2 &&
        y < size().height()- kBoardMargin)
    {
        // 获取最近的左上角的点
        int col = x / kBlockSize;
        int row = y / kBlockSize;

        int leftTopPosX = kBoardMargin + kBlockSize * col;
        int leftTopPosY = kBoardMargin + kBlockSize * row;

        // 根据距离算出合适的点击位置,一共四个点，根据半径距离选最近的
        clickPosRow = -1; // 初始化最终的值
        clickPosCol = -1;
        int len = 0; // 计算完后取整就可以了

        // 确定一个误差在范围内的点，且只可能确定一个出来
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col + 1;
        }
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - kBlockSize) * (y - leftTopPosY - kBlockSize));
        if (len < kPosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY - kBlockSize) * (y - leftTopPosY - kBlockSize));
        if (len < kPosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col + 1;
        }
    }

    // 存了坐标后也要重绘
    update();
}

void ChessboardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_pGameDialog->gameStatus != PLAYING) return;
    chessOneByPerson();
//     //人下棋，并且不能抢机器的棋
//    if (!(m_pGameDialog->gameType == pveGame && !m_pGameDialog->playerFlag))
//    {
//        chessOneByPerson();
//        // 如果是人机模式，需要调用AI下棋
//        if (m_pGameDialog->gameType == pveGame && !m_pGameDialog->playerFlag)
//        {
//            // 用定时器做一个延迟
//            QTimer::singleShot(kAIDelay, this, SLOT(chessOneByAI()));
//        }
//    }

}


void ChessboardWidget::chessOneByPerson()
{
    // 根据当前存储的坐标下子
    // 只有有效点击才下子，并且该处没有子
    if (clickPosRow != -1 && clickPosCol != -1 && m_pGameDialog->gameMapVec[clickPosRow][clickPosCol] == 0)
    {
        if(m_pGameDialog->gameType != onlineGame){
            m_pGameDialog->actionByPerson(clickPosRow, clickPosCol);
            QSound::play(CHESS_ONE_SOUND);
        }
        else{
            m_pGameDialog->onlineMyChess(clickPosRow,clickPosCol);
            QSound::play(CHESS_ONE_SOUND);
        }

        // 重绘
        update();
    }
}

void ChessboardWidget::chessOneByAI()
{
    m_pGameDialog->actionByAI(clickPosRow, clickPosCol);
    QSound::play(CHESS_ONE_SOUND);
    update();
}

void ChessboardWidget::initPVPGame()
{
//    game_type = PERSON;
//    m_pGameDialog->gameStatus = PLAYING;
//    m_pGameDialog->startGame(game_type);
//    isStart = 1;
//    update();
}

void ChessboardWidget::initPVEGame()
{
//    game_type = BOT;
//    m_pGameDialog->gameStatus = PLAYING;
//    m_pGameDialog->startGame(game_type);
//    isStart = 1;
    //    update();
}
