from abc import ABC

class NoteHandler(ABC):
    nextHandler = None
    def __init__(self, nextHandler=None):
        self.nextHandler : NoteHandler | None = nextHandler
    
    def handleRequest(self, request):
        if request == 0:
            print("No more notes to dispense")
            return
        if self.nextHandler != None:
            self.nextHandler.handleRequest(request)
        else:
            print("No more handlers for request:", request)

class TwoThousandHandler(NoteHandler):
    def handleRequest(self, request):
        if request >= 2000:
            print("Dispensing 2000 notes:", request // 2000)
        super().handleRequest(request % 2000)

class FiveHundredHandler(NoteHandler):
    def handleRequest(self, request):
        if request >= 500:
            print("Dispensing 500 notes:", request // 500)
        super().handleRequest(request % 500)

class HundredHandler(NoteHandler):
    def handleRequest(self, request):
        if request >= 100:
            print("Dispensing 100 notes:", request // 100)
        super().handleRequest(request % 100)

class Application:
    def main(self):
        handler = TwoThousandHandler(FiveHundredHandler(HundredHandler()))
        handler.handleRequest(6700)

if __name__ == "__main__":
    app = Application()
    app.main()