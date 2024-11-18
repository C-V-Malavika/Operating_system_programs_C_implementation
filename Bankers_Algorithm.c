#include <stdio.h>

int main(){

    int p;
    printf("Enter the number of processes : ");
    scanf("%d", &p);
    int r;
    printf("Enter the number of resources : ");
    scanf("%d", &r);
   
    int allocation[p][r];
    int max[p][r];
    int need[p][r];
    int finish[p];
    int available[r];
    int sum_alloc[r];
    int ans[p];
    int overall[r];
   
    for (int j = 0; j < r; j++){
        sum_alloc[j] = 0;
    }
   
    for (int j = 0; j < r; j++){
        printf("Instances for resources for R%d : ", j + 1);
        scanf("%d", &overall[j]);
    }
   
    for (int i = 0; i < p; i++){
        for (int j = 0; j < r; j++){
            printf("Allocated resources for R%d - P%d : ", j + 1, i);
            scanf("%d", &allocation[i][j]);
            sum_alloc[j] += allocation[i][j];
        }
        for (int j = 0; j < r; j++){
            printf("Maximum resources for R%d - P%d : ", j + 1, i);
            scanf("%d", &max[i][j]);
        }
        finish[i] = 0;
    }
   
    for (int i = 0; i < p; i++){
        for (int j = 0; j < r; j++){
        need[i][j] = max[i][j] - allocation[i][j];
        available[j] = overall[j] - sum_alloc[j];
        }
    }
   
    int ind = 0;
    for (int k = 0; k < p; k++) {
        for (int i = 0; i < p; i++) {
            if (finish[i] == 0) {
                int flag = 0;
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > available[j]){
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    ans[ind++] = i;
                    for (int y = 0; y < r; y++)
                        available[y] += allocation[i][y];
                    finish[i] = 1;
                }
            }
        }
    }
 
    int flag = 1;
     
    for(int i = 0; i < p; i++){
        if(finish[i] == 0) {
            flag = 0;
         printf("Deadlock cannot be avoided");
         break;
        }
    }
   
    if(flag == 1){
        printf("Solution");
        for (int i = 0; i < p - 1; i++)
            printf(" P%d ->", ans[i]);
            printf(" P%d", ans[p - 1]);
    }
   
    return (0);

}