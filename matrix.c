#include <stdio.h>

#ifdef _WIN32
    char * coloredprintf = "%04d ";
#else
    char * coloredprintf = "\x1b[1;33m%04d\x1b[0m ";
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
                //if(c % 2 == 0)
                //    printf("\x1b[40m    \x1b[0m");
                //else
                    printf("%04d ",c);
            }

            m++;
        }
        printf("\n");
    }


}