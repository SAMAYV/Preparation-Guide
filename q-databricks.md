**Design an order management service for stock buy and sell requests.**

The system does not match trades itself. Instead, it integrates with a third-party brokerage API:
- `POST /orders` → submits an order and returns a unique external order ID
- `GET /orders/{id}` → returns the latest order details and status
- `DELETE /orders/{id}` → requests cancellation of an existing order

Your design should support:
- Placing buy and sell orders
- Tracking order status over time
- Canceling orders
- Handling orders that remain in a `pending` state for a long time
- Handling orders that expire before being filled
- Identifying likely system bottlenecks and explaining how to mitigate them

Focus especially on **order lifecycle management**, **correctness under retries or partial failures**, and **how the system stays consistent with the third-party brokerage**.

Same question me deadline bhi de rkhi thi har order k sath. Sabse important tha usme ki deadline se 1s bhi late order execute ni hona chahiye