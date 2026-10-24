# Clean code notes — BMW TechWorks guest lecture (19.10.2026)

Source: `Code_Quality_AI_Era_2026_BMW_final_presentation.pdf` (124 pages, speaker: Harold-Nimród Földvári).
Slides are marked confidential. Keep this file and the slides out of public repos.
Page numbers refer to the PDF.

## The big idea
- Time spent: 75% understanding code, 20% modifying, 5% writing (p12). Write for the reader.
- Clean code = can be read and enhanced by someone other than the author (p5).
- Without care, quality drops as features grow. Refactor continuously (p75-76).
- AI era: writing is cheap, understanding and owning is not. "Never commit code you cannot explain." (p15-21, 77, 121)

## What matters (p30)
Clarity (clear at first read), brevity (no unneeded code), simplicity (simplest thing that works), humanity (write for people, not the compiler).

## Names (p36)
- A name says what something is and why it exists: `elapsedTimeInDays`, not `d`.
- Avoid `data`, `result`, `tmp`, `flag`, `handler2`. Use the domain's words (p22, 73).

## Comments (p34-35)
1. Explain WHY, never WHAT.
2. Don't comment out code. Version control keeps it.
3. Comment strange or unnatural code.
4. No redundant or mandated comments (e.g. on getters/setters). No banner comments.

## Functions and nesting (p50-55)
- Avoid arrow code (deep nesting).
- Use guard clauses, return as soon as possible, turn negative checks into positive ones, extract blocks into small functions.
- Example: `getPayAmount()` as `if (isDead) return ...; if (isSeparated) return ...; ... return normalPayAmount();` (p55).
- No `goto` (p56). Lines should stay short (column 80, p32).

## Principles (p48-71)
- **Reduce code (p49):** don't write what isn't needed; never assume; don't rewrite what exists.
- **DRY (p57-58):** one authoritative place for each piece of knowledge.
- **YAGNI (p70):** implement when needed, not when foreseen.
- **KISS (p68):** simple beats complicated.
- **SRP (p62):** a class has one reason to change.
- **Command-query separation (p63):** a method either changes state (command) or returns data (query), not both. No printing inside a query.
- **Encapsulate what changes (p59):** `private` by default, open access step by step (private → protected → public, only if really needed).
- **Program to an interface (p61):** declare variables, parameters and returns with the interface type (`List<String> x = new ArrayList<>()`).
- **Dependency injection / inversion (p65-66):** a class receives its dependencies, it doesn't create them. Depend on abstractions.
- **Open-closed (p60):** open for extension, closed for modification.
- **Delegation (p69):** let the object do the job (`customer.equals(other)`).
- **Law of Demeter (p71):** only call methods on: the object itself, its arguments, objects created in the method, its own attributes.

## Fail fast and exceptions (p67, 96, 106-120)
- Fail fast: crash early with a clear message instead of continuing with bad state.
- Never swallow an exception (`catch (...) { }` or `return null` in catch).
- Catch specific exceptions, not `Exception`/`Throwable`. Declare specific `throws`.
- Catch only what you can handle. Throw early, catch late.
- When wrapping, pass the cause: `new MyException("msg", e)`.
- Log OR throw, never both. One log message per exception.
- No exceptions for flow control. Never throw from `finally`.
- Cleanup: try-with-resources for `AutoCloseable` (p116).

## Null, strings, immutability (p83-105)
- Compare strings with `equals`, never `==` (p93). Call it on the known literal: `"Finished".equalsIgnoreCase(status)` (p99).
- `String.valueOf(x)` instead of `x.toString()` when x may be null.
- Don't create objects with incomplete data; return sensible defaults, not null. Consider `Optional` for "maybe absent" (prefer `map`/`orElse`/`orElseThrow`, p105).
- Immutable classes: `final` fields, `final` class, no leaking during construction (p84). Records (Java 16+) for data carriers (p88).
- `StringBuilder` over `StringBuffer` and repeated `+` in loops (p92-94).

## Refactoring (p38-46)
- Change structure without changing behavior (Fowler, Beck).
- Why: you can't write perfect code in one go; design evolves; hard-to-understand code is worse than lost code.
- How: small steps, tests green after each, only when it pays off, continuously, ideally in pairs.
- Tests are essential for refactoring (p46).

## Review checklist from the exercise (p72-73)
Meaningless names, boolean flag (SRP), arrow code, duplicated branches (DRY), magic numbers (`3` → named constant), swallowed exception, printing inside a query (CQS), untyped `List<Object>`, comment that says nothing. Fixed version used a named constant, a stream, and two separately named methods instead of a flag.

## Working with AI (p21-22)
- Before: give context, small steps, tests first.
- While: read every line, ask why, check every API/package exists.
- After: linters and CI, small PRs reviewed by a human.
- Tests define "correct": generated tests that mirror the code prove nothing.

---

## How this applies to `work/assignment1` (my review, not from the slides)
Already good: interface-typed repository in `Controller` (p61), DI through the constructor (p65), `private final` fields (p59, 84), `equals`-style comparisons (p93), fail-fast exceptions with messages (p67), single place for the "is red" rule (DRY, p58).

To improve, in priority order:
1. Delete the commented-out code block in `Controller.java` (p35 rule 2).
2. `View.main`: `var repo = new ArrayRepository(10)` → declare as `Repository` (p61).
3. Magic values: `"red"` and the menu numbers 0-4 → named constants (p73).
4. `View.readVehicle()` returns `null` for "back" (p97-105 advise against returning null for "no result").
5. `View.run()` catches `RuntimeException`, which is broad (p108). Fine for a menu loop, but be able to defend it.
6. `ArrayRepository` messages still say "parking lot" (names in the domain's language, but this class is generic).
7. Menu text and the "Invalid ..." messages are inconsistent.

Keep it simple: these are habits, not extra layers (YAGNI/KISS, p68-70).
