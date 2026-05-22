# Rate-Limited Executor Service
# Problem Statement
# Design and implement an Executor Service with Rate Limiting capabilities. The service accepts tasks for execution and ensures that execution respects configured rate limits based on task attributes.
# A task type is a named logical operation registered with the executor (e.g., "sendNotification", "chargeCustomer"). Each task type has rate limit rules configured against it. Clients submit individual tasks under a task type, providing attributes and the work to execute.
# A rate limit restricts how many tasks with a specific attribute value can be executed per second. For example, if a rate limit of 10 RPS is configured on the userId field for the "sendNotification" task type, then for any given userId, no more than 10 such tasks can execute per second. Tasks exceeding the limit must be queued (not dropped) and executed when capacity becomes available.

# Level 1: Single Field Rate Limiting
# Build a rate-limited executor where each task type can have at most one rate limit rule configured on a single field.
# Requirements
# Register a task type with a rate limit configuration: a field name and an allowed RPS for any unique value of that field.
# Submit tasks under a task type with a set of attributes (key-value pairs) and the work to execute.
# Enforce the rate limit using the configured field's value from the task's attributes. Tasks exceeding the limit must wait, not be dropped.
# Tasks for different field-values must not block each other.
# Submission returns a handle that the caller can use to retrieve the result.
# Safe for concurrent submissions. FIFO order per key.
# Example
# Register task type "sendNotification" with { field: "userId", rps: 5 }
# Submit 10 tasks under "sendNotification" with userId=U1 at t=0
#   → 5 execute immediately, the rest are throttled and execute as the window allows
# Submit 5 tasks under "sendNotification" with userId=U2 at t=0
#   → All 5 execute immediately (independent of U1)

# Template
from abc import ABC, abstractmethod
from concurrent.futures import Future
from typing import Callable, Any


class RateLimitedExecutor(ABC):

    @abstractmethod
    def register_task_type(self, task_type: str, *args, **kwargs) -> None:
        ...

    @abstractmethod
    def submit(self,
               task_type: str,
               attributes: dict[str, str],
               work: Callable[[], Any]) -> Future:
        ...


Entities:
    
config: [
    {
        "taskType": "sendNotification",
        "algorithm": "SlidingWindowRateLimiter",
        "rpm": 10
    }
]
    
request: {
    "taskType": "sendNotification",
    "attributes": {
        "field": "userId",
        "value": "abc",
        "timestamp": 10
    },
    "task": lambda x: print(x)
}
    
class RateLimiter(ABC):
    @abstractmethod
    + allow(request)
    
class SlidingWindowBucketState:
    - _stateLock: threading.Lock()
    + requests: deque[Request]
     
# rpm = 5
# 1, 10, 20, 30, 40, 50 -> 61,
# 1, 10, 20, 30, 40, 61

class SlidingWindowRateLimiter(RateLimiter):
    - rate: int         # allowed requests per min
    - fieldToState: dict[str, SlidingWindowBucketState]
    - _lock: threading.Lock()
        
    def getFieldState(field: str):
        with self._lock:
            if field not in fieldToState:
                fieldState = SlidingWindowBucketState()
                fieldToState[userId] = fieldState
            else:
                fieldState = fieldToState[userId]
            return fieldState
    
    def allow(request: Request):
        fields: dict[str, str] = request.attributes
        requiredField = fields["field"]
        state = getFieldState(requiredField)
        
        with state._stateLock:
            # Allow the request for the state
            currentTime = int(time.time())
            windowStartTime = currentTime - 60
            stateRequests = state.requests

            while len(stateRequests) > 0 and stateRequests[0].attributes["timestamp"] < windowStartTime:
                stateRequests.popfront()

            if len(stateRequests) < rate:
                stateRequests.append(request)
                # Allow the request now
                async request.work()
            else:
                frontRequestTimestamp = stateRequests[0].attributes["timestamp"]

                # Find the time diff for request to sleep
                timeDiff = frontRequestTimestamp + 60 - request.attributes["timestamp"]
                request.attributes["timestamp"] += timeDiff
                stateRequests.append(request)

                # Allowing request at a later time
                async request.work(time.sleep(timeDiff))
        

class ClientRequest:
    - taskType: str
    - attributes: dict[str, str]
    - work: Callable[[], Any]

class RateLimitedExecutor
    # e.g. sendNotification -> SlidingWindowRateLimiter
    - taskVsRateLimiter: dict[str, RateLimiter]
    - defaultRateLimiter (for default tasks)
    
    def __init__(config):
        # parsing of config and update the taskVsRateLimiter
    
    def register_task_type(self, task_type: str):
        pass
    
    def getLimiter(taskType):
        if taskType in taskVsRateLimiter:
            return taskVsRateLimiter[taskType]
        return defaultRateLimiter
    
    def submit(taskType, attributes, work)
        clientRequest = ClientRequest(task_type=taskType, attributes=attributes, work=work)
        rateLimiter: RateLimiter = getLimiter(taskType)
        rateLimiter.allow(clientRequest)


SlidingWindowRateLimiter
rate
requestQueue 


