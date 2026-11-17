<!-- page 1 -->
## Advanced Programming Methods Lecture 6 – Concurrency (1): Threads and Synchronization

```
Thread.ofPlatform().name("worker").start(() -> work());
```

<!-- page 2 -->
I N T R O D U C T I O N

#### Lecture overview

Processes and threads; concurrency vs. 01 parallelism

Creating and starting threads; thread builders (Java 21)

02

03

The life cycle of a thread; join

04

Interrupting threads

05

06

07

Race conditions, synchronized, the Java Memory Model

wait / notify: the producer–consumer problem

Deadlock, starvation, daemon threads, ThreadLocal

2

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 3 -->
I N T R O D U C T I O N

#### Why concurrency?

- Every modern processor has several cores – a sequential program uses only one of them

- Many programs wait : for the disk, the network, the database, the user

- Concurrency lets a program do several things _at the same time_ :

   - a server handles thousands of clients

   - a GUI stays responsive while a long computation runs in the background

   - a computation is split over all cores

- Java has supported threads since version 1.0; `java.util.concurrent` (Java 5), `CompletableFuture` (Java 8) and virtual threads (Java 21) made concurrency much easier

This lecture: threads, their life cycle and synchronization . Lecture 7: the high-level tools of `java.util.concurrent` and i virtual threads.

3

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 4 -->
# 01 Processes and threads

4

<!-- page 5 -->
0 1 · P R O C E S S E S A N D T H R E A D S

#### Processes and threads

```
OS
```

##### Process

A running program with its own memory space and resources (files, sockets). Processes are isolated; they communicate through IPC: pipes, sockets, files. A JVM normally runs as one process.

```
JVM
```

##### Thread

A sequential flow of control inside a process – a _lightweight process_ . Every process has at least one thread. Threads of a process share its memory and open files.

```
!
```

##### Consequence

Sharing memory makes communication between threads cheap – and dangerous : two threads can change the same object at the same time.

5

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 6 -->
0 1 · P R O C E S S E S A N D T H R E A D S

#### Single-threaded vs. multithreaded

###### sequential program multithreaded program

One flow of control: at any moment at most one statement is executed.

Several flows of control: at a given moment several statements may be executed – in parallel on several cores, or interleaved by time slicing on one core.

i Example – a web browser: scroll a page, download an image, play a sound and print, all at the same time.

6

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 7 -->
0 1 · P R O C E S S E S A N D T H R E A D S

#### Concurrency vs. parallelism

- Concurrency : several tasks are _in progress_ at the same time – their executions overlap in time

   - on one core, the scheduler switches between threads ( time slicing )

- Parallelism : several tasks _run_ at the same instant, on different cores

   - a concurrent program runs in parallel when there are free cores

- The scheduler of the OS (and of the JVM, for virtual threads) decides which thread runs, when and for how long

   - the order of execution is not determined by the program – it can change from one run to the next

   - ! Never rely on a particular interleaving: a concurrent program must be correct for every possible order of execution.

7

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 8 -->
0 1 · P R O C E S S E S A N D T H R E A D S

#### Benefits and costs

##### Benefits

- faster on a multi-core machine

- responsive applications: the long work runs in a _worker_ thread

###### `the classic race`

```
// a "Heisenbug": it appears and disappears
// depending on the timing of the threads
counter++;      // read, add 1, write back –
// NOT one indivisible step
```

- simpler structure for programs that serve many clients

##### Costs

- creating, scheduling and switching threads take time and memory

- shared data must be protected – extra complexity

- bugs are hard to reproduce: every run can interleave differently

8

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 9 -->
0 1 · P R O C E S S E S A N D T H R E A D S

#### Threads in every Java program

- The JVM starts the main thread , which runs `main(String[])`

- The JVM also runs its own threads: garbage collector, JIT compiler, finalizer …

```
Main.java
```

```
publicstaticvoidmain(String[] args) {
System.out.println(Thread.currentThread());
// Thread[#1,main,5,main]
//        id name prio group
}
```

- Every thread can start new threads

- A Java program ends when all its non-daemon threads have finished – not when `main` returns

9

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 10 -->
# 02

### Creating and starting threads

10

<!-- page 11 -->
0 2 · C R E A T I N G A N D S T A R T I N G T H R E A D S

#### A thread is a Thread object

- Each thread is represented by a `java.lang.Thread` object

- The code that the thread executes is a `Runnable` – a functional interface

- Two classic ways to define the code:

   - implement `Runnable` (preferred – usually a lambda)

```
java.lang.Runnable
```

```
packagejava.lang;
@FunctionalInterface
publicinterfaceRunnable {
voidrun();
}
```

   - extend `Thread` and override `run()`

- Implementing `Runnable` keeps the class free to extend another class and separates the task from the thread that runs it

11

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 12 -->
0 2 · C R E A T I N G A N D S T A R T I N G T H R E A D S

#### Defining and starting a thread

```
creating threads
```

```
// 1. a Runnable –here a lambda
Runnable task = () -> {
for(inti = 0; i < 3; i++)
System.out.println(i + " "+ Thread.currentThread().getName());
};
Thread t1 = newThread(task, "worker-1");
t1.start();                  // a NEW thread calls task.run()
// 2. a subclass of Thread
classPrinter extendsThread {
@Overridepublicvoidrun() {
System.out.println("hello from "+ getName());
}
}
newPrinter().start();
```

Call `start()` , not `run()` : `t.run()` executes the code in the current thread , like any method call – no new thread is ! created. A thread can be started only once.

12

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 13 -->
0 2 · C R E A T I N G A N D S T A R T I N G T H R E A D S

#### Two threads, interleaved

```
TwoThreads.java
```

```
publicclassTwoThreads {
staticvoidwork() {
String name = Thread.currentThread().getName();
for(inti = 0; i < 5; i++) {
System.out.println(i + " "+ name);
try{
Thread.sleep(Duration.ofMillis(
(long) (Math.random() * 100)));
} catch(InterruptedException e) {
return;                 // stop when interrupted
}
}
System.out.println("DONE! "+ name);
}
publicstaticvoidmain(String[] args) {
newThread(TwoThreads::work, "A").start();
newThread(TwoThreads::work, "B").start();
}
}
```

###### `one possible output`

<!-- Start of picture text -->
0 A 0 B 1 B 1 A 2 A 2 B 3 B 4 B 3 A DONE! B 4 A DONE! A <!-- End of picture text -->

13

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 14 -->
0 2 · C R E A T I N G A N D S T A R T I N G T H R E A D S

#### Thread builders (Java 21)

- Since Java 21, `Thread.ofPlatform()` and `Thread.ofVirtual()` return a builder

- The builder sets the name, daemon status, priority … and then starts or creates the thread

- Platform threads are wrappers around OS threads – the threads we discuss in this lecture

```
Thread.Builder
```

```
Thread t = Thread.ofPlatform()
.name("worker-", 1)   // worker-1, worker-2 …
.daemon(false)
.start(task);
Thread v = Thread.ofVirtual()
.name("virtual")
.start(task);
Thread u = Thread.ofVirtual()
.unstarted(task);     // created, not started
u.start();
```

- Virtual threads are cheap threads managed by the JVM – Lecture 7

14

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 15 -->
0 2 · C R E A T I N G A N D S T A R T I N G T H R E A D S

#### Thread properties

- `threadId()` – unique id (Java 19; replaces `getId()` )

- `■ getName()` , `setName(String)`

- `getPriority()` , `setPriority(int)` – between `MIN_PRIORITY` (1) and `MAX_PRIORITY` (10); only a _hint_ to the scheduler

- `isDaemon()` , `setDaemon(boolean)` – before `start()`

###### `static methods`

- _`// static methods – act on the CURRENT thread`_ `Thread.currentThread()`

```
Thread.sleep(Duration.ofSeconds(1)) // Java 19
Thread.sleep(1000)                  // millis
Thread.yield()          // a hint: let others run
Thread.onSpinWait()     // Java 9: busy-wait hint
Thread.interrupted()    // test AND clear flag
Thread.holdsLock(obj)
```

- `getState()` – the current `Thread.State`

- `isAlive()` – started and not yet terminated

- `isVirtual()` – Java 21

15

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 16 -->
# 03

### The life cycle of a thread

16

<!-- page 17 -->
0 3 · T H E L I F E C Y C L E O F A T H R E A D

#### The states of a thread: Thread.State

<!-- Start of picture text -->
waits for a monitor lock BLOCKED start() wait(), join() NEW RUNNABLE WAITING run() ends sleep(t), wait(t), join(t) TIMED_WAITING TERMINATED <!-- End of picture text -->

_RUNNABLE = running or ready to run. Dashed arrows: the lock is obtained, the thread is notified or interrupted, the time expires._

17

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 18 -->
0 3 · T H E L I F E C Y C L E O F A T H R E A D

#### Waiting for a thread: join

`■ t.join()` – the current thread waits until `t` terminates

`■ t.join(millis)` / `t.join(Duration)` (Java 19) – waits at most the given time

- After `join` returns normally, everything `t` wrote is visible to the current thread

###### `parallel sum`

```
int[] partial = newint[2];
Thread left  = newThread(() -> partial[0] = sum(a, 0, n / 2));
Thread right = newThread(() -> partial[1] = sum(a, n / 2, n));
left.start();
right.start();
```

```
left.join();          // wait for both halves
right.join();
System.out.println(partial[0] + partial[1]);
```

- `join` throws `InterruptedException` if the waiting thread is interrupted

18

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 19 -->
0 3 · T H E L I F E C Y C L E O F A T H R E A D

#### Methods you must not use

`■ stop()` – kills a thread at an arbitrary point, leaving objects in an inconsistent state `■ suspend()` / `resume()` – a suspended thread keeps its locks: an easy deadlock

- All three are deprecated since Java 1.2; in recent versions (Java 20+) they throw `UnsupportedOperationException`

- Thread groups ( `ThreadGroup` ) are legacy as well – use executors (Lecture 7) to manage groups of tasks

- The correct way to stop a thread is cooperative : ask it to stop, and let it finish cleanly → _interruption_

19

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 20 -->
# 04 Interrupting threads

20

<!-- page 21 -->
0 4 · I N T E R R U P T I N G T H R E A D S

#### Interruption: a polite request to stop

- `t.interrupt()` sets the interrupted flag of `t`

```
responding to interrupts
```

- If `t` is blocked in `sleep` , `wait` or `join` : the call ends with an `InterruptedException` and the flag is cleared

- If `t` is running: nothing else happens – `t` must check the flag itself

- `Thread.interrupted()` – tests and clears the flag of the current thread

- `t.isInterrupted()` – tests without clearing

```
publicvoidrun() {
try{
while(moreWork()) {
doSomeWork();
Thread.sleep(100);  // a chance to be interrupted
}
```

- `}` `catch` `(InterruptedException e) {` _`// interrupted while sleeping – clean up and end`_

- `}`

- `}`

```
// a loop with no blocking call checks the flag:
while(!Thread.currentThread().isInterrupted()
&& moreWork()) {
doSomeWork();
```

```
}
```

21

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 22 -->
0 4 · I N T E R R U P T I N G T H R E A D S

#### Do not swallow InterruptedException

###### `handling InterruptedException`

```
// WRONG –the request to stop is lost
try{
Thread.sleep(1000);
} catch(InterruptedException e) { }
// RIGHT –either propagate it ...
voidpause() throwsInterruptedException {
Thread.sleep(1000);
}
// ... or restore the flag, so that the caller sees it
try{
Thread.sleep(1000);
} catch(InterruptedException e) {
Thread.currentThread().interrupt();
return;
}
```

Catching the exception clears the flag. Code higher up that checks `isInterrupted()` will never know – unless you set the ! flag again.

22

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 23 -->
0 4 · I N T E R R U P T I N G T H R E A D S

#### A complete example: impatient main

###### `SimpleThreads.java (1)`

```
publicclassSimpleThreads {
staticvoidmsg(String m) {
System.out.printf("%s: %s%n",
Thread.currentThread().getName(), m);
```

```
}
```

###### `static void` `messageLoop() {`

```
String[] info = { "A", "B", "C", "D"};
try{
```

```
for(String s : info) {
Thread.sleep(Duration.ofSeconds(4));
msg(s);
```

```
}
```

- `}` `catch` `(InterruptedException e) { msg("I wasn't done!");`

- `}`

```
}
```

###### `SimpleThreads.java (2)`

```
publicstaticvoidmain(String[] args)
throwsInterruptedException {
Duration patience = Duration.ofSeconds(10);
longstart = System.nanoTime();
Thread t = newThread(SimpleThreads::messageLoop);
t.start();
while(t.isAlive()) {
msg("Still waiting...");
t.join(Duration.ofSeconds(1));
Duration waited = Duration.ofNanos(
System.nanoTime() -start);
if(waited.compareTo(patience) > 0
&& t.isAlive()) {
msg("Tired of waiting!");
t.interrupt();
t.join();
```

```
}
```

```
}
msg("Finally!");
```

```
}
```

- `}`

23

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 24 -->
# 05 Synchronization

24

<!-- page 25 -->
0 5 · S Y N C H R O N I Z A T I O N

#### A race condition

- Two threads deposit 50 into an account with balance 0

- Each deposit is three steps: read , add , write

- The interleaving 1, 4, 2, 5, 3, 6 gives a final balance of 50 instead of 100 – one deposit is lost

- The result depends on the timing: a race condition

```
thread 1 / thread 2
```

```
voiddeposit(intamount) {
```

```
intx = account.getBalance();   // 1   4
x += amount;                    // 2   5
account.setBalance(x);          // 3   6
```

- `}`

###### `a bad interleaving`

- `1 T1 reads  0`

- `4 T2 reads  0`

- `2 T1 x = 50`

- `5 T2 x = 50`

- `3 T1 writes 50`

- `6 T2 writes 50` _`// 50, not 100!`_

25

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 26 -->
0 5 · S Y N C H R O N I Z A T I O N

#### Seeing the race

```
Counter.java
```

```
three runs (possible output)
```

```
publicclassCounter {
privateintcount = 0;
publicvoidincrement() { count++; }
publicintget() { returncount; }
```

```
publicstaticvoidmain(String[] args)
throwsInterruptedException {
Counter c = newCounter();
Runnable task = () -> {
```

```
$ java Counter
137465
```

```
$ java Counter
118902
```

```
$ java Counter
200000
```

```
for(inti = 0; i < 100_000; i++) c.increment();
};
```

```
Thread t1 = newThread(task), t2 = newThread(task);
t1.start(); t2.start();
t1.join();  t2.join();
System.out.println(c.get());
}
```

```
}
```

`count++` is a read-modify-write: increments are lost whenever two threads read the same old value. The fix: make ! `increment` synchronized .

26

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 27 -->
0 5 · S Y N C H R O N I Z A T I O N

#### synchronized methods and blocks

- Every object has an intrinsic lock (monitor lock)

- A `synchronized` method locks `this` ; a `synchronized` block locks the given object

###### `synchronized method`

```
publicclassCounter {
privateintcount = 0;
```

```
publicsynchronizedvoidincrement() {
count++;
}
```

- A thread must own the lock to enter; other threads that need the same lock wait (state `BLOCKED` )

```
}
```

```
publicsynchronizedintget() {
```

```
returncount;
```

   - `}`

- The lock is released when the thread leaves the method or block – normally or by an exception

- A `static synchronized` method locks the `Class` object, e.g. `Counter.class`

###### `synchronized block`

```
privatefinalObject lock = newObject();
```

```
publicvoidincrement() {
synchronized(lock) {     // smaller critical section
count++;
}
}
```

- Locks are reentrant : a thread that owns a lock may enter it again

27

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 28 -->
0 5 · S Y N C H R O N I Z A T I O N

#### Java's monitor model

<!-- Start of picture text -->
monitor of object e critical section: e.wait(): release lock all synchronized methods of e + all synchronized (e) { … } blocks entry set wait set threads waiting for the lock threads that called e.wait() (BLOCKED) (WAITING) at most ONE owner thread acquire lock e.notify() / notifyAll(): compete for the lock again i Any object can be the lock of a monitor. The lock is acquired on entry and  released on exit  – also when an exception is thrown. <!-- End of picture text -->

28

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 29 -->
0 5 · S Y N C H R O N I Z A T I O N

#### Visibility: the Java Memory Model

- Each core has caches; the compiler and the CPU reorder instructions

- Without synchronization, a thread may never see a value written by another thread

- The Java Memory Model defines happens-before : what one thread is guaranteed to see

   - unlocking a lock _happens-before_ every later locking of the same lock

```
a volatile flag
```

```
publicclassWorker implementsRunnable {
privatevolatilebooleanrunning = true;
publicvoidstop() { running = false; }
@Overridepublicvoidrun() {
while(running) {      // sees the change
doSomeWork();      // thanks to volatile
}
}
}
```

   - writing a `volatile` field _happens-before_ every later read of it

   - `start()` and `join()` create happens-before edges too

- `volatile` gives visibility, not atomicity:

   - `volatileCount++` is still a race

29

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 30 -->
0 5 · S Y N C H R O N I Z A T I O N

#### Thread safety: strategies

- Do not share : confine data to one thread (local variables, `ThreadLocal` )

- Do not mutate : immutable objects – records with immutable fields, `List.of(…)` – are always thread-safe

- Synchronize every access – reads _and_ writes – to shared mutable state, always with the same lock

- Delegate to thread-safe classes: atomic variables, concurrent collections (Lecture 7)

- Keep critical sections short : never sleep, do I/O or call unknown code while holding a lock

i Document which lock guards which field. A field that is written under a lock but read without it is still a data race.

30

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 31 -->
# 06

### Waiting and notification

31

<!-- page 32 -->
0 6 · W A I T I N G A N D N O T I F I C A T I O N

#### Waiting for a condition

- Mutual exclusion is not enough: sometimes a thread must wait until another thread changes the state

- `■ wait()` – releases the lock and waits in the wait set

- `notify()` – wakes up one waiting thread; `notifyAll()` – wakes up all

- All three must be called while holding the lock of the object – otherwise `IllegalMonitorStateException`

```
guarded block
```

```
synchronizedvoiddoWhenCondition()
throwsInterruptedException {
while(!condition)
wait();        // release the lock and wait
// ... act: the condition holds here
```

```
}
```

```
synchronizedvoidchangeCondition() {
// ... change the values used in the condition
notifyAll();       // let waiting threads re-check
```

```
}
```

- A woken thread must re-acquire the lock before it continues

32

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 33 -->
0 6 · W A I T I N G A N D N O T I F I C A T I O N

#### The producer–consumer problem

- A producer thread generates pairs of numbers and stores them in a shared `CubbyHole`

- A consumer thread takes each pair and prints its sum

- ■ Requirements:

   - every pair is consumed exactly once

   - the producer waits while the cubby hole is full

```
the two threads
```

```
voidproducer(CubbyHole c) {
for(inti = 0; i < 10; i++)
for(intj = 0; j < 10; j++)
c.put(i, j);
}
```

```
voidconsumer(CubbyHole c) {
for(intk = 0; k < 100; k++)
System.out.println("got "+ c.get());
}
```

- the consumer waits while it is empty

33

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 34 -->
0 6 · W A I T I N G A N D N O T I F I C A T I O N

#### First attempt: synchronized is not enough

- `synchronized` prevents the inconsistent pair: `get` can no longer see `x` of one pair and `y` of the next

- But it does not coordinate the threads:

   - consumer faster → the same pair is consumed twice

```
CubbyHole –only mutual exclusion
```

```
publicclassCubbyHole {
privateintx, y;
publicsynchronizedintget() { returnx + y; }
publicsynchronizedvoidput(inta, intb) {
x = a; y = b;
}
}
```

- producer faster → pairs are lost

###### `a possible run`

```
put: (0,4)
got: 4
got: 4// consumed twice
put: (0,5)
put: (0,6)   // (0,5) is lost
got: 6
```

34

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 35 -->
0 6 · W A I T I N G A N D N O T I F I C A T I O N

#### Second attempt: a flag with if

■ Idea: a flag `available` tells whether there is a pair

- But what should `get` do when nothing is available?

   - it must return _something_ – the code does not even compile

   - returning a dummy value is wrong

```
still wrong
```

```
publicclassCubbyHole {
```

- `private int` `x, y;`

```
privatebooleanavailable = false;
```

```
publicsynchronizedintget() {   // won't work!
if(available) {
```

- `available =` `false` `;` `return` `x + y;`

```
}
```

   - `}` `// error: missing return statement`

- The thread must wait until the state changes – `wait()` and `notifyAll()`

- `public synchronized void` `put(` `int` `a,` `int` `b) {` `if` `(!available) {`

```
available = true;
x = a; y = b;
```

   - `}` `// and if available is true?`

- `}`

```
}
```

35

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 36 -->
0 6 · W A I T I N G A N D N O T I F I C A T I O N

#### The correct CubbyHole

- Wait in a while loop, never in an `if` :

   - another thread may have changed the state again before the woken thread gets the lock

   - _spurious wakeups_ : `wait` may return without any `notify`

- `notifyAll()` – with producers and consumers waiting on the same lock, `notify()` could wake the wrong kind of thread

- In Lecture 7: the same with `BlockingQueue` – in two lines

```
CubbyHole.java
```

```
publicclassCubbyHole {
privateintx, y;
privatebooleanavailable = false;   // the condition
publicsynchronizedintget() throwsInterruptedException {
while(!available)
wait();
available = false;
notifyAll();          // wake up the producer(s)
returnx + y;
}
publicsynchronizedvoidput(inta, intb)
throwsInterruptedException {
while(available)
wait();
x = a; y = b;
available = true;
notifyAll();          // wake up the consumer(s)
}
}
```

36

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 37 -->
# 07

### Liveness and other issues

37

<!-- page 38 -->
0 7 · L I V E N E S S A N D O T H E R I S S U E S

#### Deadlock

- Two threads each hold one lock and wait forever for the lock held by the other

- Classic cause: locks acquired in different orders

```
deadlock
```

```
voidtransfer(Account from, Account to, intsum) {
synchronized(from) {
synchronized(to) {
from.withdraw(sum);
to.deposit(sum);
```

```
}
```

- Prevention: always acquire locks in a fixed global order (e.g. by account id)

- Diagnosis: `jstack <pid>` or the thread dump of an IDE reports _Found one Javalevel deadlock_

```
}
```

- `}`

- _`// thread 1: transfer(a, b, 10)  holds a, waits for b`_

- _`// thread 2: transfer(b, a, 20)  holds b, waits for a`_

###### `fixed lock order`

```
Account first  = from.id() < to.id() ? from : to;
Account second = from.id() < to.id() ? to : from;
synchronized(first) {
synchronized(second) { ... }
```

```
}
```

38

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 39 -->
0 7 · L I V E N E S S A N D O T H E R I S S U E S

#### Other liveness problems

```
starve
```

##### Starvation

A thread never gets the CPU or the lock, because other threads always get it first – e.g. greedy threads holding a lock for a long time.

```
livelock
```

##### Livelock

Threads are not blocked, but keep reacting to each other and make no progress – like two people stepping aside in a corridor, again and again.

```
contention
```

##### Too much locking

Correct but slow: threads wait in line for one big lock. Keep critical sections short; use finer-grained locks or lock-free classes.

39

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 40 -->
0 7 · L I V E N E S S A N D O T H E R I S S U E S

#### Daemon threads and ThreadLocal

- A daemon thread serves other threads (e.g. a background cache cleaner)

   - the JVM exits when only daemon threads are left – they are stopped abruptly

   - `setDaemon(true)` before `start()` ; a thread inherits the status of its creator

- `ThreadLocal<T>` – a variable with a separate value per thread : no sharing, no locking

```
daemon, ThreadLocal
```

```
Thread cleaner = newThread(cache::evictOldEntries);
cleaner.setDaemon(true);
cleaner.start();
```

```
// SimpleDateFormat is NOT thread-safe:
```

```
// one instance per thread
privatestaticfinalThreadLocal<SimpleDateFormat> FMT =
ThreadLocal.withInitial(
```

```
() -> newSimpleDateFormat("dd.MM.yyyy"));
```

```
String today = FMT.get().format(newDate());
```

- remove the value when it is no longer needed, especially in thread pools

- for virtual threads, prefer _scoped values_ (Lecture 7)

40

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 41 -->
0 7 · L I V E N E S S A N D O T H E R I S S U E S

#### Summary

- A thread is a sequential flow of control; threads of a process share memory

- Define the work as a `Runnable` (a lambda) and call `start()` – never `run()`

- Threads go through `NEW` , `RUNNABLE` , `BLOCKED` , `WAITING` , `TIMED_WAITING` , `TERMINATED` ; `join()` waits for the end

- Stop threads cooperatively with `interrupt()` ; never swallow `InterruptedException`

- Shared mutable state needs `synchronized` (atomicity + visibility); `volatile` gives only visibility

- Wait for conditions with `wait()` in a `while` loop and `notifyAll()` ; avoid deadlock with a fixed lock order

41

Advanced Programming Methods  ·  Lecture 6 – Concurrency (1): Threads and Synchronization

<!-- page 42 -->
## Questions?

Next: Lecture 7 – java.util.concurrent and virtual threads
