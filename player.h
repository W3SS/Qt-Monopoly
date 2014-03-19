#ifndef PLAYER_H
#define PLAYER_H
#include "QString"
#include "cards.h"
#include "QPushButton"
#include "QFrame"
class Player
{
    public:
    QString name;
    QPushButton *b;
    QFrame *myinfo;
    int frame_x,frame_y,frame_width,frame_height;
    int cards_owned[32];                // 0 if not bought by player
    int balance;
    int rounds;
    Player();
    void buy_card(int ,int);
    void sell_card(int ,int);
};

#endif // PLAYER_H
