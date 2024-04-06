import time
from multiprocessing import Pool, cpu_count
import threading

def check_val_in_list(x, i, number_of_processes, queue):
    max_number_to_check = 10**8
    lower = int(i * max_number_to_check / number_of_processes)
    upper = int((i + 1) * max_number_to_check / number_of_processes)
    number_of_hits = 0
    for i in range(lower, upper):
        if i in x:
            number_of_hits += 1
    queue.put((lower, upper, number_of_hits))


def power(x, y):
    return x**y


def main():
    num_processes = max(1, cpu_count() - 1)
    lis = [(1, 2), (2, 8), (3, 1)]
    start_time = time.time()

    pool = Pool(num_processes)

    with pool as mp_pool:
        result = mp_pool.starmap(power, lis)

    print(result)

    print("execution time:", time.time() - start_time)


if __name__ == "__main__":
    main()
