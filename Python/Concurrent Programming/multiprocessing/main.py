import time
import os
from multiprocessing import Pool, cpu_count

NUM_PROCESSES = 3  # Use 3 processes explicitly for 3 tasks

def power(x, y):
    print(f"Calculating {x}^{y} in Process ID: {os.getpid()}")
    # Add some work to make the task substantial enough
    time.sleep(0.5)  # Simulate some computation
    result = x**y
    print(f"Finished {x}^{y} = {result} in Process ID: {os.getpid()}")
    return result

def main():
    start_time = time.time()
    lis = [(1, 2), (2, 8), (3, 1)]

    print(f"Main process ID: {os.getpid()}")
    print(f"Number of processes in pool: {NUM_PROCESSES}")
    print(f"Number of CPUs: {cpu_count()}")
    print("-" * 50)

    # Create a pool of processes
    with Pool(processes=NUM_PROCESSES) as mp_pool:
        result = mp_pool.starmap(power, lis)

    print("-" * 50)
    print(f"Results: {result}")
    print(f"Execution time: {time.time() - start_time:.2f} seconds")


if __name__ == "__main__":
    main()
