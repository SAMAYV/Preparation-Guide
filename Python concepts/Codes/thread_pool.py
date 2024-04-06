import concurrent.futures
 
def worker():
    print("Worker thread running")
 
pool = concurrent.futures.ThreadPoolExecutor(max_workers=2)
 
pool.submit(worker)
pool.submit(worker)
 
pool.shutdown(wait=True)
 
print("Main thread continuing to run")