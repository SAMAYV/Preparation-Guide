from abc import ABC, abstractmethod

class Book:
    def __init__(self, name):
        self.name = name

    def __str__(self):
        return f"Book: {self.name}"

class Iterator(ABC):
    @abstractmethod
    def hasNext(self) -> bool:
        pass
    @abstractmethod
    def next(self) -> object:
        pass

class BookIterator(Iterator):
    def __init__(self, books : list[Book]):
        self.books = books
        self.index = 0
    
    def hasNext(self) -> bool:
        return self.index < len(self.books)
    
    def next(self) -> object:
        book = self.books[self.index]
        self.index += 1
        return book

class Aggregate(ABC):
    @abstractmethod
    def createIterator(self) -> Iterator:
        pass

# Concrete Aggregate e.g. ArrayList, LinkedList, etc.
class BookLibrary(Aggregate):
    def __init__(self, books: list[Book]):
        self.books = books
    
    def addBook(self, book):
        self.books.append(book)
    
    # Factory method for iterator
    def createIterator(self) -> Iterator:
        return BookIterator(self.books)


if __name__ == "__main__":
    library = BookLibrary([Book("Book 0"), Book("Book 1")])
    library.addBook(Book("Book 2"))
    library.addBook(Book("Book 3"))

    iterator = library.createIterator()
    while iterator.hasNext():
        book = iterator.next()
        print(f"Book: {book}")
