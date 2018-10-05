#include <iostream>
using namespace std;
#include "treeavl.h"

int main()
{
	TreeAVL<int> t;

	t.Insert(30);
    t.Insert(5);
    t.Insert(35);
    t.Insert(32);
    t.Insert(40);
    t.Insert(45);
   	t.Preorder();
	return 0;
}