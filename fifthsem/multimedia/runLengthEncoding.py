def run_length_encode(text):
    if not text:
        return ""
    
    encoded = ""
    count = 1

    for i in range(1, len(text)):
        if text[i] == text[i - 1]:
            count += 1
        else:
            encoded += str(count) + text[i - 1]
            count = 1

    # Add the last character group
    encoded += str(count) + text[-1]
    return encoded


def run_length_decode(encoded):
    decoded = ""
    i = 0

    while i < len(encoded):
        # Read the number (could be multi-digit)
        num = ""
        while i < len(encoded) and encoded[i].isdigit():
            num += encoded[i]
            i += 1
        
        # Read the character
        if i < len(encoded):
            decoded += encoded[i] * int(num)
            i += 1

    return decoded


# --- Test ---
text = "AAABBBCCDDDDEE"
encoded = run_length_encode(text)
decoded = run_length_decode(encoded)

print(f"Original : {text}")
print(f"Encoded  : {encoded}")
print(f"Decoded  : {decoded}")
print(f"Match    : {text == decoded}")
```

