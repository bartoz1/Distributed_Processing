import random
import timeit
import time


def is_name_index(name: str, index: int):
    number = len(name) % 10
    tmp = index
    while tmp != 0:
        if tmp % 10 == number:
            return True
        tmp = tmp // 10
    return False


start = time.perf_counter_ns()

with open('test.txt', 'w') as file:
    file.write('Bartosz 184477')
print(f'write time: {time.perf_counter_ns() - start} ns')

start = time.perf_counter_ns()
with open('test.txt', 'r') as file:
    temp = file.read()
    temp = temp.split(' ')
    print(temp)
print(f'read  time: {time.perf_counter_ns() - start} ns')


SETUP_CODE = '''
from __main__ import is_name_index
'''

TEST_CODE = '''
with open('test.txt', 'r') as file:
    temp = file.read().split(' ')
    is_name_index(temp[0], int(temp[1]))
'''

# timeit.repeat statement
times = timeit.timeit(setup=SETUP_CODE,
                      stmt=TEST_CODE,
                      number=10000)

print(f'Pomiar wydajności funkcji is_name_index: {times}')

