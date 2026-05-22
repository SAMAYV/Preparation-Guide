from abc import ABC, abstractmethod

# The strategy interface declares operations common to all supported versions of some algorithm. The context uses this
# interface to call the algorithm defined by the concrete strategies.
class Strategy(ABC):
    @abstractmethod
    def execute(self, a, b):
        pass

# Concrete strategies implement the algorithm while following the base strategy interface. The interface makes them
# interchangeable in the context.
class ConcreteStrategyAdd(Strategy):
    def execute(self, a, b):
        return a + b

class ConcreteStrategySubtract(Strategy):
    def execute(self, a, b):
        return a - b

class ConcreteStrategyMultiply(Strategy):
    def execute(self, a, b):
        return a * b


# The context defines the interface of interest to clients.
class Context:
    # The context maintains a reference to one of the strategy objects. The context doesn't know the concrete class of a
    # strategy. It should work with all strategies via the strategy interface.
    def __init__(self, strategy: Strategy | None = None):
        self._strategy = strategy
    
    # strategy can be switched at runtime.
    def setStrategy(self, strategy: Strategy):
        self._strategy = strategy
    
    # The context delegates some work to the strategy object instead of implementing multiple versions of the algorithm on its own.
    def executeStrategy(self, a: int, b: int):
        if self._strategy is None:
            raise Exception("Strategy not set")
        return self._strategy.execute(a, b)


if __name__ == "__main__":
    # Example with hardcoded values
    print("=== Strategy Pattern Demo ===\n")
    
    context = Context()
    
    context.setStrategy(ConcreteStrategyAdd())
    print(f"10 + 5 = {context.executeStrategy(10, 5)}")
    
    context.setStrategy(ConcreteStrategySubtract())
    print(f"10 - 5 = {context.executeStrategy(10, 5)}")
    
    context.setStrategy(ConcreteStrategyMultiply())
    print(f"10 * 5 = {context.executeStrategy(10, 5)}")
    
    print("\n=== Interactive Mode ===\n")
