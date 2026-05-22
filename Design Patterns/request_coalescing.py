import asyncio

# Request coalescing pattern
class CoalescingCache:
    def __init__(self):
        self.inflight = {}  # key -> Future
    
    async def get(self, key):
        # Check if another request is already fetching this key
        if key in self.inflight:
            return await self.inflight[key]
        
        # No inflight request, we'll fetch it
        future = asyncio.Future()
        self.inflight[key] = future
        
        try:
            value = await fetch_from_backend(key)
            future.set_result(value)
            return value
        finally:
            del self.inflight[key]