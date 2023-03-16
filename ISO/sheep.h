#pragma once

#include <fstream>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <cmath>

#include "solution.h"

/********************************************************************************
**羊群算法V15.1
**牧羊犬阶段为将羊群中一定数量的整只羊随机打散
**本版本牧羊犬阶段有未打散羊群向打散羊群漫游的过程
*********************************************************************************/
#define SHEEP_VERSION "15.1"				//当前算法的版本信息，更改时注意使用双引号

using  namespace std;
#define pai acos(-1.0)

#define DIM					100				//粒子维度
#define SNUM				40				//种群规模
#define ITE					20000000		//迭代次数
#define N					1				//每组的测试数目
#define SET					1				//测试组数
#define DEGREE_HUNTAWAY		0.2				//牧羊犬介入程度
#define Epsilon				1e-10			//GD误差
#define step                1E-4			
//2245

//#define U					0.000001			//最小阀值
#define U					0.000000000001			//最小阀值
#define PRINT_BELLWETHER	1					//是否在文件1中输出每一代领头羊
#define PRINT_HUNTAWAY		1					//是否输出牧羊犬介入
#define TIMES_HUNTAWAY		0	 				//牧羊犬介入代数最小间隔
#define PRINTF_RESULT_FILE	1					//是否输出文件2 仅输出每次最终结果
#define PRINTF_iteration_FILE	1				//是否输出文件3 输出每次评估结果

/*各种适应度函数选择，要用哪个，就设置为1,但只能有一个为1*/
#define TEST_FUN_CHOICE		"shifted_Rotated_Non_Continuous_Rastrigin"		//改变测试函数，请同时将此宏定义改为对应测试函数名

#define Best_fitness		800.0						//改变测试函数，请同时更改此函数的全局最优解

#define left_range			-100.0						//每一维度坐标范围(如果是整数，请务必写为**.0，比如整数600写为600.0)
#define right_range			100.0						 //每一维度坐标范围(如果是整数，请务必写为**.0，比如整数600写为600.0)

//注意：
//二维函数只能测试二维
//其余普通函数可测试任意维度
//旋转平移函数只能测试10维，30维和50维	



#define FM_Problem 0  //维度：6，范围：[−6.4, 6.35],fitness:0，迭代：50000、100000、1500000
#define Spread_Spectrum_Radar_Polly_phase_Code_Design 0  //维度：20，范围：[0, 2*pai],fitness:0，迭代：50000、100000、1500000
#define Gear_train_design_problem 0 //维度：4，范围：[12,60],fitness:0,迭代：5000



struct SHEEP
{
public:
	solution coordinate;						//存储每只羊的坐标
	double	 fitness;                           //存储适度值
	int		 number;                            //存储羊的编号
	int		 scatter;                           //判断这只羊是否被打散 1被打散，0没被打散
};

class GROUPSHEEP
{
private:                                			//牧场范围，也就是解空间范围
	double	left;                                	//存储每维坐标的范围
	double	right;
public:
	SHEEP	sheep[SNUM];						//羊群
	int		bellwethernumber;					//领头羊编号
	double	worstfitness;						//种群最差适度值
	double	meanfitness;						//整个羊群的适度值的平均值
	double	oldbellwetherfitness;				//存储上一代领头羊的适度值
	int		generationTimes;					//当前迭代次数
	double  GBest[DIM];                                //最优羊的位置
	double	Bestres;                                //最优羊的评估结果
	double  BeforeGD;                                //梯度下降之前的值
	double  AfterGD;                                //梯度下降后的值
	int		NFE_iteration;						//调用评估函数的次数
	double	his_Bestres[ITE + 5];					//历史最优羊的评估结果


public:
	GROUPSHEEP();
	void	initofgroup();						//初始化种群
	void	leader();                                //领头羊阶段
	void	wander();                                //羊群漫游阶段
	void	bellwether();						//更新一次领头羊,并且求出羊群的平均适度值和最差适度值
	int		huntaway();                                //牧羊犬阶段
	void	GradientDescent();					//梯度下降
	void	CHECK(double res);					//检测是否得出更优解
	//void    Pseudo_GradientDescent();
};

double Computafitness(double a[]);				//测试函数		

   