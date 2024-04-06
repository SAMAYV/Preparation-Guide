class AuthMethod(object):
    def __init__(self, level):
        self.level = level

    def __call__(self, fn):
        def __fn():
            print(f"Level: {self.level}")
            fn()
            print("Auth:", fn.__name__)
        return __fn

@AuthMethod("admin")
def process_document():
    print('Processing')

process_document()