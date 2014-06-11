// Free_Flow_sol.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

int Direction[5][2] = {{0,1},{0,-1},{1,0},{-1,0},{0,0}} ;


void set_all_element(elements_of_pairs * pairs,char **table,int numbers_of_pairs,int size_N)
{
   int pointer=0;
   for(int i = 0;i<size_N;i++)
	   for(int j = 0;j<size_N;j++)
	   {
		   bool temp = true;
		   if(table[i][j]!='.')
		   {
			   if(pointer==0)
			   {
				   pairs[pointer].Initialization_point_location(i,j);
				   pairs[pointer].set_type(table[i][j]);
				   pointer++;
			   }
			   else
			   {
				   for(int k=0;k<pointer;k++)
				   {
					   if(table[i][j] == pairs[k].get_type())
					   {
						   pairs[k].Initialization_point_location(i,j);
						   temp = false;
					   }
				   }
				   if(temp)
				   {
					   pairs[pointer].Initialization_point_location(i,j);
				       pairs[pointer].set_type(table[i][j]);
				       pointer++;
				   }
			   }
		   }
	   }
}
bool test_same_color(int x,int y,elements_of_table table,char color)
{
	//cout<<"--------------"<<endl;
	//table.print_table();
	int count = 0;
	for(int i =0;i<4;i++)
	{
		if(x+Direction[i][0] >-1 && x+Direction[i][0]<table.get_size() && y+Direction[i][1]>-1 && y+Direction[i][1]<table.get_size())
			if(table.get_block_type(x+Direction[i][0],y+Direction[i][1]) == color  && table.get_block_num(x+Direction[i][0],y+Direction[i][1])==0)
				count++;
	}
	if( count > 1)
	   return false;
	else
       return true;
}
int test_only_one_way(elements_of_pairs pairs,elements_of_table table,int num)
{
	int temp = 0;
	int dir = 0;
	for(int i =0;i<4;i++){
		if(pairs.get_path_pointer(num,0)+Direction[i][0] >-1 && pairs.get_path_pointer(num,0)+Direction[i][0]<table.get_size() && pairs.get_path_pointer(num,1)+Direction[i][1]>-1 && pairs.get_path_pointer(num,1)+Direction[i][1]<table.get_size())
            if(table.get_block_type(pairs.get_path_pointer(num,0)+Direction[i][0],pairs.get_path_pointer(num,1)+Direction[i][1]) == '.'){
			   temp++;
			   dir = i;
		    }
	}
    if(temp>1)     
	   return 4;          //more way or no way
	else if(temp ==1)
	   return dir;        //one way
	else 
	  return 0;
}
bool test_finish(elements_of_table table,int x,int y)
{
	for(int i = 0;i<4;i++)
	{
		if(x+Direction[i][0] >-1 && x+Direction[i][0]<table.get_size() && y+Direction[i][1] >-1 && y+Direction[i][1]<table.get_size())
		  if(table.get_block_type(x,y) == table.get_block_type(x+Direction[i][0],y+Direction[i][1]) &&  table.get_block_num(x,y) != table.get_block_num(x + Direction[i][0],y+Direction[i][1]) )
			 return true;
	}
	return false;
}
bool flood_test(int x,int y,elements_of_table &table)
{
	if(test_finish(table,x,y))
	   return true;
	else
	{
		for(int i=0;i<4;i++)
		{
			if(x+Direction[i][0] >-1 && x+Direction[i][0]<table.get_size() && y+Direction[i][1] >-1 && y+Direction[i][1]<table.get_size())
				if(table.get_block_type(x+Direction[i][0],y+Direction[i][1]) =='.')
				{
					  table.set_block_type(x+Direction[i][0],y+Direction[i][1],table.get_block_type(x,y));
					  table.set_block_num(x+Direction[i][0],y+Direction[i][1],0);
				      if( flood_test(x+Direction[i][0],y+Direction[i][1],table))
						  return true;
				}
		}
	}
	return false;
}
bool check_Affect(elements_of_table table,color_table the_color_table,int color_table_pointer)
{
	elements_of_table copy_table(table.get_size());
	for(int i = color_table_pointer+1;i<the_color_table.get_size();i++)
	{
		copy_table = table;
		if(!flood_test(the_color_table.get_location(i,0),the_color_table.get_location(i,1), copy_table))
		{   copy_table.clear_block();
			return false;
		}
	}
	copy_table.clear_block();
	return true;
}
bool Exhaustion_free_flow(elements_of_table table,int x,int y,color_table the_color_table,int color_table_pointer)
{
	if(test_finish(table,x,y))
	{
		color_table_pointer++;
		if(color_table_pointer != the_color_table.get_size())
		{
			return Exhaustion_free_flow(table,the_color_table.get_location(color_table_pointer,0),the_color_table.get_location(color_table_pointer,1),the_color_table,color_table_pointer);
		}
		else
		{
		  cout<<"--------------"<<endl;
		  table.print_table();
		  return true;
		}	
	}
	else
	{
		elements_of_table copy_table(table.get_size());
	    copy_table = table;
		for(int i =0;i<4;i++)
		{
			if(x+Direction[i][0] >-1 && x+Direction[i][0]<copy_table.get_size() && y+Direction[i][1] >-1 && y+Direction[i][1]<copy_table.get_size())
				if(copy_table.get_block_type(x+Direction[i][0],y+Direction[i][1]) =='.')
				{
                  if(check_Affect(copy_table,the_color_table,color_table_pointer))
					if(test_same_color(x+Direction[i][0],y+Direction[i][1],table,table.get_block_type(x,y)))
					{
					  copy_table.set_block_type(x+Direction[i][0],y+Direction[i][1],copy_table.get_block_type(x,y));
					  copy_table.set_block_num(x+Direction[i][0],y+Direction[i][1],copy_table.get_block_num(x,y));
				      if( Exhaustion_free_flow(copy_table,x+Direction[i][0],y+Direction[i][1],the_color_table,color_table_pointer))
					  {
						  copy_table.clear_block();
						  return true;
					  }
					  else{
				        copy_table.set_block_type(x+Direction[i][0],y+Direction[i][1],'.');
					    copy_table.set_block_num(x+Direction[i][0],y+Direction[i][1],2)   ;
					  }
					}
				}
		}
		copy_table.clear_block();
	}
		return false;
}
int Finish_Necessary_way(elements_of_pairs * pairs,elements_of_table table,int numbers_of_pairs)
{
	int *try_and_false;
	try_and_false = new int [numbers_of_pairs*2];
	for(int i =0;i<numbers_of_pairs*2;i++)
		try_and_false[i] = 0;
	int false_count = 0;
	int finish_count = 0;
	int num = 0;
	bool temp_try = true;

	while(numbers_of_pairs != finish_count  && temp_try ) {
       for(int i=0;i<2;i++)
	   {
		   if(!pairs[num].get_Is_finish())
		   {
			   int Judge = 6;
			   while(Judge!=4 && Judge!=5)
			   {
				    if(abs(pairs[num].get_path_pointer(0,0)-pairs[num].get_path_pointer(1,0)) +  abs(pairs[num].get_path_pointer(0,1)-pairs[num].get_path_pointer(1,1)) ==1){
                         pairs[num].set_Is_finish(true);
						 for(int j=0;j<numbers_of_pairs*2;j++)
						   try_and_false[j] = 0;			
						 finish_count++;
						 break;
			        }
					
			        Judge = test_only_one_way(pairs[num],table,i);

					if(Judge!=4 && Judge!=5){	  
				    	pairs[num].set_path_pointer(i,pairs[num].get_path_pointer(i,0)+Direction[Judge][0],pairs[num].get_path_pointer(i,1)+Direction[Judge][1]);
						table.set_block_type( pairs[num].get_path_pointer(i,0), pairs[num].get_path_pointer(i,1) ,pairs[num].get_type());
						table.set_block_num( pairs[num].get_path_pointer(i,0), pairs[num].get_path_pointer(i,1),i);
						for(int j=0;j<numbers_of_pairs*2;j++)
						   try_and_false[j] = 0;
					}
					else{
					   if(try_and_false[num*2+i] == 1)
						  temp_try=false;
					   try_and_false[num*2+i] = 1;
					}
			   }
		   }
	   }
	   num = (num+1) % numbers_of_pairs;
	   false_count = 0;
	   for(int i=0;i<numbers_of_pairs*2;i++)
		   false_count = false_count + try_and_false[i];

	}
	return finish_count;
}

bool free_flow_algorithm(elements_of_pairs * pairs,elements_of_table table,int numbers_of_pairs)
{
	int false_count = 0;
	int finish_count = 0;
	finish_count =  Finish_Necessary_way(pairs,table,numbers_of_pairs);
	false_count = numbers_of_pairs-finish_count;

	if(numbers_of_pairs!=finish_count)
	{
		int temp=0;
	    color_table new_color(false_count);
	    for(int i=0;i< numbers_of_pairs;i++)
	     {
				if(!pairs[i].get_Is_finish()){
			    	new_color.set_location(temp,pairs[i].get_path_pointer(0,0),pairs[i].get_path_pointer(0,1));
					temp++;
			    }
	    }
		if(!Exhaustion_free_flow(table,new_color.get_location(0,0),new_color.get_location(0,1),new_color,0))
			cout<<"No Sol"<<endl;
		return false;
	}
	else
		return true;
}
void Initialization_class_table(elements_of_table the_table,char **table,int size_N,elements_of_pairs *pairs,int numbers_of_pairs)
{
	for(int i=0;i<size_N;i++)
			for(int j=0;j<size_N;j++)
				the_table.set_block_type(i,j,table[i][j]);

	for(int i=0;i<numbers_of_pairs;i++)
	{
		for(int j= 0;j<2;j++)
			the_table.set_block_num(pairs[i].get_path_pointer(j,0),pairs[i].get_path_pointer(j,1),j);
	}
}
int count_number_of_pairs(char **table,int size_N)
{
	int count=0;
	for(int j=0;j<size_N;j++)
		for(int k=0;k<size_N;k++)
			if(table[j][k]!='.')
				   count++;
    return count /=2;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int test_times=0;
	int size_N = 0;
	int numbers_of_pairs;
	cin>>test_times;
	clock_t start_time, end_time;
	start_time = clock();

	for(int i = 0;i<test_times;i++)
	{	
	//	start_time =clock();
		cin>>size_N;
	    char **table;
	    table = new char*[size_N];
		for(int j=0;j<size_N;j++)
			table[j] = new char[size_N+1];

		for(int k =0;k<size_N;k++)
	    	  cin >> table[k];

		elements_of_table new_table(size_N);
		numbers_of_pairs = count_number_of_pairs(table,size_N);

		elements_of_pairs *pairs;
		pairs = new elements_of_pairs[numbers_of_pairs];
		set_all_element(pairs,table,numbers_of_pairs,size_N);

		Initialization_class_table(new_table,table,size_N,pairs,numbers_of_pairs);

		if(free_flow_algorithm(pairs,new_table,numbers_of_pairs))
		{
			cout<<"----------------"<<endl;
			new_table.print_table();
		}
		
	}
	end_time = clock();
		cout<< "Total Time = "<<(float)(end_time - start_time)/CLOCKS_PER_SEC<<" sec"<<endl;
	system("pause");
	return 0;
}


/*
class all_pairs
{
private:
	elements_of_pairs *pairs;
	int number;
public:
    all_pairs(int number)
	{
		pairs = new elements_of_pairs[number];
		this->number = number;
	}


};*/
