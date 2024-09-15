#include <stdio.h>

int main() {
  char operator;
  double num1, num2, result;

  // Prompt user to enter an operator
  printf("Enter an operator (+, -, *, /): ");
  scanf(" %c", &operator);

  // Prompt user to enter two numbers
  printf("Enter two numbers: ");
  scanf("%lf %lf", &num1, &num2);

  // Perform the calculation based on the operator
  switch (operator) {
  case '+':
    result = num1 + num2;
    printf("%.2lf + %.2lf = %.2lf\n", num1, num2, result);
    break;
  case '-':
    result = num1 - num2;
    printf("%.2lf - %.2lf = %.2lf\n", num1, num2, result);
    break;
  case '*':
    result = num1 * num2;
    printf("%.2lf * %.2lf = %.2lf\n", num1, num2, result);
    break;
  case '/':
    if (num2 != 0) {
      result = num1 / num2;
      printf("%.2lf / %.2lf = %.2lf\n", num1, num2, result);
    } else {
      printf("Error: Division by zero is not allowed.\n");
    }
    break;
  default:
    printf("Error: Invalid operator.\n");
    break;
  }

  return 0;
}
