#include <iostream>
#include <set>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "sheep.h"
#include "math_tool.h"

double Computafitness(double X[]) 
{
    return 0;
}

double *ComputGradient(double X[])
{
    return 0;
}


GROUPSHEEP::GROUPSHEEP() {
	left = left_range;
	right = right_range;
}



void GROUPSHEEP::initofgroup() {					//��?����?
	generationTimes = 1;
	NFE_iteration = 0;
	Bestres = 9e9;
	for (int i = 0; i <= ITE + 2; i++)his_Bestres[i] = 0;
	for (int i = 0; i < SNUM; i++) {				//��?����?
		for (int j = 0; j < DIM; j++) {				//��?���?����?
			sheep[i].coordinate[j] = rand() / (double)RAND_MAX*(right - left) + left;	//������???������?
		}
		sheep[i].fitness = Computafitness(sheep[i].coordinate);		//����?����?�������??

		CHECK(sheep[i].fitness);	//��������������������his_Bestres
		sheep[i].number = i + 1;					//����?���������?��?��������?
	}
}

void GROUPSHEEP::leader() {
	//cout << "leader" << endl;
	GradientDescent();
	double loc[DIM], res;//?����???������?������?��?��?
	for (int i = 0; i < SNUM; i++) {
		sheep[i].scatter = 0;
		for (int j = 0; j < DIM; j++) {
			loc[j] = sheep[i].coordinate[j] + rand() / (double)RAND_MAX*(sheep[bellwethernumber - 1].coordinate[j] - sheep[i].coordinate[j]);
			if (loc[j] < left)
				loc[j] = right - left + loc[j];
			else if (loc[j] > right)
				loc[j] = loc[j] - right + left;
		}
		res = Computafitness(loc);
		CHECK(res);	//��������������������his_Bestres
		if (res < sheep[i].fitness) {					//��?����?����????����?��
			for (int k = 0; k < DIM; k++) {
				sheep[i].coordinate[k] = loc[k];
			}
			sheep[i].fitness = res;
		}
	}
	generationTimes++;
}

//?����??��?����??

void GROUPSHEEP::wander() {
	//cout << "wander" << endl;
	int i, j, random;
	double loc[DIM], res;
	for (i = 0; i < SNUM; i++) //�?����������???��
	{
		for (j = 0; j < DIM; j++)
		{
			do {
				random = (int)(rand() / (double)RAND_MAX*SNUM);//������???����?��[0..39]
			} while (random == i || random == SNUM);	//��??����������?��?
			if (sheep[i].fitness < sheep[random].fitness)
			{
				loc[j] = sheep[random].coordinate[j];
				sheep[random].coordinate[j] = sheep[random].coordinate[j] + rand() / (double)RAND_MAX*(sheep[i].coordinate[j] - sheep[random].coordinate[j]);
				if (sheep[random].coordinate[j] < left)					//����������??
					sheep[random].coordinate[j] = right - left + sheep[random].coordinate[j];
				else if (sheep[random].coordinate[j] > right)
					sheep[random].coordinate[j] = sheep[random].coordinate[j] - right + left;
				res = Computafitness(sheep[random].coordinate);
				CHECK(res);	//��������������������his_Bestres
				if (res < sheep[random].fitness) 		//��?����?����???
					sheep[random].fitness = res;
				else
					sheep[random].coordinate[j] = loc[j];

				loc[j] = sheep[i].coordinate[j];
				sheep[i].coordinate[j] = sheep[i].coordinate[j] + rand() / (double)RAND_MAX*(sheep[i].coordinate[j] - sheep[random].coordinate[j]);
				if (sheep[i].coordinate[j] < left)					//����������??
					sheep[i].coordinate[j] = right - left + sheep[i].coordinate[j];
				else if (sheep[i].coordinate[j] > right)
					sheep[i].coordinate[j] = sheep[i].coordinate[j] - right + left;
				res = Computafitness(sheep[i].coordinate);
				CHECK(res);	//��������������������his_Bestres
				if (res < sheep[i].fitness) 		//��?����?����???
					sheep[i].fitness = res;
				else
					sheep[i].coordinate[j] = loc[j];
			}
			else
			{
				loc[j] = sheep[i].coordinate[j];
				sheep[i].coordinate[j] = sheep[i].coordinate[j] + rand() / (double)RAND_MAX*(sheep[random].coordinate[j] - sheep[i].coordinate[j]);
				if (sheep[i].coordinate[j] < left)					//����������??
					sheep[i].coordinate[j] = right - left + sheep[i].coordinate[j];
				else if (sheep[i].coordinate[j] > right)
					sheep[i].coordinate[j] = sheep[i].coordinate[j] - right + left;
				res = Computafitness(sheep[i].coordinate);
				CHECK(res);	//��������������������his_Bestres
				if (res < sheep[i].fitness) 		//��?����?����???
					sheep[i].fitness = res;
				else
					sheep[i].coordinate[j] = loc[j];

				loc[j] = sheep[random].coordinate[j];
				sheep[random].coordinate[j] = sheep[random].coordinate[j] + rand() / (double)RAND_MAX*(sheep[i].coordinate[j] - sheep[random].coordinate[j]);
				if (sheep[random].coordinate[j] < left)					//����������??
					sheep[random].coordinate[j] = right - left + sheep[random].coordinate[j];
				else if (sheep[random].coordinate[j] > right)
					sheep[random].coordinate[j] = sheep[random].coordinate[j] - right + left;
				res = Computafitness(sheep[random].coordinate);
				CHECK(res);	//��������������������his_Bestres
				if (res < sheep[random].fitness) 		//��?����?����???
					sheep[random].fitness = res;
				else
					sheep[random].coordinate[j] = loc[j];
			}
		}
	}
}


void GROUPSHEEP::bellwether() {						//?��??������?��
	double bellwetherfitness;
	double sum = 0;
	bellwetherfitness = sheep[0].fitness;
	bellwethernumber = 1;
	for (int k = 1; k < SNUM; k++) {
		if (sheep[k].fitness < bellwetherfitness) {
			bellwetherfitness = sheep[k].fitness;
			bellwethernumber = k + 1;				//������?��?��
		}
	}
	for (int j = 0; j < DIM; j++)
		GBest[j] = sheep[bellwethernumber - 1].coordinate[j];
	//��?��??
	for (int i = 0; i < SNUM; i++)
		sum += sheep[i].fitness;
	meanfitness = sum / SNUM;
	//������??
	worstfitness = sheep[0].fitness;
	for (int j = 1; j < SNUM; j++) {
		if (sheep[j].fitness > worstfitness) {
			worstfitness = sheep[j].fitness;
		}
	}
}


int GROUPSHEEP::huntaway()
{

	static int lastHunt = 0;//��?������?������?
	if (fabs(sheep[bellwethernumber - 1].fitness - oldbellwetherfitness) >= U) return 0;
	if (generationTimes < lastHunt) lastHunt = 0;
	if (generationTimes - lastHunt <= TIMES_HUNTAWAY) return 0; //������?����?����������??������?����������?������?����

	int i, j, random, randomsheep;
	double loc[DIM], res;
	lastHunt = generationTimes;		//������?������?������?
	int k_max = 20;             //����������??SNUM/2
	//int number = 0;


	if (fabs(sheep[bellwethernumber - 1].fitness - oldbellwetherfitness) < U)
	{
		//cout << "huntaway" << endl;
		int k = 1;									//��0������������????		
		while (k <= k_max) {							//��k����
			double bellwetherfitness1 = sheep[bellwethernumber - 1].fitness;
			//cout <<"begin k="<<k << endl;
			int isscatter = 0;               //��?����????����1��0
			//Sleep(1000);
			srand((int)time(0));

			for (i = 0; i < SNUM; i++) {
				if (i + 1 != bellwethernumber)			//������????
				{
					if (isscatter >= k)
						break;
					else {
						//double pp = k / SNUM;
						if (rand() / (double)RAND_MAX < 0.3)
						{
							if (sheep[i].scatter == 1)
								continue;

							else
							{
								sheep[i].scatter = 1;
								//cout << "������=" << i << endl;
								isscatter++;               //��?��������?
								for (j = 0; j < DIM; j++)
								{
									sheep[i].coordinate[j] = rand() / (double)RAND_MAX*(right - left) + left;//��������������
									if (sheep[i].coordinate[j] < left)			//����?�󝝝�?����?
										sheep[i].coordinate[j] = right - left + sheep[i].coordinate[j];
									else if (sheep[i].coordinate[j] > right)
										sheep[i].coordinate[j] = sheep[i].coordinate[j] - right + left;
								}
								sheep[i].fitness = Computafitness(sheep[i].coordinate);  //�󝝝���?��?
								CHECK(sheep[i].fitness);	//��������������������his_Bestres
							}
							i += int(rand() / (double)RAND_MAX);
						}
					}
				}
			}
			int num = 0;
			if (k > isscatter) {
				for (i = SNUM; i >= 0; i--)
				{
					if (i + 1 != bellwethernumber)			//������????
					{
						if (num < k - isscatter)
						{
							if (sheep[i].scatter == 0)
							{
								sheep[i].scatter = 1;
								//cout << "-------num������=" << i;
								for (j = 0; j < DIM; j++)
								{
									sheep[i].coordinate[j] = rand() / (double)RAND_MAX*(right - left) + left;//��������������
									if (sheep[i].coordinate[j] < left)			//����?�󝝝�?����?
										sheep[i].coordinate[j] = right - left + sheep[i].coordinate[j];
									else if (sheep[i].coordinate[j] > right)
										sheep[i].coordinate[j] = sheep[i].coordinate[j] - right + left;
								}
								sheep[i].fitness = Computafitness(sheep[i].coordinate);  //�󝝝���?��?
								CHECK(sheep[i].fitness);	//��������������������his_Bestres
								num++;
							}
						}
					}
				}
			}
			isscatter = isscatter + num;

			for (i = 0; i < SNUM; i++)
			{
				//��?��?����
				if (isscatter == 0)
					return 0;
				if (sheep[i].scatter != 1)
				{
					//��?��?����i?��??����?����random��?��?
					while (1)
					{
						random = (int)(rand() / (double)RAND_MAX*(SNUM));
						if (sheep[random].scatter == 1)
							break;

					}
					if (sheep[i].fitness <= sheep[random].fitness)
					{
						//cout << "i=" << i << endl;
						//cout << "select a random sheep is" << random<<endl;
						//��???������?����??����?����������������?
						for (j = 0; j < DIM; j++)
						{
							loc[j] = sheep[random].coordinate[j] + rand() / (double)RAND_MAX*(sheep[i].coordinate[j] - sheep[random].coordinate[j]);
							//printf("%.6lf", rand() / (double)RAND_MAX);
							if (loc[j] < left)			//����?�󝝝�?����?
								loc[j] = right - left + loc[j];
							else if (loc[j] > right)
								loc[j] = loc[j] - right + left;
						}
						res = Computafitness(loc);		//����??
						CHECK(res);//��������������������his_Bestres

						if (res < sheep[random].fitness)	//��?����?����???
						{
							for (j = 0; j < DIM; j++)
							{
								sheep[random].coordinate[j] = loc[j];
							}

							sheep[random].fitness = res;
						}

						//��?����
						for (j = 0; j < DIM; j++)
						{
							loc[j] = sheep[i].coordinate[j] + rand() / (double)RAND_MAX*(sheep[i].coordinate[j] - sheep[random].coordinate[j]);
							if (loc[j] < left)					//����������??
								loc[j] = right - left + loc[j];
							else if (loc[j] > right)
								loc[j] = loc[j] - right + left;
						}
						res = Computafitness(loc);
						CHECK(res);//��������������������his_Bestres
						if (res < sheep[i].fitness)			//��?����?����???
						{
							for (j = 0; j < DIM; j++)
							{
								sheep[i].coordinate[j] = loc[j];
							}
							sheep[i].fitness = res;
						}

					}
					else	//��???������?����???�㝝��������
					{
						for (j = 0; j < DIM; j++)
						{
							loc[j] = sheep[i].coordinate[j] + rand() / (double)RAND_MAX*(sheep[random].coordinate[j] - sheep[i].coordinate[j]);
							//printf("%.6lf", rand() / (double)RAND_MAX);
							if (loc[j] < left)			//����?�󝝝�?����?
								loc[j] = right - left + loc[j];
							else if (loc[j] > right)
								loc[j] = loc[j] - right + left;
						}
						res = Computafitness(loc);	//����??
						CHECK(res);//��������������������his_Bestres
						if (res < sheep[i].fitness)	//��?����?����???
						{
							for (j = 0; j < DIM; j++)
							{
								sheep[i].coordinate[j] = loc[j];
							}
							sheep[i].fitness = res;
						}
						//��?����
						for (j = 0; j < DIM; j++)
						{
							loc[j] = sheep[random].coordinate[j] + rand() / (double)RAND_MAX*(sheep[random].coordinate[j] - sheep[i].coordinate[j]);
							if (loc[j] < left)					//����������??
								loc[j] = right - left + loc[j];
							else
								if (loc[j] > right)
									loc[j] = loc[j] - right + left;
						}
						res = Computafitness(loc);
						CHECK(res);//��������������������his_Bestres
						if (res < sheep[random].fitness)			//��?����?����???
						{
							for (j = 0; j < DIM; j++)
							{
								sheep[random].coordinate[j] = loc[j];
							}
							sheep[random].fitness = res;
						}

					}
				}
			}
			bellwether();

			double nowbellfitness = sheep[bellwethernumber - 1].fitness;
			if (nowbellfitness < bellwetherfitness1)
			{
				//cout<<"��"<< k<<"����������??<<nowbellfitness <<" ??����?�㝝��?<<endl;
				sheep[bellwethernumber - 1].fitness = nowbellfitness;
				bellwetherfitness1 = nowbellfitness;
				k = 1;     //?�k����������?????��������������?
				//cout << "back to k=1" << endl;

				for (int i = 0; i < SNUM; i++)
				{
					sheep[i].scatter = 0;
				}
			}
			else {
				//	cout << "--------��" << k << "����?��?? << nowbellfitness << " ??����?��???" << endl;
				k++;				//?�k������????�����㝝�����k+1����������?
				for (int i = 0; i < SNUM; i++)
				{
					sheep[i].scatter = 0;
				}
			}

		}

	}
	return 1;
}

//?����
void GROUPSHEEP::GradientDescent()
{
	double PreviousFitness, NowFitness;
	double Step;
	int count = 0;
	BeforeGD = Computafitness(GBest);
	CHECK(BeforeGD);//��������������������his_Bestres
	while (true)
	{
		Step = 1.0 / (1.0 + exp(++count));
		PreviousFitness = Computafitness(GBest);
		CHECK(PreviousFitness);//��������������������his_Bestres
		double* Gradient = ComputGradient(GBest);
		//CHECK(*Gradient);//��������������������his_Bestres
		for (int j = 0; j < DIM; j++)
		{
			GBest[j] -= Step * Gradient[j];
			if (GBest[j] < left)			//����?�󝝝�?����?
				GBest[j] = rand() / (double)RAND_MAX * (right - left) + left;//new
			else if (GBest[j] > right)
				GBest[j] = rand() / (double)RAND_MAX * (right - left) + left;//new
		}
		delete[] Gradient;
		NowFitness = Computafitness(GBest);
		CHECK(NowFitness);//��������������������his_Bestres
		if (NowFitness < sheep[bellwethernumber - 1].fitness)
		{
			for (int j = 0; j < DIM; j++)
				sheep[bellwethernumber - 1].coordinate[j] = GBest[j];
			sheep[bellwethernumber - 1].fitness = NowFitness;
		}
		//������?����
		if ((fabs(NowFitness - PreviousFitness) < Epsilon) || (NowFitness >= PreviousFitness))
		{
			break;
		}

	}
	AfterGD = NowFitness;
}

void GROUPSHEEP::CHECK(double res) {
	if (fabs(res) < fabs(Bestres)) {
		Bestres = res;

	}
	his_Bestres[NFE_iteration++] = Bestres;
}
