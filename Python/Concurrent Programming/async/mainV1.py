import asyncio


async def async_sleep():
    print("Before sleep")
    await asyncio.sleep(5)
    print("After  sleep")


async def return_hello():
    return "Hello"


async def main():
    await async_sleep()
    hello_text = await return_hello()
    print(hello_text)


if __name__ == "__main__":
    asyncio.run(main())
