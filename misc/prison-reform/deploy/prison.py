#!/usr/local/bin/python
import ast

code = ""
while line := input("> "):
    code += line + "\n"

def try_resolve(name):
    if name == "print": return -1
    try: return eval(name) if name.isidentifier() else -1
    except NameError: return -1

if any(type(n) in (ast.Attribute, ast.Subscript, ast.Constant, ast.Assign, ast.AnnAssign, ast.AugAssign, ast.comprehension, ast.For, ast.Try, ast.ExceptHandler, ast.With, ast.FunctionDef, ast.Lambda, ast.AsyncFunctionDef, ast.ClassDef, ast.Import, ast.ImportFrom) or type(n) == ast.Name and try_resolve(n.id) in list(__builtins__.__dict__.values()) + [try_resolve, __builtins__, ast] for n in ast.walk(ast.parse(code))): print("Hacking detected!")
else: exec(code)
