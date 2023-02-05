#!/usr/local/bin/python

import json
import sys

from unittest import TestCase, TestLoader, TextTestRunner
from util import SilentResult, SubmissionImporter

suite = TestLoader().discover('tests')

tests = []
stack = [suite]

while stack:
    current = stack.pop()
    if isinstance(current, TestCase):
        tests.append(current._testMethodName)
        continue
    for test in current:
        if isinstance(test, TestCase):
            tests.append(test._testMethodName)
        else:
            stack.append(test)

submission = json.loads(input())['file']
sys.meta_path.insert(0, SubmissionImporter(submission))

with open('/dev/null', 'w') as f:
    stdout = sys.stdout
    stderr = sys.stderr

    sys.stdout = f
    sys.stderr = f

    result = TextTestRunner(resultclass=SilentResult).run(suite)
    assert isinstance(result, SilentResult)

    sys.stdout = stdout
    sys.stderr = stderr

status = {}
messages = {}
for array, label in [
    (result.successes, 'success'),
    (result.failures, 'failure'),
    (result.errors, 'error'),
]:
    for test, error in array:
        name = test._testMethodName
        status[name] = label
        if error is not None:
            messages[name] = error

result = [
    {
        'name': name,
        'status': status.get(name, 'missing'),
        'message': messages.get(name, None),
    }
    for name in reversed(tests)
]

print(json.dumps(result))
