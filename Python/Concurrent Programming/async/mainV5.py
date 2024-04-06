import asyncio
import time


async def async_sleep(n):
    print(f"Before sleep {n}")
    for i in range(n-1, 0, -1):
        yield i
        await asyncio.sleep(i)
    print(f"After sleep {n}")


async def print_hello():
    print("Hello")


async def main():
    start_time = time.time()
    async for k in async_sleep(5):
        print(k)
    print('total time: ', time.time() - start_time)


if __name__ == "__main__":
    asyncio.run(main())
