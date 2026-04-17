import asyncio

async def fn():
    task = asyncio.create_task(fn2())
    print("one")
    await task # Wait for the task to complete since fn() coroutine would go into sleep state.
    print('four')
    await asyncio.sleep(1)
    print('five')
    await asyncio.sleep(1)
 
async def fn2():
    print("two")
    await asyncio.sleep(1)
    print("three")
     
asyncio.run(fn())
