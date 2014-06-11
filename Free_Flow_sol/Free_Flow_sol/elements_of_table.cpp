#include "block.h"
#include "elements_of_table.h"


elements_of_table::elements_of_table(int size)
{
	the_block = new block*[size];
	for(int j=0;j<size;j++)
		the_block[j] = new block[size];
	this->size = size;
}
elements_of_table& elements_of_table::operator=(const elements_of_table& other)
{
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
		{
			this->set_block_type(i,j,other.get_block_type(i,j));
			this->set_block_num(i,j,other.get_block_num(i,j));
		}

		return *this;
}
void elements_of_table::set_block_type(int x,int y,char type)
{
	the_block[x][y].set_type(type);
}
void elements_of_table::set_block_num(int x,int y,int num)
{
	the_block[x][y].set_num(num);
}
char elements_of_table::get_block_type(int x,int y) const
{
	return the_block[x][y].get_type();
}
int elements_of_table::get_block_num(int x,int y) const
{
	return the_block[x][y].get_num();
}
int elements_of_table::get_size()
{
	return size;
}


;