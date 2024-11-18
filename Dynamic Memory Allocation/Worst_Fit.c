#include <stdio.h>

int worstfit(int arr[], int n){
    int maxi = arr[0];
    int max_ind = 0;
    for (int i = 1; i < n; i++){
        if (arr[i] > maxi){
            maxi = arr[i];
            max_ind = i;
        }
    }
    return max_ind;
}

int main(){
    
    int blocks[] = {100, 500, 200, 300, 600};
    int process[4][2] = {{0, 212}, {1, 417}, {2, 112}, {3, 426}};
    int ans[] = {100, 100, 100, 100};
    int finish[] = {0, 0, 0, 0};

    int b = 5;
    int p = 4;

    for (int i = 0; i < p; i++){
        if (finish[i] == 0){
            int ind = worstfit(blocks, b);
            if (blocks[ind] - process[i][1] > 0){
                blocks[ind] -= process[i][1];
                ans[i] = ind + 1;
                finish[i] = 1;
            }
        }
    }

    printf("Process\t\tBlock\n");
    for (int i = 0; i < p; i++){
        if (ans[i] != 100){
            printf("%d\t\t\t%d\n", i + 1, ans[i]);
        }
        else{
            printf("%d\t\t\t%s\n", i + 1, "Not Allocated");
        }
    }
    return 0;
}