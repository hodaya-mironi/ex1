#include "anomaly_detection_util.h"
#include <math.h>



float average(const float* x, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += *(x + i);
    }
    if (size == 0) {
        return 0;
    }
    return sum / size;
}

float var(float* x, int size) {
    if (size == 0) {
        return 0;
    }
    float avg = average(x, size);
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += pow(*(x + i), 2);
    }
    return (1 / size) * sum - pow(avg, 2);

    
}


float cov(float* x, float* y, int size) {
    float sum = 0; 
    float avgX = average(x, size);
    float avgY = average(y, size);
    for(int i = 0; i < size; i++) {
          sum = sum + (*(x + i) - avgX) *  (*(y + i) - avgY); 
    }
     return sum / size; 
}

float pearson(float* x, float* y, int size) {
    float deviationX = 0, deviationY = 0;
    float varX = var(x, size);
    float varY = var(y, size);
    if (varX <= 0 || varY <= 0) {
        return 0;
    }
    deviationX = sqrt(varX);
    deviationY = sqrt(varY);
    return cov(x, y, size) / (deviationX * deviationY);
}

Line linear_reg(Point** points, int size) {
    float a = 0, b = 0;
    float* x;
    x = new float[size];
    float* y;
    y = new float[size];
    for (int i = 0; i < size; i++)
    {
        x[i] = *(points + i))->x;
        y[i] = *(points + i))->y;
    }
    float _cov = cov(x, y, size);
    float _var = var(x, size);
    if (_var != 0) {
        a = _cov / _var;
    }
    b = average(y, size) - a * average(x, size);
    return Line(a, b);

}

float dev(Point p, Point** points, int size) {
        return 0;
}

float dev(Point p, Line l) {
    return 0;
   // return abs(l.f(p.x) - p.y);
}
