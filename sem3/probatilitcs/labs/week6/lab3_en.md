<!-- page 1 -->
# Lab 3

1. i) Explain which probability is estimated by the call prob_cond(5000) below.

[ ]: from random import sample

def prob_cond(nr_sim): countA, countB = 0, 0 for _ in range(nr_sim): drawn_balls = sample(['red','blue','green'],counts=[5,3,2],k=3) if 'red' in drawn_balls: countA+=1 if len(set(drawn_balls))==1: countB+=1 return countB/countA prob_cond(5000)

ii) Calculate the theoretical value of the probability estimated by simulations. You may use:

[ ]: from math import comb

2. Simulate rolling a die 500 times. Display the histogram of the relative frequencies of the obtained numbers and the bars corresponding to the theoretical probabilities, by replacing the question marks in the following code:

[ ]: from random import randrange from matplotlib.pyplot import bar, hist, grid, show, legend

data = [randrange(?,?) for _ in range(?)] bin_edges = [k+0.5 for k in range(?)] hist(?, ?, density = True, rwidth = 0.9, color = 'green', edgecolor = 'black', alpha = 0.5, label = 'relative frequencies') distribution = dict([(?,?) for i in range(1,7)]) bar(?, ?, width = 0.85, color = 'red', edgecolor = 'black', alpha = 0.6, label = 'probabilities') legend(loc = 'lower left') grid() show()

3. An urn contains 6 balls inscribed with the digit 1 and 4 balls inscribed with the digit 0. 5 balls are drawn at random with replacement from the urn. Let _X_ be the random variable that gives the sum of the numbers on the drawn balls.

a) Generate a list of 1000 values of _X_ .

b) Display the histogram of the relative frequencies and the bars corresponding to the theoretical values.

c) Estimate the probability _P_ (1 _< X ≤_ 4) and display its theoretical value.

<!-- page 2 -->
Use the methods rvs, pmf, cdf of the object binom:

- [ ]: from scipy.stats import binom help('scipy.stats.binom')

   4. a) Implement in Python the following Monte Carlo algorithm:

Input: A vector _v_ with 100 elements.

1. Choose a number _k_ at random from the set _{_ 1 _,_ 2 _, . . . ,_ 100 _}_ .

2. Choose _k_ elements of _v_ at random, without replacement, to form a sublist _w_ of _v_ .

Output: the maximum of _w_ .

b) Estimate the probability that the output of the algorithm is 100 for v=[1,2,...,100].

c) Find the probability that the output of the algorithm is 100 for v=[1,2,...,100].
