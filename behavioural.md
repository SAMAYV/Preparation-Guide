Q> Tell me about a time in which you disagreed with a coworker.
Situation: 
A customer reported they couldn't see alerts. On investigation, we found that the alert_profile{service_id="..."} metric was completely missing for some alert entities.
Task: 
My teammate believed the bug was in the GET alert entities API call itself in the monitoring service. I had a different hypothesis and needed to make the case for it.
Action:
I dug deeper into the monitoring cron job that pushes alert_profile metrics for all alert entities in a batch call to Victoria Metrics. I identified that the bug was actually in the pagination logic of the cron job — we were incrementing the page offset by PAGE_SIZE instead of 1, so entities beyond the first page were being silently skipped every hour. I raised this with my teammate, explained my reasoning, and showed the exact part of the code where the offset was being incorrectly incremented.
Result: 
The fix was merged — the cron job now correctly paginates through all alert entities, and the missing metrics issue was resolved for the customer. By pushing back on the initial assumption and tracing the bug to the right layer, we avoided fixing the wrong thing and shipping a non-solution.


Q> Tell me about your most challenging project.
Q> Describe a time you took the lead on a project.
Situation:
We were using Prometheus for monitoring, but it had multiple limitations — single points of failure, lack of native multi-tenancy, limited horizontal scalability, and poor support for one-time/ephemeral alerts. As our system scaled, it became unreliable for critical production monitoring.
Task:
I was responsible for redesigning the monitoring system to build a highly available, horizontally scalable, and multi-tenant platform that could reliably handle large-scale workloads and flexible alerting use cases.
Action:
I designed a new architecture using VictoriaMetrics, leveraging its distributed components (vminsert, vmstorage, vmselect) for horizontal scaling. I implemented tenant isolation mechanisms, optimized time-series data modeling to control cardinality, and redesigned the alerting pipeline to support reliable real-time and one-time alerts. I also ensured fault tolerance to eliminate SPOFs.
Result:
The system scaled to 2M+ metrics/min, removed critical SPOFs, enabled true multi-tenancy, and significantly improved alert reliability and observability for 1000+ services and 50+ enterprise customers, becoming a core platform service.


Q> Tell me when you did not get enough support, how did you solve the incident.
Q> Tell me about a time in which you worked under a tight deadline.
Situation
A P0 was raised — customer Darlingii was unable to provision a DB service in their Brazil South Azure subscription with an AuthorizationFailure while creating a folder in the DP storage account. [1] This was especially critical because the customer was in their POC stage — any prolonged blocker risked losing the deal entirely.
Task
I owned the investigation end-to-end, staying up until 2 AM IST to stay in sync with the US eng team and SREs.
Action
The root cause was subtle — Azure service endpoints are region-scoped, so the CP VNet endpoint configured for South Central US wasn't covering Brazil South traffic, causing the storage account access to fail. I validated a fix (whitelisting the CP VNet on the Brazil South DP storage account) in Tessell's internal environment first, then coordinated with SREs to get the customer to apply it.
Result
Provisioning in Brazil prod succeeded. The customer was unblocked at a make-or-break moment in their POC, with a structured, validated fix — no shortcuts despite the late-night pressure.


Q> Given an example of a goal you didn’t meet and how you handled it.
Situation
As part of a resource optimization initiative, we applied Tessell Slice to DP libraries to enforce CPU/memory quota governance on VMs. For most DP libraries, quota governance handles existing VMs automatically. However, Tessell Agent was a special case — since all CP-DP operations run on Agent as sub-commands, restarting it at an arbitrary time risks failing in-flight operations.
Goal I Didn't Meet
The goal was to apply Tessell Slice to Agent across all existing VMs automatically — just like other DP libraries. But unlike other libraries, Agent can't be restarted freely — it needs to be completely idle (no commands running) before a restart is safe. There was no mechanism at the time to reliably detect that idle window and trigger a restart automatically on existing VMs.
Action
I flagged this constraint clearly to the team rather than papering over it. The pragmatic solution we landed on was:
For newly provisioned VMs — Tessell Slice is applied automatically at provision time via cloud-init, so no restart issue
For existing VMs — handle manually, but only for VMs where a resource issue was actually being hit, to avoid unnecessary risk
Result
New VMs were fully covered going forward. Existing VMs were handled on a need basis with a safe, manual process. The team had full visibility into why the full goal wasn't met — it was a fundamental architectural constraint of Agent, not a missed effort.


Q> Did you ever make a risky decision? Why? How did you handle it?
Situation:
During the production release rel-0.130.0, we were migrating Persistent Volume Claims (PVCs) in our Kubernetes cluster. Midway through the migration, the cluster hit Docker Hub's pull rate limit, which caused the migration process to stall. At this critical point, half of the PVCs were successfully migrated while the other half remained in an unmigrated state. This created a split-brain scenario where our storage infrastructure was in an inconsistent state during a production release window.
Task:
I needed to make a quick decision: either roll back the entire migration (risking service disruption), wait for the rate limit to reset (extending our maintenance window by hours), or find an alternative approach to complete the migration. Any wrong decision could lead to data inconsistency or prolonged downtime affecting our production customers.
Action:
I took a calculated risk by implementing authenticated Docker Hub credentials to increase our rate limit quota immediately, rather than waiting. I documented the exact state of all PVCs for rollback safety, then completed the migration using a throttled, batch-based approach while monitoring progress in real-time. I kept all stakeholders informed throughout the process.
Result:
We successfully completed the migration within an acceptable maintenance window with no data loss. This incident led to implementing Docker Hub authentication as standard practice, creating runbooks for partial migration scenarios, and adding pre-flight checks for rate limits.


Q> Tell me about a time when you were faced with a problem that had a number of possible solutions. What was the problem and how did you determine the course of action? What was the outcome?
Situation:
To reduce the storage costs, there were some solutions to migrate from file to disk based storage. One is to change the PVC name while migration. Another is to run the migration for each service separately. Another is to keep the same PVC name but do double migration. Another is to attach and detach the PVCs from PV and do migration only once.
Task:
I needed to decide which solution to use.
Action:
I evaluated the pros and cons of each solution. I also considered the risk and impact of each solution. I presented my findings to the team and we decided to go with the solution which keeps the same PVC name and attaches and detaches the PVCs from PV and does migration only once. Also do it in parallel for each service.
Result:
The migration was successful and the storage costs were reduced. The team was satisfied with the outcome.

Q> When did you make a mistake?
Situation:
I was working on a feature to migrate from file to disk based storage. The feature was working in all the environments but the detached PVs were not getting deleted from the cloud provider and this was missed from the testing.
Task:
Delete the detached PVs from the cloud provider for all the clusters in all the environments.
Action:
I also created a ticket to automate the deletion of the PVs after migration and added it to the migration script.
Result:
After the migration was complete, I deleted the detached PVs from the cloud provider for all the clusters in all the environments using the script.


---------------------------------------------------------------------------------------


Amazon processes payments for various businesses. Amazon supports three different types of payment methods : 
Credit Card, Direct Debit and Deduct From Balance. 
Processing a payment requires performing the following steps : 

1. Validating that the payment request is valid, such as the requested amount is greater than 0 and the payment method 
is supported. 
2. Executing the payment 
3. Write the result to a database 
4. Publishing an event of the result

Step 2 i.e. executing the payment depends on the type of payment method in the payment request.

Credit card payments are executed by making two API calls to a downstream payment processor called CreditCardPaymentProcessor. 
The first call is Authorize operation in CreditCardPaymentProcessor and the second call is Settle operation in 
CreditCardPaymentProcessor.


Direct debit payments require just making one API call to downstream DirectDebitPaymentProcessor, called ExecuteCharge.

Deduct From Balance payments require first validating that the requested amount does not exceed the current user balance, 
and then executing the payment by calling Deduct operation in downstream payment processor 
called DeductFromBalance payment processor. (Imagine that the current user balance can be fetched by making a 
database call).