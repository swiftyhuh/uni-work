<!-- page 1 -->
# Mathematical Logic – Proofs by Resolution (recap)

𝑃→𝑄≡¬𝑃∨𝑄 ¬(𝑃→𝑄) ≡𝑃∧¬𝑄

- 𝑃∧𝑄→𝑅 processed as a whole - or process separately P, Q and ¬𝑅

- why?

The method:

   - negate the statement (why?)

- (1) - convert to prenex form

      - move quantifiers as prefix

   - convert to skolem form

      - remove quatifiers and replace with functions

   - convert to clausal form = conj NF = (… ∨… ) ∧(… ∨… ) …

- (2) - unifications and substitutions

- (3) - resolve by (predicates) resolution

- (4) - resolution for propositions (explanation) - examples

- (5) - ex 37, example of predicates resolution

   - Prolog computation - example, the English succession - Prolog execution of above

fact 𝐵. {𝐵} definite clause 𝐵←𝐴1, … , 𝐴𝑛. {¬𝐴1, … , ¬𝐴𝑛, 𝐵} goal ←𝐴1, … , 𝐴𝑛. {¬𝐴1, … , ¬𝐴𝑛}
