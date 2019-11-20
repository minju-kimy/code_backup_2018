import json
from pprint import pprint
with open('./ML_second/Woman/nearest_neighbors/test (1).jpg.npz.json') as data_file:
    data = json.load(data_file)
# pprint(data)

for i in range(5):
    a = data[i]
    print(a['filename'])