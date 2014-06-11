class elements_of_pairs
{
   private:
	   char element_type;
	   bool Is_finish ;
	   int path_pointer[2][2];
   public:
       elements_of_pairs()
	   {
		   for(int i =0;i<2;i++)
			   for(int j=0;j<2;j++)
		           path_pointer[i][j]=50;

		   element_type='.';
		   Is_finish = false;
	   }

	   char get_type()
	   {
		   return element_type;
	   }

	   void set_type(char type)
	   {
		   element_type = type;
	   }

	   void Initialization_point_location(int x ,int y)
	   {
		   if(path_pointer[0][0] ==50 && path_pointer[0][1]==50)
			 set_path_pointer(0,x,y);
		   else
			 set_path_pointer(1,x,y);
	   }

	   bool get_Is_finish()
	   {
		   return Is_finish;
	   }

	   void set_Is_finish(bool set)
	   {
		   Is_finish = set;
	   }
	   void set_path_pointer(int number,int x,int y)
	   {
		   path_pointer[number][0] = x;
		   path_pointer[number][1] = y;
	   }

	   int get_path_pointer(int number,int xy)
	   {
		   return path_pointer[number][xy];
	   }

};