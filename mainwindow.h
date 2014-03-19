#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QDesktopWidget"
#include <QMainWindow>
#include "QFrame"
#include "QPushButton"
#include "QLayout"
#include "qlayout.h"
#include "QTextEdit"
#include "QLabel"
#include "QLineEdit"
#include "cards.h"
#include "player.h"
#include "bank.h"
#include "QImage"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    Bank b;
    int pid,cid;
     int x,y,z,count_of_cards;
     int prev,next;
    //------------var chinya------------------
    QDesktopWidget *mydesk;
    QRect rect;
    int x_max,y_max;
    QWidget *window;
    QPushButton *dice;
    QPushButton *button[32];
    QFrame *board,*current_player,*current_card;
    int number_of_players,player_width,player_height;
    QLabel *label[4],*current_player_name,*current_player_balance,*current_player_cards;
    QTextEdit *text[4];
    QLineEdit *dice_display[2];
    Ui::MainWindow *ui;
    int close_x,close_y,close_width,close_height;
    int board_width,board_height,bt1_height,bt1_width,bt2_height,bt2_width;
    int dice_width,dice_height,dice_x,dice_y;
    static int index1,index2,chance,index3,index4;
    QPushButton *cls;
    Cards array_of_cards[32];
    Player *player[4];
    QLabel *player1_name,*player2_name,*player3_name,*player4_name;
    QLabel *player1_score,*player2_score,*player3_score,*player4_score;
    int current_player_x,current_player_y,current_player_width,current_player_height;

    QPushButton *buy_button,*sell_button,*build_button;

    QLabel *current_card_name_of_city,*current_card_owner,
    *current_card_price_of_city,
    current_card_rent_without_house,current_card_rent_with_1_house,
    current_card_rent_with_2_house,
    current_card_rent_with_3_house,
    current_card_rent_with_hotel,
    current_card_cost_of_house,
    current_card_cost_of_hotel,
    current_card_mortgage_val,
    *current_card_type_of_building;

    int current_card_x,current_card_y,current_card_width,current_card_height;



    explicit MainWindow(QWidget *parent = 0);
    //--------------core functions----------------
    void update_info(int ,int,int);

    void pay_rent(int,int);
    void if_start(int);
    void if_income_tax(int);
    void if_chance(int,int);
    void if_jail(int);
    void if_collect_500(int );
    void if_comm_chest(int,int);
    void if_club(int);
    void if_rest_room(int);
    void if_wealth_tax(int);
    void if_goto_club(int);
    void if_normal_card(int,int);
    //--------------------------------------------
    void delay();
    ~MainWindow();
    void show_frames();
    void set_visible_frames();
    void update_current_player();
    void set_current_card( );
    void score_board_update();
    void after_roll();
    void after_roll_card();
public slots:
    void purchase();
    void sell();
    void renovate(int,int);
    //----------------------------------
    void start_2();
    void start_3();
    void start_4();
     void show_players();
    void setdie();
    void finish();
};
#endif // MAINWINDOW_H
