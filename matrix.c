#include <stdio.h>

#ifdef _WIN32
    char * coloredprintf = "%03d ";
#else
    char * coloredprintf = "\x1b[33m%03d\x1b[0m ";
#endif

int primality_test(int number, int divisor){
    if(number % divisor == 0)
        return 0;
    
    if (divisor <= number/2)
        return primality_test(number,divisor + 1);
    else
        return 1;
}
int is_prime(int number){
    if(number == 2)
        return 1;
    else if(number == 1 || number % 2 == 0)
        return 0;
    else
        return primality_test(number,2);
}

int main(){
    int ma[100][100];
    int n, i, j, c, m = 1;

    printf("\nTamanho da matriz: ");
    scanf("%d",&n);

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(i % 2 == 0)
                c = m;
            else
                c = (i+1)*n - j;


            if(is_prime(c)){
                printf(coloredprintf,c);
            }else{
                printf("%03d ",c);
            }

            m++;
        }
        printf("\n");
    }


}