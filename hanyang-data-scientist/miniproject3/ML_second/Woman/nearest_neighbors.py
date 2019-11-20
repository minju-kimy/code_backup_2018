from annoy import AnnoyIndex
from scipy import spatial
from nltk import ngrams
import random, json, glob, os, codecs, random
import numpy as np

# data structures
learning_file_index_to_file_name = {}
learning_file_index_to_file_vector = {}
test_file_index_to_file_name = {}
test_file_index_to_file_vector = {}
chart_image_positions = {}

# config
dims = 2048
n_nearest_neighbors = 3
trees = 2000
learning_infiles = glob.glob('learning_image_vectors/*.npz')
test_infiles = glob.glob('input_image_vectors/*.npz')


# build ann index
t = AnnoyIndex(dims)

# learning images indexing
for file_index, i in enumerate(learning_infiles):
  file_vector = np.loadtxt(i)
  file_name = os.path.basename(i)
  learning_file_index_to_file_name[file_index] = file_name
  learning_file_index_to_file_vector[file_index] = file_vector
  t.add_item(file_index, file_vector)
  print("learning image indexing succeed")

# test images indexing
for file_index, i in enumerate(test_infiles):
  file_vector = np.loadtxt(i)
  file_name = os.path.basename(i)
  test_file_index_to_file_name[file_index] = file_name
  test_file_index_to_file_vector[file_index] = file_vector
  t.add_item(file_index, file_vector)
  print("test image indexing succeed")
t.build(trees)




# create a nearest neighbors json file for each input
if not os.path.exists('nearest_neighbors'):
  os.makedirs('nearest_neighbors')

for i in test_file_index_to_file_name.keys():
  master_file_name = test_file_index_to_file_name[i]
  master_vector = test_file_index_to_file_vector[i]

  named_nearest_neighbors = []
  nearest_neighbors = t.get_nns_by_item(0, n_nearest_neighbors)


  for j in nearest_neighbors:
    neighbor_file_name = learning_file_index_to_file_name[j]
    neighbor_file_vector = learning_file_index_to_file_vector[j]

    similarity = 1 - spatial.distance.cosine(master_vector, neighbor_file_vector)
    rounded_similarity = int((similarity * 10000)) / 10000.0

    named_nearest_neighbors.append({
      'filename': neighbor_file_name,
      'similarity': rounded_similarity
    })
  print("succeed2")


  with open('nearest_neighbors/' + master_file_name + '.json', 'w') as out:
    json.dump(named_nearest_neighbors, out)