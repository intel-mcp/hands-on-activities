#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

__declspec(target(mic))

double a, b, sum;

__attribute__((target(mic))) void MyFunction() {
    sum = a + b;
}

int main(int argc, char * argv[] ) {
    a=5;
    b=2;

    #pragma offload target(mic) in (a, b) out (sum)
    {
        MyFunction();
    }

    printf("sum %f \n", sum);
}
