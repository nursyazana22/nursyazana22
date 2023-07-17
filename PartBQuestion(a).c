import random

def get_random_number():
  return random.randint(50000, 80000)

def main():
  number = get_random_number()
  print("Passing random number:", number)

if __name__ == "__main__":
  main()
