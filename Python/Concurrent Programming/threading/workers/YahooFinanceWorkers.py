import threading
import requests
from lxml import html
import time
import random


class YahooFinanceScheduler(threading.Thread):
    def __init__(self, input_queue, **kwargs):
        super().__init__(**kwargs)
        self._input_queue = input_queue
        self.start()

    def run(self):
        while True:
            # Below line is an atomic operations, Queue from multiprocessing is thread safe
            val = self._input_queue.get()
            if val == 'DONE':
                break
            else:
                yahooFinanceWorker = YahooFinanceWorker(symbol=val)
                price = yahooFinanceWorker.get_price()
                print(price)
                time.sleep(random.random())


class YahooFinanceWorker():
    x_path = '//*[@id="quote-header-info"]/div[3]/div[1]/div[1]/fin-streamer[1]'

    def __init__(self, symbol, *args, **kwargs):
        self._symbol = symbol
        base_url = 'https://finance.yahoo.com/quote/'
        self._url = base_url + self._symbol

    def get_price(self):
        response = requests.get(self._url)
        if response.status_code != 200:
            print(f"Couldn't fetch price for {self._symbol}")
            return
        else:
            try:
                page_contents = html.fromstring(response.text)
                price = float(page_contents.xpath(self.x_path)[0].text.replace(",", ""))
                return price
            except Exception as e:
                print("Parsing failed with the following error:", e)
                return

    def run(self):
        self.get_price()
