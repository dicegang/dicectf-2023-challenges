import os
from collections import defaultdict
from dataclasses import dataclass
from typing import Optional

from . import driver

FLAG = os.getenv("FLAG")

# Helper because I'm lazy ;)
class MagicDict(defaultdict):
    def __init__(self, d):
        super().__init__(lambda: None, d)


@dataclass
class RequestRecord:
    time: str
    server: str
    method: str
    url: str
    status: int
    bytes_sent: int
    time_elapsed: float
    remote_addr: str
    user: Optional[str]
    headers: MagicDict


example_entries = [
    RequestRecord(
        time="03/Feb/2023:20:59:59 +0000",
        server="ctf.dicega.ng",
        method="GET",
        url="/api/v1/challs",
        status=401,
        bytes_sent=77,
        time_elapsed=12.5583,
        remote_addr="192.203.219.26",
        headers=MagicDict(
            {
                "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/109.0.0.0 Safari/537.36",
                "Host": "ctf.dicega.ng",
                "Accept": "*/*",
                "Connection": "keep-alive",
                "Referer": "https://ctf.dicega.ng/challs",
            }
        ),
        user=None,
    ),
    RequestRecord(
        time="03/Feb/2023:21:00:23 +0000",
        server="dicega.ng",
        method="POST",
        url="/ALFA_DATA/alfacgiapi/perl.alfa",
        status=200,
        bytes_sent=7479,
        time_elapsed=5.2315,
        remote_addr="169.254.169.254",
        headers=MagicDict(
            {
                "User-Agent": "Mozlila/5.0 (Linux; Android 7.0; SM-G892A Bulid/NRD90M; wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/60.0.3112.107 Moblie Safari/537.36",
                "Host": "dicega.ng",
                "Accept": "text/html",
                "Connection": "keep-alive",
            }
        ),
        user=None,
    ),
    RequestRecord(
        time="05/Feb/2023:21:00:01 +0000",
        server="ctf.dicega.ng",
        method="POST",
        url="/api/v1/challs/misc-mlog/submit",
        status=401,
        bytes_sent=62,
        time_elapsed=14.3463,
        remote_addr="192.203.219.26",
        headers=MagicDict(
            {
                "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/109.0.0.0 Safari/537.36",
                "Host": "ctf.dicega.ng",
                "Accept": "*/*",
                "Connection": "keep-alive",
                "Referer": "https://ctf.dicega.ng/challs",
            }
        ),
        user=None,
    ),
]

BANNER = """
⠀[blue]          [magenta] ▄▄▄▄    [red]                     [white]⠀
⠀[blue]          [magenta] ▀▀██    [red]                     [white]⠀
⠀[blue] ████▄██▄ [magenta]   ██    [red]   ▄████▄    ▄███▄██ [white]⠀
⠀[blue] ██ ██ ██ [magenta]   ██    [red]  ██▀  ▀██  ██▀  ▀██ [white]⠀
⠀[blue] ██ ██ ██ [magenta]   ██    [red]  ██    ██  ██    ██ [white]⠀
⠀[blue] ██ ██ ██ [magenta]   ██▄▄▄ [red]  ▀██▄▄██▀  ▀██▄▄███ [white]⠀
⠀[blue] ▀▀ ▀▀ ▀▀ [magenta]    ▀▀▀▀ [red]    ▀▀▀▀     ▄▀▀▀ ██ [white]⠀
⠀[blue]          [magenta]         [red]             ▀████▀▀ [white]⠀
"""
PITCH = """
[b red]Tired[/] of writing log formatters for your web server?
[b red]Had enough[/] of figuring out inscrutable log format strings?
Ever wish you could have an [b red]AI[/] write your code for you?
""".replace(
    "\n", " "
)
UPSELL = """
We hope you've enjoyed trying out [b][blue]m[/][magenta]l[/][red]og[/][/b]!
To make use of this [b]incredible[/] productivity booster in your own project,
you can subscribe [i b red]now[/] at the low cost of [i red][b]$1[/]/format string[/]!
""".replace(
    "\n", " "
)


def cli():
    from rich.console import Console
    from rich.padding import Padding
    from rich.panel import Panel
    from rich.text import Text

    console = Console(width=80, force_terminal=True)
    console.print(BANNER, justify="center")
    console.print(
        Panel(Text.from_markup(PITCH, style="yellow"), style="green", width=64),
        justify="center",
    )

    console.print()
    console.print(
        "[b]Want to see what [blue]m[/][magenta]l[/][red]og[/] can do for you?[/] "
        "Here's an example!\n"
    )

    def display_results(fmt):
        console.print("[green]Your format string is:[/]")
        console.print(Text(repr(fmt), style="yellow"), soft_wrap=True)

        console.print()
        console.print("[green]Here are some examples:[/]")
        for record in example_entries:
            console.print(Text(fmt.format(record), style="yellow"), soft_wrap=True)

    console.print(
        "[cyan]Description of log line to generate:[/] "
        "the time, followed by the server name in brackets, then the method, url, status code, and the referer header",
        soft_wrap=True,
    )
    console.print()
    display_results(
        "{0.time} [{0.server}] {0.method} {0.url} {0.status} {0.headers[Referer]}"
    )

    console.print()
    console.rule(style="white")
    console.print()

    console.print("[b green]Give it a try![/]\n")

    s = console.input("[cyan]Description of log line to generate:[/] ")

    console.print()
    with console.status("Generating..."):
        fmt = driver.execute(s)

    display_results(fmt)

    console.print()
    console.print(
        Panel(
            Text.from_markup(
                UPSELL + "\n[i cyan]https://ctf.dicega.ng/[/]", style="yellow"
            ),
            style="green",
            width=64,
        ),
        justify="center",
    )


if __name__ == "__main__":
    cli()
