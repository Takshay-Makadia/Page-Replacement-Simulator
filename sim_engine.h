#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

#define FRAME_WIDTH 2

void printFrames(int frames[], int frameSize, int reference) {
    printf("%d: [", reference);
    for (int i = 0; i < frameSize; i++) {
        if (frames[i] == -1)
            printf("  ");
        else
            printf("%*d", FRAME_WIDTH, frames[i]);
        if (i < frameSize - 1)
            printf("|");
    }
    printf("] ");
}

double sim(int arr[],int arrSize,int frameSize,int verbose,char* method){
    int frames[frameSize];
    memset(frames, -1, sizeof(frames));
    int pageFaults = 0,total=0;

    if(verbose)
        printf("%s method in use\n",method);

    int mp[100];
    memset(mp, -1, sizeof(mp));
    int framesFilled=0,del=0;

    for(int i=0;i<arrSize;++i){

        if(mp[arr[i]]>=0 && framesFilled!=frameSize){
            if(verbose){
                printFrames(frames,frameSize,arr[i]);
                printf("\n");
            }
        }
        else if(mp[arr[i]]>=0 && framesFilled==frameSize){
            total++;
            if(verbose){
                printFrames(frames,frameSize,arr[i]);
                printf("\n");
            }
        }
        else if(mp[arr[i]]==-1 && framesFilled!=frameSize){
            frames[framesFilled++]=arr[i];
            mp[arr[i]]=i;

            if(verbose){
                printFrames(frames,frameSize,arr[i]);
                printf("\n");
            }
        }
        else{
            if(method[0]=='l'){
                int num,idx=100;
                for(int j=0;j<100;++j){
                    if(mp[j]!=-1 && idx>mp[j]){
                        num=j;
                        idx=mp[j];
                    }
                }

                for(int j=0;j<frameSize;++j){
                    if(frames[j]==num){
                        mp[frames[j]]=-1;
                        mp[arr[i]]=i;
                        frames[j]=arr[i];
                    }
                }

                total++;
                pageFaults++;
                if(verbose){
                    printFrames(frames,frameSize,arr[i]);
                    printf("F\n");
                }
            }
            else if(method[0]=='f'){
                mp[frames[del]]=-1;
                mp[arr[i]]=i;
                frames[del]=arr[i];
                del=(del+1)%frameSize;
                total++;
                pageFaults++;
                if(verbose){
                    printFrames(frames,frameSize,arr[i]);
                    printf("F\n");
                }
            }
            else{
                int num;
                for(int j=i+1;j<arrSize;++j){
                    if(mp[arr[j]]>=0)
                        num=arr[j];
                }

                for(int j=0;j<frameSize;++j){
                    if(frames[j]==num){
                        mp[frames[j]]=-1;
                        mp[arr[i]]=i;
                        frames[j]=arr[i];
                    }
                }

                total++;
                pageFaults++;
                if(verbose){
                    printFrames(frames,frameSize,arr[i]);
                    printf("F\n");
                }
            }
        }
    }

    if(total==0 && pageFaults==0)
        return 0.00;

    return (double)(((pageFaults*1.0)/total)*100);
}