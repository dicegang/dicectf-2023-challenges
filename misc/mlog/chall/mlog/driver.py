import subprocess
import sys
from pathlib import Path

child_path = Path(__file__).parent / "predict.py"


def execute(prompt: str) -> str:
    p = subprocess.Popen(
        [sys.executable, str(child_path)],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
    )
    assert p.stdin is not None
    assert p.stdout is not None
    p.stdin.write(prompt.encode())
    p.stdin.close()
    return p.stdout.read().decode().strip()
