import cProfile
def quicksort(numbers, low, high):
    if low < high:
        pivot = partition(numbers, low, high)
        quicksort(numbers, low, pivot - 1)
        quicksort(numbers, pivot + 1, high)

def partition(numbers, low, high):
    pivot = numbers[high]
    i = low - 1
    for j in range(low, high):
        if numbers[j] <= pivot:
            i = i + 1
            numbers[i], numbers[j] = numbers[j], numbers[i]
        numbers[i + 1], numbers[high] = numbers[high], numbers[i + 1]
    return i + 1

cProfile.run('quicksort([10, 80, 30, 90, 40], 0, 4)')

with cProfile.Profile() as pr:
    quicksort([10, 80, 30, 90, 40], 0, 4)
    pr.print_stats()

# The issue with cProfile is that it is too chatty for a production grade code as it samples to base minimum call possible which populates the overall report with base modules or language code where we don’t have control. 
# Also to visualize such hugs stats file you will have to use a tool like snakeviz to visualize the data.