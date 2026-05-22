from abc import ABC, abstractmethod

# The component interface defines operations that can be altered by decorators.
class DataSource(ABC):
    @abstractmethod
    def writeData(self, data):
        pass
    
    @abstractmethod
    def readData(self) -> str:
        pass


# Concrete components provide default implementations for the operations. There might be several variations of these classes in a program.
class FileDataSource(DataSource):
    def __init__(self, filename):
        self.filename = filename
    
    def writeData(self, data):
        # Write data to file.
        print(f"Writing data to {self.filename}: {data}")
    
    def readData(self):
        # Read data from file.
        print(f"Reading data from {self.filename}")
        return "File data"


# The base decorator class follows the same interface as the other components. The primary purpose of this class is to
# define the wrapping interface for all concrete decorators.
class DataSourceDecorator(DataSource):
    def __init__(self, source: DataSource):
        self.wrappee = source
    
    # The base decorator simply delegates all work to the wrapped component. Extra behaviors can be added in concrete decorators.
    def writeData(self, data):
        self.wrappee.writeData(data)
    
    # Concrete decorators may call the parent implementation of the operation instead of calling the wrapped object
    # directly. This approach simplifies extension of decorator classes.
    def readData(self):
        return self.wrappee.readData()


# Concrete decorators must call methods on the wrapped object, but may add something of their own to the result.
class EncryptionDecorator(DataSourceDecorator):
    def writeData(self, data):
        # 1. Encrypt passed data.
        encrypted_data = f"Encrypted({data})"
        print(f"Encrypting data...")
        # 2. Pass encrypted data to the wrappee's writeData method.
        self.wrappee.writeData(encrypted_data)
    
    def readData(self):
        # 1. Get data from the wrappee's readData method.
        data = self.wrappee.readData()
        # 2. Try to decrypt it if it's encrypted.
        print(f"Decrypting data...")
        # 3. Return the result.
        return data


# You can wrap objects in several layers of decorators.
class CompressionDecorator(DataSourceDecorator):
    def writeData(self, data):
        # 1. Compress passed data.
        compressed_data = f"Compressed({data})"
        print(f"Compressing data...")
        # 2. Pass compressed data to the wrappee's writeData method.
        self.wrappee.writeData(compressed_data)
    
    def readData(self):
        # 1. Get data from the wrappee's readData method.
        data = self.wrappee.readData()
        # 2. Try to decompress it if it's compressed.
        print(f"Decompressing data...")
        # 3. Return the result.
        return data


# Client code that uses an external data source.
# DataManager objects neither know / care about data storage. They work with a pre-configured data source received from the app configurator.
class DataManager:
    def __init__(self, source: DataSource):
        self.source = source
    
    def load(self):
        return self.source.readData()
    
    def save(self, data_records):
        self.source.writeData(data_records)


# The app can assemble different stacks of decorators at runtime, depending on the configuration or environment.
class ApplicationConfigurator:
    def configurationExample(self, enabled_encryption=True, enabled_compression=True):
        source: DataSource = FileDataSource("salary.dat")
        if enabled_encryption:
            source = EncryptionDecorator(source)
        if enabled_compression:
            source = CompressionDecorator(source)
        logger = DataManager(source)
        salary = logger.load()
        logger.save("John: $100000, Mary: $120000")


if __name__ == "__main__":
    print("\n\n=== Configured Usage ===\n")
    configurator = ApplicationConfigurator()
    configurator.configurationExample()
