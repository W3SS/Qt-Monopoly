#include "cards.h"
#include "QString"
Cards::Cards()
{
    name_of_city="hello";
    color=' ';
    owner=0;                 //Bank->0;player-x->x
    price_of_city=0;
    rent_without_house=0;
    rent_with_1_house=0;
    rent_with_2_house=0;
    rent_with_3_house=0;
    rent_with_hotel=0;
    type_of_rent=0;
}
void Cards::set_val(QString name,char col,int ow,int pricecity,int rentwithouthouse,
                    int rentwith1house,int rentwith2house,int rentwith3house,int rentwithhotel,
                    int costofhouse,int costhotel,int mortgageval)
{
    name_of_city=name;
    color=col;
    owner=ow;
    price_of_city=pricecity;
    rent_without_house=rentwithouthouse;
    rent_with_1_house=rentwith1house;
    rent_with_2_house=rentwith2house;
    rent_with_3_house=rentwith3house;
    rent_with_hotel=rentwithhotel;
    cost_of_house=costofhouse;
    cost_of_hotel=costhotel;
    this->mortgage_val=mortgageval;

}
