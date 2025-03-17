double NumOfDigits(double num)
{
	double dig_counter = 0;
	double test = 0;
	
	while(num > test)
	{
		++dig_counter;
		num /= 10;
	}
	
	return dig_counter;
}

double Sqrt(double input)
{
	double increasment = 1;
	double res = 0;
	
	if (0 > input)
	{
		return -1;
	}
	while(NumOfDigits(res) < 15)
	{
		while((res * res) < num)
		{
			res += increasment;
		}
		if((res * res) == num)
		{
			return res;
		}
		
		res -= increasment;
		increasment /= 10;
	}	
	
	return res;
}

