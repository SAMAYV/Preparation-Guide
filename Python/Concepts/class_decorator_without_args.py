class AuthMethod:    
    def __init__(self, fn):
        self.fn = fn
        
    def __call__(self, *args):
        self.fn(*args)
        print("Auth:", self.fn.__name__, *args)

@AuthMethod
def process_document(abc):
    print('Processing ', abc)

process_document('123')