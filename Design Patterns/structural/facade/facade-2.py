class InventoryService:
    def checkStock(self, productId, quantity):
        print(f"Checking stock for {productId} with quantity {quantity}")
        return True
    
class PaymentService:
    def processPayment(self, paymentMethod, amount):
        print(f"Processing payment of {amount} with card {paymentMethod}")
        return True
    
class ShippingService:
    def shipOrder(self, productId, quantity):
        print(f"Shipping {quantity} of {productId}")
        return True

class NotificationService:
    def sendConfirmation(self, productId, quantity):
        print(f"Sending order confirmation for {quantity} of {productId}")
        return True

# Any change in placing order process will not affect the client code as the client code is interacting with the facade.
# This is hiding the complexity of the system from the client.
class OrderFacade:
    def __init__(self):
        self.inventoryService = InventoryService()
        self.paymentService = PaymentService()
        self.shippingService = ShippingService()
        self.notificationService = NotificationService()

    def placeOrder(self, productId, quantity, paymentMethod):
        print(f"Placing order for {quantity} of product {productId}")
        
        if not self.inventoryService.checkStock(productId, quantity):
            print("Out of stock")
            return
        
        if not self.paymentService.processPayment(paymentMethod, 100):
            print("Payment failed")
            return
        
        if not self.shippingService.shipOrder(productId, quantity):
            print("Shipping failed")
            return
        
        if not self.notificationService.sendConfirmation(productId, quantity):
            print("Notification failed")
            return
        
        print("Order placed successfully")

class Application:
    def main(self):
        facade = OrderFacade()
        facade.placeOrder(1, 2, "credit_card")

if __name__ == "__main__":
    app = Application()
    app.main()
