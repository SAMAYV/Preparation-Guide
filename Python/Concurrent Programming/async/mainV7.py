import asyncio
import multiprocessing


class MultiProcessingAsync(multiprocessing.Process):
    def __init__(self, durations):
        super().__init__()
        self._durations = durations

    @staticmethod
    async def async_sleep(duration):
        await asyncio.sleep(duration)
        return duration

    async def consecutive_sleeps(self):
        pending = set()
        for duration in self._durations:
            pending.add(asyncio.create_task(self.async_sleep(duration)))

        while len(pending) > 0:
            done, pending = await asyncio.wait(pending, return_when='FIRST_COMPLETED')
            print('Done:')
            for done_task in done:
                print(await done_task)

    def run(self):
        asyncio.run(self.consecutive_sleeps())
        print('Process finished')


def main():
    durations = [1, 6, 3, 4, 9, 7, 5, 2, 10]
    processes = []
    for i in range(2):
        processes.append(MultiProcessingAsync(durations[i*5:(i+1)*5]))

    for p in processes:
        p.start()

    for p in processes:
        p.join()


if __name__ == '__main__':
    main()
