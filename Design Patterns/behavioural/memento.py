from abc import ABC, abstractmethod

# Memento is the one who holds the state
class Memento():
    def __init__(self, state):
        self.state = state
    
    def getState(self):
        return self.state
    
    def setState(self, state):
        self.state = state


# Originator is the one who creates the snapshot and restores from it
class Originator():
    def __init__(self, state):
        print(f"Originator created. Initial state: {state}")
        self.state = state
    
    def getState(self):
        return self.state
    
    def setState(self, state):
        print(f"Originator setting state. New state: {state}")
        self.state = state
    
    def save(self):
        return Memento(self.state)
    
    def restore(self, memento: Memento):
        self.state = memento.getState()


# CareTaker is the one who saves the snapshot and decides when to rollback
class CareTaker():
    def __init__(self):
        self.mementos = []
    
    def addMemento(self, memento: Memento):
        print(f"Adding memento to CareTaker. Snapshot taken: {memento.getState()}")
        self.mementos.append(memento)

    def undo(self):
        if len(self.mementos) > 0:
            return self.mementos.pop()
        else:
            return None

class Application:
    def main(self):
        caretaker = CareTaker()
        state = {"balance": 1000, "used": 500}
        originator = Originator(state)
        # Taking snapshot
        caretaker.addMemento(originator.save())
        # Modifying state
        originator.setState({"balance": 1000, "used": 600})
        # Taking snapshot
        caretaker.addMemento(originator.save())
        # Modifying state
        originator.setState({"balance": 1000, "used": 700})
        # Rolling back to last snapshot
        originator.restore(caretaker.undo())
        print(f"State after rolling back to last snapshot: {originator.getState()}")


if __name__ == "__main__":
    app = Application()
    app.main()
