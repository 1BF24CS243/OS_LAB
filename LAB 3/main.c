#include <stdio.h>

int main() {
    int n, i, time = 0, remain;
    int tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], wt[n], tat[n];

    // Input AT and BT in same line
    for(i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for process %d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    remain = n;

    while(remain > 0) {
        int executed = 0;

        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0) {
                executed = 1;

                if(rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    wt[i] = time - at[i] - bt[i];
                    rt[i] = 0;
                    remain--;
                }
            }
        }

        if(executed == 0) {
            time++;
        }
    }

    for(i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");

    float total_wt = 0, total_tat = 0;

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
