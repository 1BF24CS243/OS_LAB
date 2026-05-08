#include <stdio.h>
#include <stdbool.h>

int main() {

    int n, m;
    int alloc[20][20], request[20][20];
    int available[20], work[20];
    bool finish[20] = {false};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("\nEnter Available Vector:\n");

    for (int j = 0; j < m; j++) {
        scanf("%d", &available[j]);
        work[j] = available[j];
    }

    int count = 0;

    while (count < n) {

        bool found = false;

        for (int i = 0; i < n; i++) {

            if (!finish[i]) {

                int j;

                for (j = 0; j < m; j++) {

                    if (request[i][j] > work[j])
                        break;
                }

                if (j == m) {

                    for (int k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }

                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found)
            break;
    }

    bool deadlock = false;

    printf("\nDeadlocked Processes: ");

    for (int i = 0; i < n; i++) {

        if (!finish[i]) {
            printf("P%d ", i);
            deadlock = true;
        }
    }

    if (!deadlock)
        printf("None");

    return 0;
}

