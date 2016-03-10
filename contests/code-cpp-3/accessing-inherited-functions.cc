class D : A, B, C
{

	int val;
	public:
	//Initially val is 1
	D()
	{
		val=1;
	}


	//Implement this function
	void update_val(int x)
	{
		while (x % 2 == 0) x /= 2, A::func(val);
		while (x % 3 == 0) x /= 3, B::func(val);
		while (x % 5 == 0) x /= 5, C::func(val);
	}
	//For Checking Purpose
	void check(int); //Do not delete this line.
};
