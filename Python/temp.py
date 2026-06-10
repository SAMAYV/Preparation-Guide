a = "abc"
for i in a:
    print(chr(ord(i) - 97 + 65))
    
for i in "123":
    print(int(i))
    
numbers = [1, 2, 3, 4, 5, 6]
evens = list(filter(lambda x: x % 2 == 0, numbers))
print(evens)

numbers = [1, 2, 3, 4]
squared = list(map(lambda x: x**2, numbers))
print(squared)

students = [("Alice", 25), ("Bob", 20), ("Charlie", 23)]
# Sort by age (the second item in the tuple)
sorted_students = sorted(students, key=lambda student: student[1])
print(sorted_students)

# import sys
# data = sys.stdin.read()
# print(data.strip().split('\n'))

for line in sys.stdin:
    line = line.strip()
    if not line:
        break
    print("input", line)

import copy

original = [[1, 2], [3, 4]]
deep_copy = copy.deepcopy(original)

deep_copy[0][0] = 99
print(original[0][0])