import json
#from pprint import pprint
with open('./ML_second/Man/nearest_neighbors/15ba6cd976.jpg.npz.json') as data_file:
    data = json.load(data_file)
# pprint(data)

for i in range(5):
    a = data[i]
    print(a['filename'].strip(".npz"))