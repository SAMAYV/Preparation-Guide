import queue
from dataclasses import dataclass

@dataclass
class EmailTask:
    recipient: str
    template: str
    data: str

class EmailService:
    def __init__(self):
        self._email_queue = queue.Queue(maxsize=10000)

    # API handler (producer)
    def signup(self, email: str, name: str) -> None:
        # Fast: Save user to database
        user_repository.save(email, name)

        # Fast: Enqueue background work
        self._email_queue.put(EmailTask(email, "welcome", name))

        # Return immediately - user sees instant response

    # Worker thread (consumer)
    def email_worker(self) -> None:
        while True:
            task = self._email_queue.get()
            # Slow: Connect to email server and send
            email_client.send(task.recipient, task.template, task.data)
