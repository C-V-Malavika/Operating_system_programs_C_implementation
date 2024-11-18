#include <stdio.h>

int main(){

    int n;

    printf("Enter the number of processes : ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], rbt[n], st[n], ft[n], wt[n], rt[n], tat[n];

    for (int i = 0; i < n; i++){
        pid[i] = i + 1;
        printf("Arrival time for process %d : ", i + 1);
        scanf("%d", &at[i]);
        printf("Burst time for process %d : ", i + 1);
        scanf("%d", &bt[i]);
        rbt[i] = bt[i];
    }

    st[0] = at[0];
    ft[0] = st[0] + bt[0];

    for (int i = 1; i < n; i++){
        st[i] = ft[i - 1];
        ft[i] = st[i] + bt[i];
    }    
    for (int i = 0; i < n; i++){
        wt[i] = st[i] - at[i];
        rt[i] = wt[i];
        tat[i] = ft[i] - at[i];
        
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