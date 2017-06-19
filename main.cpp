#pragma once
#include "2015180048.h"#include "Judgment.h"#include "Judgment.cpp"int main(){ Judgment j;
 j.SetYourFunc(  BlackAttack_2015180048, BlackDefence_2015180048,  WhiteAttack_2015180048, WhiteDefence_2015180048
 );
 //j.GamePlay();
 while (1) {  int a, b;  cout << "검은돌 공격" << endl;  BlackAttack_2015180048(&a, &b);  WhiteDefence_2015180048(a, b);
  cout << "흰돌 공격" << endl;  WhiteAttack_2015180048(&a, &b);  BlackDefence_2015180048(a, b); }
 return 1;}
