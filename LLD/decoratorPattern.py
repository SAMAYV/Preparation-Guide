"""
Decorator Design Pattern: https://youtu.be/w6a9MXUwcfY?si=1Rm3UB-J_TDet3Zz

Problem:
    Assume a case where there can be various types of object of a base object with various combination of
    features. If we implement each type of class for every type of object it's not scalable. It's better to
    implement decorators/wrappers for every customisation on the base class.

Example:
    Pizza, pizzas can be of various types, plain margherita, margherita with extra toppings of various kinds.
    We cant implement a pizza for every combination as number of combinations will blow out.
    What we can instead do is implement a basic margherita pizza and implement topping class for individual
    toppings and nest them together to for pizza with custom toppings.

"""
from abc import ABC, abstractmethod


class BasePizza(ABC):
    @abstractmethod
    def price(self):
        pass


class MargheritaPizza(BasePizza):
    def __init__(self):
        super().__init__()
        self._price = 100

    @property
    def price(self):
        return self._price


class CustomPizzaWithToppings(BasePizza):
    def __init__(self, base_pizza, price):
        super().__init__()
        self._base_pizza = base_pizza
        self._price = price

    @property
    def price(self):
        return self._base_pizza.price + self._price


class ExtraCheeseTopping(CustomPizzaWithToppings):
    def __init__(self, base_pizza):
        self._price = 20
        super().__init__(base_pizza, self._price)


class MushroomTopping(CustomPizzaWithToppings):
    def __init__(self, base_pizza):
        self._price = 30
        super().__init__(base_pizza, self._price)


class ChickenTopping(CustomPizzaWithToppings):
    def __init__(self, base_pizza):
        self._price = 80
        super().__init__(base_pizza, self._price)


class CornTopping(CustomPizzaWithToppings):
    def __init__(self, base_pizza):
        self._price = 15
        super().__init__(base_pizza, self._price)


class PepperoniTopping(CustomPizzaWithToppings):
    def __init__(self, base_pizza):
        self._price = 120
        super().__init__(base_pizza, self._price)


def main():
    classic_margherita = MargheritaPizza()
    double_cheese_margherita = ExtraCheeseTopping(MargheritaPizza())
    triple_cheese_margherita = ExtraCheeseTopping(ExtraCheeseTopping(MargheritaPizza()))
    margherita_with_corn_and_cheese = CornTopping(ExtraCheeseTopping(MargheritaPizza()))
    chicken_margherita = ChickenTopping(MargheritaPizza())
    monster_pizza = PepperoniTopping(ChickenTopping(CornTopping(MushroomTopping(ExtraCheeseTopping(MargheritaPizza())))))

    print('classic_margherita: ', classic_margherita.price)
    print('double_cheese_margherita: ', double_cheese_margherita.price)
    print('triple_cheese_margherita: ', triple_cheese_margherita.price)
    print('margherita_with_corn_and_cheese: ', margherita_with_corn_and_cheese.price)
    print('chicken_margherita: ', chicken_margherita.price)
    print('monster_pizza:', monster_pizza.price)


if __name__ == "__main__":
    main()
