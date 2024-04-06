import asyncio
import time


async def async_sleep():
    print("Before sleep")
    await asyncio.sleep(5)
    print("After  sleep")


async def print_hello():
    print("Hello")


async def main():
    start_time = time.time()
    task = asyncio.create_task(async_sleep())
    task2 = asyncio.create_task(async_sleep())
    task3 = asyncio.create_task(print_hello())
    await task
    await task2
    await task3
    print('total time: ', time.time() - start_time)


if __name__ == "__main__":
    asyncio.run(main())
