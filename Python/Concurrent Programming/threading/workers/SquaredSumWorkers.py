import threading


class SquaredSumWorker(threading.Thread):
    def __init__(self, n, **kwargs):
        super().__init__(**kwargs)
        self._n = n
        # Important to start execution in constructor
        # daemon is used should be set before the start
        self.start()

    def _calculate_sum_of_squares(self):
        sum_squares = 0
        for i in range(self._n):
            sum_squares += i ** 2

        print(sum_squares)

    def run(self):
        self._calculate_sum_of_squares()
