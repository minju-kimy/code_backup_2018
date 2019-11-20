import elasticsearch
import json

es_client = elasticsearch.Elasticsearch("localhost:9200")

with open('C:/Users/user/Desktop/miniproject3/ML_second/Man/nearest_neighbors/test.jpg.npz.json') as data_file:
    data = json.load(data_file)

filename=[]
for i in range(len(data)):
    filename.append(data[i]['filename'][:27])

doc =[]
for i in filename:
    doc.append(es_client.search(index = 'men_name_url',doc_type='table', body={
    'query':{
        'match':{
            'url':i
        }
            
        }, 'size': 1
    }
))

for i in range(len(doc)):
    print(doc[i]['hits']['hits'][0]['_source']['column3'])

