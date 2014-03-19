#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QRect"
#include "QFrame"
#include "QLayout"
#include "QButtonGroup"
#include "QPushButton"
#include "qlayout.h"
#include <iostream>
#include "QTime"
#include "cards.h"
#include "ctime"

int MainWindow::index1=0;
int MainWindow::index2=0;
int MainWindow::chance=0;
int MainWindow::index3=0;
int MainWindow::index4=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mydesk = new QDesktopWidget();
    rect=mydesk->screenGeometry();
    x_max=rect.width();
    y_max=rect.height();
    if(x_max/(x_max%y_max)<3)
    {
        board_width=board_height=y_max;
        bt1_height=bt1_width=(board_height*(.10));
        bt2_height=bt2_width=(board_width*(.15));
    }
    else
    {
        board_width=board_height=y_max*(0.9);
        bt1_height=bt1_width=(board_height*(.10));
        bt2_height=bt2_width=(board_width*(.15));
    }
    QWidget *frame = new QWidget(this);

    window=new QWidget();
    frame->setGeometry(0, 0,634,424);
    frame->setStyleSheet("background-image: url(c:\\mix.jpg)");
    board=new QFrame(window);
    board->setGeometry(0,0,board_width,board_height);
    board->setStyleSheet("background-color:rgb(155,155,155)");
    board->setFrameStyle(3);
    cls=new QPushButton("EXIT!!!",window);
    close_x=board_width;
    close_width=x_max-board_width;
    close_height=y_max/10;
    close_y=y_max-close_height;
    cls->setGeometry(close_x,close_y,close_width,close_height);
    cls->setVisible(true);
    //creating the buttons
    for(int i=0;i<32;i++)
    {
        button[i]=new QPushButton();
    }
    button[8]->setGeometry(0,2,bt2_height,bt2_width);

    button[8]->setParent(board);
    button[16]->setGeometry(board_height-bt2_height-5,0,bt2_height,bt2_width);

    button[16]->setParent(board);
    button[24]->setGeometry(board_height-bt2_height,board_height-bt2_height-5,bt2_height,bt2_width);

    button[24]->setParent(board);
    button[0]->setGeometry(5,board_height-bt2_height,bt2_height,bt2_width);

    button[0]->setParent(board);
    int x,y;
    x=0,y=board_height-bt2_height-bt1_height;
    for(int i=1;i<=7;i++)
    {
        button[i]->setGeometry(x,y,bt1_height,bt1_width);
        button[i]->setParent(board);
        y-=bt1_height;
    }
    x=bt2_height,y=0;
    for(int i=9;i<=15;i++)
    {
        button[i]->setGeometry(x,y,bt1_height,bt1_width);

        button[i]->setParent(board);
        x+=bt1_height;
    }
    x=board_width-bt1_width,y=bt2_height;
    for(int i=17;i<=23;i++)
    {
        button[i]->setGeometry(x,y,bt1_height,bt1_width);
        button[i]->setParent(board);
        y+=bt1_height;
    }
    x=board_width-bt2_width-bt1_width,y=board_height-bt1_height;
    for(int i=25;i<=31;i++)
    {
        button[i]->setGeometry(x,y,bt1_height,bt1_width);
        button[i]->setParent(board);
        x-=bt1_width;
    }
    dice=new QPushButton("Roll!",board);
    dice_width=board_width/10;
    dice_height=board_height/10;
    dice_x=(board_width-dice_width)/2;
    dice_y=(board_height-dice_height)/2;
    dice->setGeometry(dice_x,dice_y,dice_width,dice_height);
    dice->setStyleSheet("* { background-color: rgb(0,255,255) }");
    dice_display[0]=new QLineEdit(board);
    dice_display[0]->setGeometry(dice_x-(dice_width),dice_y+(dice_height/5),dice_width/2,dice_height/2);
    dice_display[0]->setStyleSheet("color: rgb(0,0,0);background-color: rgb(255,255,255)");
    dice_display[0]->setVisible(true);
    dice_display[0]->setEnabled(false);
    dice_display[1]=new QLineEdit(board);
    dice_display[1]->setGeometry(dice_x+((3*dice_width)/2),dice_y+(dice_height/5),dice_width/2,dice_height/2);
    dice_display[1]->setStyleSheet("color: rgb(0,0,0);background-color: rgb(255,255,255)");;
    dice_display[1]->setVisible(true);
    dice_display[1]->setEnabled(false);

    //------------------******************---------------------------------
    int player1_width=bt2_width/4,player1_height=bt2_width/4,player1_x=button[0]->x(),player1_y=button[0]->y();
    int player2_width=bt2_width/4,player2_height=bt2_width/4,player2_x=bt2_width-player2_width,player2_y=button[0]->y();
    int player3_width=bt2_width/4,player3_height=bt2_width/4,player3_x=bt2_width-player2_width,player3_y=button[0]->y()+bt2_width-player3_width;
    int player4_width=bt2_width/4,player4_height=bt2_width/4,player4_x=button[0]->x(),player4_y=button[0]->y()+bt2_width-player3_width;
    player_width=bt1_width/2,player_height=bt1_width/2;
    //------------------******************---------------------------------
    player[0]=new Player();
    player[1]=new Player();
    player[2]=new Player();
    player[3]=new Player();
    player[0]->b=new QPushButton("1",window);
    player[0]->b->setGeometry(player1_x,player1_y,player1_width,player1_height);
    player[1]->b=new QPushButton("2",window);
    player[1]->b->setGeometry(player2_x,player2_y,player2_width,player2_height);
    player[2]->b=new QPushButton("3",window);
    player[2]->b->setGeometry(player3_x,player3_y,player3_width,player3_height);
    player[3]->b=new QPushButton("4",window);
    player[3]->b->setGeometry(player4_x,player4_y,player4_width,player4_height);
    //----------------frames--------------------
    player[0]->myinfo=new QFrame(window);
    player[0]->frame_x=board_width;
    player[0]->frame_y=0;
    player[0]->frame_width=(x_max-board_width)/4;
    player[0]->frame_height=(y_max)/8;
    player[0]->myinfo->setGeometry(player[0]->frame_x,player[0]->frame_y,player[0]->frame_width,player[0]->frame_height);

    player[0]->myinfo->setFrameStyle(3);
    player1_name=new QLabel(window);
    player1_score=new QLabel(window);
    player1_name->setText("  NONE!!");
    QString temp="  Amount :-";
    temp.append(QString::number(player[0]->balance));
    player1_score->setText(temp);
    player1_name->setGeometry(player[0]->frame_x,player[0]->frame_y,player[0]->frame_width,(player[0]->frame_height/2));
    player1_score->setGeometry(player[0]->frame_x,(player[0]->frame_height/2),player[0]->frame_width,(player[0]->frame_height/2));
    player1_score->setVisible(true);
    player1_name->setVisible(true);
//------------------player-1 end------------------------
    player[1]->myinfo=new QFrame(window);
    player[1]->frame_x=board_width+player[0]->frame_width;
    player[1]->frame_y=0;
    player[1]->frame_width=(x_max-board_width)/4;
    player[1]->frame_height=(y_max)/8;
    player[1]->myinfo->setGeometry(player[1]->frame_x,player[1]->frame_y,player[1]->frame_width,player[1]->frame_height);
    //player[1]->myinfo->setStyleSheet("background-color:rgb(155,155,155)");
    player[1]->myinfo->setFrameStyle(3);
    player2_name=new QLabel(window);
    player2_score=new QLabel(window);
    player2_name->setText("  NONE!!");
    temp="  Amount :-";
    temp.append(QString::number(player[1]->balance));
    player2_score->setText(temp);
    player2_name->setGeometry(player[1]->frame_x,player[1]->frame_y,player[1]->frame_width,(player[1]->frame_height/2));
    player2_score->setGeometry(player[1]->frame_x,(player[1]->frame_height/2),player[1]->frame_width,(player[1]->frame_height/2));
    player2_score->setVisible(true);
    player2_name->setVisible(true);
//------------player-2 end--------------------
    player[2]->myinfo=new QFrame(window);
    player[2]->frame_x=board_width+2*player[1]->frame_width;
    player[2]->frame_y=0;
    player[2]->frame_width=(x_max-board_width)/4;
    player[2]->frame_height=(y_max)/8;
    player[2]->myinfo->setGeometry(player[2]->frame_x,player[2]->frame_y,player[2]->frame_width,player[2]->frame_height);
    //player[2]->myinfo->setStyleSheet("background-color:rgb(155,155,155)");
    player[2]->myinfo->setFrameStyle(3);
    player3_name=new QLabel(window);
    player3_score=new QLabel(window);
    player3_name->setText("  NONE!!");
    temp="  Amount :-";
    temp.append(QString::number(player[2]->balance));
    player3_score->setText(temp);
    player3_name->setGeometry(player[2]->frame_x,player[2]->frame_y,player[2]->frame_width,(player[2]->frame_height/2));
    player3_score->setGeometry(player[2]->frame_x,(player[2]->frame_height/2),player[2]->frame_width,(player[2]->frame_height/2));
    player3_score->setVisible(true);
    player3_name->setVisible(true);
//------------player-3 end--------------------

    player[3]->myinfo=new QFrame(window);
    player[3]->frame_x=board_width+3*player[2]->frame_width;
    player[3]->frame_y=0;
    player[3]->frame_width=(x_max-board_width)/4;
    player[3]->frame_height=(y_max)/8;
    player[3]->myinfo->setGeometry(player[3]->frame_x,player[3]->frame_y,player[3]->frame_width,player[3]->frame_height);
    //player[3]->myinfo->setStyleSheet("background-color:rgb(155,155,155)");
    player[3]->myinfo->setFrameStyle(3);
    player4_name=new QLabel(window);
    player4_score=new QLabel(window);
    player4_name->setText("  NONE!!");
    temp="  Amount :-";
    temp.append(QString::number(player[3]->balance));
    player4_score->setText(temp);
    player4_name->setGeometry(player[3]->frame_x,player[3]->frame_y,player[3]->frame_width,(player[3]->frame_height/2));
    player4_score->setGeometry(player[3]->frame_x,(player[3]->frame_height/2),player[3]->frame_width,(player[3]->frame_height/2));
    player4_score->setVisible(true);
    player4_name->setVisible(true);
    //------------player-4 end--------------------
    //------------frame end-----------------
    //Chance and community chests-----------------------------------------------------------------------------
    for(int i=0;i<4;i++)
    {
        text[i]=new QTextEdit();
        text[i]->setStyleSheet("* { background-color: rgb(240,255,255) }");
        label[i]=new QLabel();
    }
    label[0]->setGeometry(215,100,60,60);
    label[0]->setParent(board);
    label[0]->setText("CHANCE");
    label[0]->setVisible(true);
    text[0]->setGeometry(115,145,260,160);
    text[0]->setText("2-Loss in share market Rs.2000\n4-Fine for drink and drive Rs.1000"
               "\n6-House repairing Rs.1500\n8-Loss due to fire in godown Rs.3000\n10-Go to Jail\n12-Go to rest house,you can not play next turn");

    text[0]->setParent(board);
    text[0]->setEnabled(false);
    text[0]->setVisible(true);
    label[1]->setGeometry(485,100,100,60);
    label[1]->setParent(board);
    label[1]->setText("COMMUNITY\n     CHEST");
    label[1]->setVisible(true);
    text[1]->setGeometry(385,145,260,160);
    text[1]->setText("2-Collect Rs.500/player\n4-1st prize in contest,Rs.2500"
               "\n6-Tax refund Rs.2000\n8-Won jackpot of Rs.1000\n10-Recieve interest on shares Rs.1500\n12-Sale of stock, Rs.3000");
    text[1]->setParent(board);
    text[1]->setEnabled(false);
    text[1]->setVisible(true);
    label[2]->setGeometry(215,400,60,60);
    label[2]->setParent(board);
    label[2]->setText("CHANCE");
    label[2]->setVisible(true);
    text[2]->setGeometry(115,445,260,160);
    text[2]->setText("3-Lottery prize Rs.2500\n5-You have won cross-word competition prize of Rs.1000"
               "\n7-You won jackpot of Rs.2000\n9-Collect 1500 and go to Darjeeling\n11-Prize for best performance in export Rs.3000");
    text[2]->setParent(board);
    text[2]->setEnabled(false);
    text[2]->setVisible(true);
    label[3]->setGeometry(485,400,100,60);
    label[3]->setParent(board);
    label[3]->setText("COMMUNITY\n     CHEST");
    label[3]->setVisible(true);
    text[3]->setGeometry(385,445,260,160);
    text[3]->setText("3-Go to Jail\n5-School and Medical fees, Rs.1000"
               "\n7-Marriage celebrations Rs.2000\n9-General repair of all properties\nPay Rs.100 per house,Rs.200 per hotel\n11-Pay insurance premium,Rs.1500");
    text[3]->setParent(board);
    text[3]->setEnabled(false);
    text[3]->setVisible(true);
    //-------------------------------------------------------------------------------------------------------
    //setting the values of cards-----------------------------------------------------------------------------
    array_of_cards[1].set_val("MUMBAI",'r',0,8500,1200,4000,5500,7500,9000,7500,7500,4200);
    array_of_cards[2].set_val("AHMEDABAD",'r',0,4000,400,1200,3000,4500,6000,5000,5000,1700);
    array_of_cards[4].set_val("INDORE",'b',0,1500,100,600,1500,2500,3500,2000,2000,700);
    array_of_cards[6].set_val("JAIPUR",'b',0,3000,200,1500,2700,4000,5500,4000,4000,1500);
    array_of_cards[7].set_val("AKOLA",'g',0,2500,200,900,1600,2500,3500,3000,3000,1200);
    array_of_cards[9].set_val("DELHI",'g',0,6000,700,3000,4300,5500,7500,5000,5000,3000);
    array_of_cards[11].set_val("AMRITSAR",'y',0,3300,300,1400,2800,4000,5000,4500,4500,1600);
    array_of_cards[13].set_val("KANPUR",'b',0,4000,400,1500,3000,4500,5500,4500,4500,2000);
    array_of_cards[14].set_val("HYDERABAD",'r',0,5000,500,1500,3000,4200,5000,4500,4500,2500);
    array_of_cards[15].set_val("COCHIN",'g',0,3000,300,1500,2700,4000,5500,4000,4000,1500);
    array_of_cards[17].set_val("AGRA",'b',0,2500,200,900,1600,2500,3500,3000,3000,1200);
    array_of_cards[18].set_val("SRINAGAR",'y',0,5000,500,3000,5000,7000,8000,5000,5000,2500);
    array_of_cards[19].set_val("OOTY",'g',0,2500,200,1000,2500,3500,4500,3000,3000,1200);
    array_of_cards[21].set_val("SIMLA",'y',0,2000,200,1000,2700,4500,6000,3500,3500,1100);
    array_of_cards[22].set_val("KOLKATA",'r',0,6500,800,3200,4500,6500,8000,6000,6000,3200);
    array_of_cards[23].set_val("MARGAO",'g',0,4000,400,2200,3500,5000,6500,4500,4500,2000);
    array_of_cards[25].set_val("CHENNAI",'y',0,7000,900,3500,5000,7000,8500,6500,6500,3500);
    array_of_cards[27].set_val("BENGALURU",'y',0,4500,500,1500,3000,4500,5500,4500,4500,2000);
    array_of_cards[28].set_val("DARJEELING",'r',0,2500,200,1200,2600,3500,5000,3000,3000,1200);
    array_of_cards[30].set_val("PATNA",'b',0,2000,200,800,2000,3000,4500,2500,2500,1000);
    //------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------------
    //setting value of places--------------------------------------------------------------
    array_of_cards[0].set_val("START",'\0',8,0,0,0,0,0,0,0,0,0);
    array_of_cards[3].set_val("INCOME\nTAX",'\0',8,0,0,0,0,0,0,0,0,0);
    array_of_cards[5].set_val("CHANCE",'\0',8,0,0,0,0,0,0,0,0,0);
    array_of_cards[8].set_val("JAIL",'\0',8,0,0,0,0,0,0,0,0,0);
    array_of_cards[10].set_val("COLLECT\n500",'\0',8,0,0,0,0,0,0,0,0,0);
    array_of_cards[12].set_val("COMMUNITY\nCHEST",'\0',8,0,0,0,0,0,0,0,0,0);
    array_of_cards[16].set_val("CLUB",'\0',8,0,0,0,0,0,0,0,0,0);
    array_of_cards[20].set_val("CHANCE",'\0',8,0,0,0,0,0,0,0,0,0);
    array_of_cards[24].set_val("RESTROOM",'\0',8,0,0,0,0,0,0,0,0,0);
    array_of_cards[26].set_val("WEALTH TAX",'\0',8,0,0,0,0,0,0,0,0,0);
    array_of_cards[29].set_val("COMMUNITY\nCHEST",'\0',8,0,0,0,0,0,0,0,0,0);
    array_of_cards[31].set_val("GO TO \nCLUB",'\0',8,0,0,0,0,0,0,0,0,0);

    //-------------------------------------------------------------------------------------

    //coloring the board-----------------------------------------------------------------------------
    for(int i=0;i<32;i++)
    {
        if(array_of_cards[i].color=='r')
        {
            button[i]->setStyleSheet("* { background-color: rgb(255,0,0) }");
        }
        else if(array_of_cards[i].color=='g')
        {
            button[i]->setStyleSheet("* { background-color: rgb(0,255,0) }");
        }
        else if(array_of_cards[i].color=='b')
        {
             button[i]->setStyleSheet("* { background-color: rgb(0,0,255) }");
        }
        else if(array_of_cards[i].color=='y')
        {
             button[i]->setStyleSheet("* { background-color: rgb(255,255,0) }");
        }
        else
        {
             button[i]->setStyleSheet("* { background-color: rgb(255,255,255) }");
        }
    }
    //-------------------------------------------------------------------------------------------------------
    //naming the board-----------------------------------------------------------------------------
    for(int i=0;i<32;i++)
    {
        button[i]->setText(array_of_cards[i].name_of_city);
    }

    //-------------------------------------------------------------------------------------------------------
    //this->showFullScreen();
    //--------------------------current_player_information---------------------------------------------------

    current_player_x=board_width;
    current_player_y=y_max/8;
    current_player_width=(x_max-board_width)/2;
    current_player_height=(y_max/2);
    current_player=new QFrame();
    current_player->setParent(window);
    current_player->setStyleSheet("background-color:rgb(180,205,225)");
    current_player->setGeometry(current_player_x,current_player_y,current_player_width,current_player_height);
    current_player->setFrameStyle(3);

    current_player_name=new QLabel("\n  NAME\t-->\t PLAYER\n\n");
    current_player_name->setParent(window);
    current_player_name->setGeometry(board_width,y_max/8,current_player_width,current_player_height/8);
    current_player_name->setVisible(true);
    current_player_balance=new QLabel("  SCORE\t-->\t");
    current_player_balance->setParent(window);
    current_player_balance->setGeometry(board_width,y_max/8+(current_player_height/8),current_player_width,current_player_height/8);
    current_player_balance->setVisible(true);
    current_player_cards=new QLabel("  NUMBER OF CARDS\t-->");
    current_player_cards->setParent(window);
    current_player_cards->setGeometry(board_width,y_max/8+2*(current_player_height/8),current_player_width,current_player_height/8);
    current_player_cards->setVisible(true);
    //--------------------------current_player_information---------------------------------------------------
    //--------------------------current_card-----------------------------------------------------------------
    current_card_x=board_width+current_player_width;
    current_card_y=y_max/8;
    current_card_width=(x_max-board_width)/2;
    current_card_height=(y_max/2);
    current_card=new QFrame(window);
    current_card->setGeometry(current_card_x,current_card_y,current_card_width,current_card_height);
    current_card->setFrameStyle(3);

    current_card_name_of_city=new QLabel(window);
    current_card_name_of_city->setText("  Name of city:- Start");
    current_card_name_of_city->setGeometry(current_card_x,(y_max/8),current_card_width,current_card_height/8);

    current_card_owner=new QLabel(window);
    current_card_owner->setText("  Owner:- 123");
    current_card_owner->setGeometry(current_card_x,current_card_y+(y_max/16),current_card_width,current_card_height/8);

    current_card_price_of_city=new QLabel(window);
    current_card_price_of_city->setText("  Price of the city:- Not available");
    current_card_price_of_city->setGeometry(current_card_x,current_card_y+2*(y_max/16),current_card_width,current_card_height/8);

    current_card_type_of_building=new QLabel(window);
    current_card_type_of_building->setText(" Type of Building :- None");
    current_card_type_of_building->setGeometry(current_card_x,current_card_y+3*(y_max/16),current_card_width,current_card_height/8);

    //---------------------------current_card_end------------------------------------------------------------

    buy_button=new QPushButton("  BUY  ");

    buy_button->setParent(window);
    buy_button->setGeometry(board_width,y_max/8+(7*current_player_height/8),current_player_width/3,current_player_height/8);
    buy_button->setVisible(true);
    buy_button->setEnabled(false);

    build_button=new QPushButton("  BUILD  ");
    build_button->setParent(window);
    build_button->setGeometry(board_width+current_player_width/3,y_max/8+(7*current_player_height/8),current_player_width/3,current_player_height/8);
    build_button->setVisible(true);
    build_button->setEnabled(false);

    sell_button=new QPushButton("  SELL  ");
    sell_button->setParent(window);
    sell_button->setGeometry(board_width+current_player_width/3+current_player_width/3,y_max/8+(7*current_player_height/8),current_player_width/3,current_player_height/8);
    sell_button->setVisible(true);
    sell_button->setEnabled(false);

    ui->setupUi(this);
    connect(this->ui->pushButton,SIGNAL(clicked()),this,SLOT(start_2()));
    connect(this->ui->pushButton_2,SIGNAL(clicked()),this,SLOT(start_3()));
    connect(this->ui->pushButton_3,SIGNAL(clicked()),this,SLOT(start_4()));
    connect(dice,SIGNAL(clicked()),this,SLOT(setdie()));
    connect(cls,SIGNAL(clicked()),this,SLOT(finish()));
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::update_current_player()
{
    int num_of_cards=0;

    for(int i=0;i<32;i++)
    {
        if(player[chance]->cards_owned[i]==1)
        {
            num_of_cards=num_of_cards+1;

        }
    }
    count_of_cards=0;
    std::cout<<"function chance"<<chance<<"\n";
    current_player_name->setText("\n  NAME\t-->\t"+player[chance]->name+"-"+QString::number(chance+1));
    current_player_balance->setText("  SCORE\t-->\t"+QString::number(player[chance]->balance));
    current_player_cards->setText("  NUMBER OF CARDS\t-->\t"+QString::number(num_of_cards));


}
void MainWindow::start_2()
{
    number_of_players=2;
    set_visible_frames();
    show_players();
    window->showFullScreen();
    this->close();
}
void MainWindow::start_4()
{
    number_of_players=4;
    set_visible_frames();
    show_players();
    window->showFullScreen();
    this->close();
}
void MainWindow::start_3()
{
    number_of_players=3;
    set_visible_frames();
    show_players();
    window->showFullScreen();
    this->close();
}
void MainWindow::show_players()
{
    if(number_of_players==2)
    {
        player[2]->b->setVisible(false);
        player[3]->b->setVisible(false);
    }
    if(number_of_players==3)
    {
        player[3]->b->setVisible(false);
    }
}
void MainWindow::setdie()
{
    srand(time(NULL));
    disconnect(sell_button,SIGNAL(clicked()),this,SLOT(sell()));
    disconnect(buy_button,SIGNAL(clicked()),this,SLOT(purchase()));
    int y=(rand()%6+1);
    dice_display[0]->setText(QString::number(y));
    int z=(rand()%6+1);
    dice_display[1]->setText(QString::number(z));
    int x=y+z;
//    x=4;//-------------------------------------------------------------------------------------------------------------------
    int i=1;
    std::cout<<"chance is:-"<<chance<<"\n";
    chance=chance%number_of_players;
    show_frames();
    update_current_player();
    if(chance==0)
    {
        prev=index1;
        while(i<=x)
        {
           index1=(index1+1)%32;
           player[0]->b->setParent(window);
           player[0]->b->setGeometry(button[index1]->x(),button[index1]->y(),player_width,player_height);
           player[0]->b->show();
           i++;
           dice->setEnabled(false);
           delay();
           dice->setEnabled(true);
        }
        set_current_card();
        if(x!=12)
        {
            chance=1;
        }
        next=index1;
        if(abs(prev-next)>19)
        {
            player[0]->rounds++;
            player[0]->balance+=1500;
        }
        std::cout<<"Index1 is:-"<<index1<<"\n";
        update_info(0,index1,x);
        score_board_update();
        after_roll();
        //player1_score->setText(QString::number(player[0]->balance));
        //setting the value of score--------------
    }
    else if(chance==1)
    {
        prev=index2;
        while(i<=x)
        {
            index2=(index2+1)%32;
            player[1]->b->setParent(window);
            player[1]->b->setGeometry(button[index2]->x(),button[index2]->y(),player_width,player_height);
            player[1]->b->show();
            i++;
            dice->setEnabled(false);
        delay();
            dice->setEnabled(true);
        }
        set_current_card();
        if(x!=12)
            {
               chance=2;
            }
            next=index2;
            if(abs(prev-next)>19)
            {
                player[1]->rounds++;
                player[1]->balance+=1500;
            }
            update_info(1,index2,x);
            score_board_update();
            after_roll();
            //player2_score->setText(QString::number(player[1]->balance));
            //setting the value
            std::cout<<"Index2 is:-"<<index2<<"\n";
    }
    else if(chance==2)
    {
        prev=index3;
        while(i<=x)
        {
            index3=(index3+1)%32;
            player[2]->b->setParent(window);
            player[2]->b->setGeometry(button[index3]->x(),button[index3]->y(),player_width,player_height);
            player[2]->b->show();
            i++;
            dice->setEnabled(false);
            delay();
            dice->setEnabled(true);
        }
            set_current_card();
            if(x!=12)
            {
               chance=3;
            }
        std::cout<<"Index3 is:-"<<index3<<"\n";
        next=index3;
        if(abs(prev-next)>19)
        {
            player[2]->rounds++;
            player[2]->balance+=1500;
        }
        update_info(2,index3,x);
        score_board_update();
        after_roll();
        //player3_score->setText(QString::number(player[2]->balance));
    }
    else if(chance==3)
    {
         prev=index4;
        while(i<=x)
        {
            index4=(index4+1)%32;
            player[3]->b->setParent(window);
            player[3]->b->setGeometry(button[index4]->x(),button[index4]->y(),player_width,player_height);
            player[3]->b->show();
            i++;
            dice->setEnabled(false);
            delay();
            dice->setEnabled(true);
        }
        set_current_card();
            if(x!=12)
            {
               chance=0;
            }
        std::cout<<"Index4 is:-"<<index4<<"\n";
        next=index4;
        if(abs(prev-next)>19)
        {
            player[3]->rounds++;
            player[3]->balance+=1500;
        }
        update_info(3,index4,x);
        score_board_update();
        after_roll();
        //player4_score->setText(QString::number(player[3]->balance));
    }
}
void MainWindow::set_current_card()
{
    int index=30;
    if(chance==0)
    {
        index=index1;
    }
    else if(chance==1)
    {
        index=index2;
    }
    else if(chance==2)
    {
        index=index3;
    }
    else
    {
        index=index4;
    }
    QString temp="  Owner:- ";
    if(array_of_cards[index].owner==0)
    {
        temp.append("Bank");
    }
    else if(array_of_cards[index].owner==1)
    {
        temp.append("Player-1");
    }
    else if(array_of_cards[index].owner==2)
    {
        temp.append("Player-2");
    }
    else if(array_of_cards[index].owner==3)
    {
        temp.append("Player-3");
    }
    else if(array_of_cards[index].owner==4)
    {
        temp.append("Player-4");
    }
    current_card_name_of_city->setText("  Name of City/Card :- "+ array_of_cards[index].name_of_city);
    current_card_owner->setText(temp);
    current_card_price_of_city->setText("  Price of the City :- "+ QString::number(array_of_cards[index].price_of_city));
    if(array_of_cards[index].type_of_rent==0)
    {
    current_card_type_of_building->setText("  Type of Building :- No Building");
    }
    else if(array_of_cards[index].type_of_rent<=3)
    {
     current_card_type_of_building->setText("  Type of Building :- "+QString::number(array_of_cards[index].type_of_rent)+" House");
    }
    else
    {
        current_card_type_of_building->setText("  Type of Building :- Hotel");
    }
    if(array_of_cards[index].color=='r')
    {
    current_card->setStyleSheet("background-color:rgb(255,0,0)");
    }
    else if(array_of_cards[index].color=='g')
    {
    current_card->setStyleSheet("background-color:rgb(0,255,0)");
    }
    else if(array_of_cards[index].color=='b')
    {
    current_card->setStyleSheet("background-color:rgb(0,0,255)");
    }
    else if(array_of_cards[index].color=='y')
    {
    current_card->setStyleSheet("background-color:rgb(255,255,0)");
    }
    else
    {
        current_card->setStyleSheet("background-color:rgb(255,255,255)");
    }

}
void MainWindow::set_visible_frames()
{
    if(number_of_players==2)
    {
        player[2]->myinfo->setEnabled(false);
        player[3]->myinfo->setEnabled(false);
        player[1]->myinfo->setStyleSheet("background-color:rgb(255,255,255)");
        player[0]->myinfo->setStyleSheet("background-color:rgb(255,255,255)");
        player1_name->setText("  PLAYER-1");
        player2_name->setText("  PLAYER-2");
    }
    if(number_of_players==3)
    {
        player[3]->myinfo->setEnabled(false);
        player[2]->myinfo->setStyleSheet("background-color:rgb(255,255,255)");
        player[1]->myinfo->setStyleSheet("background-color:rgb(255,255,255)");
        player[0]->myinfo->setStyleSheet("background-color:rgb(255,255,255)");
        player3_name->setText("  PLAYER-3");
        player2_name->setText("  PLAYER-2");
        player1_name->setText("  PLAYER-1");
    }
    if(number_of_players==4)
    {
        player[3]->myinfo->setStyleSheet("background-color:rgb(255,255,255)");
        player[2]->myinfo->setStyleSheet("background-color:rgb(255,255,255)");
        player[1]->myinfo->setStyleSheet("background-color:rgb(255,255,255)");
        player[0]->myinfo->setStyleSheet("background-color:rgb(255,255,255)");
        player4_name->setText("  PLAYER-4");
        player3_name->setText("  PLAYER-3");
        player2_name->setText("  PLAYER-2");
        player1_name->setText("  PLAYER-1");
    }
}
void MainWindow::show_frames()
{
    int trp=chance;
    player[trp]->myinfo->setStyleSheet("background-color:rgb(155,155,155)");
    if(trp==0)
    {
        trp=trp+number_of_players;
    }
    if(trp>0)
    {
        player[trp-1]->myinfo->setStyleSheet("background-color:rgb(255,255,255)");
    }
}
void MainWindow::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(0);
    while( QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void MainWindow::finish()
{
    window->close();
}
void MainWindow::score_board_update()
{
    player1_score->setText(QString::number(player[0]->balance));
    player2_score->setText(QString::number(player[1]->balance));
    player3_score->setText(QString::number(player[2]->balance));
    player4_score->setText(QString::number(player[3]->balance));
}
//-------------core functions--------------------
//------------zhooooooooooooooooooooollll--------
void MainWindow::update_info(int player_id,int card_id,int dice)
{
    std::cout<<"update info called";
    switch(card_id)
    {
    case 0:
        if_start(player_id);
        buy_button->setEnabled(false);
        break;
    case 3:
        if_income_tax(player_id);
        buy_button->setEnabled(false);
        break;
    case 5:
        if_chance(player_id,dice);
        buy_button->setEnabled(false);
        break;
    case 8:
        if_jail(player_id);
        buy_button->setEnabled(false);
        break;
    case 10:
        if_collect_500(player_id);
        buy_button->setEnabled(false);
        break;
    case 12:
        if_comm_chest(player_id,dice);
        buy_button->setEnabled(false);
        break;
    case 16:
        if_club(player_id);
        buy_button->setEnabled(false);
        break;
    case 20:
         if_chance(player_id,dice);
         buy_button->setEnabled(false);
         break;
    case 24:
         if_rest_room(player_id);
         buy_button->setEnabled(false);
        break;
    case 26:
         if_wealth_tax(player_id);
         buy_button->setEnabled(false);
        break;
    case 29:
         if_comm_chest(player_id,dice);
         buy_button->setEnabled(false);
        break;
    case 31:
         if_goto_club(player_id);
         buy_button->setEnabled(false);
        break;
     default:
         if_normal_card(player_id,card_id);
        break;
    }
}
void MainWindow::if_start(int player_id)
{
    if(player[player_id]->rounds==0)
    {
        player[player_id]->balance= player[player_id]->balance*1;
    }
}
void MainWindow::if_income_tax(int player_id)
{
    for(int i=0;i<32;i++)
    {
        if(player[player_id]->cards_owned[i]==1)
        {
            count_of_cards=count_of_cards+1;
        }
        else
        {
            count_of_cards=count_of_cards*1;
        }
    }
    player[player_id]->balance=player[player_id]->balance-(count_of_cards*50);
}
void MainWindow::if_chance(int player_id,int dice)
{
    switch(dice)
    {
    case 2:
        player[player_id]->balance-=2000;
        break;
    case 3:
        player[player_id]->balance+=2500;
        break;
    case 4:
        player[player_id]->balance-=1000;
        break;
    case 5:
        player[player_id]->balance+=1000;
        break;
    case 6:
        player[player_id]->balance-=1500;
        break;
    case 7:
        player[player_id]->balance+=2000;
        break;
    case 8:
        player[player_id]->balance-=3000;
        break;
    case 9:
        player[player_id]->balance+=1500;
        break;
    case 10:
        player[player_id]->b->setGeometry(button[8]->x(),button[8]->y(),player_width,player_height);
        if(player_id==0)
        {
            index1=8;
        }
        else if(player_id==1)
        {
            index2=8;
        }
        else if(player_id==2)
        {
            index3=8;
        }
        else
        {
            index4=8;
        }
        if_jail(player_id);
        break;
    case 11:
        player[player_id]->balance+=3000;
        break;
    case 12:
        player[player_id]->b->setGeometry(button[24]->x(),button[24]->y(),player_width,player_height);
        if(player_id==0)
        {
            index1=24;
        }
        else if(player_id==1)
        {
            index2=24;
        }
        else if(player_id==2)
        {
            index3=24;
        }
        else
        {
            index4=24;
        }
        if_rest_room(player_id);
        break;
    }
}
void MainWindow::if_comm_chest(int player_id,int dice)
{
    switch(dice)
    {
    case 2:
        player[player_id]->balance+=((number_of_players-1)*500);
        break;
    case 3:
        player[player_id]->b->setGeometry(button[8]->x(),button[8]->y(),player_width,player_height);
        if(player_id==0)
        {
            index1=8;
        }
        else if(player_id==1)
        {
            index2=8;
        }
        else if(player_id==2)
        {
            index3=8;
        }
        else
        {
            index4=8;
        }
        if_jail(player_id);
        break;
    case 4:
        player[player_id]->balance+=2500;
        break;
    case 5:
        player[player_id]->balance-=1000;
        break;
    case 6:
        player[player_id]->balance+=2000;
        break;
    case 7:
        player[player_id]->balance-=2000;
        break;
    case 8:
        player[player_id]->balance+=1000;
        break;
    case 9:
        player[player_id]->balance-=500;
        break;
    case 10:
         player[player_id]->balance+=1500;
        break;
    case 11:
        player[player_id]->balance-=1500;
        break;
    case 12:
        player[player_id]->balance+=3000;
        break;
    }
}
void MainWindow::if_rest_room(int player_id)
{
    player[player_id]->balance+=100;
    for (int p=0;p<number_of_players;p++)
    {
        if(p!=player_id)
        {
            player[p]->balance-=100;
        }
    }
}
void MainWindow::if_wealth_tax(int player_id)
{
    int a=0,b=0;
    for(int i=0;i<32;i++)
    {
        if(player[player_id]->cards_owned[i]==1)
        {
            a+=array_of_cards[i].type_of_rent%4;
            b+=array_of_cards[i].type_of_rent%5-a;
        }
    }
    player[player_id]->balance-=(a*50)+(b*100);
}
void MainWindow::if_goto_club(int player_id)
{
    player[player_id]->b->setGeometry(button[16]->x(),button[16]->y(),player_width,player_height);
    if(player_id==0)
    {
        index1=16;
    }
    else if(player_id==1)
    {
        index2=16;
    }
    else if(player_id==2)
    {
        index3=16;
    }
    else
    {
        index4=16;
    }
    if_club(player_id);
}
void MainWindow::if_normal_card(int player_id,int card_id)
{
    std::cout<<"\ninside normal card...\n";
    if(array_of_cards[card_id].owner==0)
    {
        buy_button->setEnabled(true);
        pid=player_id;
        cid=card_id;
        connect(buy_button,SIGNAL(clicked()),this,SLOT(purchase()));
        std::cout<<"\nbuy_button connected...\n";
    }
    else
    {
        if((player_id+1)==array_of_cards[card_id].owner)
        {
            sell_button->setEnabled(true);
            build_button->setEnabled(true);
            pid=player_id;
            cid=card_id;
            connect(sell_button,SIGNAL(clicked()),this,SLOT(sell()));
            connect(build_button,SIGNAL(clicked()),this,SLOT(renovate()));
        }
        else
        {
            sell_button->setEnabled(false);
            build_button->setEnabled(false);
            buy_button->setEnabled(false);
            pay_rent(player_id,card_id);
        }
    }
}
void MainWindow::renovate(int player_id, int card_id)
{
    int count_of_cards_of_particular_color=0;
    for(int p=0;p<32;p++)
    {
        if(array_of_cards[p].color==array_of_cards[card_id].color && array_of_cards[p].owner==player_id)
        {
            count_of_cards_of_particular_color++;
        }
    }
    if(count_of_cards_of_particular_color>=3 && array_of_cards[card_id].type_of_rent<=4)
    {
        int a;
        if(array_of_cards[card_id].type_of_rent==4)
        {
            a=player[player_id]->balance-=array_of_cards[card_id].cost_of_hotel;
            b.Total_amount+=a;
        }
        else
        {
            a=player[player_id]->balance-=array_of_cards[card_id].cost_of_house;
            b.Total_amount+=a;
        }
        array_of_cards[card_id].type_of_rent++;
    }
    after_roll();
    after_roll_card();
    score_board_update();
}
void MainWindow::pay_rent(int player_id, int cards_id)
{
    std::cout<<"\nInside pay rent";
    int owner=array_of_cards[cards_id].owner;
    if(array_of_cards[cards_id].type_of_rent==0)
    {
        player[player_id]->balance=player[player_id]->balance-array_of_cards[cards_id].rent_without_house;
        player[owner-1]->balance=player[owner-1]->balance+array_of_cards[cards_id].rent_without_house;
    }
    else if(array_of_cards[cards_id].type_of_rent==1)
    {
        player[player_id]->balance-=array_of_cards[cards_id].rent_with_1_house;
        player[owner-1]->balance+=array_of_cards[cards_id].rent_with_1_house;
    }
    else if(array_of_cards[cards_id].type_of_rent==2)
    {
        player[player_id]->balance-=array_of_cards[cards_id].rent_with_2_house;
        player[owner-1]->balance+=array_of_cards[cards_id].rent_with_2_house;
    }
    else if(array_of_cards[cards_id].type_of_rent==3)
    {
        player[player_id]->balance-=array_of_cards[cards_id].rent_with_3_house;
        player[owner-1]->balance+=array_of_cards[cards_id].rent_with_3_house;
    }
    else
    {
        player[player_id]->balance-=array_of_cards[cards_id].rent_with_hotel;
        player[owner-1]->balance+=array_of_cards[cards_id].rent_with_hotel;
    }

}
void MainWindow::if_jail(int player_id)
{
    player[player_id]->balance-=500;
    b.Total_amount+=500;

}
void MainWindow::if_club(int player_id)
{
    player[player_id]->balance-=100;
    for (int p=0;p<number_of_players;p++)
    {
        if(p!=player_id)
        {
            player[p]->balance+=100;
        }
        else
        {
            std::cout<<"brr";
        }
    }

}
void MainWindow::if_collect_500(int player_id)
{
    player[player_id]->balance+=500;
    b.Total_amount-=500;
}
void MainWindow::sell()
{
    sell_button->setEnabled(false);
    player[pid]->balance+=array_of_cards[cid].mortgage_val;
    b.Total_amount-=array_of_cards[cid].mortgage_val;
    player[pid]->cards_owned[cid]=0;
    array_of_cards[cid].owner=0;
    after_roll();
    after_roll_card();
    score_board_update();

}
void MainWindow::purchase()
{

    std::cout<<"\n\nInside buy city";
    buy_button->setEnabled(false);
    array_of_cards[cid].owner=pid+1;
    if(player[pid]->balance>=array_of_cards[cid].price_of_city && pid==chance-1)
    {
        player[pid]->balance-=array_of_cards[cid].price_of_city;
        std::cout<<"\n"<<"Subtacted"<<"\n"<<pid<<cid<<"\n";
        b.Total_amount+=array_of_cards[cid].price_of_city;
        player[pid]->cards_owned[cid]=1;
    }
    after_roll();
    after_roll_card();
    score_board_update();
}
void MainWindow::after_roll()
{
    int num_of_cards=0;
    for(int i=0;i<32;i++)
    {
        if(player[(chance-1+number_of_players)%number_of_players]->cards_owned[i]==1)
        {
            num_of_cards=num_of_cards+1;
        }
    }
    current_player_name->setText("\n  NAME\t-->\t"+player[(chance-1+number_of_players)%number_of_players]->name+"-"+QString::number(chance));
    current_player_balance->setText("  SCORE\t-->\t"+QString::number(player[(chance-1+number_of_players)%number_of_players]->balance));
    current_player_cards->setText("  NUMBER OF CARDS\t-->\t"+QString::number(num_of_cards));
}
void MainWindow::after_roll_card()
{
    int index=30;
    if(chance==0)
    {
        index=index4;
    }
    else if(chance==1)
    {
        index=index1;
    }
    else if(chance==2)
    {
        index=index2;
    }
    else
    {
        index=index3;
    }
    QString temp="  Owner:- ";
    if(array_of_cards[index].owner==0)
    {
        temp.append("Bank");
    }
    else if(array_of_cards[index].owner==1)
    {
        temp.append("Player-1");
    }
    else if(array_of_cards[index].owner==2)
    {
        temp.append("Player-2");
    }
    else if(array_of_cards[index].owner==3)
    {
        temp.append("Player-3");
    }
    else if(array_of_cards[index].owner==4)
    {
        temp.append("Player-4");
    }
    current_card_name_of_city->setText("  Name of City/Card :- "+ array_of_cards[index].name_of_city);
    current_card_owner->setText(temp);
}
