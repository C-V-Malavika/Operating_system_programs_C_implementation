%%writefile EX3.c

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void factorial();
void evenodd();
void addreal();
void revnum();
void armstrong();
void fibonacci();
void sortnumbers();
void palindrome();
void printFileLineCount();
void convertCase();

int main() {
    
    int ch;
    printf("Enter a choice:\n");
    printf("1: Factorial\n");
    printf("2: Fibonacci Series\n");
    printf("3: Sorting Numbers\n");
    printf("4: Armstrong Number\n");
    printf("5: Palindrome\n");
    printf("6: Even or Odd\n");
    printf("7: Print File Line Count\n");
    printf("8: Addition of Two Real Numbers\n");
    printf("9: Reverse Number\n");
    printf("10: Convert Case (Upper <-> Lower)\n");
    scanf("%d", &ch);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    else if (pid == 0){
      switch (ch) {
        case 1:
          factorial();
          break;
        case 2:
          fibonacci();
          break;
        case 3:
          sortnumbers();
          break;
        case 4:
          armstrong();
          break;
        case 5:
          palindrome();
          break;
        case 6:
          evenodd();
          break;
        case 7:
          printFileLineCount();
          break;
        case 8:
          addreal();
          break;
        case 9:
          revnum();
          break;
        case 10:
          convertCase();
          break;
        default:
          printf("Invalid choice!\n");
      }
    }
    
    else {
      int status;
      waitpid(pid, &status, 0);
    }
}


// Factorial of a number

void factorial() {

  int result = 1, num;
  printf("Enter the number to find factorial: ");
  scanf("%d", &num);
    while (num > 0) {
    result = result * num;
    num--;
  }
  printf("Factorial: %d\n", result);
}


// Fibonacci series

void fibonacci() {

  int n, t1 = 0, t2 = 1, nextTerm;
  printf("Enter the number of terms: ");
  scanf("%d", &n);
  printf("Fibonacci Series: ");
  for (int i = 1; i <= n; ++i) {
    printf("%d ", t1);
    nextTerm = t1 + t2;
    t1 = t2;
    t2 = nextTerm;
  }
  printf("\n");
}


// Sorting of n numbers

void sortnumbers() {

  int n;
  printf("Enter number of elements: ");
  scanf("%d", &n);
  int arr[n];
  printf("Enter the numbers:\n");
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (arr[i] > arr[j]) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }

  printf("Sorted numbers: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}


// Check for palindrome

void palindrome() {

  char str[100];
  printf("Enter a string: ");
  scanf("%s", str);
  int len = strlen(str);
  int flag = 1;

  for (int i = 0; i < len / 2; i++) {
    if (str[i] != str[len - i - 1]) {
      flag = 0;
    break;
    }
  }

  if (flag) {
    printf("%s is a palindrome.\n", str);
  }
  else {
    printf("%s is not a palindrome.\n", str);
  }
}


// Armstrong number

void armstrong() {

  int num;
  printf("Enter the number to find if it is an Armstrong number: ");
  scanf("%d", &num);
  int numc = num,
  val = 0, res = 0;

  while (num > 0) {
    val++;
    num = num / 10;
  }

  num = numc;

  while (num > 0) {
    int m = num % 10, v = 1;
    for (int i = 0; i < val; i++) {
      v = v * m;
    }
    res += v;
    num = num / 10;
  }
  if (res == numc) {
    printf("%d is an Armstrong number.\n", numc);
  }
  else {
    printf("%d is not an Armstrong number.\n", numc);
  }
}


// Even or odd number

void evenodd() {

  int num;
  printf("Enter the number to find even or odd: ");
  scanf("%d", &num);
  if (num % 2 == 0) {
    printf("Number is even\n");
  }
  else {
    printf("Number is odd\n");
  }
}


// Print file with line count

void printFileLineCount() {

  char filename[100];
  printf("Enter the filename: ");
  scanf("%s", filename);

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("File not found!\n");
    return;
  }

  int lineCount = 0; char ch;
  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      lineCount++;
    }
  }
  fclose(file);
  printf("Total number of lines: %d\n", lineCount);
}


// Addition of two real numbers

void addreal() {

  double num1, num2;
  printf("Enter the two numbers: ");
  scanf("%lf %lf", &num1, &num2);
  double result = num1 + num2;
  printf("The result is: %lf\n", result);
}


// Reverse a number

void revnum() {

  int num, rev = 0;
  printf("Enter the number: ");
  scanf("%d", &num);

  while (num > 0) {
    int mod = num % 10;
    rev = rev * 10 + mod;
    num = num / 10;
  }
  printf("The reversed number is: %d\n", rev);
}


// Convert string from upper to lower and vice versa

void convertCase(){

  char str[100];
  printf("Enter a string: ");
  scanf("%s", str);


  for (int i = 0; str[i] != '\0'; i++) {
    if (islower(str[i])) {
      str[i] = toupper(str[i]);
    }
    else if (isupper(str[i])) {
      str[i] = tolower(str[i]);
    }
  }

  printf("Converted string: %s\n", str);
}