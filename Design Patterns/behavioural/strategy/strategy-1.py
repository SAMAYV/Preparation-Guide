from abc import ABC, abstractmethod

class PaymentStrategy(ABC):
    @abstractmethod
    def pay(self, amount: float) -> bool:
        pass

class CreditCardPayment(PaymentStrategy):
    def __init__(self, card_number: str):
        self.card_number = card_number

    def pay(self, amount: float) -> bool:
        # Credit card processing logic
        print(f"Paid {amount} with credit card")
        return True

class PayPalPayment(PaymentStrategy):
    def __init__(self, email: str):
        self.email = email

    def pay(self, amount: float) -> bool:
        # PayPal processing logic
        print(f"Paid {amount} with PayPal")
        return True

class ShoppingCart:
    def __init__(self, payment_strategy: PaymentStrategy):
        self.payment_strategy = payment_strategy

    def set_payment_strategy(self, strategy: PaymentStrategy) -> None:
        self.payment_strategy = strategy

    def checkout(self, amount: float) -> None:
        self.payment_strategy.pay(amount)

# Usage
cart = ShoppingCart(payment_strategy=CreditCardPayment("1234-5678"))

# Changing payment strategy at runtime
cart.set_payment_strategy(CreditCardPayment("1234-5678"))
cart.checkout(100.00)

cart.set_payment_strategy(PayPalPayment("user@example.com"))
cart.checkout(50.00)

