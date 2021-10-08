/*
Author: Flutterheart the Alicorn
Purpose: Abstractly testing operating system performance using various abstract
metrics in POSIX Version: In Development
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#ifndef PATH // MODIFY THIS TO WHATEVER DIRECTORY YOU WANT THE TESTS TO TAKE IN
#define PATH "/home/amelia/testdir/"
#endif // PATH
#ifndef MAX_BUF
#define MAX_BUF 1024
#endif // MAX_BUF

void foldertest() {
  /*Nessecary code for this part of the program*/
  FILE *fp;
  char buf[BUFSIZ];

  const char *resultspath = PATH "results.txt";
  snprintf(buf, sizeof(buf), "touch %s", resultspath);
  system(buf);

  fp = fopen(resultspath, "w+");

  /*One folder... hmmmm*/
  fprintf(fp, "Results for Making 1 Folder:\n");
  struct stat st = {0};
  if (stat("test", &st) == 1) {
    snprintf(buf, sizeof(buf), "rm", resultspath);
    system(buf); // Rewrite in C
  }

  double eltimetest1 = 0.0;
  clock_t begin = clock(); // Do the fun!
  char dirbuf[BUFSIZ];
  const char *testdir = PATH "testdir/";
  printf("%s\n", testdir);
  mkdir(testdir, 777); // add ifdef for non linux systems to not include 777
  clock_t end = clock();

  eltimetest1 += (double)(end - begin) / CLOCKS_PER_SEC;

  fprintf(fp, "Elapsed time: %f seconds\n", eltimetest1);

  snprintf(dirbuf, sizeof(buf), "rm -rf %s", testdir);
  // system(dirbuf);

  /*OH SHIT!!?!? 100 FOLDERS????*/
  fprintf(fp, "Results for Making 100 Folders:\n");
  int i;
  double eltimetest2 = 0.0;
  clock_t begin2 = clock();
  for (i = 0; i <= 100; i++) {
    chdir(PATH);
    char filename1 = i - '0';
    snprintf(dirbuf, sizeof(buf), "mkdir %s%d", testdir, i);
    system(dirbuf);
  }
  clock_t end2 = clock();
  eltimetest2 += (double)(end2 - begin2) / CLOCKS_PER_SEC;
  fprintf(fp, "Elapsed time: %f seconds\n", eltimetest2);

  i = 0;
  chdir(PATH);
  while (i <= 100) {
    char filename2 = i - '0';
    snprintf(dirbuf, sizeof(buf), "rm -rf %s%d", testdir, i);
    system(dirbuf);
    i++;
  }

  double finaltime = eltimetest1 + eltimetest2;

  fclose(fp);
  return;
}

void rwtest() {
  char buf[BUFSIZ];
  FILE *fp;
  const char *resultspath = PATH "results.txt";
  fp = fopen(resultspath, "a+");
  FILE *onegigwrite;
  const char *onegigwrpath = PATH "1gtestwritefile";
  fprintf(fp, "\n");
  double eltimetest3 = 0.0;
  clock_t begin3 = clock();
  // system("dd if=/dev/urandom of=rwtestrandom bs=64M count=16
  // iflag=fullblock");

  onegigwrite = fopen(onegigwrpath, "w+");
  size_t i = 0;
  while (i < 1000000000) {
    int rngnum = rand() % 10;
    char charnum = rngnum - '0';
    fprintf(onegigwrite, &charnum);
    i++;
  }
  clock_t end3 = clock();
  eltimetest3 += (double)(end3 - begin3) / CLOCKS_PER_SEC;

  snprintf(buf, sizeof(buf), "rm %s", onegigwrpath);
  system(buf);

  fprintf(fp, "Disk Read/Write Test (1.8GB)\n");
  fprintf(fp, "Elapsed time: %f seconds\n", eltimetest3);
}

void dbtest() {
  char contans;
  printf("Do you want to conduct database testing? This will likely require a "
         "COBOL compiler!");
  scanf("%c", &contans);
  if (contans == 'y' || contans == 'Y')
  {
    
  }
}

int main() {
  char path[MAX_BUF];
  char initans;
  chdir(PATH);
  getcwd(path, MAX_BUF);
  printf("Your current working directory is %s, do you wish to continue y/n?",
         path);
  scanf("%c", &initans);
  if (initans == 'y' || initans == 'Y') {
    foldertest();
    printf("Folder Writing Test Complete!\n");
    rwtest();
    printf("Random R/W Test Complete!\n");

  } else if (initans == 'n' || initans == 'N') {
    return 0;
  } else if (initans == 'd' || initans == 'D') {
    printf("%s", PATH);
    const char *resultspath = PATH "results.txt";
    printf("%s", resultspath);
  } else {
    printf("You did not input a valid response, please try again! ");
    return -1;
  }
}
