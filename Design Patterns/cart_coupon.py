from abc import ABC, abstractmethod

class Item(ABC):
    def __init__(self, name, price: float):
        self.name = name
        self.price = price

    def getPrice(self) -> float:
        return self.price


class ItemDecorator(Item):
    def __init__(self, item: Item):
        self.item = item

    def getPrice(self) -> float:
        return self.item.getPrice()


class PercentageCoupon(ItemDecorator):
    def __init__(self, item: Item, discountPercent):
        self.discountPercent = discountPercent
        super().__init__(item)
    
    def getPrice(self) -> float:
        return (self.item.getPrice() * self.discountPercent) / 100


class FixedAmountCoupon(ItemDecorator):
    def __init__(self, item: Item, discountValue):
        self.discountValue = discountValue
        super().__init__(item)
    
    def getPrice(self) -> float:
        return self.item.getPrice() - self.discountValue
    

class Cart:
    def __init__(self):
        self.itemQuantityMap: dict[Item, int] = {}

    def getCartValue(self):
        cost = 0
        for item, quantity in self.itemQuantityMap.items():
            cost += quantity * item.getPrice()
        return cost
    
    def addItem(self, item: Item):
        self.itemQuantityMap[item] += 1

    def applyPercentageCoupon(self, item: Item, percentDiscount):
        quantity = self.itemQuantityMap.get(item, 0)
        decoratedItem = PercentageCoupon(item, percentDiscount)
        del self.itemQuantityMap[item]
        self.itemQuantityMap[decoratedItem] = quantity
    

class CartDecorator(Cart):
    def __init__(self, cart: Cart):
        self.cart = cart
    
    def getCartValue(self):
        return self.cart.getCartValue()


class PercentCartCoupon(CartDecorator):
    def __init__(self, cart: Cart, discountPercent):
        self.discountPercent = discountPercent
        super().__init__(cart)
    
    def getCartValue(self):
        return (self.cart.getCartValue() * self.discountPercent) / 100


class GroceryApp():
    def __init__(self):
        self.cart = Cart()

    def applyCouponToCart(self, discountPercent):
        self.cart = PercentCartCoupon(self.cart, discountPercent)
