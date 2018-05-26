#ifndef THREADS_FLOAT_H
#define THREADS_FLOAT_H

#define FIX_F (1<<16)  /*pow(2,16)*/
#define FIX_F_BY_2 (1<<15)
#define CONST_59_60 16110
#define CONST_1_60 273


long inline divide_x_y (long x, long y)
{
	return x * FIX_F / y;
}

int inline fix_to_int(long i)
{
	if(i > 0)
	{
		return (i + FIX_F_BY_2) / FIX_F;
	}
	else
		return 0;
}

long inline multiple_x_y (long x, long y)
{
	return x * y / FIX_F;
}

long inline multiple_x_n(long x, int n)
{
	return x * n;
}

long inline int_to_fix(int i)
{
	return i * FIX_F;
}
#endif
