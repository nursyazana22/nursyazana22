import random

def get_random_number():
  """Returns a random number between 50,000 and 80,000."""
  return random.randint(50000, 80000)

def main():
  """Starts the server and passes one random number."""
  number = get_random_number()
  print("Passing random number:", number)

if __name__ == "__main__":
  main()
