# Suppose, we have a set of jobs, and we are aware of every job’s deadline and its duration. 
# The execution of a job cannot be interrupted prior to its ending. It is required to create 
# such a schedule to accomplish the biggest number of jobs.

import heapq

def max_jobs(jobs):
    # jobs = [(duration, deadline)]
    jobs.sort(key=lambda x: x[1])

    total_time = 0
    max_heap = []

    for duration, deadline in jobs:
        total_time += duration
        heapq.heappush(max_heap, -duration)

        if total_time > deadline:
            longest = -heapq.heappop(max_heap)
            total_time -= longest

    return len(max_heap)