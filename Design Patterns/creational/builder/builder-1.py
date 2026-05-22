from typing import Optional

# NOTE: Builder is less common in Python. Python has better alternatives like dataclasses with default values, keyword arguments, 
# or simple dictionaries. This pattern adds unnecessary complexity for most Python use cases.

class HttpRequest:
    def __init__(self):
        self.url: Optional[str] = None
        self.method: Optional[str] = None
        self.headers: dict[str, str] = {}
        self.body: Optional[str] = None

class HttpRequestBuilder:
    def __init__(self):
        self._request = HttpRequest()

    def url(self, url: str) -> 'HttpRequestBuilder':
        self._request.url = url
        return self

    def method(self, method: str) -> 'HttpRequestBuilder':
        self._request.method = method
        return self

    def header(self, key: str, value: str) -> 'HttpRequestBuilder':
        self._request.headers[key] = value
        return self

    def body(self, body: str) -> 'HttpRequestBuilder':
        self._request.body = body
        return self

    def build(self) -> 'HttpRequest':
        # Validate required fields
        if self._request.url is None:
            raise ValueError("URL is required")
        return self._request

# Usage
request: HttpRequest = (HttpRequestBuilder()
    .url("https://api.example.com")
    .method("POST")
    .header("Content-Type", "application/json")
    .body('{"key": "value"}')
    .build()
)
