#include <stdio.h>
#include <limits.h>

int main() {

    int buffer_size = 3;
    int buffer[buffer_size];
    int len_string = 7;
    int item;
    int page_hit = 0;
    int page_fault = 0;
    int pointer = 0;
    int string[len_string];
    int dist[buffer_size];

    for (int j = 0; j < buffer_size; j++) {
        buffer[j] = -1;
    }

    printf("Enter the reference string (7 pages): ");
    for (int i = 0; i < len_string; i++) {
        scanf("%d", &item);
        string[i] = item;
    }

    for (int i = 0; i < len_string; i++) {
        item = string[i];

        int flag = 0; 
        for (int j = 0; j < buffer_size; j++) {
            if (buffer[j] == item) {
                page_hit += 1;
                flag = 1;
                break;
            }
        }

        if (flag == 0) { 
            page_fault += 1;

            if (pointer < buffer_size) {
                buffer[pointer++] = item;
            } else {
                
                for (int j = 0; j < buffer_size; j++) {
                    dist[j] = INT_MAX; 
                    for (int k = i + 1; k < len_string; k++) {
                        if (buffer[j] == string[k]) {
                            dist[j] = k - i; 
                            break;
                        }
                    }
                }

                int max_dist_index = 0;
                for (int j = 1; j < buffer_size; j++) {
                    if (dist[j] > dist[max_dist_index]) {
                        max_dist_index = j;
                    }
                }
                buffer[max_dist_index] = item;
            }
        }
    }

    printf("Page Hits: %d\n", page_hit);
    printf("Page Faults: %d\n", page_fault);

    return 0;
}