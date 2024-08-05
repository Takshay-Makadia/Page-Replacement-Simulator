#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include "sim_engine.h"

int main(int argc,char* argv[]){

    if (argc != 5) {
        printf("Usage: %s min_frames max_frames increment filename\n", argv[0]);
        exit(0);
    }

    int minFrames=atoi(argv[1]);
    int maxFrames=atoi(argv[2]);
    int increment=atoi(argv[3]);
    char* filename=argv[4];

    if(minFrames<2 || maxFrames>100 || minFrames>maxFrames){
        printf("min_frames>1 and max_frames<=100 and min_frames<=max_frames\n");
        exit(0);
    }

    if(increment<=0){
        printf("increment>0\n");
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

    ptr = fopen("vmrates.dat", "w+");

    if (ptr == NULL) {
        printf("Error with opening the file.\n");
        exit(0);
    }

    double missRate;

    for(int i=minFrames;i<=maxFrames;i+=increment){
        if(i+increment>maxFrames)
            fprintf(ptr,"%d \n",i);
        else
            fprintf(ptr,"%d ",i);
    }

    for(int i=minFrames;i<=maxFrames;i+=increment){
        missRate=sim(arr,arrSize,i,0,"opt");
        printf("opt, %d frames: Miss rate = %0.2f %%\n",i,missRate);
        if(i+increment>maxFrames)
            fprintf(ptr,"%.2f \n",missRate);
        else
            fprintf(ptr,"%.2f ",missRate);
    }

    for(int i=minFrames;i<=maxFrames;i+=increment){
        missRate=sim(arr,arrSize,i,0,"lru");
        printf("lru, %d frames: Miss rate = %0.2f %%\n",i,missRate);
        if(i+increment>maxFrames)
            fprintf(ptr,"%.2f \n",missRate);
        else
            fprintf(ptr,"%.2f ",missRate);
    }

    for(int i=minFrames;i<=maxFrames;i+=increment){    
        missRate=sim(arr,arrSize,i,0,"fifo");
        printf("fifo, %d frames: Miss rate = %0.2f %%\n",i,missRate);
        if(i+increment>maxFrames)
            fprintf(ptr,"%.2f \n",missRate);
        else
            fprintf(ptr,"%.2f ",missRate);
    }

    fclose(ptr);

    return 0;
}