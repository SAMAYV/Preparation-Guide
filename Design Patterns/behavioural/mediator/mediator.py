from abc import ABC, abstractmethod

class Colleague(ABC):
    @abstractmethod
    def placeBid(self, amount):
        pass
    @abstractmethod
    def receiveBidNotification(self, message):
        pass
    @abstractmethod
    def getName(self):
        pass

# Works like a subject
class AuctionMediator(ABC):
    @abstractmethod
    def addBidder(self, bidder: Colleague):
        pass
    @abstractmethod
    def placeBid(self, bidder: Colleague, amount):
        pass

# Works like a observer
class Bidder(Colleague):
    def __init__(self, name, mediator: AuctionMediator):
        self.name = name
        self.auctionMediator = mediator
        # Bidder added to the given auction
        self.auctionMediator.addBidder(self)
        self.bidAmount = 0
    
    def placeBid(self, amount):
        print("Bidder {} placing bid of {}".format(self.name, amount))
        self.auctionMediator.placeBid(self, amount)
    
    def receiveBidNotification(self, message):
        print(f"{self.name} received notification: {message}")

    def getName(self):
        return self.name


class Auction(AuctionMediator):
    def __init__(self):
        self.colleagues : list[Colleague] = []
        self.currentBid = 0

    def addBidder(self, bidder: Colleague):
        self.colleagues.append(bidder)
    
    # Notify all bidders except the current bidder
    def placeBid(self, bidder: Colleague, amount):
        for colleague in self.colleagues:
            if bidder.getName() != colleague.getName():
                colleague.receiveBidNotification(amount)


if __name__ == "__main__":
    auction = Auction()
    bidder1 = Bidder("Bidder 1", auction)
    bidder2 = Bidder("Bidder 2", auction)
    bidder3 = Bidder("Bidder 3", auction)
    bidder1.placeBid(100)
    bidder2.placeBid(200)
    bidder3.placeBid(300)
