<!-- page 1 -->
# Lab 1

1. a) For the lab, working with Jupyter notebooks (JupyterLab) is recommended. You have several options, choose the one that suits you best:

- Google Colab (online, no installation required): https://colab.research.google.

- com/

- Visual Studio Code (Jupyter extension): https://code.visualstudio.com/docs/

- datascience/jupyter-notebooks

- PyCharm (Jupyter notebook support): https://www.jetbrains.com/help/pycharm/

- jupyter-notebook-support.html

- JupyterLab (local installation): https://jupyterlab.readthedocs.io/en/stable/

- getting_started/installation.html

The recommendation above is not mandatory. You can use any Python programming environment that suits you.

b) To (re)familiarize yourself with Python, you can consult:

- https://docs.python.org/3/tutorial/introduction.html

- https://docs.python.org/3/tutorial/controlflow.html

For the following problems, we will refer to the following documentation: https://docs.python.org/3/library/random.html https://docs.python.org/3/library/math.html https://docs.python.org/3/library/itertools.html

2. For this problem, we will use the following functions:

[ ]: from random import sample from math import factorial from itertools import permutations help('random.sample') help('math.factorial') help('itertools.permutations')

   - a) Display a list with all the permutations of the word randomise.

   - b) Display the total number of permutations of the word randomise.

   - c) Display a random permutation of the word randomise.

   3. Write functions that solve the previous problem for arrangements and combinations, using:

- [ ]: from random import sample from math import perm, comb from itertools import permutations, combinations

<!-- page 2 -->
||Example calls:|
|---|---|
|[1]|: get_arrangements('word',2)|
|[1]|: [('w', 'o'),|
||('w', 'r'), ('w', 'd'), ('o', 'w'),|
||('o', 'r'),|
||('o', 'd'),|
||('r', 'w'), ('r', 'o'),|
||('r', 'd'),|
||('d', 'w'),|
||('d', 'o'), ('d', 'r')]|
|[2]|: get_arrangements('word',2,total_number=True)|
|[2]|: 12|
|[3]|: get_arrangements('word',2,at_random=True)|
|[3]|: ['r', 'o']|
|[4]|: get_combinations('word',2)|
|[4]|: [('w', 'o'), ('w', 'r'), ('w', 'd'), ('o', 'r'), ('o', 'd'), ('r', 'd')]|
|[5]|: get_combinations('word',2,total_number=True)|
|[5]|: 6|
|[6]|: get_combinations('word',2,at_random=True)|
|[6]|: ['o', 'd']|
||4. An ice cream shop has 7 avors: Banana,Chocolate,Kiwi,Mango,Pistachio,Raspberry, Vanilla. Generate all the possible ways in which a customer can order a cone with 3 scoops. A avor may be used for several scoops and the order of the scoops on the cone is irrelevant. You can use|
|[ ]|: from itertools import combinations_with_replacement|
||Examples: CCP, KPR.|
||How many congurations are possible?|
