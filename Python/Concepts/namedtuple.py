from collections import namedtuple

Parts = {'id_num':'1234', 'desc':'Ford Engine',
     'cost':1200.00, 'amount':10}
z = namedtuple('Parts', Parts.keys())
parts = z(**Parts)
print (parts)