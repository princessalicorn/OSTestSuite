#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#ifndef MAX_BUF
#define MAX_BUF 1024
#endif // MAX_BUF


void foldertest()
{
    /*Nessecary code for this part of the program*/
    FILE *fp;
    system("touch /home/amelia/results.txt"); //MAKE A CONSTANT VARIABLE FOR PATH!!!
    fp = fopen("/home/amelia/results.txt", "w+"); //MAKE A CONSTANT VARIABLE FOR PATH!!!

    /*One folder... hmmmm*/
    fprintf(fp, "Results for Making 1 Folder:\n");
    struct stat st = {0};
    if (stat("test", &st) == 1)
    { //MAKE A CONSTANT VARIABLE FOR PATH!!!
        system("rm -rf test"); //rewrite this in C
    }
    double eltimetest1 = 0.0;
    clock_t begin = clock(); //Do the fun!
    mkdir("test", 777); //add ifdef for non linux systems to not include 777
    clock_t end = clock();
    eltimetest1 += (double)(end - begin) / CLOCKS_PER_SEC;

    fprintf(fp, "Elapsed time: %f seconds\n", eltimetest1);

    system("rm -rf test"); //rewrite this in C

    /*OH SHIT!!?!? 100 FOLDERS????*/
    fprintf(fp, "Results for Making 100 Folders:\n");
    int i = 0;
    double eltimetest2 = 0.0;
    clock_t begin2 = clock();
    while (i <= 100)
    {
        char filename1 = ("%d", i);
        mkdir(filename1, 777);
        i++;
    }
    clock_t end2 = clock();
    eltimetest2 += (double)(end2 - begin2) / CLOCKS_PER_SEC;
    fprintf(fp, "Elapsed time: %f seconds\n", eltimetest2);

    i = 0;
    while (i <= 100)
    {
        char filename2 = ("%d", i);
        rmdir(filename2);
        i++;
    }

    double finaltime = eltimetest1 + eltimetest2;

    fclose(fp);
    return;
}

void rwtest()
{
    FILE *fp;
    fp = fopen("/home/amelia/results.txt", "a+");

    fprintf(fp, "\n");
    double eltimetest3 = 0.0;
    clock_t begin3 = clock();
    //system("dd if=/dev/urandom of=rwtestrandom bs=64M count=16 iflag=fullblock");
    FILE *onegigwrite;
    onegigwrite = fopen("/home/amelia/1gtestwritefile", "w+");
    size_t i = 0;
    while (i < 1000000000)
    {
        int rngnum = rand() % 10;
        char charnum = rngnum - '0';
        fprintf(onegigwrite, &charnum);
        i++;
    }
    clock_t end3 = clock();
    eltimetest3 += (double)(end3 - begin3) / CLOCKS_PER_SEC;
    //system("rm /home/amelia/1gtestwritefile");

    fprintf(fp, "Disk Read/Write Test (1.8GB)\n");
    fprintf(fp, "Elapsed time: %f seconds\n", eltimetest3);

}

int main()
{
    char path[MAX_BUF];
    char initans;
    getcwd(path, MAX_BUF);
    printf("Your current working directory is %s, do you wish to continue y/n? Note this operation will temporarily take numerous gigabytes of space! ", path);
         scanf("%c", &initans);
        if(initans == 'y' || initans == 'Y')
        {
            foldertest();
            printf("Folder Writing Test Complete!");
            rwtest();

        }
        else if(initans == 'n' || initans == 'N')
        {
            return 0;
        }
        else
        {
            printf("You did not input a valid response, please try again! ");
            return -1;
        }
}
