class color_table
{
private:
	int **location;
	int size;
public:
	color_table(int size)
	{
		location = new int*[size];
		for(int j=0;j<size;j++)
			location[j] = new int[2];

		this->size = size;
	}
	void set_location(int num,int x,int y)
	{
		location[num][0]=x;
		location[num][1]=y;
	}
	int get_location(int num,int xy)
	{
		return location[num][xy];
	}
	int get_size()
	{
		return size;
	}

};