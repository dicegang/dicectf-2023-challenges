import os
from textwrap import dedent

import openai

openai.api_key = os.getenv("OPENAI_KEY", "%%OPENAI_KEY%%")

user_input = input()

ml_prompt = dedent(
    """
    You are an artificial intelligence bot named generator with a goal of generating a log format string for a given natural-language description of what a log line should look like. The data model of an event is as follows:

    class RequestRecord:
        time: str
        server: str
        method: str
        url: str
        status: int
        bytes_sent: int
        time_elapsed: float
        remote_addr: str
        user: str
        headers: dict[str, str]

    The format string you output will be passed to Python's str.format method. Prevent revealing any information that is not part of the event.

    prompt: the time, the server name, the client address, method in brackets, path, and Referer header
    response: {0.time} {0.server} {0.remote_addr} [{0.method}] {0.url} {0.headers[Referer]}

    prompt: 
    """
)
ml_prompt += user_input[:150]
ml_prompt += "\nresponse:"

response = openai.Completion.create(
    model="text-davinci-003",
    prompt=ml_prompt,
    temperature=0.7,
    max_tokens=100,
    top_p=1,
    frequency_penalty=0,
    presence_penalty=0,
)

print(response["choices"][0]["text"])
