#include <stdio.h>

int min_burst_time(int arr[], int n, int fin[]){

    int min_ele = 1000;
    int min_ind = 0;
    for (int i = 0; i < n; i++){
        if ((arr[i] < min_ele) && (fin[i] != 1)){
            min_ele = arr[i];
            min_ind = i;
        }
    }
    return min_ind;
}

int main(){

    int n;

    printf("Enter the number of processes : ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], rbt[n], st[n], ft[n], wt[n], rt[n], tat[n], fin[n];

    for (int i = 0; i < n; i++){
        pid[i] = i + 1;
        at[i] = 0;
        printf("Arrival time for process %d : ", i + 1);
        scanf("%d", &at[i]);
        printf("Burst time for process %d : ", i + 1);
        scanf("%d", &bt[i]);
        rbt[i] = bt[i];
    }

    int min_ind = min_burst_time(bt, n, fin);
    st[min_ind] = at[min_ind];
    ft[min_ind] = st[min_ind] + bt[min_ind];
    wt[min_ind] = st[min_ind] - at[min_ind];
    rt[min_ind] = wt[min_ind];
    tat[min_ind] = ft[min_ind] - at[min_ind];
    fin[min_ind] = 1;

    for (int i = 1; i < n; i++){
        int ind = min_burst_time(bt, n, fin);
        st[ind] = ft[min_ind];
        ft[ind] = st[ind] + bt[ind];
        wt[ind] = st[ind] - at[ind];
        rt[ind] = wt[ind];
        tat[ind] = ft[ind] - at[ind];
        fin[ind] = 1;
        min_ind = ind;
    }    

    float avg_w = 0, avg_tat = 0, avg_rt = 0;

    printf("Gantt chart\n");
    printf("PID\tAT\tBT\tST\tFT\tWT\tTAT\n");
    for (int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], st[i], ft[i], wt[i], tat[i]);
        avg_w += wt[i];
        avg_tat += tat[i];
        avg_rt += rt[i];
    }
    printf("Average waiting time : %.2f\n", avg_w / n);
    printf("Average turn around time : %.2f\n", avg_tat / n);
    printf("Average response time : %.2f", avg_rt / n);
}