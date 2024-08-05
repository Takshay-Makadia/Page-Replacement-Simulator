#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void generateRandom(int range,int seqLen,char *filename){
    FILE* ptr;
    ptr = fopen(filename, "w+");

    if (ptr == NULL) {
        printf("Error with opening the file.\n");
        exit(0);
    }

    int prev=-1;
    for(int i=0;i<seqLen;++i){
        int num=rand()%range;
        if(num!=prev){
            fprintf(ptr,"%d ",num);
            prev=num;;
        }
        else
            --i;
    }

    fclose(ptr);
}

int main(int argc,char *argv[]){
    if(argc!=4){
        printf("Usage : %s page_reference_range sequence_length file_name\n",argv[0]);
        exit(0);
    }

    int range=atoi(argv[1]);
    int seqLen=atoi(argv[2]);
    char *filename=argv[3];

    if(range>99 || range<1){
        printf("Range must be between 1 to 99.\n");
        exit(0);
    }

    generateRandom(range,seqLen,filename);
    printf("Sequence generated successfully.\n");

    return 0;
}