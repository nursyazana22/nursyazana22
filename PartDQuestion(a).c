#include <stdio.h>
int main()
{
def fibonacci(n):
 
  if n == 0:
    return 0
  elif n == 1:
    return 1 
  else:
    return fibonacci(n - 1) + fibonacci(n - 2)

def main():
  for i in range(1, 10001):
    print(fibonacci(i))

if __name__ == "__main__":
  main()
}

