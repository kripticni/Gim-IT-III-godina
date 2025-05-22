import string
import random

alphabet = list(string.ascii_lowercase)
random.shuffle(alphabet)
permutation = ''.join(alphabet)

print(permutation)
