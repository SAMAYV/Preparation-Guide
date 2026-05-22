from abc import ABC, abstractmethod

class AlertObserver(ABC):
    @abstractmethod
    def update(self):
        pass

class StockSubject(ABC):
    def __init__(self):
        self.observers : list[AlertObserver] = []
        self.stock = 0
    
    def registerObserver(self, observer: AlertObserver):
        self.observers.append(observer)
    
    def unregisterObserver(self, observer: AlertObserver):
        self.observers.remove(observer)

    def notifyObservers(self):
        for observer in self.observers:
            observer.update()

    def getStock(self):
        return self.stock

    @abstractmethod
    def addStock(self, count):
        pass

    @abstractmethod
    def getName(self) -> str:
        pass

class IPhoneStock(StockSubject):
    def addStock(self, count):
        print(f"Adding stock for IPhone: {count}")
        if self.getStock() == 0:
            self.stock += count
            print(f"Stock added: {count}")
            self.notifyObservers()
        else:
            self.stock += count
    
    def getName(self):
        return "IPhone"

class PS5Stock(StockSubject):
    def addStock(self, count):
        print(f"Adding stock for PS5: {count}")
        if self.getStock() == 0:
            self.stock += count
            print(f"Stock added: {count}")
            self.notifyObservers()
        else:
            self.stock += count    
    
    def getName(self):
        return "PS5"


class EmailAlertObserver(AlertObserver):
    # The observer object holds a reference to the subject.
    def __init__(self, email, subject: StockSubject):
        self.email = email
        self.subject = subject
        self.subject.registerObserver(self)
    
    def update(self):
        self.sendMail()
        print(f"Email sent to {self.email}: {self.subject.getStock()} {self.subject.getName()} in stock")

    def sendMail(self):
        print(f"Sending mail to {self.email}")


class SMSAlertObserver(AlertObserver):
    def __init__(self, phone, subject: StockSubject):
        self.phone = phone
        self.subject = subject
        self.subject.registerObserver(self)

    def update(self):
        self.sendSMS()
        print(f"SMS sent to {self.phone}: {self.subject.getStock()} IPhones in stock")

    def sendSMS(self):
        print(f"Sending SMS to {self.phone}")


class Application:
    def main(self):
        iphoneSubject = IPhoneStock()
        ps5Subject = PS5Stock()

        emailObserverIPhone = EmailAlertObserver("test@test.com", iphoneSubject)
        smsObserverIPhone = SMSAlertObserver("1234567890", iphoneSubject)

        iphoneSubject.addStock(10)
        ps5Subject.addStock(5)


if __name__ == "__main__":
    app = Application()
    app.main()
