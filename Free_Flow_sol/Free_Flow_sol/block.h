class block
{
private:
	char type;
	int num;
public:
	block()
	{
		type = '.';
		num = 2;
	}
	void set_type(char the_type)
	{
		type=the_type;
	}
	void set_num(int the_num)
	{
		num = the_num;
	}
	char get_type()
	{
		return type;
	}
	int get_num()
	{
		return num;
	}
};
