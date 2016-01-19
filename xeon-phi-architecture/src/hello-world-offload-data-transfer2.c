#include <stdio.h>
#include <stdlib.h>

#pragma offload_attribute(push, target(mic))
    void Function1(){
        printf("Hello World from coprocessor 0!\n");
        fflush(0);
    }
    
    void Function2(){
        printf("Hello World from coprocessor 1!\n");
        fflush(0);
    }

    void Function3(){
        char* env_var = getenv("ENV_VAR");
        if (env_var){
            printf("ENV_VAR=%s on the coprocessor 0\n", env_var);
        }
        else{
            printf("ENV_VAR is not defined on the coprocessor 0\n");
        }
    }

    void Function4(){
        char* env_var = getenv("ENV_VAR");
        if (env_var){
            printf("ENV_VAR=%s on the coprocessor 1\n", env_var);
        }else{
            printf("ENV_VAR is not defined on the coprocessor 1\n");
        }
    }
#pragma offload_attribute(pop)


int main(int argc, char * argv[]){
    
    printf("Hello World from host!\n");
    char* env_var = getenv("ENV_VAR");

    if (env_var){
        printf("ENV_VAR=%s on the host system\n", env_var);
    }else{
        printf("ENV_VAR is not defined on the host system\n");
    }

    #pragma offload target(mic:0){
    {
        Function1();
    }
    #pragma offload target (mic:1)
    {
        Function2();
    }
    #pragma offload target(mic:0)
    {
        Function3();
    }
    #pragma offload target(mic:1)
    {
        Function4();
    }
}
