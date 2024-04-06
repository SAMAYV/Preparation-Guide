"""
Factory pattern generates objects based on parameters passed to the factory. That is if you have a
restaurant as factory, and you tell the restaurant to bring you Pizza it'll return a pizza object and so
on for various other dishes.

"""

from abc import ABC, abstractmethod


class Shape(ABC):
    @abstractmethod
    def draw(self):
        pass


class Square(Shape):
    def draw(self):
        print("Drawing a Square.")


class Circle(Shape):
    def draw(self):
        print("Drawing a Circle.")


class Triangle(Shape):
    def draw(self):
        print("Drawing a Triangle.")


class ShapeFactory:
    @staticmethod
    def get_shape(shape):
        shape_factory_map = {
            'square': Square,
            'circle': Circle,
            'triangle': Triangle
        }
        return shape_factory_map[shape.lower()]()


def main():
    circle = ShapeFactory().get_shape('CirCle')
    square = ShapeFactory().get_shape('Square')
    triangle = ShapeFactory().get_shape('triangle')

    circle.draw()
    triangle.draw()
    square.draw()


if __name__ == '__main__':
    main()
