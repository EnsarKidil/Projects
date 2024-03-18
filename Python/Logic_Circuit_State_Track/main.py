import itertools

def bool_to_int(b):
    return 1 if b else 0

# The functions for A_next, B_next, and z, represented in Python
def A_next(a, b, x, y):
    return bool_to_int((b and x) or (not b and not y)) and not a or (b or x and y) and a

def B_next(a, b, x, y):
    return bool_to_int((not a and x) and not b) or (not a or x and y) and b

def z(a, b, x, y):
    return bool_to_int((a and not x and not y) or (b and not x and not y))

# Create a list of all possible combinations of a, b, x, and y
combinations = list(itertools.product([0, 1], repeat=4))

print("a | b | x | y | A_next | B_next | z")
print("--|---|---|---|--------|--------|--")
for a, b, x, y in combinations:
    print(f"{a} | {b} | {x} | {y} |   {A_next(a, b, x, y)}   |   {B_next(a, b, x, y)}   | {z(a, b, x, y)}")
