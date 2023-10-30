#pragma once


namespace ds
{
	template<int rows_count>
	class sparse_array
	{
	public:
		using func_t = int; 
		
		sparse_array();

		int add_column();
		void remove_column(int id);

		void for_each(func_t func);
	
		void get(int row, int id);
		void add(int row, int id);
	private:

	};
}