from abc import ABC, abstractmethod
from collections import defaultdict

# The base publisher class includes subscription management code and notification methods.
class EventManager:
    def __init__(self):
        self._listeners : dict[str, list[EventListener]] = defaultdict(list)
    
    def subscribe(self, event_type, listener):
        self._listeners[event_type].append(listener)
    
    def unsubscribe(self, event_type, listener):
        self._listeners[event_type].remove(listener)
    
    def notifySubscribers(self, event_type, data):
        for listener in self._listeners[event_type]:
            listener.update(data)


# The concrete publisher contains real business logic that's interesting for some subscribers. We could derive this class
# from the base publisher, but that isn't always possible in real life because the concrete publisher might already be a
# subclass. In this case, you can patch the subscription logic in with composition, as we did here.
class Editor:
    def __init__(self):
        self.subject = EventManager()
        self.file_path = None
    
    # Methods of business logic can notify subscribers about changes.
    def openFile(self, path):
        self.file = path
        self.subject.notifySubscribers("open", self.file_path)
    
    def saveFile(self):
        self.subject.notifySubscribers("save", self.file_path)


# Here's the subscriber / observer interface.
class EventListener(ABC):
    @abstractmethod
    def update(self, filename):
        pass

# Concrete subscribers react to updates issued by the publisher they are attached to.
class LoggingListener(EventListener):
    def __init__(self, log_filename, message):
        self.log = log_filename
        self.message = message
    
    def update(self, filename):
        log_message = self.message.replace('%s', filename)
        print(f"LOG [{self.log}]: {log_message}")


class EmailAlertsListener(EventListener):
    def __init__(self, email, message):
        self.email = email
        self.message = message
    
    def update(self, filename):
        email_message = self.message.replace('%s', filename)
        print(f"EMAIL to {self.email}: {email_message}")


# An application can configure publishers and subscribers at runtime.
class Application:
    def config(self):
        editor = Editor()
        
        logObserver = LoggingListener("/path/to/log.txt", "Someone has opened the file: %s")
        editor.subject.subscribe("open", logObserver)
        
        emailAlertObserver = EmailAlertsListener("admin@example.com", "Someone has changed the file: %s")
        editor.subject.subscribe("save", emailAlertObserver)
        
        return editor


if __name__ == "__main__":
    app = Application()
    editor = app.config()
    
    print("=== Opening file ===")
    editor.openFile("document.txt")
    
    print("\n=== Saving file ===")
    editor.saveFile()
