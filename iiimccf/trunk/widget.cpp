#include "graphdev.h"
#include "widget.h"
#include <iostream>
using namespace std;

/*
 * Implementation of Status bar.
 */

Stts::Stts()
{
  title = new String;
}
Stts::~Stts()
{
  hide();
  delete title;
}

void Stts::update()
{

}


/*
 * Implementation of Preedit.
 */


Prdt::Prdt()
{
  prdt_text = new Text;
  cur_x =0;
  cur_y =0;
  shift_x = 0;
  shift_y = 0;
}

Prdt::~Prdt()
{
  hide();
}


bool Prdt::update()
{
  hide();
  /*
  
  cur_x = iiimccf->x;
  cur_y = iiimccf->y;
  
  prdt_text->fh(16);
  prdt_text->fw(16);

  shift();
  
  prdt_text->x(cur_x - shift_x);
  prdt_text->y(cur_y - shift_y);
  prdt_text->fc(4);
  
 */
  show();
}



/*
 * Implementation of LookupChoice.
 */


Lkc::Lkc()
{
  lkc_text = new Text;
  cur_x=20;
  cur_y=20;

}


Lkc::~Lkc()
{
  hide();
}

bool Lkc::update()
{
  hide();
  /*
  cur_x = iiimccf->x;
  cur_y = iiimccf->y;
  
  lkc_text->fw(16);
  lkc_text->fh(16);

  
  shift();
  
  lkc_text->x(cur_x - shift_x);
  lkc_text->y(cur_y - shift_y);
*/
  show();
}


bool Lkc::draw()
{
  Rectangle up,left,right,bottom;
  int u,l,r,b;
  u=lkc_text->y() -3;
  l=lkc_text->x() -3;
  r=lkc_text->x() + lkc_text->w() +3;
  b=lkc_text->y() + lkc_text->h() +3;
  cout << " u:" << u
       << " l:" << l
       << " r:" << r
       << " b:" << b << endl;
  up.update( l, u, r, u,8);
  left.update( l,u,l,b ,8);
  right.update( r,u,r,b,15);
  bottom.update( l,b,r,b,15);
  up.render();
  left.render();
  right.render();
  bottom.render();

  lkc_text->fc(16);
  lkc_text->render();
  cout << "---end of render-----" << endl;
  
  return true; 
}