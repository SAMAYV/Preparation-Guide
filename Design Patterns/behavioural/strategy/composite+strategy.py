from abc import ABC, abstractmethod
from enum import Enum

class Operator(Enum):
    ADD = 1
    SUB = 2
    MUL = 3
    DIV = 4

class Expression(ABC):
    @abstractmethod
    def evaluate(self):
        pass

class Number(Expression):
    def __init__(self, value):
        self.value = value

    def evaluate(self):
        return self.value
    
class Strategy(ABC):
    @abstractmethod
    def execute(self, a, b):
        pass

class AddStrategy(Strategy):
    def execute(self, a, b):
        return a + b
    
class SubStrategy(Strategy):
    def execute(self, a, b):
        return a - b

class MulStrategy(Strategy):
    def execute(self, a, b):
        return a * b

class DivStrategy(Strategy):
    def execute(self, a, b):
        return a / b
    
class StrategyFactory:
    _strategies = {
        Operator.ADD: AddStrategy(),
        Operator.SUB: SubStrategy(),
        Operator.MUL: MulStrategy(),
        Operator.DIV: DivStrategy()
    }
    @staticmethod
    def getStrategy(operator: Operator) -> Strategy:
        return StrategyFactory._strategies[operator]

class ArithmeticExpression(Expression):
    def __init__(self, left: Expression, right: Expression, operator: Operator):
        self.left = left
        self.right = right
        self.operator = operator

    def evaluate(self):
        strategy = StrategyFactory.getStrategy(self.operator)
        return strategy.execute(self.left.evaluate(), self.right.evaluate())

class Application:
    def main(self):
        expression = ArithmeticExpression(Number(10), Number(5), Operator.ADD)
        print(f"10 + 5 = {expression.evaluate()}")

        expression = ArithmeticExpression(Number(2), expression, Operator.MUL)
        print(f"2 * (10 + 5) = {expression.evaluate()}")

if __name__ == "__main__":
    app = Application()
    app.main()
