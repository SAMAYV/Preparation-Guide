import time
from Concurrency.threading.workers.WikiWorker import WikiWorker
from Concurrency.threading.workers.YahooFinanceWorkers import YahooFinanceScheduler
from multiprocessing import Queue

# def main():
#     from workers.SleepyWorkers import SleepyWorker
#     from workers.SquaredSumWorkers import SquaredSumWorker
#     start_time = time.time()
#
#     current_workers = []
#
#     for i in range(5):
#         maximum_value = (i+1) * 1_000_000
#         squared_sum_worker = SquaredSumWorker(maximum_value)
#         current_workers.append(squared_sum_worker)
#
#     for worker in current_workers:
#         # Blocks parents execution till threads are done.
#         worker.join()
#
#     print(f"Calculating sum of squares took: {time.time() - start_time:.2f}")
#
#     start_time = time.time()
#
#     current_workers = []
#
#     for seconds in range(1, 6):
#         sleepy_worker = SleepyWorker(seconds)
#         current_workers.append(sleepy_worker)
#
#     for worker in current_workers:
#         worker.join()
#
#     print(f"Sleeping took: {time.time() - start_time:.2f}")


def main():
    symbol_queue = Queue()

    start_time = time.time()

    wikiWorker = WikiWorker()
    yahoo_finance_scheduler_threads = []
    number_of_threads = 100

    for _ in range(number_of_threads):
        yahoo_finance_scheduler = YahooFinanceScheduler(symbol_queue)
        yahoo_finance_scheduler_threads.append(yahoo_finance_scheduler)

    for symbol in wikiWorker.get_sp_500_companies():
        symbol_queue.put(symbol)

    for _ in range(number_of_threads):
        symbol_queue.put('DONE')

    for yahoo_finance_scheduler_thread in yahoo_finance_scheduler_threads:
        yahoo_finance_scheduler_thread.join()

    print(f"It took {time.time() - start_time:.2f} seconds to fetch the prices of all companies.")


if __name__ == "__main__":
    main()
