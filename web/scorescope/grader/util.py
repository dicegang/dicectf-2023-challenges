import importlib
import importlib.abc
import importlib.util
import seccomp
import sys
import traceback
import unittest

class TestCase(unittest.TestCase):
    @property
    def submission(self):
        import submission
        return submission

class SubmissionImporter(importlib.abc.MetaPathFinder, importlib.abc.Loader):
    def __init__(self, submission):
        super().__init__()
        self.submission = submission

    def find_module(self, fullname):
        if fullname == 'submission':
            return self
        return None

    def load_module(self, fullname):
        if fullname in sys.modules:
            return sys.modules[fullname]
        spec = importlib.util.spec_from_loader(fullname, loader=None)
        assert spec is not None
        module = importlib.util.module_from_spec(spec)

        filter = seccomp.SyscallFilter(defaction=seccomp.KILL)
        filter.add_rule(seccomp.ALLOW, 'rt_sigaction')
        filter.add_rule(seccomp.ALLOW, 'rt_sigreturn')
        filter.add_rule(seccomp.ALLOW, 'exit_group')
        filter.add_rule(seccomp.ALLOW, 'brk')
        filter.add_rule(seccomp.ALLOW, 'write')
        filter.add_rule(seccomp.ALLOW, 'close')
        filter.add_rule(seccomp.ALLOW, 'munmap')
        filter.load()

        exec(self.submission, module.__dict__)
        sys.modules[fullname] = module
        return module

    def find_spec(self, fullname, path, target=None):
        del path
        del target
        if fullname == 'submission':
            return importlib.util.spec_from_loader(fullname, self)
        return None

hide = set()
def hidden(func):
    hide.add(func.__name__)
    return func

class SilentResult(unittest.TestResult):
    successes = []
    def addSuccess(self, test):
        super().addSuccess(test)
        self.successes.append((test, None))

    def _exc_info_to_string(self, err, test):
        if test._testMethodName in hide:
            return None
        t, e, _ = err
        return ''.join(traceback.format_exception_only(t, e))
