from abc import ABC
from enum import Enum 

class LogLevel(Enum):
    INFO = 1
    DEBUG = 2
    ERROR = 3
    WARNING = 4

class LogProcessor(ABC):
    nextLogProcessor = None
    def __init__(self, nextLogProcessor=None):
        self.nextLogProcessor : LogProcessor | None = nextLogProcessor
    
    def log(self, type: Enum, message):
        if self.nextLogProcessor != None:
            self.nextLogProcessor.log(type, message)
        else:
            print(f"No more log processors for {type.name}: {message}")

class InfoLogProcessor(LogProcessor):
    def log(self, type, message):
        if type == LogLevel.INFO:
            print(f"INFO: {message}")
        else:
            super().log(type, message)

class DebugLogProcessor(LogProcessor):
    def log(self, type, message):
        if type == LogLevel.DEBUG:
            print(f"DEBUG: {message}")
        else:
            super().log(type, message)

class ErrorLogProcessor(LogProcessor):
    def log(self, type, message):
        if type == LogLevel.ERROR:
            print(f"ERROR: {message}")
        else:
            super().log(type, message)

class Application:
    def main(self):
        logProcessor = InfoLogProcessor(DebugLogProcessor(ErrorLogProcessor()))
        logProcessor.log(LogLevel.INFO, "Info message")
        logProcessor.log(LogLevel.DEBUG, "Debug message")
        logProcessor.log(LogLevel.ERROR, "Error message")
        logProcessor.log(LogLevel.WARNING, "Warning message")

if __name__ == "__main__":
    app = Application()
    app.main()
