from abc import ABC, abstractmethod

# Observer will observe the subject
class Observer(ABC):
    @abstractmethod
    def update(self, symbol: str, price: float) -> None:
        pass

# Subject is the one which is being observed
class Subject(ABC):
    @abstractmethod
    def attach(self, observer: Observer) -> None:
        pass

    @abstractmethod
    def detach(self, observer: Observer) -> None:
        pass

    @abstractmethod
    def notify_observers(self) -> None:
        pass

class Stock(Subject):
    def __init__(self, symbol: str):
        self._observers: list[Observer] = []
        self.symbol = symbol
        self.price = 0.0

    def attach(self, observer: Observer) -> None:
        self._observers.append(observer)

    def detach(self, observer: Observer) -> None:
        self._observers.remove(observer)

    def set_price(self, price: float) -> None:
        self.price = price
        self.notify_observers()  # Price changed, tell everyone

    def notify_observers(self) -> None:
        for observer in self._observers:
            observer.update(self.symbol, self.price)

class PriceDisplay(Observer):
    def update(self, symbol: str, price: float) -> None:
        print(f"Display updated: {symbol} = ${price}")

class PriceAlert(Observer):
    def __init__(self, threshold: float):
        self.threshold = threshold

    def update(self, symbol: str, price: float) -> None:
        if price > self.threshold:
            print(f"Alert! {symbol} exceeded ${self.threshold}")

# Usage
stock = Stock("AAPL")

display = PriceDisplay()
alert = PriceAlert(150.00)

stock.attach(display)
stock.attach(alert)

stock.set_price(145.00)  # Both observers get notified
stock.set_price(155.00)  # Both observers get notified

