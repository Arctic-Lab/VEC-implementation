#pragma once
#include <vector>
#include <assert.h>

#include "common/common.h"
#include "task.h"

class solution 
{
public:

solution(double total): m_total(total) {

}

bool constrained(std::vector<task>& tasks)
{
    assert(tasks.size() == m_vec.size());
    double sum = 0;
    int n = m_vec.size();
    for(int i = 0; i < n; ++i) 
    {
        sum += m_vec[i];
        double useTime = tasks[i].requiredComputation / m_vec[i];
        if( useTime > tasks[i].maxTime ) return false;
    }
    return sum < m_total + EPS;
}

double getFitness(std::vector<task>& tasks)
{
    assert(tasks.size() == m_vec.size());
    assert(constrained(tasks));
    if(m_vec.size() == 0) return 0;
    double rev = 0;
    int n = m_vec.size();
    for(int i = 0; i < n; ++i)
    {
        rev += tasks[i].requiredComputation / m_vec[i];
    }
    return rev / n;
}

public:
    std::vector<double> m_vec;

private:
    double m_total;
};