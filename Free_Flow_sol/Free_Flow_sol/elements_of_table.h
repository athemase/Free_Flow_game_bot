#include "block.h"
using namespace std;

class elements_of_table
{
private:
	block **the_block;
    int size;
public:
	elements_of_table(int size)
	{
	    the_block = new block*[size];
		for(int j=0;j<size;j++)
			the_block[j] = new block[size];

		this->size = size;
	}
	elements_of_table& operator=(const elements_of_table& other)
	{
		for(int i=0;i<size;i++)
			for(int j=0;j<size;j++)
			{
	   	       this->set_block_type(i,j,other.get_block_type(i,j));
	           this->set_block_num(i,j,other.get_block_num(i,j));
			}

		return *this;
	}

	void clear_block()
	{
		for(int j=0;j<size;j++)
			delete (the_block[j]);
		delete (the_block);
	}

	void set_block_type(int x,int y,char type)
	{
		the_block[x][y].set_type(type);
	}
	void set_block_num(int x,int y,int num)
	{
		the_block[x][y].set_num(num);
	}
	char get_block_type(int x,int y) const
	{
		return the_block[x][y].get_type();
	}
	int get_block_num(int x,int y) const
	{
		return the_block[x][y].get_num();
	}
	int get_size()
	{
		return size;
	}
	void print_table()
	{
		for(int j=0;j<size;j++)
		    {
			   for(int k =0;k<size;k++)
			   	 cout<<the_block[j][k].get_type();
			   cout<<endl;
		    }
	}
};