import copy
import threading
import time

ctr = 0
lock = threading.Lock()

def incrementer():
    global ctr
    # lock.acquire()
    with lock:
        temp = copy.deepcopy(ctr)
        time.sleep(0.001)
        ctr = temp + 1
    # lock.release()


def main():
    threads = []
    for _ in range(4):
        t = threading.Thread(target=incrementer)
        t.start()
        threads.append(t)

    for thread in threads:
        thread.join()

    print(ctr)


if __name__ == '__main__':
    main()
