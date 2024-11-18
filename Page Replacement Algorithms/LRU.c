#include <stdio.h>

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

        int flag = 0; 
        for (int j = 0; j < buffer_size; j++) {
            if (buffer[j] == item) {
                page_hit += 1;
                flag = 1;
                
                dist[j] = i;
                break;
            }
        }

        if (flag == 0) { 
            page_fault += 1;

            if (pointer < buffer_size) { 
                buffer[pointer] = item;
                dist[pointer] = i; 
                pointer++;
            } else { 
                int min_dist_index = 0;
                for (int j = 1; j < buffer_size; j++) {
                    if (dist[j] < dist[min_dist_index]) {
                        min_dist_index = j;
                    }
                }
                buffer[min_dist_index] = item;
                dist[min_dist_index] = i; 
            }
        }
    }

    printf("Page Hits: %d\n", page_hit);
    printf("Page Faults: %d\n", page_fault);
    return 0;
}