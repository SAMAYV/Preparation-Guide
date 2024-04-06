"""
Principle:
    Whenever a sender sends a request and sender doesn't care who fulfills the request.
    Basically we will have a list of receivers and the senders request will traverse through the list
    of receivers and whichever receiver can fulfill the request will send the response.

Example:
    ATM:
        User requests a withdrawal of 2000Rs.
        The ATM has 3 types of handlers: 2000Rs Notes Handler, 500Rs Notes Handler, 100Rs Notes Handler
        The request will traverse through the Note Handlers and each handle the request to the best of
        their capabilities.

Applications:
    - ATM
    - Vending Machine
    - Logger
"""
from abc import ABC, abstractmethod


class LoggerInterface(ABC):
    # Logging Levels
    INFO = 1
    DEBUG = 2
    ERROR = 3

    def __init__(self, next_logger=None):
        self._next_logger = next_logger

    @abstractmethod
    def log(self, log_level, message):
        if self._next_logger:
            self._next_logger.log(log_level, message)


class ErrorLogger(LoggerInterface):
    def __init__(self, next_logger=None):
        super().__init__(next_logger)
        self._log_level = LoggerInterface.ERROR

    def log(self, log_level, message):
        if log_level == self._log_level:
            print(f"ERROR: {message}")
        else:
            super().log(log_level, message)


class InfoLogger(LoggerInterface):
    def __init__(self, next_logger=None):
        super().__init__(next_logger)
        self._log_level = LoggerInterface.INFO

    def log(self, log_level, message):
        if log_level == self._log_level:
            print(f"INFO: {message}")
        else:
            super().log(log_level, message)


class DebugLogger(LoggerInterface):
    def __init__(self, next_logger=None):
        super().__init__(next_logger)
        self._log_level = LoggerInterface.DEBUG

    def log(self, log_level, message):
        if log_level == self._log_level:
            print(f"DEBUG: {message}")
        else:
            super().log(log_level, message)


def main():
    Logger = InfoLogger(DebugLogger(ErrorLogger()))
    Logger.log(Logger.ERROR, "An Error Occurred.")
    Logger.log(Logger.DEBUG, "Debugging on line 75")
    Logger.log(Logger.INFO, "All three Loggers worked fine!")


if __name__ == "__main__":
    main()
