#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    
    int ch;
    printf("1)ls\n2)cp\n3)cat\n4)grep\n5)ps\n6)stat\n");
    printf("Enter the choice (1/2/3/4/5/6) : ");
    scanf("%d", &ch);
    char str1[50], str2[50], str3[50];

    switch(ch){

        case 1:
            printf("Enter the name of the directory : ");
            scanf("%s", str1);
            execl("/bin/ls", "ls", str1, NULL);
        break;

        case 2:
            printf("Enter the source filename : ");
            scanf("%s", str1);
            printf("Enter the destination filename : ");
            scanf("%s", str2);
            execl("/bin/cp", "cp", str1, str2, NULL);
        break;

        case 3:
            printf("Enter the first filename : ");
            scanf("%s", str1);
            printf("Enter the second filename : ");
            scanf("%s", str2);
            printf("Enter the third filename : ");
            scanf("%s", str3);
            execl("/bin/cat", "cat", str1, str2, str3, NULL);
        break;

        case 4:
            printf("Enter the pattern to search : ");
            scanf("%s", str1);
            printf("Enter the filename : ");
            scanf("%s", str2);
            execlp("grep", "grep", str1, str2, NULL);
        break;

        case 5:
            execlp("ps", "ps", NULL);
        break;
        
        case 6:
            printf("Enter the filename : ");
            scanf("%s", str1);
            execlp("stat", "stat", str1, NULL);
        break;
    }
    return 0;
}