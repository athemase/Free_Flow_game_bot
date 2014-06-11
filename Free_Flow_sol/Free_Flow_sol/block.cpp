#include "block.h"

block::block()
{
	type = '.';
	num = 2;
}
void block::set_type(char the_type)
{
	type=the_type;
}
void block::set_num(int the_num)
{
	num = the_num;
}
char block::get_type()
{
	return type;
}
int block::get_num()
{
	return num;
}

;