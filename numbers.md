Scaling reads: Caching, precomputation
Scaling writes: Sharding, partitioning, batching

1 day = 100k seconds

CACHE:
Throughput: 1 redis cache instance can handle 100k operations (reads, writes) per sec
Reads: < 1ms within the same region
Writes: < 1ms same-AZ, 1-2ms cross-AZ (within the same region) for optimized systems
Memory: Up to 1TB on memory-optimized instances

DATABASE:
Storage: Single instances handle up to 64 TiB for most database engines
Read Latency: 1-5ms for cached data, 5-30ms for disk (optimized configurations for RDS and Aurora)
Write Latency: 5-15ms for commit latency (for single-node, high-performance setups)
Read Throughput: Up to 50k TPS in single-node configurations on Aurora and RDS
Write Throughput: 10k TPS in single-node configurations on Aurora and RDS
Connections: 10k concurrent connections, depending on database and instance type

APP SERVERS:
Connections: 100k+ concurrent connections per instance for optimized configurations
CPU: 8-64 cores
Memory: 64-512GB standard, up to 2TB available for high-memory instances
Network: 25 Gbps standard, up to 50-100 Gbps on high-performance instances
Startup Time: 30-60 seconds for containerized apps

MESSAGE QUEUE:
Throughput: Up to 500k messages/second per broker in modern configurations
Latency: 1-5ms end-to-end within a region for optimized setups
Message Size: 1KB-10MB efficiently handled (desired 1MB)
Storage: Up to 50TB per broker in advanced configurations
Retention: Weeks to months of data, depending on disk capacity and configuration

With consistent sub-5ms latencies, you can now use queues within synchronous request flows—getting the benefits of reliable delivery and decoupling without forcing APIs to be async.
Queues can serve as the backbone for event sourcing, real-time analytics, and data integration patterns that previously required specialized systems.

YT shorts has 1 hour of uploaded content in 1 sec
Fanout read/write limit: 100k followers

-------------------------------------------------------------

ZooKeeper provides a consistent, reliable source of truth that all servers can trust. When servers come online, they register in ZooKeeper. When users connect to servers, that mapping gets stored in ZooKeeper. ZooKeeper then notifies interested servers about changes and automatically handles failures through its ephemeral nodes. It gives you reliable service discovery, configuration management, and leader election without building these complex distributed algorithms yourself.

- Another approach for us to use is to always assign users to a specific Chat Server based on their user ID. If we do this correctly, we'll always know which Chat Server is responsible for a given user so, when we need to send them messages, we can do so directly.
To do this we'll need to keep a central registry of how many Chat Servers we have, their addresses, and the which segments of a consistent hash space they own. We might use a service like ZooKeeper or Etcd to do this.

-------------------------------------------------------------

Isolation levels control how much concurrent transactions can see of each other's changes. Think of it as how "isolated" each transaction is from seeing other transactions' work.

Start here. Can you keep all the contended data in a single database? If yes, use pessimistic locking or optimistic concurrency based on your conflict frequency.
Single database, high contention: Pessimistic locking with explicit locks (FOR UPDATE). This provides predictable performance, is simple to reason about, and handles worst-case scenarios well.
Single database, low contention: Optimistic concurrency control using existing columns as versions. This provides better performance when conflicts are rare and has no blocking.
Multiple databases, must be atomic: Distributed transactions (2PC for strong consistency, Sagas for resilience). Use only when you absolutely need atomicity across systems.
User experience matters: Distributed locks with reservations to prevent users from entering contention scenarios. This is great for ticketing, e-commerce, and any user-facing competitive flows.

Flash Sale/Inventory Systems - Perfect for demonstrating a mix of approaches. You can use optimistic concurrency with a dedicated version column for inventory updates, combined with temporary cart "holds" (using distributed locks with TTL) to improve user experience and reduce contention at checkout.

Here are some bang on examples of when you might need to use contention patterns:
Multiple users competing for limited resources such as concert tickets, auction bidding, flash sale inventory, or matching drivers with riders
Prevent double-booking or double-charging in scenarios like payment processing, seat reservations, or meeting room scheduling
Ensure data consistency under high concurrency for operations like account balance updates, inventory management, or collaborative editing
Handle race conditions in distributed systems in any scenario where the same operation might happen simultaneously across multiple servers and where the outcome is sensitive to the order of operations.

-------------------------------------------------------------

Event sourcing is about replaying events to reconstruct the state of the system with the goal of increasing robustness and reliability.
We're using the logs in event store (kafka) to store the entire history of the system but also to orchestrate next steps. Whenever something happens that we need to react to, we write an event to the event store and have a worker who can pick it up and react to it. Each worker consumes events, performs its work, and emits new events.
- This gives you:
Fault tolerance: If a worker crashes, another picks up the event
Scalability: Add more workers to handle higher load
Observability: Complete audit trail of all events
Flexibility: Possible to add new steps or modify workflows

Workflow systems and durable execution are the solutions to this problem, and they show up in many system design interviews, particularly when there is a lot of state and a lot of failure handling.

Workflows often show up when there is a state machine or a stateful process in the design. If you find a sequence of steps that require a flow chart, there's a good chance you should be using a workflow system to design the system around it.

Problem:
- What we really want to do is to describe a workflow, a reliable, long-running processes that can survive failures and continue where they left off. Our ideal system needs to be robust to server crashes or restarts instead of losing all progress and it shouldn't require us to hand-roll the infrastructure to make it work.

Solution:
- Enter workflow systems and durable execution engines. 
- These solutions provide the benefits of event sourcing and state management without requiring you to build the infrastructure yourself. 
- Workflow systems and durable execution engines give tools for handling these common multi-step processes.
- Both provide a language for you to describe the high-level workflow of your system and they handle the orchestration of it, but they differ in how those workflows are described and managed.
- Most durable execution engines use code to describe the workflow. You write a function that represents the workflow, and the engine handles the orchestration of it.
- The most popular durable execution engine is Temporal.

Durable Execution Engine (Working):
- Workflows are the high-level flow of your system, and activities are the individual steps in that flow.
- Workflows are deterministic: given the same inputs and history, they always make the same decisions. This enables replay-based recovery. 
- Activities need to be idempotent: they can be called multiple times with the same inputs and get the same result, but temporal guarantees that they are not retried once they return successfully.
- Workflows can also utilize signals to wait for external events. For example, if you're waiting for a human to pick up an order, your workflow can wait for a signal that the human has picked up the order before continuing. Most durable execution engines provide a way to wait for signals that is more efficient and lower-latency than polling.

Managed Workflow System:
- Managed workflow systems use a more declarative approach. You define the workflow in a declarative language, and the engine handles the orchestration of it.
- Under the covers the managed workflow systems are doing the same thing as the durable execution engines: they are orchestrating a workflow, calling activities, and recording progress in such a way that they can be resumed in the case of failures.
- One of the most significant is the ability to visualize workflows as diagrams which means a much nicer UI.

Both approaches provide durable execution so your workflow's state persists across failures, restarts, and even code deployments. When a workflow executes an activity, the engine saves a checkpoint. If the server crashes, another worker picks up exactly where it left off. You can write code very similar to the single-server orchestration we saw earlier, but with the added guarantees of fault-tolerance, scalability, and observability.

- Temporal is the most powerful open-source option. It provides true durable execution with strong consistency guarantees. Workflows can run indefinitely, survive any failure, and maintain perfect audit trails. The downside is operational complexity - you need to run Temporal clusters in production. Use this when you need maximum control and have the team to operate it.
- AWS Step Functions offers serverless workflows if you're already on AWS. You define workflows as state machines in JSON, which is less expressive than code but eliminates operational overhead.

Common interview scenarios:
- Workflows often show up when there is a state machine or a stateful process in the design. If you find a sequence of steps that require a flow chart, there's a good chance you should be using a workflow system to design the system around it.
- In your interview, listen for phrases like "if step X fails, we need to undo step Y" or "we need to ensure all steps complete or none do." That's a clear signal for workflows.
- Only introduce workflows when you identify specific problems they solve: partial failure handling, long-running processes, complex orchestration, or audit requirements
- The key insight is recognizing when you're manually building what a workflow engine provides: state persistence across failures, orchestration of multiple services, handling of long-running processes, and automatic retries with compensation. If you find yourself implementing distributed sagas by hand or building state machines in Redis, it's time to consider a workflow system.

------------------------------------------------------------

Flink is a stream processing framework that gives us a bunch of convenient tools for handling batching and aggregation in streaming applications. Flink handles checkpoint and recovery for us, so we don't have to worry about losing data or struggling with itchy problems like event delays.
For this Flink application, we'll use BoundedOutOfOrdernessWatermarkStrategy to handle late events: basically we'll tell Flink that we're ok waiting up to some time (probably 30 seconds here, < 1 minute) for late events to arrive. We'll also use a tumbling window of 1 hour to aggregate the views for each video.

------------------------------------------------------------

One subtlety worth calling out is that if you use fixed-size chunks (e.g., every 5MB), inserting a single byte near the beginning of the file shifts all subsequent chunk boundaries, causing every chunk after the edit to produce a different fingerprint. This makes delta sync nearly useless. The solution is Content-Defined Chunking (CDC), where chunk boundaries are determined by the file's content using a rolling hash (like Rabin fingerprinting). With CDC, a small edit only affects the chunks immediately surrounding the change, the vast majority of chunks remain identical. This is how systems like Dropbox actually achieve efficient delta sync in practice.

------------------------------------------------------------

REDIS:

Redlock is an algorithm designed for distributed locking using Redis. It was created by Salvatore Sanfilippo (the creator of Redis) to solve a specific problem: making sure a lock remains valid even if a single Redis node crashes.

The solution is to move the entire read-calculate-update logic into a single atomic operation. With Redis, this can be achieved using something called Lua scripting. Lua scripts are atomic, so the entire rate limiting decision becomes race-condition free. Instead of separate read and write operations, we send a Lua script to Redis that reads the current state, calculates the new token count, and updates the bucket all in one atomic step.

In production, you'd likely use Redis Cluster rather than managing individual Redis instances yourself. Redis Cluster automatically handles the data sharding we just described by dividing keys across 16,384 hash slots and distributing those slots across multiple Redis nodes. When you store a rate limit key like alice:bucket, Redis Cluster automatically determines which node should store it based on the key's hash slot. This way instead of building custom consistent hashing logic in your API gateways, you just connect to the Redis Cluster and it handles routing automatically.

This works particularly well with Redis Cluster, which has built-in failover capabilities that can detect master failures and promote replicas without manual intervention. The trade-off is increased infrastructure cost and the need to handle replica synchronization lag, though Redis replication is typically very fast.

------------------------------------------------------------

🏃 The Managing Long-Running Tasks pattern splits API requests into two phases: immediate acknowledgment and background processing. When users submit heavy tasks (like video encoding), the web server instantly validates the request, pushes a job to a queue (Redis/RabbitMQ), and returns a job ID, all within milliseconds. Meanwhile, separate worker processes continuously poll the queue, grab pending jobs, execute the actual time-consuming work, and update the job status in a database.

- What you gain:
Fast user response times - API calls return in milliseconds instead of timing out after 30 seconds. Users get immediate acknowledgment that their request was received.
Independent scaling - Web servers and workers scale separately. Add more workers during peak processing times without paying for idle web servers.
Fault isolation - A worker crash processing one video doesn't bring down your entire API. Failed jobs can be retried without affecting user-facing services.
Better resource utilization - CPU-intensive workers run on compute-optimized instances. Memory-heavy tasks get high-memory machines. Web servers use cheap, general-purpose instances.

------------------------------------------------------------

- Blob storage signatures are the security proof inside a presigned URL. Your backend creates a signature over details like the HTTP method, object path, and expiry time using its cloud secret, and blob storage verifies that signature when the client uses the URL.
So the mental model is a temporary access pass. Instead of giving the client permanent S3 or blob credentials, you give them a URL that says this user can upload or download this one file until this time. If the URL is changed or expired, the storage service rejects it.

- With a blob storage presigned URL, the storage service verifies the signature using your cloud credentials. With a CDN signed URL, your backend signs the URL with a private key, and the CDN edge verifies it with the matching public key. So for a download flow, your app server first checks that the user is allowed to access the file, then returns a temporary CDN URL, and the client downloads from the CDN directly.
A good mental model is this. Blob storage signature means storage is the gatekeeper. CDN signature means the CDN is the gatekeeper.

-----------------------------------------------------------

- A combination of four strategies will allow you to scale writes beyond what a single, unoptimized database or server can handle:
Vertical Scaling and Database Choices
Sharding and Partitioning
Handling Bursts with Queues and Load Shedding
Batching and Hierarchical Aggregation

An easy mistake to make is to employ write scaling strategies when no scaling is necessary! If you see something that looks like it might be a bottleneck, that's a good time to use some quick back-of-the-envelope math to see if it's worth the effort.

If you're dealing with high volume analytics or numeric data, batching and hierarchical aggregation can give you immediate 5-10x improvements.
Finally, queues and load shedding are great tools when requirements allow for async processing or even dropping requests. Keep them in mind as you're navigating requirements to see if they're a good fit.
The key insight is that write scaling is about reducing throughput per component.

