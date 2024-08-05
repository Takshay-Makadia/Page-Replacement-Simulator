#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include "sim_engine.h"

int main(int argc,char* argv[]){

    if (argc != 4) {
        printf("Usage: %s num_frames filename method\n", argv[0]);
        exit(0);
    }

    int frameSize = atoi(argv[1]);
    if (frameSize <= 0 || frameSize > 100) {
        printf("Number of frames must be between 1 and 100\n");
        exit(0);
    }

    char *filename = argv[2];
    char *method = argv[3];

    if(strcmp(method,"fifo")!=0 && strcmp(method,"lru")!=0 && strcmp(method,"opt")!=0){
        printf("method must be either <fifo> OR <lru> OR <opt>\n");
        exit(0);
    }

    FILE *ptr = fopen(filename, "r");
    if (ptr == NULL) {
        printf("Error opening file %s\n", filename);
        exit(0);
    }

    int tmp;
    int arrSize = 0;
    while (fscanf(ptr, "%d", &tmp) == 1) {
        arrSize++;
    }

    fclose(ptr);

    ptr = fopen(filename, "r");
    if (ptr == NULL) {
        printf("Error opening file %s\n", filename);
        exit(0);
    }

    int arr[arrSize];
    tmp=0;
    while (fscanf(ptr, "%d", &arr[tmp++]) == 1);

    fclose(ptr);

    double missRate=sim(arr,arrSize,frameSize,1,method);

    printf("Miss rate = %0.2f %%\n",missRate);

    return 0;
}