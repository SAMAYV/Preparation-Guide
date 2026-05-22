from abc import ABC, abstractmethod

class PaymentFlow(ABC):
    @abstractmethod
    def validateRequest(self, request):
        pass
    @abstractmethod
    def calculateFees(self, request):
        pass
    @abstractmethod
    def debitAmount(self, request):
        pass
    @abstractmethod
    def creditAmount(self, request):
        pass
    
    def processPayment(self, request):
        self.validateRequest(request)
        self.calculateFees(request)
        self.debitAmount(request)
        self.creditAmount(request)

class PayToFriendFlow(PaymentFlow):
    def validateRequest(self, request):
        print("Validating request for Pay to Friend")
    
    def calculateFees(self, request):
        print("Calculating fees for Pay to Friend")
    
    def debitAmount(self, request):
        print("Debiting amount for Pay to Friend")
    
    def creditAmount(self, request):
        print("Crediting amount for Pay to Friend")

class PayToMerchantFlow(PaymentFlow):
    def validateRequest(self, request):
        print("Validating request for Pay to Merchant")
    
    def calculateFees(self, request):
        print("Calculating fees for Pay to Merchant")
    
    def debitAmount(self, request):
        print("Debiting amount for Pay to Merchant")
    
    def creditAmount(self, request):
        print("Crediting amount for Pay to Merchant")

class PaymentFlowFactory:
    def createPaymentFlow(self, flowType) -> PaymentFlow:
        if flowType == "PayToFriend":
            return PayToFriendFlow()
        elif flowType == "PayToMerchant":
            return PayToMerchantFlow()
        else:
            raise Exception("Invalid flow type")

class Application:
    def main(self):
        factory = PaymentFlowFactory()
        flow = factory.createPaymentFlow("PayToFriend")
        flow.processPayment("request")

if __name__ == "__main__":
    app = Application()
    app.main()
