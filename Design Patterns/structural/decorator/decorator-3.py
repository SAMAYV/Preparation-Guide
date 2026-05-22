from abc import ABC, abstractmethod

# Component
class BasePizza(ABC):
    @abstractmethod
    def getCost(self) -> int:
        pass

    @abstractmethod
    def getIngredients(self) -> str:
        pass

# Concrete component
class Margherita(BasePizza):
    def getCost(self):
        return 100
    
    def getIngredients(self):
        return "Tomato, Cheese"

# Concrete component
class Pepperoni(BasePizza):
    def getCost(self):
        return 150
    
    def getIngredients(self):
        return "Tomato, Cheese, Pepperoni"
    
# Decorator
class ToppingDecorator(BasePizza):
    def __init__(self, pizza: BasePizza):
        self.pizza = pizza
    
    def getCost(self):
        return self.pizza.getCost()
    
    def getIngredients(self):
        return self.pizza.getIngredients()

# Concrete decorators
class CheeseTopping(ToppingDecorator):
    def getCost(self):
        return self.pizza.getCost() + 20
    
    def getIngredients(self):
        return self.pizza.getIngredients() + ", ExtraCheese"

# Concrete decorators
class MushroomTopping(ToppingDecorator):
    def getCost(self):
        return self.pizza.getCost() + 30
    
    def getIngredients(self):
        return self.pizza.getIngredients() + ", Mushroom"
    

class Application:
    def main(self):
        pizza = Margherita()
        print(f"Cost: {pizza.getCost()}, Ingredients: {pizza.getIngredients()}")

        pizza = CheeseTopping(pizza)
        print(f"Cost: {pizza.getCost()}, Ingredients: {pizza.getIngredients()}\n")

        print("Dynamically adding mushroom topping\n")
        pizza = MushroomTopping(pizza)
        print(f"Cost: {pizza.getCost()}, Ingredients: {pizza.getIngredients()}")


if __name__ == "__main__":
    app = Application()
    app.main()
