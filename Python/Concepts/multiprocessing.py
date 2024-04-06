import multiprocessing  
import time 
  
COUNT = 50000000
  
def countdown(n): 
    while n>0: 
        n -= 1
  
if __name__ == "__main__": 
    # creating processes  
    start = time.time() 
    p1 = multiprocessing.Process(target = countdown, args =(COUNT//2, )) 
    p2 = multiprocessing.Process(target = countdown, args =(COUNT//2, )) 
  
    # starting process 1  
    p1.start() 
    # starting process 2  
    p2.start()  
  
    # wait until process 1 is finished  
    p1.join()  
    # wait until process 2 is finished  
    p2.join() 
    end = time.time() 
    print('Time taken in seconds -', end - start) 