import json
#from pprint import pprint
with open('C:/Users/user/Desktop/miniproject3/ML_second/Man/nearest_neighbors/test.jpg.npz.json') as data_file:
    data = json.load(data_file)
# pprint(data)

filename = []
for i in range(3):
    a = data[i]
    b = a['filename'].strip(".npz")
    filename.append(b)
print(filename)