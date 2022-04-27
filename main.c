#include "stdio.h"
#include "inttypes.h"
typedef long double f64_t;

const f64_t pi = 3.14159265358979323846;
const f64_t pi2 = pi * 2;
const f64_t piHalf = pi/2;

f64_t power(f64_t val, f64_t exponent) {
    f64_t powVal = 1; 
    for (uint64_t i = 0; i < exponent; i++) powVal *= val;
    return powVal;
}

f64_t taylorSeries(f64_t piNormalizedVal, uint64_t steps) {
    f64_t seriesVal = piNormalizedVal;

    // first series
    int8_t op = 1;
    f64_t tempVal = power(seriesVal, 3) / 6;  // fact(3) = 6 
    seriesVal -= tempVal;

    for (uint64_t i = 4; i < steps*4; i += 2) {
        tempVal *= piNormalizedVal / i;
        tempVal *= piNormalizedVal / (i+1);
        seriesVal += op ? tempVal : -tempVal; // you could also use ((i+1) % 3 == 0) but there is no reason to
        op = !op;
    } 
    return seriesVal;
}

f64_t normalizeToPi(f64_t rad){
    uint64_t scale = rad / pi2; // type casting is essientally acting as a floor function
    f64_t bottom = scale * pi2;
    f64_t pi2NormalizedVal = rad - bottom;

    return ((pi < pi2NormalizedVal) ? (pi - pi2NormalizedVal) : pi2NormalizedVal);
}


f64_t sine(f64_t rad){
    f64_t piNormalizedVal = normalizeToPi(rad);
    return taylorSeries(piNormalizedVal, 16);
}

f64_t cosine(f64_t rad){
    return sine(rad+piHalf);
}

f64_t tangent(f64_t rad){
    return sine(rad)/cosine(rad);
}

f64_t cotangent(f64_t rad){
    return 1/tangent(rad);
}

f64_t secant(f64_t rad){
    return 1/cosine(rad);
}
f64_t cosecant(f64_t rad){
    return 1/sine(rad);
}

int main(){
   return 0;
}