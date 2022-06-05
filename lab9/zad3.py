import multiprocessing as mp
# print("Number of processors: ", mp.cpu_count())


def howmany_within_range(row, minimum, maximum):
    """Returns how many numbers lie within `maximum` and `minimum` in a given `row`"""
    count = 0
    for n in row:
        if minimum <= n <= maximum:
            count = count + 1
    return count

results = []

def collect_result(result):
    global results
    results.append(result)

if __name__ == "__main__":
    pool = mp.Pool(mp.cpu_count())
    data = [
    [1, 5, 7, 3, 7, 8, 10, 22, 0],
    [1, 5, 7, 13, 7, 5, 10, 22, 0]
    ]
    mapped_data = []
    for row in data:
        mapped_data.append((row, 6, 7))
        # mapped_data.append(6)
        # mapped_data.append(7)

    pool.map_async(howmany_within_range, mapped_data, chunksize=1, callback=collect_result)
    result_objects = pool.map_async(howmany_within_range, data, chunksize=3, callback=collect_result)
    results = [r.get()[1] for r in result_objects]


    pool.close()
    pool.join()
    print(results)
