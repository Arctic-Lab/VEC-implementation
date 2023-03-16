#pragma once

template<int Num>
void _mul_marix( double z[Num], double M[Num][Num] )
{
	double z2[Num];
	int i = 0, j = 0;
	for (int i = 0; i < Num; i++) {
		z2[i] = z[i];
		z[i] = 0.0;
	}
	for (j = 0; j < Num; j++)
	{
		for (i = 0; i < 2; i++)
		{
			z[j] += z2[i] * M[i][j];
		}
	}
}