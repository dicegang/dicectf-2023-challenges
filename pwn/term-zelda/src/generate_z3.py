from z3 import *


# for direction, name in zip([-16, 1, 16, -1], ["NORTH", "EAST", "SOUTH", "WEST"]):
s = Solver()
x, y = BitVecs("x y", 8)
s.add(
    x & 0b11 == 1,
    y & 0b11 == 1,
    ZeroExt(64, x) + 16 * ZeroExt(64, y) == 0x2a7,
)
while s.check() == sat:
    print(f"{s.model()}")
    s.add(Or(x != s.model()[x], y != s.model()[y]))
