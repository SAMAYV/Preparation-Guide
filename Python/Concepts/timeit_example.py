import timeit
setup = """
import random
numbers = [random.randint(0, 10000) for _ in range(1000)]
def bubble_sort(numbers):
    for i in range(len(numbers) - 1):
        for j in range(len(numbers) - i - 1):
            if numbers[j] > numbers[j + 1]:
                numbers[j], numbers[j + 1] = numbers[j + 1], numbers[j]
""" 
stmt = "bubble_sort(numbers)"
print(timeit.timeit(stmt, setup, number=100))

import timeit
setup = """
import random
""" 
stmt = """
numbers = [random.randint(0, 10000) for _ in range(1000)]
def bubble_sort(numbers):
    for i in range(len(numbers) - 1):
        for j in range(len(numbers) - i - 1):
            if numbers[j] > numbers[j + 1]:
                numbers[j], numbers[j + 1] = numbers[j + 1], numbers[j]
bubble_sort(numbers)
"""
print(timeit.repeat(setup=setup, stmt=stmt, repeat=3, number=10))