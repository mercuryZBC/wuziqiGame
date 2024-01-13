#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include <QWidget>
#include"GameModel.h"
class GameDialog;
namespace Ui {
class ChessboardWidget;
}

class ChessboardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChessboardWidget(GameDialog* game,QWidget *parent = nullptr);
    ~ChessboardWidget();
private:
    GameDialog* m_pGameDialog;
    bool isStart;
    int clickPosRow, clickPosCol; // 存储将点击的位置
protected:
    // 绘制
    void paintEvent(QPaintEvent *event);
    // 监听鼠标移动情况，方便落子
    void mouseMoveEvent(QMouseEvent *event);
    // 实际落子
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void chessOneByPerson();
    void chessOneByAI();
public:
    void initPVPGame();
    void initPVEGame();
private:
    Ui::ChessboardWidget *ui;
};

#endif // CHESSBOARDWIDGET_H
