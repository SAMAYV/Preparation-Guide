from abc import ABC, abstractmethod

class FileSystem(ABC):
    name: str
    @abstractmethod
    def ls(self, path):
        pass

class File(FileSystem):
    def __init__(self, name):
        self.name = name

    def ls(self, path):
        print(f"File: {path}")

class Directory(FileSystem):
    def __init__(self, name):
        self.name = name
        self.fileSystems : list[FileSystem] = []

    def add(self, fs):
        self.fileSystems.append(fs)

    def remove(self, fs):
        self.fileSystems.remove(fs)

    def ls(self, path=None):
        if path == None:
            path = self.name
        
        print(f"Listing files in directory: {path}")
        for fs in self.fileSystems:
            fs.ls(path + "/" + fs.name)

class Application:
    def main(self):
        root = Directory("root")
        root.add(File("file1"))
        root.add(File("file2"))
        dir1 = Directory("dir1")
        dir1.add(File("file3"))
        dir1.add(File("file4"))
        root.add(dir1)
        root.ls()

if __name__ == "__main__":
    app = Application()
    app.main()
