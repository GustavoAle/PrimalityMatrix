#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    char * coloredprintf = "%04lu ";
#else
    char * coloredprintf = "\x1b[1;33m%04lu\x1b[0m ";
#endif

unsigned long int primality_test(unsigned long int number, unsigned long int divisor){
    if(number % divisor == 0)
        return 0;
    
    if (divisor <= number/2)
        return primality_test(number,divisor + 1);
    else
        return 1;
}
unsigned long int is_prime(unsigned long int number){
    if(number == 2)
        return 1;
    else if(number == 1 || number % 2 == 0)
        return 0;
    else
        return primality_test(number,2);
}

int main(){
    FILE *f;
    unsigned long int n, x, y, c, m = 1, w, h;
    unsigned char r, g, b;
    double perc;
    unsigned char *img = NULL;
 
    printf("\nTamanho da matriz: ");
    scanf("%lu",&n);

    w = n;
    h = n;

    unsigned long int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int

    img = (unsigned char *)malloc(3*w*h);
    memset(img,0,3*w*h);

    srand(time(NULL));

    printf("\n");
    printf("\x1b%d",7);
    for(unsigned long int i=0; i<w; i++)
    {
        for(unsigned long int j=0; j<h; j++)
        {
            if(i % 2 == 0)
                c = m;
            else
                c = (i+1)*n - j;

            //x=i; y=(h-1)-j;
            x=j; y=i;
            if(is_prime(c)){
                /*
                r = (rand() % 255);
                g = (rand() % 255);
                b = (rand() % 255);
                //printf(coloredprintf,c);
                */
                r = g = b = 0;
            }else{
                r = 255;
                g = 255;
                b = 255;
                //printf("%04lu ",c);
            }

            img[(x+y*w)*3+2] = (unsigned char)(r);
            img[(x+y*w)*3+1] = (unsigned char)(g);
            img[(x+y*w)*3+0] = (unsigned char)(b);

            m++;
        }
        perc = (double)(i+1)/w * 100;

        printf("\x1b%d",8);
        printf("\x1b%d",7);
        printf("Efetuado: %3.2lf%%",perc);
        
        //printf("\n");
    }

    printf("\n\nPixels gravados");

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};

    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

    bmpinfoheader[ 4] = (unsigned char)(       w    );
    bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
    bmpinfoheader[ 6] = (unsigned char)(       w>>16);
    bmpinfoheader[ 7] = (unsigned char)(       w>>24);
    bmpinfoheader[ 8] = (unsigned char)(       h    );
    bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
    bmpinfoheader[10] = (unsigned char)(       h>>16);
    bmpinfoheader[11] = (unsigned char)(       h>>24);

    f = fopen("img.bmp","wb");
    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);
    for(int i=0; i<h; i++)
    {
        fwrite(img+(w*(h-i-1)*3),3,w,f);
        fwrite(bmppad,1,(4-(w*3)%4)%4,f);
    }

    free(img);
    fclose(f);
    printf("\nDone!\n\n");
}