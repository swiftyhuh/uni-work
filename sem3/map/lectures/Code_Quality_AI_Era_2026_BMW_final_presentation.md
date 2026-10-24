<!-- page 1 -->
Beyond working code: the art of clean code

Code quality in the age of AI

19/10/2026

BMW TechWorks Romania  ·  Invited talk

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 2 -->
#### Harold-Nimród Földvári

Invited speaker from industry

TODAY'S QUESTION

Now

Before

<!-- Start of picture text -->
PhD <!-- End of picture text -->

Tech Lead – generative & agentic AI applications

BMW TechWorks (since 2024)

Full-stack developer, automotive & manufacturing projects

msg systems (2017 – 2024)

Serverless workflows

Babeș-Bolyai University, Cluj-Napoca

If AI can write the code for us, why should we still care how good the code is?

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 3 -->
Agenda

01

###### Code quality

What it is and why it matters

02

Code quality in the era of AI

What changed when AI started writing code

03

Programming principles

The habits that keep code clean

04

Java best practices

Reference material to read at home

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 4 -->
###### Recommended reading

###### Clean Code

_A Handbook of Agile Software Craftsmanship_

About the code itself: names, functions, comments, error handling

###### The Clean Coder

_A Code of Conduct for Professional Programmers_

About the professional behind the code: saying no, estimating, testing, discipline

Robert C. Martin – “Uncle Bob”

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 5 -->
Clean code

“Clean code can be read, and enhanced by a developer other than its original author.” Dave Thomas, quoted in Clean Code

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 6 -->
19.10.2026 | FG-9-X bmwtechworks.ro

<!-- page 7 -->
19.10.2026 | FG-9-X bmwtechworks.ro

<!-- page 8 -->
19.10.2026 | FG-9-X bmwtechworks.ro

<!-- page 9 -->
19.10.2026 | FG-9-X bmwtechworks.ro

<!-- page 10 -->
PART 01

The importance of code quality

1  ·  Code quality

2  ·  Code quality in the era of AI 3  ·  Programming principles

4  ·  Java best practices

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 11 -->
###### Why is it so important?

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 12 -->
<!-- Start of picture text -->
Why is it so important? <!-- End of picture text -->

<!-- Start of picture text -->
understanding code 75% modifying code 20% writing new code 5% <!-- End of picture text -->

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 13 -->
###### Why is it so important? - Maintenance is hard

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 14 -->
PART 02

Code quality in the era of AI

1  ·  Code quality

- 2  ·  Code quality in the era of 3  ·  Programming principles

- AI

4  ·  Java best practices

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 15 -->
###### Code got cheap to write

~80%

of developers use AI tools in their daily workflow _Stack Overflow Developer Survey 2025_

~75% of new code at Google is AIgenerated – up from ~25% in 2024 _Sundar Pichai, April 2026_

“Vibe coding” Collins Word of the Year 2025: building software by prompting, without reading the code _Collins Dictionary, Nov 2025_

Writing code is no longer the bottleneck. Understanding, reviewing and owning it is.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 16 -->
###### The bottleneck has moved

Generate seconds

Understand & review minutes – hours

###### Maintain

years

An assistant or agent writes 200 lines while you get a coffee

Someone has to read, question and verify every line

Fix, extend, debug at 3 AM – usually not by the original author

Remember the pie chart: ~75% of coding time goes into understanding existing code, only ~5% into writing new code.

AI made the 5% faster – and multiplied the amount of code everyone has to read.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 17 -->
###### What the data says (2024 – 2026)

## 1.7×

more issues per pull request in AI-coauthored PRs; readability issues more than 3× higher _CodeRabbit, Dec 2025 – 470 open-source PRs_

8×

more duplicated code blocks in 2024; moved (refactored) code down ~40% _GitClear, 2025 – 211 million changed lines_

45%

of AI-generated code samples contained an OWASP Top-10 flaw (Java: over 70%) _Veracode GenAI Code Security Report, 2025 – 100+ LLMs_

24%

of issues introduced by AI commits are still in the code today – 41% of the security issues

_Liu et al., 2026 – 304,362 AI commits, 6,275 repos_

_Exact numbers depend on tool, model and study design – the direction is consistent across studies._

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 18 -->
###### AI is an amplifier

“AI’s primary role in software development is that of an amplifier.”

~90%

of tech professionals use AI at work _DORA 2025_

_DORA – State of AI-assisted Software Development 2025 (~5,000 respondents)_

Good engineering practices + AI → faster and better.

Weak practices + AI → more code, more bugs, faster.

_DORA 2025: throughput goes up with AI adoption – but so does delivery instability._

29%

66%

of developers trust the accuracy of AI output (down from 40%) _Stack Overflow 2025_

spend more time fixing AI code that is “almost right, but not quite” _Stack Overflow 2025_

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 19 -->
###### New risks that come with AI-generated code

###### Hallucinated APIs & packages

1 ~20% of suggested packages did not exist (2024 study); attackers register them – “slopsquatting”

###### Over-engineering

3 Extra layers, options and “future-proof” abstractions nobody asked for – YAGNI

###### Tests that prove nothing

5 Generated tests that mirror the implementation – green, but they never fail

###### Copy-paste instead of reuse

- 2 New code is generated next to the helper that already exists – DRY breaks quietly

- Swallowed exceptions

- 4 Broad exception handling is the most frequent smell in AI commits (Liu et al. 2026)

- Comprehension debt

- 6 Code that works, but nobody on the team really understands

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 20 -->
###### Why clean code matters even more with AI

###### Your codebase is the prompt

Assistants copy the patterns they see. Messy code in → messy code out. Clean, consistent code gets you better suggestions.

Names are context

Good names, small functions and clear modules tell humans and models what the code is for.

Tests are the guardrails

Agents iterate until the tests pass – so your tests define what “correct” means.

You own every line

“The AI wrote it” is not an answer in a code review, an incident or an exam.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 21 -->
Working with AI assistants – the professional way

###### Before

- Give context: conventions, architecture, examples (e.g. AGENTS.md, project rules)

- Split the task into small steps

- Write – or at least describe – the tests first

###### While

- Read every line: if you cannot explain it, do not commit it

- Ask “why?” and ask for alternatives

- Check that every API and package really exists

After

- Linters, formatters, static analysis and security scans in CI

- Small pull requests, reviewed by a human

- Use AI to refactor and explain too – with tests green

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 22 -->
Classic principles – AI edition

|Principle|Typical AI failure|What you do|
|---|---|---|
|DRY|Generates a new helper next to the existing one|Search first; tell the AI what to reuse|
|KISS / YAGNI|Adds layers, flags and “future-proof” options|Delete what is not needed today|
|SRP|200-line functions that do everything|Ask for – or extract – small units|
|Fail-fast|`catch (Exception e) { }`and silent defaults|Specific exceptions, errors surface early|
|Clear names|`data`,`result`,`tmp`,`handler2`|Rename to the language of the domain|
|Refactoring|Rewrites everything instead of small steps|Small steps, tests green after each one|

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 23 -->
PART 01

# What can we do for code quality?

1  ·  Code quality

2  ·  Code quality in the era of AI 3  ·  Programming principles

4  ·  Java best practices

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 24 -->
###### PART 01

# Code reviews

1  ·  Code quality

2  ·  Code quality in the era of AI

3  ·  Programming principles

4  ·  Java best practices

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 25 -->
###### Code review

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 26 -->
###### Code review

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 27 -->
###### Good code / Bad code

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 28 -->
###### Code review

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 29 -->
Message

“Style matters and there’s beauty in simplicity.”

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 30 -->
###### What should matter

Clarity

The reader understands it at first read

Brevity

No unnecessary code

###### Simplicity

The simplest solution that works

Humanity Write for humans, not for the compiler

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 31 -->
###### Simplicity and clarity

###### Before

###### After

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 32 -->
###### Humanity – Indentation

<!-- Start of picture text -->
Column 80 <!-- End of picture text -->

How many programmers lay out their code

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 33 -->
###### Humanity – Indentation

How people read

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 34 -->
###### Avoid unnecessary comments

```
//=======================================
//  THIS BUTTON GETS INFORMATION FROM A TEXT BOX
//=======================================
privatevoidbtnStrings_Click(object sender, EventArgs e)
{
string firstName;
string messageText;
messageText = "Your name is: ";
//=======================================
//  GET THE TEXT FROM THE TEXT BOX
//=======================================
firstName = textBox1.Text;
//MessageBox.Show(messageText + firstName);
}
```

Good code is its own best documentation!

Banner comments repeat what the code says; commentedout code is dead weight.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 35 -->
###### How to comment

Never explain what code does – Explain why you did it this 1 way

- 2 Don’t comment out code – we have version controlling

- Comment strange or unnatural code – even if it is not your

- 3 code

No redundant and mandated comments – Example: don’t 4 comment getters and setters

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 36 -->
###### Variable names

75% of time is reading – names are the cheapest documentation.

A name should say what something is and why it exists:

`elapsedTimeInDays` not `d`

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 37 -->
###### PART 01

# Refactoring

1  ·  Code quality

2  ·  Code quality in the era of AI

3  ·  Programming principles

4  ·  Java best practices

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 38 -->
###### Refactoring

Re•fac•to•ring  (noun) “a disciplined technique for restructuring an existing body of code, altering its internal structure without changing its external behavior.”

– refactoring.com

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 39 -->
###### Refactoring

Re•fac•to•ring  (noun) “a disciplined technique for restructuring an existing body of code, altering its internal structure without changing its external behavior.”

– refactoring.com

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 40 -->
###### Refactoring

Re•fac•to•ring  (noun) “a disciplined technique for restructuring an existing body of code, altering its internal structure without changing its external behavior .”

– refactoring.com

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 41 -->
###### Refactoring – two definitions and a habit

Martin Fowler

“A change made to the internal structure of software to make it easier to understand and cheaper to modify without changing its observable behavior”

Kent Beck

“A change to the system that leaves its behavior unchanged , but enhances some nonfunctional quality – simplicity, flexibility, understandability, performance”

“I am not a great programmer, I am just a good programmer with great habits.” Kent Beck

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 42 -->
Why to refactor?

1 You can’t write perfect code in one sitting

2 Design, rather than happening right just once, evolves continuously

<!-- Start of picture text -->
3 <!-- End of picture text -->

Code that’s hard to understand is worse than code that’s lost

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 43 -->
Why to refactor?

To make the code easier to understand

To make it easier to maintain

<!-- Start of picture text -->
To make change affordable <!-- End of picture text -->

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 44 -->
###### When to refactor?

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 45 -->
###### How to refactor? – Evolve It and Strike a Balance

Just because you think it needs to change, it does not make 1 it so

2 Consider cost and impact of change

- Make the job smaller! And like testing it’s best done

- 3 continuously !

4 Don’t soldier alone – Pair programming

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 46 -->
###### How to refactor? – Testing is essential

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 47 -->
PART 03

Programming principles Clear code is better than clever code

1  ·  Code quality

2  ·  Code quality in the era of AI

3  ·  Programming principles

4  ·  Java best practices

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 48 -->
###### Programming principles

- 1 Reduce Code

- Open Closed Design

- 5 Principle

- Dependency Injection

- 9 or Inversion principle

You aren’t going to 13 need it

- 2 Abstraction

- Command–query

- 6 separation

10 Fail-fast

_Main focus today_

- Don’t repeat yourself

- 3 (DRY)

- Single Responsibility

- 7 Principle

11 KISS principle

- Encapsulate What

- 4 Changes

- Programming for

- 8 Interface not implementation

- 12 Delegation principle

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 49 -->
###### Reduce code

##### Don’t write code that’s not 01 needed

Don’t write anything that is 03 not needed

Never assume 02

- Don’t re-write something

- 04 you already have

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 50 -->
Reduce code – Nested Conditions / Arrow code

<!-- Start of picture text -->
if if if if //do something... endif endif endif endif <!-- End of picture text -->

<!-- Start of picture text -->
Deep nesting creates an arrow shape. Hard to read, hard to test. <!-- End of picture text -->

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 51 -->
###### Reduce code – Nested Conditions / Arrow code

###### Version 1

```
ifthing.it_happened_this_way()
ifvalidation.pending_check()
make_response(encoding, message)
return
```

```
ifnot thing.it_happened_this_way()
ifvalidation.pending_check()
log_message(message)
redirect_to(target)
return
```

###### Version 2

```
ifthing.it_happened_this_way()
ifvalidation.pending_check()
make_response(encoding, message)
return
```

```
else
```

```
ifvalidation.pending_check()
log_message(message)
redirect_to(target)
return
```

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 52 -->
###### Reduce code – Nested Conditions / Arrow code

###### Combine the conditions with &&

```
ifthing.it_happened_this_way() && validation.pending_check()
make_response(encoding, message)
return
ifnot thing.it_happened_this_way() && validation.pending_check()
log_message(message)
redirect_to(target)
return
```

###### … or move the common check outside

```
ifvalidation.pending_check()
ifthing.it_happened_this_way()
make_response(encoding, message)
return
ifnot thing.it_happened_this_way()
log_message(message)
redirect_to(target)
return
```

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 53 -->
Reduce code – Nested Conditions / Arrow code

```
ifvalidation.pending_check()
ifthing.it_happened_this_way()
make_response(encoding, message)
else
log_message(message)
redirect_to(target)
return
```

Same behaviour, half the code.

One outer check, a simple if/else, one return.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 54 -->
Reduce code – Nested Conditions / Arrow code

Replace conditions with guard 1 clauses

Convert negative checks into 3 positive checks

Decompose conditional blocks into 2 separate functions

- Always opportunistically return as

- 4 soon as possible from the function

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 55 -->
Reduce code – Nested Conditions / Arrow code

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 56 -->
Reduce code – Don’t use #goto

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 57 -->
Abstraction

###### Each significant piece of functionality in a program should be implemented in just one place in the source code.

Where similar functions are carried out by distinct pieces of code, it is generally beneficial to combine them into one by abstracting out the varying parts.

- _Benjamin C. Pierce, Types and Programming Languages (2002)_

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 58 -->
Don’t repeat yourself (DRY)

“Every piece of knowledge must have a single, unambiguous, authoritative representation within a system.”

In software engineering, don’t repeat yourself (DRY) is a principle of software development, aimed at reducing repetition of information of all kinds, especially useful in multi-tier architectures.

The principle has been formulated by Andy Hunt and Dave Thomas in their book The Pragmatic Programmer.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 59 -->
###### Encapsulate What Changes

Only one thing is constant in software field and that is “Change”, so encapsulate the code you expect or suspect to be changed in future.

Benefit of this OOPS Design principle is that it’s easy to test and maintain proper encapsulated code.

If you are coding in Java then follow principle of making variable and methods private by default and increasing access step by step e.g. from private to protected and not public.

Open access step by step

###### `private`

```
protected
```

```
public
```

_default  →  only if really needed_

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 60 -->
###### Open Closed Design Principle

Classes, methods or functions should be Open for extension (new functionality) and Closed for modification.

##### OPEN

for extension (new functionality)

It’s a principle for object oriented design first described by Bertrand Meyer that says that “software entities (classes, modules, functions, etc.) should be open for extension, but closed for modification”.

##### CLOSED

for modification

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 61 -->
###### Programming for Interface not implementation

Always program for interface and not for implementation – this will lead to flexible code which can work with any new implementation of interface.

So use interface type on variables, return types of method or argument type of methods in Java. This has been advised by many Java programmers including in Effective Java and Head First Design Patterns.

```
List<String> names = newArrayList<>();          // interface type: any implementation can be
plugged in
```

```
ArrayList<String> names = newArrayList<>();    // tied to one implementation
```

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 62 -->
Single Responsibility Principle (SRP)

###### A class should have only one reason to change.

Single Responsibility Principle is another SOLID design principle, and represents “S” in the SOLID acronym. As per SRP, there should not be more than one reason for a class to change, or a class should always handle single functionality.

If you put more than one functionality in one class in Java it introduces coupling between the two functionalities, and even if you change one functionality there is a chance you break the coupled functionality, which requires another round of testing to avoid any surprise in the production environment.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 63 -->
Command–query separation

Every method should either be a command that performs an action, or a query that returns data to the caller, but not both.

In other words, asking a question should not change the answer. More formally, methods should return a value only if they are referentially transparent and hence possess no side effects.

_The fundamental idea is that we should divide an object’s methods into two sharply separated categories:_

###### Queries

Return a result and do not change the observable state of the system (are free of side effects).

###### Commands

Change the state of a system but do not return a value.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 64 -->
###### Command–query separation

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 65 -->
###### Dependency Injection or Inversion principle

Don’t ask for dependency – it will be provided to you by the framework.

This has been very well implemented in the Spring framework. The beauty of this design principle is that any class which is injected by a DI framework is easy to test with mock objects and easier to maintain, because object creation code is centralized in the framework and client code is not littered with it.

High-level modules should not depend on low-level modules. Both should depend on abstractions.

There are multiple ways to implement dependency injection, like using byte code instrumentation, which some AOP (Aspect Oriented Programming) frameworks like AspectJ do, or by using proxies just like in Spring. It represents “D” in SOLID.

Abstractions should not depend on details. Details should depend on abstractions.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 66 -->
###### Dependency Injection or Inversion principle

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 67 -->
###### Fail-fast

Fail-fast is a property of a system or module with respect to its response to failures. A fail-fast system is designed to immediately report at its interface any failure or condition that is likely to lead to failure. Fail-fast systems are usually designed to stop normal operation rather than attempt to continue a possibly flawed process.

A crash with a clear message today is cheaper than corrupted data discovered in three months.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 68 -->
###### KISS principle

KISS is an acronym for “Keep it simple, stupid” as a design principle noted by the U.S. Navy in 1960.

The KISS principle states that most systems work best if they are kept simple rather than made complicated; therefore simplicity should be a key goal in design and unnecessary complexity should be avoided.

The phrase has been associated with aircraft engineer Kelly Johnson (1910–1990). The term “KISS principle” was in popular use by 1970. Variations on the phrase include “keep it short and simple” and “keep it simple and straightforward”.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 69 -->
###### Delegation principle

###### Don’t do all stuff by yourself, delegate it to the respective class.

A classical example of the delegation design principle is the `equals()` and `hashCode()` methods in Java. In order to compare two objects for equality we ask the class itself to do the comparison instead of the client class doing that check.

Benefit of this design principle: no duplication of code and pretty easy to modify behavior.

```
if(customer.equals(other)) {     // the object compares itself
...
}
```

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 70 -->
You aren’t gonna need it

“You aren’t gonna need it” (acronym: YAGNI) is a principle of extreme programming (XP) that states a programmer should not add functionality until deemed necessary.

XP co-founder Ron Jeffries has written: “Always implement things when you actually need them, never when you just foresee that you need them.”

Other forms of the phrase include “You aren’t going to need it” and “You ain’t gonna need it”.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 71 -->
Law of Demeter – “Don’t talk to strangers”

A method of an object may only call methods of:

<!-- Start of picture text -->
1 The object itself <!-- End of picture text -->

<!-- Start of picture text -->
2 An argument of the method <!-- End of picture text -->

<!-- Start of picture text -->
3 Any object within the method <!-- End of picture text -->

4 Any attributes/properties of the object

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 72 -->
###### Exercise: review the AI’s code

```
// Generated by an AI assistant
publicList<Object> process(List<Object> data, booleanflag) {
List<Object> result = newArrayList<>();
try{
for(inti = 0; i < data.size(); i++) {
Object o = data.get(i);
if(o != null) {
if(flag) {
if(o.toString().length() > 3) {
result.add(o.toString().toUpperCase());
}
} else{
if(o.toString().length() > 3) {
result.add(o.toString().toLowerCase());
}
}
}
}
System.out.println(JsonUtils.toPrettyJson(result));
} catch(Exception e) {
// ignore
}
returnresult;
}
```

YOUR TASK

3 minutes, in pairs

It compiles. It probably works. Find at least 5 problems. Which principles from today does it break?

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 73 -->
###### Exercise: one possible answer

1 Meaningless names: `process` , `data` , `flag` , `o`

2 Boolean flag – one method, two jobs (SRP)

3 Arrow code: four levels of nesting

4 Duplicated branches (DRY)

5 Magic number 3

6 `catch (Exception e) {}` – swallowed (fail-fast)

7 Printing inside a query (CQS)

8 `List<Object>` : no types; `JsonUtils` – does it even exist?

9 A comment that adds nothing

```
privatestaticfinalintMIN_LENGTH = 4;
publicList<String> toDisplayNames(
List<String> names) {
returnnames.stream()
.filter(Objects::nonNull)
.filter(n -> n.length() >=
MIN_LENGTH)
.map(String::toUpperCase)
.toList();
}
// lower-case variant = a second,
// separately named method
```

_Same behaviour for the upper-case case – a fraction of the code, and every line can be explained._

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 74 -->
###### Take home message

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 75 -->
###### Take home message

_Without care, code quality goes down as the number of features goes up._

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 76 -->
###### Take home message

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 77 -->
Take-home message in the age of AI

### AI writes code. Engineers own its quality.

1

Read more than you write

2

Keep it simple, clean and tested – for humans and for machines

3

Never commit code you cannot explain

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 78 -->
###### The Programmer’s Oath

###### I promise that, to the best of my ability and judgement:

1 I will not produce harmful code.

- The code that I produce will always be my best work. I

- 2 will not knowingly allow code that is defective either in behavior or structure to accumulate.

- I will produce, with each release, a quick, sure, and

- 3 repeatable proof that every element of the code works as it should.

I will make frequent, small, releases so that I do not 4 impede the progress of others.

- I will fearlessly and relentlessly improve my creations at every opportunity. I will never degrade them.

5

- I will do all that I can to keep the productivity of myself,

- 6 and others, as high as possible. I will do nothing that decreases that productivity.

- I will continuously ensure that others can cover for me,

- 7 and that I can cover for them.

- I will produce estimates that are honest both in

- 8 magnitude and precision. I will not make promises without certainty.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 79 -->
Useful links

<!-- Start of picture text -->
www.refactoring.com <!-- End of picture text -->

www.sourcemaking.com

<!-- Start of picture text -->
www.blog.codinghorror. com <!-- End of picture text -->

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 80 -->
###### Refactoring exercise

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 81 -->
PART 04

Bonus: Java

Best practices – reference material

1  ·  Code quality

2  ·  Code quality in the era of AI

3  ·  Programming principles

4  ·  Java best practices

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 82 -->
###### PART 04

# Immutable objects

1  ·  Code quality

2  ·  Code quality in the era of AI

3  ·  Programming principles

4  ·  Java best practices

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 83 -->
Immutable Objects

“Classes should be immutable unless there’s a very good reason to make them mutable. … If a class cannot be made immutable, limit its mutability as much as possible.” Joshua Bloch, Effective Java

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 84 -->
###### Immutable Objects

Immutable classes are those classes whose objects can not be modified once created – any modification on an immutable object results in another immutable object. The best examples to understand immutable and mutable objects are `String` and `StringBuffer` .

How to implement:

1

###### 2

###### 3

###### 4

State of an immutable object can not be modified after construction – any modification should result in a new immutable object.

All fields of an immutable class should be `final` .

Object must be properly constructed, i.e. the object reference must not leak during the construction process.

The class should be `final` in order to restrict subclasses from altering the immutability of the parent class.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 85 -->
###### Benefits of Immutable Objects

###### Thread safe

- 1 Immutable objects are by default thread safe, can be shared without synchronization in concurrent environment.

###### Simpler development

- 2 Immutable object simplifies development, because it’s easier to share between multiple threads without external synchronization.

###### Reusability

###### Better performance

3 Immutable object boosts performance of Java application by reducing synchronization in code.

- You can cache immutable objects and reuse them,

- 4 much like String literals and Integers. You can use static factory methods like `valueOf()` , which can return an existing immutable object from cache, instead of creating a new one.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 86 -->
###### Disadvantages of Immutable Objects

Apart from the advantages above, immutable objects have the disadvantage of creating garbage as well.

Since an immutable object can not be reused, it is just “use and throw”. String is a prime example: it can create a lot of garbage and can potentially slow down the application due to heavy garbage collection – but that is an extreme case, and if used properly immutable objects add a lot of value.

The cost

More objects, more garbage.

With modern garbage collectors this rarely matters.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 87 -->
###### Immutable Objects in Java

`java.lang.String` already mentioned

###### Wrapper classes

`Integer` , `Byte` , `Character` , `Short` , `Boolean` , `Long` , `Double` , `Float` (all in `java.lang` )

###### `java.lang.StackTraceElement`

###### `java.io.File`

Represents an object external to the VM (a file on the local system), which may or may not exist, and has some methods modifying and querying the state of this external object. But the File object itself stays immutable. (All other classes in java.io are mutable.)

used in building exception stacktraces

###### Most enum classes

###### `java.awt.Font`

`java.math.BigInteger` and `java.math.BigDecimal`

Representing a font for drawing text on the screen (there may be some mutable subclasses, but this would certainly not be useful)

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 88 -->
###### Modern Java: records (Java 16+)

- One line declares an immutable data carrier

- Fields are `private final` ; constructor, accessors, `equals()` , `hashCode()` and `toString()` are generated

- Validate in the compact constructor – fail fast

- “Changing” a value returns a new object

- Current LTS release: Java 25 (Sept 2025)

```
publicrecordMoney(BigDecimal amount,
Currency currency) {
// compact constructor: validate
publicMoney {
Objects.requireNonNull(amount);
Objects.requireNonNull(currency);
}
publicMoney add(Money other) {
returnnewMoney(amount.add(other.amount),
currency);
}
}
```

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 89 -->
###### PART 04

# Strings

1  ·  Code quality

2  ·  Code quality in the era of AI

3  ·  Programming principles

4  ·  Java best practices

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 90 -->
Strings

###### A String can be constructed by either:

- directly assigning a string literal to a String reference – just like a primitive, or

- via the “new” operator and constructor, similar to any other classes. However, this is not commonly used and is not recommended.

###### For example,

```
String str1 = "Java is Hot";           // Implicit construction via string literal
String str2 = newString("I'm cool");  // Explicit construction via new
```

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 91 -->
###### Java Strings

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 92 -->
<!-- Start of picture text -->
Strings <!-- End of picture text -->

###### Strings are immutable (and final)

<!-- Start of picture text -->
String a = "aaaa" + "bbb";   // 2 new Strings + temp StringBuffer + result String <!-- End of picture text -->

<!-- Start of picture text -->
String a = "aaaa"; a = a.concat("bbb");     // uses a character array in background <!-- End of picture text -->

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 93 -->
Strings

###### Always use “equals” to compare two Strings

```
if(a.equals(b)) { ... }     // compares the content
if(a == b) { ... }          // compares references –may work by accident (string interning)
```

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 94 -->
###### String vs StringBuffer vs StringBuilder

###### StringBuffer

- is mutable – you can modify it without creating a new object

- All public methods are synchronized , therefore it is thread-safe but also very slow

###### StringBuilder

- is a copy of StringBuffer but without synchronization

- Use it whenever possible!

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 95 -->
###### PART 04

# Exception handling

1  ·  Code quality

2  ·  Code quality in the era of AI

3  ·  Programming principles

4  ·  Java best practices

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 96 -->
###### Exception handling – the rules

###### Always clean up after handling 1 exceptions

- Exceptions should not dictate your

- 3 flow

- Throw only relevant exceptions – wrap

- 2 them if necessary

- 4 One single log entry per exception

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 97 -->
###### How to avoid NullPointerException

Tony Hoare

“I call it my billion-dollar mistake. It was the invention of the null reference in 1965. At that time, I was designing the first comprehensive type system for references in an object oriented language (ALGOL W). My goal was to ensure that all use of references should be absolutely safe, with checking performed automatically by the compiler. But I couldn’t resist the temptation to put in a null reference, simply because it was so easy to implement. This has led to innumerable errors, vulnerabilities, and system crashes, which have probably caused a billion dollars of pain and damage in the last forty years.”

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 98 -->
###### How to avoid NullPointerException

###### Check the known value first – the simplest and most effective technique

<!-- Start of picture text -->
private boolean isFinished(String status) { if (status.equalsIgnoreCase("Finished")) { return true ; status  may be  null  → } NullPointerException return false ; } <!-- End of picture text -->

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 99 -->
###### How to avoid NullPointerException

Call `equals()` and `equalsIgnoreCase()` on the known String literal rather than on an unknown object

<!-- Start of picture text -->
private boolean isFinished(String status) { if ("Finished".equalsIgnoreCase(status)) { return true ; The literal is never  null  – no } NullPointerException return false ; } <!-- End of picture text -->

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 100 -->
###### How to avoid NullPointerException

###### Use `valueOf()` over `toString()` where both return the same result

```
BigDecimal bd = getPrice();
System.out.println(String.valueOf(bd));   // doesn't throw NPE
System.out.println(bd.toString());        // throws
NullPointerException if bd is null
```

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 101 -->
How to avoid NullPointerException

###### Using null safe methods and libraries

```
// StringUtils methods are null safe, they don't throw
NullPointerException
System.out.println(StringUtils.isEmpty(null));
System.out.println(StringUtils.isBlank(null));
System.out.println(StringUtils.isNumeric(null));
System.out.println(StringUtils.isAllUpperCase(null));
```

Output: `true true false false`

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 102 -->
###### How to avoid NullPointerException

###### Use of annotation `@NotNull` and `@Nullable`

```
String capitalize(@NonNullString in) {
```

```
returnin.toUpperCase();     // no null check required
```

```
}
```

```
voidcaller(String s) {
```

```
if(s != null)
```

```
System.out.println(capitalize(s));   // preceding null
check is required
}
```

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 103 -->
How to avoid NullPointerException

Follow the contract and define a reasonable default value – don’t allow the creation of objects with incomplete information and work with reasonable default values.

Example

An Employee cannot be created without id and name, but may have an optional phone number. If the Employee has no phone number, return a default value instead of null.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 104 -->
How to avoid NullPointerException

If you are using a database for storing your domain objects such as Customers, Orders etc., then you should define your null-ability constraints on the database itself .

```
name  VARCHAR(100)  NOT NULL
```

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 105 -->
###### How to avoid NullPointerException

###### Use Java 8 – Optional

A container object which may or may not contain a non-null value. If a value is present, `isPresent()` will return true and `get()` will return the value.

```
publicOptional<Customer> findCustomerByName(String name) {
}
```

```
Optional<Customer> optional = findCustomerByName("John Doe");
if(optional.isPresent()) {
Customer customer = optional.get();
// deal with customer
} else{
// deal with absence
}
```

Modern style: prefer `map` , `orElse` , `orElseThrow` , `ifPresent` over `isPresent()` plus `get()`

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 106 -->
###### Exception Handling Best Practices

###### Never swallow the exception in catch block

- `}` `catch` `(NoSuchMethodException e) {` `return null` `;     // the cause of the exception is lost`

- `forever }`

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 107 -->
###### Exception Handling Best Practices

###### Declare the specific checked exceptions that your method can throw

<!-- Start of picture text -->
public void foo()  throws Exception { // Incorrect way } public void foo()  throws SpecificException1, SpecificException2 { // Correct way } <!-- End of picture text -->

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 108 -->
###### Exception Handling Best Practices

###### Do not catch the `Exception` and `Throwable` class – rather catch specific sub classes

<!-- Start of picture text -->
try { someMethod(); }  catch (Exception e) {      // too broad LOGGER.error("method has failed", e); } <!-- End of picture text -->

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 109 -->
###### Exception Handling Best Practices

###### Always correctly wrap the exceptions in custom exceptions so that the stack trace is not lost

- `}` `catch` `(NoSuchMethodException e) {` `throw new` `MyServiceException("Some information: " + e.getMessage()); // Incorrect way – the stack trace is lost`

- `}`

- `}` `catch` `(NoSuchMethodException e) {` `throw new` `MyServiceException("Some information: ", e); // Correct way – the cause is passed on`

- `}`

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 110 -->
###### Exception Handling Best Practices

###### Either log the exception or throw it – but never do both

```
} catch(NoSuchMethodException e) {
LOGGER.error("Some information", e);
throwe;     // the same error will appear several
times in the logs
}
```

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 111 -->
###### Exception Handling Best Practices

###### Never throw any exception from the finally block

<!-- Start of picture text -->
try { someMethod();    // Throws exceptionOne }  finally { cleanUp(); // If finally also throws an exception, exceptionOne will be lost forever } <!-- End of picture text -->

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 112 -->
###### Exception Handling Best Practices

###### Always catch only those exceptions that you can actually handle

<!-- Start of picture text -->
}  catch (NoSuchMethodException e) { throw e;     // Avoid this as it doesn't help anything } <!-- End of picture text -->

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 113 -->
###### Exception Handling Best Practices

###### Use finally blocks instead of catch blocks if you are not going to handle the exception

<!-- Start of picture text -->
try { someMethod();    // Method 2 }  finally { cleanUp();       // do cleanup here } <!-- End of picture text -->

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 114 -->
###### Exception Handling Best Practices

##### Throw early

as soon as the problem is detected

##### Catch late

at the level that can do something meaningful

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 115 -->
Exception Handling Best Practices

Always clean up after handling the exception – if you are using resources like database connections or network connections, make sure you clean them (in the finally block)

Next: the modern way to clean up.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 116 -->
###### Modern Java: try-with-resources (Java 7+)

```
try(Connection conn = dataSource.getConnection();
PreparedStatement stmt = conn.prepareStatement(SQL)) {
stmt.setLong(1, customerId);
returnmapCustomer(stmt.executeQuery());
```

- `}   // conn and stmt are closed here - even on exception`

Works with every `AutoCloseable` : connections, 1 streams, files, locks

Resources are closed automatically, in reverse 2 order

No more cleanup code in `finally` – and nothing 3 thrown from `finally`

Exceptions from `close()` are kept as suppressed – 4 the original error is not lost

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 117 -->
Exception Handling Best Practices

Throw only relevant exceptions from a method – wrap exceptions in a custom exception if necessary

Expose exceptions that make sense at the method’s level of abstraction; wrap low-level ones.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 118 -->
Exception Handling Best Practices

Never use exceptions for flow control in your program

Exceptions are for exceptional situations, not for if/else logic – they are slow and hide intent.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 119 -->
###### Exception Handling Best Practices

###### Always include all information about an exception in a single log message

```
LOGGER.debug("Using cache sector A");
LOGGER.debug("Using retry sector B");
```

Multiple log lines get interleaved with other threads – keep it in one message.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 120 -->
###### Exception Handling Best Practices

Use template methods for repeated `try-catch` DRY applies to error handling too.

```
classDBUtil {
publicstaticvoidcloseConnection(Connection conn) {
try{
conn.close();
} catch(SQLException ex) {
thrownewRuntimeException("Cannot close connection",
ex);
}
}
}
```

```
publicvoiddataAccessCode() {
Connection conn = null;
try{
conn = getConnection();
....
} finally{
DBUtil.closeConnection(conn);
}
}
```

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 121 -->
# Thank you for your attention!

Any questions?

Never commit code you cannot explain.

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 122 -->
References

1 <u>http://www.ntu.edu.sg/home/ehchua/programming/java/J3d_String.html</u>

2 <u>http://javahungry.blogspot.com/2013/08/hashing-how-hash-map-works-in-java-or.html</u>

3 <u>http://www.javapractices.com/topic/TopicAction.do?Id=29</u>

4 <u>http://principles-wiki.net/start</u>

5 <u>http://www.oodesign.com</u>

6 <u>http://javarevisited.blogspot.ro/</u>

_Original course material: msg systems – Dr. Catalin Rusu, Adrian Schwartzkopf, Cristina Grebenisan_

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 123 -->
Sources – code quality in the era of AI (1/2)

<u>stackoverflow.blog/2025/12/29/developers-remain-willing-but-reluctant-to-use-ai-the-2025-</u> Stack Overflow Developer Survey 2025 <u>developer-survey-results-are-here</u> DORA – State of AI-assisted Software Development <u>infoq.com/news/2025/09/dora-state-of-ai-in-dev-2025</u> 2025 Google: ~75% of new code AI-generated (Apr 2026) <u>semafor.com/article/04/24/2026/google-ceo-says-75-of-companys-new-code-is-ai-generated</u> CodeRabbit – State of AI vs Human Code Generation <u>coderabbit.ai/blog/state-of-ai-vs-human-code-generation-report</u> (Dec 2025) GitClear – AI code quality research 2025 <u>devclass.com/2025/02/20/ai-is-eroding-code-quality-states-new-in-depth-report</u>

19.10.2026 | FG-9-X

bmwtechworks.ro

<!-- page 124 -->
Sources – code quality in the era of AI (2/2)

<u>veracode.com/press-release/ai-generated-code-poses-major-security-risks-in-nearly-half-of-all-</u> Veracode – GenAI Code Security Report (2025) <u>development-tasks-veracode-research-reveals</u> Liu et al. – Debt Behind the AI Boom (2026) <u>arxiv.org/abs/2603.28592</u> Spracklen et al. – package hallucinations (USENIX <u>arxiv.org/abs/2406.10279</u> Security 2025) METR – AI and experienced open-source developers <u>eweek.com/news/news-ai-tools-slow-developer-productivity-study</u> (2025) Collins Word of the Year 2025: “vibe coding” <u>ctvnews.ca/lifestyle/article/vibe-coding-named-word-of-the-year-by-collins-dictionary</u>

19.10.2026 | FG-9-X

bmwtechworks.ro
