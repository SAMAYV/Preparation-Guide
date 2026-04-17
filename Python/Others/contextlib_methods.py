from contextlib import closing
from urllib.request import urlopen

with closing(urlopen("http://www.google.com")) as webpage:
    for line in webpage:
        # process the line
        pass


from contextlib import suppress

with suppress(FileNotFoundError):
    with open('fauxfile.txt') as fobj:
        for line in fobj:
            print(line)

from contextlib import redirect_stdout

path = 'text.txt'
with open(path, 'w') as fobj:
    with redirect_stdout(fobj):
        help(redirect_stdout)