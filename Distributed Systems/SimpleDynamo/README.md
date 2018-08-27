Simplified Version of Amazon’s Dynamo that implements partitioning, replication and failure handling. 
The application implements a distributed key-value storage system that provides both availability and linearizability. The implementation performs successful read and write operations even in the presence of failures. Similar to DHT ,the application contains a content provider
providing simpliﬁed Dynamo functionality to store and retrieve data across multiple devices even under failures.

Implementing the ContentProvider :

In implementing the content provider, we may make the following assumptions:
1. There will always be 5 nodes in the system (except for failures). There is no implementation of joining or departure of nodes. The nodes hard-code the ring structure, as long as they handle failure.
2. There will be at most one failure at a time. We will emulate a failure by force-closing an app on one emulator. We will not close the emulator itself.
3. All failures are temporary. You can assume that a failed node will recover soon. It will not be permanently unavailable during a run.
4. Correctness is more important than performance!
5. We do not  implement virtual nodes. (These are part of the Dynamo protocol) All partitions are static and ﬁxed.
6. Hinted handoff is not implemented. This means that,during a failure,it is OK to replicate on only two nodes (if the third replica would be on a failed node). (Again, see the Dynamo paper.)
7. Linearizability will be checked only on a per-key basis. Formally, we implement per-key linearizability.

