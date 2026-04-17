class MetaEnforceClassRules(type):
    def __new__(cls, name, bases, namespace):
        if "run" not in namespace:
            raise TypeError("Must define run()")
        return super().__new__(cls, name, bases, namespace)

class MetaSingletonPattern(type):
    _instance = None
    def __call__(cls, *args, **kwargs):
        if cls._instance is None:
            cls._instance = super().__call__(*args, **kwargs)
        return cls._instance

class Meta(type):
    def __new__(cls, name, bases, namespace):
        print(f"[Meta __new__] Creating class: {name}")
        # Modify class: inject a new attribute
        namespace['added_by_meta'] = "hello"
        return super().__new__(cls, name, bases, namespace)

    def __call__(cls, *args, **kwargs):
        print(f"[Meta __call__] Creating instance of: {cls.__name__}")
        # Control instantiation (e.g., logging, singleton, validation)
        obj = super().__call__(*args, **kwargs)
        print(f"[Meta __call__] Instance created: {obj}")
        return obj

class MyClass(metaclass=Meta):
    def __init__(self, x):
        print(f"MyClass __init__ with x={x}")
        self.x = x
