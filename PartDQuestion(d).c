import threading

def fibonacci_series(n):
    fib_list = [0, 1]  
    while fib_list[-1] <= n:
        next_num = fib_list[-1] + fib_list[-2]
        fib_list.append(next_num)

    # Print the Fibonacci series
    for num in fib_list:
        print("Fibonacci:", num)

def square_numbers(n):
    for num in range(1, n+1):
        square = num ** 2
        print("Square:", square)

def cube_numbers(n):
    for num in range(1, n+1):
        cube = num ** 3
        print("Cube:", cube)


fibonacci_thread = threading.Thread(target=fibonacci_series, args=(10000,))
square_thread = threading.Thread(target=square_numbers, args=(10000,))
cube_thread = threading.Thread(target=cube_numbers, args=(10000,))

fibonacci_thread.start()
square_thread.start()
cube_thread.start()

fibonacci_thread.join()
square_thread.join()
cube_thread.join()

print("All Completed.")

