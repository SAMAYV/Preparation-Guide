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
    tasks = [asyncio.wait_for(async_sleep(30), 5), async_sleep(6), print_hello()]
    try:
        await asyncio.gather(*tasks)
    except asyncio.TimeoutError:
        print("Encountered timeout error.")
    print('total time: ', time.time() - start_time)


if __name__ == "__main__":
    asyncio.run(main())
