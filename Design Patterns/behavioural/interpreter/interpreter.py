from abc import ABC, abstractmethod

# Context to interpret the expression
class Context:
    def __init__(self):
        self.variables = {}
    
    def get(self, variable) -> int:
        return self.variables[variable]
    
    def set(self, variable, value):
        self.variables[variable] = value


class AbstractExpression(ABC):
    @abstractmethod
    def interpret(self, context: Context) -> int:
        pass


class NumberTerminalExpression(AbstractExpression):
    def __init__(self, number):
        self.number = number
    
    def interpret(self, context: Context):
        return context.get(self.number)


class AddNonTerminalExpression(AbstractExpression):
    def __init__(self, left: AbstractExpression, right: AbstractExpression):
        self.left = left
        self.right = right
    
    def interpret(self, context: Context):
        return self.left.interpret(context) + self.right.interpret(context)


class SubtractNonTerminalExpression(AbstractExpression):
    def __init__(self, left: AbstractExpression, right: AbstractExpression):
        self.left = left
        self.right = right
    
    def interpret(self, context: Context):
        return self.left.interpret(context) - self.right.interpret(context)


class Application:
    def main(self):
        context = Context()
        context.set("a", 10)
        context.set("b", 5)
        context.set("c", 2)
        expression = SubtractNonTerminalExpression(
            AddNonTerminalExpression(
                NumberTerminalExpression("a"),
                NumberTerminalExpression("b")
            ),
            NumberTerminalExpression("c")
        )
        result = expression.interpret(context)
        print(f"Result: {result}")

        # Interpret in different contexts
        context.set("a", 20)
        context.set("b", 10)
        context.set("c", 5)
        result = expression.interpret(context)
        print(f"Result: {result}")


if __name__ == "__main__":
    app = Application()
    app.main()
