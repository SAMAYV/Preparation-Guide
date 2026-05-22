from abc import ABC, abstractmethod

# NOTE: This is the Decorator design pattern, which is different from Python's @decorator syntax. The naming can be confusing 
# since Python decorators (with @) are a language feature for function/class modification, while this is an
# object composition pattern for adding behavior at runtime.

class DataSource(ABC):
    @abstractmethod
    def write_data(self, data: str) -> None:
        pass

    @abstractmethod
    def read_data(self) -> str:
        pass

class FileDataSource(DataSource):
    def __init__(self, filename: str):
        self.filename = filename

    def write_data(self, data: str) -> None:
        # Write to file
        pass

    def read_data(self) -> str:
        # Read from file
        return "data from file"

class EncryptionDecorator(DataSource):
    def __init__(self, source: DataSource):
        self._wrapped = source

    def write_data(self, data: str) -> None:
        encrypted = self._encrypt(data)
        self._wrapped.write_data(encrypted)  # Delegate to wrapped object

    def read_data(self) -> str:
        data = self._wrapped.read_data()
        return self._decrypt(data)

    def _encrypt(self, data: str) -> str:
        return f"encrypted:{data}"

    def _decrypt(self, data: str) -> str:
        return data.replace("encrypted:", "")

class CompressionDecorator(DataSource):
    def __init__(self, source: DataSource):
        self._wrapped = source

    def write_data(self, data: str) -> None:
        compressed = self._compress(data)
        self._wrapped.write_data(compressed)  # Delegate to wrapped object

    def read_data(self) -> str:
        data = self._wrapped.read_data()
        return self._decompress(data)

    def _compress(self, data: str) -> str:
        return f"compressed:{data}"

    def _decompress(self, data: str) -> str:
        return data.replace("compressed:", "")

# Usage
source = FileDataSource("data.txt")
source = CompressionDecorator(source)
source = EncryptionDecorator(source)
source.write_data("sensitive info")
# Data gets compressed, then encrypted, then written to file

