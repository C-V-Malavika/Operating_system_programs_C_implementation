#include <stdio.h>

int main() {

    int buffer_size = 3;
    int buffer[buffer_size];
    int len_string = 7;
    int item;
    int page_hit = 0;
    int page_fault = 0;
    int pointer = 0;

    for (int j = 0; j < buffer_size; j++) {
        buffer[j] = -1;
    }

    printf("Enter the reference string (7 pages): ");
    for (int i = 0; i < len_string; i++) {
        scanf("%d", &item);

        int flag = 0; 
        for (int j = 0; j < buffer_size; j++) {
            if (buffer[j] == item) {
                page_hit += 1;
                flag = 1;
                break;
            }
        }

        if (flag == 0) { 
            buffer[pointer] = item;
            pointer = (pointer + 1) % buffer_size;
            page_fault += 1;
        }
    }

    printf("Page Hits = %d\n", page_hit);
    printf("Page Faults = %d\n", page_fault);
    return 0;
}