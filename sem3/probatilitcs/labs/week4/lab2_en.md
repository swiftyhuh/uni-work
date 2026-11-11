<!-- page 1 -->
# Laboratorul 2

1. Two players choose two distinct sums that can be obtained by rolling three dice, then simulate rolling three dice 100000 times in Python. The winning player is the one whose sum appears more often. What distinct sums should the two players choose in order to maximize their chances of winning?

[ ]: from itertools import product from random import randint from matplotlib.pyplot import plot, grid, xticks, yticks, title, show help('itertools.product') help('random.randint')

Geometric probability in 2D

Let _M ⊂ D ⊂_ R2 be sets with nite area. A point _X_ is chosen uniformly at random from _D_ (the sample space is _D_ ). The probability that " _X_ belongs to _M_ " is dened by _P_ ( _X ∈ M_ ) :=area<u>(</u>_M_<u>)</u> area ( _D_ )_._

<!-- Start of picture text -->
D X M <!-- End of picture text -->

2. a) Generate _N ∈{_ 500 _,_ 1000 _,_ 2000 _}_ uniformly random points in a square. Display the relative frequency of the points that:

i) lie inside the circle tangent to the sides of the square.

ii) are closer to the center of the square than to the vertices of the square.

iii) are closer to the center of the square than to the bottom side of the square.

iv) form, together with the vertices of the square, two acute triangles and two obtuse triangles.

b) Plot the square and the points for each case.

c) Compare the obtained relative frequencies with the corresponding geometric probabilities.

- [ ]: from matplotlib.pyplot import axis, plot, show from random import random from math import dist help('random.random') help('math.dist')

- [ ]: axis('square') axis((0, 1, 0, 1)) F=[random(),random()] plot(F[0],F[1],'ro') show()
