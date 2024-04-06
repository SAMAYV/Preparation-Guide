import asyncio
import time


async def async_sleep(n):
    print(f"Before sleep {n}")
    await asyncio.sleep(n)
    print(f"After sleep {n}")


async def print_hello():
    print("Hello")


async def main():
    start_time = time.time()
    tasks = [async_sleep(2), async_sleep(1), print_hello()]
    await asyncio.gather(*tasks)
    print('total time: ', time.time() - start_time)


if __name__ == "__main__":
    asyncio.run(main())
