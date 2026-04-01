import heapq
from collections import Counter

# Node class
class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq


# Build Huffman Tree
def build_tree(text):
    freq = Counter(text)
    heap = [Node(char, f) for char, f in freq.items()]
    heapq.heapify(heap)

    while len(heap) > 1:
        left = heapq.heappop(heap)
        right = heapq.heappop(heap)

        merged = Node(None, left.freq + right.freq)
        merged.left = left
        merged.right = right

        heapq.heappush(heap, merged)

    return heap[0]


# Generate Codes
def generate_codes(node, prefix="", code_map={}):
    if node:
        if node.char:
            code_map[node.char] = prefix
        generate_codes(node.left, prefix + "0", code_map)
        generate_codes(node.right, prefix + "1", code_map)
    return code_map


# Encode
def encode(text):
    root = build_tree(text)
    codes = generate_codes(root)
    encoded = "".join(codes[ch] for ch in text)
    return encoded, root


# Decode
def decode(encoded, root):
    decoded = ""
    current = root

    for bit in encoded:
        if bit == "0":
            current = current.left
        else:
            current = current.right

        if current.char:
            decoded += current.char
            current = root

    return decoded


# Example
text = input("Enter text to encode: ")
encoded, tree = encode(text)
decoded = decode(encoded, tree)

print("Original:", text)
print("Encoded:", encoded)
print("Decoded:", decoded)