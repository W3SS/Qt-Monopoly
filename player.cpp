#include "player.h"

Player::Player()
{
    name="Player";
    rounds=0;
    balance=30000;
    for(int i=0;i<32;i++)
    {
        cards_owned[i]=0;
    }
}
void Player::buy_card(int index_of_card,int price_of_card)
{
    cards_owned[index_of_card]=1;
    balance=balance-price_of_card;
}
void Player::sell_card(int index_of_card,int price_of_card)
{
    cards_owned[index_of_card]=0;
    balance=balance-price_of_card;
}
