from abc import ABC, abstractmethod

class WeightMachineAdaptee(ABC):
    def getWeightInPound(self, pounds) -> float:
        return pounds

class WeightMachineAdapterInterface(ABC):
    @abstractmethod
    def getWeightInKg(self, pounds) -> float:
        pass

class ConcreteWeightMachineAdapter(WeightMachineAdapterInterface):
    def __init__(self, adaptee: WeightMachineAdaptee):
        self.adaptee = adaptee
    
    def getWeightInKg(self, pounds):
        adapteeWeight = self.adaptee.getWeightInPound(pounds)
        return self.convertPoundToKg(adapteeWeight)
    
    def convertPoundToKg(self, kg):
        return kg * 2.20462
    
class Application:
    def main(self):
        adapter = ConcreteWeightMachineAdapter(WeightMachineAdaptee())
        pounds = 50
        print(f"Weight in Kg: {adapter.getWeightInKg(pounds)}")
