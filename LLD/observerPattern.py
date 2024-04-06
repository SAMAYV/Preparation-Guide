"""
Observer Design Pattern: https://youtu.be/Ep9_Zcgst3U?si=QaVQVhlxRgnchxEh

Problem:

Principle:
    There are 2 type of entities observable and observer. If the state of the observable changes
    it's the duty of the observable to notify the observers that the state has been updated.
    It's a one-to-many relationship between observable and observer.

Skeleton (Pseudo-code):

    class Observable:
        observerList = []

        def add(self, observer):
            pass

        def remove(self, observer):
            pass

        def notify(self):
            pass

        def setData(self):
            pass


    class observableConcreteClass:

        def __init__(self, t):
            super().__init__()
            self.t = t

        def add(self, observer):
            # Register an observer to the observable.
            self.observerList.append(observer)

        def remove(self, observer):
            # De-register an observer from the observable
            self.observerList.remove(observer)

        def notify(self):
            for observer in self.observerList:
                 observer.update()

        def setData(self, t):
            self.t = t
            self.notify()


    class Observer:
        def update():
            pass


    class ObserverConcreteClass:

        def __init__(self, observableObject):
            super().__init__()
            self.observableObject = observableObject

        def update(self):
            print(f"Observable Updated to {self.observableObject.t}")


EXAMPLE:
    Weather station:
        Observable:
            Weather station
        Observer:
            TV Display
            Mobile Display


Use-case:
    Implement Notify me functionality on E-commerce websites. If a product is out of stock, notify the
    subscribed user once the product is back in stock.
"""
from abc import ABC, abstractmethod


class ObservableProduct(ABC):
    @abstractmethod
    def add_observer(self, observing_entity):
        pass

    @abstractmethod
    def remove_observer(self, observing_entity):
        pass

    @abstractmethod
    def _notify_observers(self):
        pass

    @abstractmethod
    def set_product_status(self, product_status):
        pass


class ConcreteObservableProduct(ObservableProduct):
    def __init__(self, product_name, in_stock: bool = False):
        super().__init__()
        self._product_name = product_name
        self._in_stock = in_stock
        self._observer_list = []

    def add_observer(self, observing_entity):
        self._observer_list.append(observing_entity)

    def remove_observer(self, observing_entity):
        self._observer_list.remove(observing_entity)

    def _notify_observers(self):
        for observer in self._observer_list:
            observer.update(self)

    def set_product_status(self, product_status: bool):
        self._in_stock = product_status
        if self._in_stock:
            self._notify_observers()

    @property
    def product_name(self):
        return self._product_name

    def __repr__(self):
        return f"{self._product_name}: {'in Stock' if self._in_stock else 'out of stock'}: {self._observer_list}"


class ObserverEntity(ABC):
    @abstractmethod
    def update(self, observable_entity):
        pass


class ConcreteObserverEntity(ObserverEntity):
    def __init__(self, observer_name):
        super().__init__()
        self._name = observer_name

    def update(self, observable_entity):
        print(f"{self._name} bought {observable_entity.product_name}.")

    def __repr__(self):
        return f"{self._name}"


def main():
    products = ['Iphone 11', 'Iphone 12', 'Iphone 13', 'Iphone 14', 'Iphone 15']

    customer_names = ['Arpan', 'Harsh', 'Shreyans', 'Aman', 'Vidit', 'Piyush']

    product_catalogue = {product: ConcreteObservableProduct(product)
                         for product in products}

    customers = {name: ConcreteObserverEntity(name) for name in customer_names}

    # Creating Preferences
    product_catalogue['Iphone 11'].add_observer(customers['Arpan'])
    product_catalogue['Iphone 12'].add_observer(customers['Harsh'])
    product_catalogue['Iphone 13'].add_observer(customers['Shreyans'])
    product_catalogue['Iphone 14'].add_observer(customers['Aman'])
    product_catalogue['Iphone 15'].add_observer(customers['Vidit'])
    product_catalogue['Iphone 12'].add_observer(customers['Shreyans'])
    product_catalogue['Iphone 13'].add_observer(customers['Piyush'])
    product_catalogue['Iphone 14'].add_observer(customers['Arpan'])
    product_catalogue['Iphone 15'].add_observer(customers['Harsh'])
    product_catalogue['Iphone 11'].add_observer(customers['Vidit'])
    product_catalogue['Iphone 15'].add_observer(customers['Aman'])
    product_catalogue['Iphone 12'].add_observer(customers['Piyush'])

    product_catalogue['Iphone 15'].set_product_status(True)
    product_catalogue['Iphone 13'].set_product_status(True)
    product_catalogue['Iphone 14'].set_product_status(True)
    product_catalogue['Iphone 12'].set_product_status(True)


if __name__ == "__main__":
    main()
