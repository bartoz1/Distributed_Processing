import threading
import asyncio
import multiprocessing
import time


start = time.perf_counter_ns()

with open('test.txt', 'w') as file:
    file.write('Bartosz 184477')
print(f'write time: {time.perf_counter_ns() - start} ns')

start = time.perf_counter_ns()
with open('test.txt', 'r') as file:
    temp = file.read()
print(f'read  time: {time.perf_counter_ns() - start} ns')

