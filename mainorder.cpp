#include "order.h"
#include <iostream>
using namespace std;
 
int main(int argc, char const *argv[])
{
	Order robot=Order(100,100,false);
	cout << robot.get_order_R()<< endl;
	cout << robot.get_order_L()<< endl;
	return 0;
}